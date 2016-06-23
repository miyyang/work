#include <stdio.h>

extern int mm_init (void);
extern void *mm_malloc (size_t size);
extern void mm_free (void *ptr);
extern void *mm_realloc(void *ptr, size_t size);


/* 
 * Students work in teams of one or two.  Teams enter their team name, 
 * personal names and login IDs in a struct of this
 * type in their bits.c file.
 */
typedef struct {
    char *teamname; /* ID1+ID2 or ID1 */
    char *name1;    /* full name of first member */
    char *id1;      /* login ID of first member */
    char *name2;    /* full name of second member (if any) */
    char *id2;      /* login ID of second member */
} team_t;

extern team_t team;


// constants

#define WSIZE 4
#define DSIZE 8
#define ALIGNMENT 8
#define BLOCK_SIZE_16B 16
#define BLOCK_SIZE_8B 8
#define BLKSIZE 24				/*Minimum block size in BST*/
#define CHUNKSIZE (1<<8)

//micros

#define MAX(x, y) ( (x)>(y)? (x): (y) )
#define MIN(x, y) ( (x)<(y)? (x): (y) )

/*Pack a size and allocated bit into a word*/
#define PACK(size, alloc) ((size)|(alloc))
				
/* rounds up to the nearest multiple of ALIGNMENT */
#define ALIGN(size) (((size) + (ALIGNMENT-1)) & ~0x7)	
//#define SIZE_T_SIZE (ALIGN(sizeof(size_t)))

/*Read and write a word at address p*/
#define GET(p) (*(unsigned int *)(p))
#define PUT(p, val) (*(unsigned int *)(p)=(val))

/*Given header pointer p,Read the size and allocated fileds from address p*/
#define SIZE(p) (GET(p) & (~0x7))
#define ALLOC(p) (GET(p) & (0x1))
#define PREVALLOC(p) (GET(p) & (0x2))
#define PREV_E_FREE(p) (GET(p) & (0x4))

/*Given block pointer bp, read the size and allocated fields from address bp*/
#define GET_SIZE(bp) ((GET(HEAD(bp)))&~0x7)
#define GET_ALLOC(bp) ((GET(HEAD(bp)))&0x1)
#define GET_PREVALLOC(bp) ((GET(HEAD(bp)))&0x2)
#define GET_PREV_E_FREE(bp) ((GET(HEAD(bp)))&0x4)

/*Given block pointer bp, operate the PREVALLOC bit and PREV_E_FREE bit */
#define SET_PREVALLOC(bp) (GET(HEAD(bp)) |= 0x2)
#define RESET_PREVALLOC(bp) (GET(HEAD(bp)) &= ~0x2)
#define SET_PREV_E_FREE(bp) (GET(HEAD(bp)) |= 0x4)
#define RESET_PREV_E_FREE(bp) (GET(HEAD(bp)) &= ~0x4)

/*Given pointer p, compute addresses of its HEAD,LEFT,RIGHT,PARENT,BROTHER and FOOT pointer*/
#define HEAD(p) ((void *)(p) - WSIZE)
#define LEFT(p) ((void *)(p))
#define RIGHT(p) ((void *)(p) + WSIZE)
#define PARENT(p) ((void *)(p) + 2 * WSIZE)
#define BROTHER(p) ((void *)(p) + 3 * WSIZE)
#define FOOT(p) ((void *)(p) + SIZE(HEAD(p)) - DSIZE)

/*Given block pointer bp, get the POINTER of its directions*/
#define GET_NEXT(bp) ((void *)(bp) + SIZE(((void *)(bp) - WSIZE)))
#define GET_PREV(bp) ( GET_PREV_E_FREE(bp) ? ((void *)bp - BLOCK_SIZE_8B ): ((void *)(bp) - SIZE((void *)(bp) - DSIZE)) )

/*Get the LEFT,RIGHT,PARENT,BROTHER and FOOT pointer of the block to which bp points*/
#define GET_LEFT(bp) ((long)GET(LEFT(bp))|(0x800000000))
#define GET_RIGHT(bp) ((long)GET(RIGHT(bp))|(0x800000000))
#define GET_PARENT(bp) ((long)GET(PARENT(bp))|(0x800000000))
#define GET_BROTHER(bp) ((long)GET(BROTHER(bp))|(0x800000000))

/*Define value to each character in the block bp points to.*/
#define PUT_HEAD(bp, val) (PUT(HEAD(bp), val))
#define PUT_FOOT(bp, val) (PUT(FOOT(bp), val))
#define PUT_LEFT(bp, val) (PUT(LEFT(bp), ((unsigned int)(long)val)))
#define PUT_RIGHT(bp, val) (PUT(RIGHT(bp), ((unsigned int)(long)val)))
#define PUT_PARENT(bp, val) (PUT(PARENT(bp), ((unsigned int)(long)val)))
#define PUT_BROTHER(bp, val) (PUT(BROTHER(bp), ((unsigned int)(long)val)))