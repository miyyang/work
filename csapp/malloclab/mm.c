#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <unistd.h>

#include "mm.h"
#include "memlib.h"

///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
//////////////       function declarations    /////////////
//////////////     & global variables         /////////////
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////

// identity

team_t team = {
    "PB13011079",
    "YangZhi",
    "miyyang@mail.ustc.edu.cn",
    "",
    ""
};

// static functions

static void *coalesce(void *bp);
static void *mm_extend(size_t size);
static void place(void *ptr, size_t asize);
static void insert_node(void *bp);
static void delete_node(void *bp);
static void *find_fit(size_t asize);

// global variables

static void *heaphead;
static void *root;
static void *list16;
static void *list8;	
static void *NIL;

///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
//////////////     basic mem heap management  /////////////
//////////////            function            /////////////
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////

// init

int mm_init(void)
{
	// initial global variables
    NIL = (void *)0x800000000; 
    root = NIL;
    list16 = NIL;
    list8 = NIL;
	// create empty heap
    if ((heaphead = mem_sbrk(4 * WSIZE)) == (void*)-1)
        return -1;
    // header
    PUT(heaphead, 0);	
    PUT(heaphead + (1 * WSIZE), PACK(DSIZE, 1));
    PUT(heaphead + (2 * WSIZE), PACK(DSIZE, 1));
    PUT(heaphead + (3 * WSIZE), PACK(0, 3));
    heaphead += (2 * WSIZE);
	// extend the heap
    if (mm_extend(CHUNKSIZE / WSIZE)==NULL)
        return -1;
    return 0;
}

// extend

void *mm_extend(size_t words)
{
    void *bp;
    void *end = mem_heap_hi() - (WSIZE - 1);
    int size = words;
    if (!PREVALLOC(end))
    {
        if (PREV_E_FREE(end)) 
        	size -= BLOCK_SIZE_8B;
        else 
        	size -= SIZE(end - WSIZE);
    }
    if (size <= 0) 
    	return NULL;
    size = MAX(CHUNKSIZE, size);
    if ((long)(bp = mem_sbrk(size)) == -1)
        return NULL;
    size_t sign = 0 | GET_PREVALLOC(bp) | GET_PREV_E_FREE(bp);
    PUT_HEAD(bp, PACK(size,sign));	
    PUT_FOOT(bp, PACK(size,sign));	
    PUT_HEAD(GET_NEXT(bp), PACK(0,1));	
    insert_node(coalesce(bp));
    return (void*)bp;
}

// malloc

void *mm_malloc(size_t size)
{
    size_t asize;
    void *bp;
    if (size <= 0)
        return NULL;
    asize = ALIGN(size + WSIZE);
    if ((bp = find_fit(asize)) == NIL)		
	{
        mm_extend(asize);
        if ((bp = find_fit(asize)) == NIL)
            return NULL;
    }
    place(bp, asize);
    return bp;
}

// free

void mm_free(void *bp)
{
	if (bp == NULL) 
		return;
    size_t size = GET_SIZE(bp);
    size_t checkalloc = GET_ALLOC(bp);
    if (checkalloc == 0) 
    	return;	
    size_t sign = 0 | GET_PREVALLOC(bp) | GET_PREV_E_FREE(bp);
    PUT_HEAD(bp, PACK(size, sign));
    PUT_FOOT(bp, PACK(size, sign));
    insert_node(coalesce(bp));
}

// realloc

// ptr == null, malloc
// size == 0, free
// size > 0 && new < old, divide into two
// size > 0 && new > old, coalesce and malloc and free
void *mm_realloc(void *ptr, size_t size)
{
    if (ptr==NULL) 
    	return mm_malloc(size);
    if (size == 0)
    {
        mm_free(ptr);
        return NULL;
    }
    if (size > 0)
    {
        size_t oldsize = GET_SIZE(ptr);
        size_t newsize = ALIGN(size + WSIZE);
        if (newsize <= oldsize)
        {
            if (GET_ALLOC(GET_NEXT(ptr)))
            {
                if ((oldsize - newsize) >= DSIZE)
                {
                    size_t sign = 1 | GET_PREVALLOC(ptr) | GET_PREV_E_FREE(ptr);
                    PUT_HEAD(ptr, PACK(newsize,sign));
                    void *temp = GET_NEXT(ptr);
                    PUT_HEAD(temp, PACK(oldsize-newsize,2));
                    PUT_FOOT(temp, PACK(oldsize-newsize,2));
                    insert_node(coalesce(temp));
                }
                return ptr;
            }
            else
            {
                size_t csize = oldsize + GET_SIZE(GET_NEXT(ptr));
                delete_node(GET_NEXT(ptr));
                size_t sign = 1 | GET_PREVALLOC(ptr) | GET_PREV_E_FREE(ptr);
                PUT_HEAD(ptr, PACK(newsize,sign));
                void *temp = GET_NEXT(ptr);
                PUT_HEAD(temp, PACK(csize-newsize,2));
                PUT_FOOT(temp, PACK(csize-newsize,2));
                insert_node(coalesce(temp));
                return ptr;
            }
        }
        else
        {
            void* next = GET_NEXT(ptr);
            size_t next_alloc = GET_ALLOC(next);
            size_t next_size = GET_SIZE(next);
            if (next_size == 0 || GET(GET_NEXT(next)) == 0) 
            {
                mm_extend(newsize - oldsize);
            }
            size_t csize;
            if (!next_alloc && ((csize = oldsize + next_size) >= newsize))
            {
                delete_node(GET_NEXT(ptr));
                if ((csize-newsize) >= DSIZE)
                {
                    size_t sign = 1 | GET_PREVALLOC(ptr) | GET_PREV_E_FREE(ptr);
                    PUT_HEAD(ptr, PACK(newsize,sign));
                    ptr=GET_NEXT(ptr);
                    PUT_HEAD(ptr, PACK(csize-newsize,2));
                    PUT_FOOT(ptr, PACK(csize-newsize,2));
                    insert_node(coalesce(ptr));
				}
				else
				{
				    size_t sign = 1 | GET_PREVALLOC(ptr) | GET_PREV_E_FREE(ptr);
					PUT_HEAD(ptr,PACK(csize,sign));
                    SET_PREVALLOC(GET_NEXT(ptr));
				}
				return ptr;
			}
			else
			{
				void *newptr;
				if ((newptr=find_fit(newsize))==NIL)
				{        
					mm_extend(newsize);
					if ((newptr = find_fit(newsize)) == NIL)
                         return NULL;
				}
				place(newptr, newsize);
				memcpy(newptr, ptr, oldsize - WSIZE);
				mm_free(ptr);
				return newptr;
			}
		}
	}
    else 
    	return NULL;
}

///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
//////////////      helping functions         /////////////
//////////////                                /////////////
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////

// merge two block and update the BST
static void *coalesce(void *bp)
{	
	size_t size = GET_SIZE(bp);

	size_t prev_alloc = GET_PREVALLOC(bp);
	
	size_t next_alloc = GET_ALLOC(GET_NEXT(bp));
	
	if (prev_alloc && next_alloc)
        return bp;
	else if (prev_alloc && !next_alloc) 
	{
	    size += GET_SIZE(GET_NEXT(bp));
	    delete_node(GET_NEXT(bp));
		size_t sign = 0 | GET_PREVALLOC(bp) | GET_PREV_E_FREE(bp);
		PUT_HEAD(bp, PACK(size,sign));
		PUT_FOOT(bp, PACK(size,sign));
		return bp;
	}
	else if (!prev_alloc && next_alloc) 
	{
	    void* prev = (void *)GET_PREV(bp);
	    size_t sign = 0 | GET_PREVALLOC(prev) | GET_PREV_E_FREE(prev);
	    delete_node(prev);
		size += GET_SIZE(prev);
		PUT_HEAD(prev, PACK(size, sign));
		PUT_FOOT(prev, PACK(size, sign));
		return prev;
	}
	else 
	{
	    void* prev = (void *)GET_PREV(bp);
	    void* next = (void *)GET_NEXT(bp);
	    size += GET_SIZE(prev) + GET_SIZE(next);
		delete_node(prev);
		delete_node(next);
		size_t sign = 0 | GET_PREVALLOC(bp) | GET_PREV_E_FREE(bp);
        PUT_HEAD(prev, PACK(size,sign));
		PUT_FOOT(prev, PACK(size,sign));
		return prev;
	}
}

// asize == DSIZE, get from 8-byte list
// asize <= 2*DSIZE, get from 16-byte list
// else, get from BST or extend the heap
static void *find_fit(size_t asize)
{
    if (asize == DSIZE && list8 != NIL) 
    	return list8;
    if (asize <= 2*DSIZE && list16 != NIL) 
    	return list16;
	void *fit = NIL;
	void *temp = root;
	while (temp != NIL)
	{
		if (asize <= GET_SIZE(temp))
		{
			fit = temp;
			temp = (void*)GET_LEFT(temp);
		}
		else
			temp = (void*)GET_RIGHT(temp);
	}
	return fit;
}

static void place(void *bp,size_t asize)
{
	size_t csize = GET_SIZE(bp);
	delete_node(bp);
	if ((csize-asize) >= (2*DSIZE))
	{
	    size_t sign = 1 | GET_PREVALLOC(bp) | GET_PREV_E_FREE(bp);
		PUT_HEAD(bp,PACK(asize,sign));
		bp = GET_NEXT(bp);
		PUT_HEAD(bp, PACK(csize-asize,2));
		PUT_FOOT(bp, PACK(csize-asize,2));
		insert_node(coalesce(bp));
	}
	else
	{
	    size_t sign = 1 | GET_PREVALLOC(bp) | GET_PREV_E_FREE(bp);
		PUT_HEAD(bp,PACK(csize, sign));
	}
}

// blocksize == 8, insert to 8-byte list
// blocksize == 16, insert to 16-byte list
// blocksize >= 24, insert to BST
static void insert_node(void *bp)
{
    RESET_PREVALLOC(GET_NEXT(bp));
    size_t bpsize = GET_SIZE(bp);
    if (bpsize == DSIZE)
    {
        SET_PREV_E_FREE(GET_NEXT(bp));
        PUT_LEFT(bp, list8);
        list8 = bp;
    }    
    if (bpsize == 2*DSIZE)
    {
        PUT_LEFT(bp, NIL);
        PUT_RIGHT(bp, list16);
        PUT_LEFT(list16, bp);
        list16 = bp;
        return;
    }
    else if (bpsize < BLKSIZE) 
    	return;
	if (root == NIL)
	{
		root = bp;
		PUT_LEFT(bp, NIL);
        	PUT_RIGHT(bp, NIL);
		PUT_PARENT(bp, NIL);
		PUT_BROTHER(bp, NIL);
		return;
	}
	void *parent = NIL;
	void *temp = root;
	int dir = -1;
	while (1)
	{
	    if (temp == NIL)
	    {
            PUT_LEFT(bp, NIL);
            PUT_RIGHT(bp, NIL);
            PUT_PARENT(bp, parent);
            PUT_BROTHER(bp, NIL);
            break;
        }
		if (GET_SIZE(bp) == GET_SIZE(temp))
		{
		    void* tempL = (void *)GET_LEFT(temp);
		    void* tempR = (void *)GET_RIGHT(temp);
		    PUT(LEFT(bp), GET(LEFT(temp)));
            PUT(RIGHT(bp), GET(RIGHT(temp)));
            PUT_PARENT(tempL, bp);
            PUT_PARENT(tempR, bp);
		    PUT_PARENT(bp, parent);
            PUT_BROTHER(bp, temp);
            PUT_LEFT(temp, bp);
		    break;
		}
		else if (GET_SIZE(bp) < GET_SIZE(temp))
		{
			parent = temp;
			dir = 0;
			temp = (void *)GET_LEFT(temp);
		}
		else
		{
			parent = temp;
			dir = 1;
			temp = (void *)GET_RIGHT(temp);
		}
	}
	if (dir == -1) 
		root = bp;
	else if (dir == 0) 
		PUT_LEFT(parent, bp);
	else if (dir == 1) 
		PUT_RIGHT(parent, bp);
	else 
		return;
}

// blocksize == 8, remove from 8-byte list
// blocksize == 16, remove from 16-byte list
// else, remove >= 24, remove from BSt
static void delete_node(void *bp)
{
    SET_PREVALLOC(GET_NEXT(bp));
    size_t bpsize = GET_SIZE(bp);
    if (bpsize == DSIZE) 
    {
        RESET_PREV_E_FREE(GET_NEXT(bp));
        void* temp = list8;
        if (temp == bp)
        {
            list8 = (void *)GET_LEFT(bp);
            return;
        }
        while (temp != NIL)
        {
            if ((void *)GET_LEFT(temp) == bp) 
            	break;
            temp = (void *)GET_LEFT(temp); 
        } 
        PUT_LEFT(temp, (void *)GET_LEFT(bp));
    }     
    if (bpsize == 2*DSIZE) 
    {
        void* bpL = (void *)GET_LEFT(bp);
        void* bpR = (void *)GET_RIGHT(bp);
        
        if (bp == list16)
            list16 = bpR;    
        
        PUT_RIGHT(bpL, bpR);
        PUT_LEFT(bpR, bpL);
        return;
    }    
    if (bpsize < BLKSIZE) 
    	return;
    if (((void *)GET_LEFT(bp) != NIL) && ((void *)GET_BROTHER(GET_LEFT(bp)) == bp))
	{
        PUT_BROTHER(GET_LEFT(bp), GET_BROTHER(bp));
        PUT_LEFT(GET_BROTHER(bp), GET_LEFT(bp));
    }
	else if ((void *)GET_BROTHER(bp) == NIL)
	{
		if (bp == root)
		{
			if ((void *)GET_RIGHT(bp) == NIL)
			{
				root = (void *)GET_LEFT(bp);
				if (root != NIL)
				    PUT_PARENT(root, NIL);
			}
			else
			{
				void *temp = (void *)GET_RIGHT(bp);
				while ((void *)GET_LEFT(temp) != NIL)
                    temp = (void *)GET_LEFT(temp);
				void *rootL = (void *)GET_LEFT(bp);
				void *rootR = (void *)GET_RIGHT(bp);
				void *tempR = (void *)GET_RIGHT(temp);
				void *tempP = (void *)GET_PARENT(temp);
				root = temp;
				PUT_PARENT(root, NIL);
				PUT_LEFT(root, rootL);
				PUT_PARENT(rootL, root);
				if (root != rootR)
				{
					PUT_RIGHT(root, rootR);
					PUT_PARENT(rootR, root);
					PUT_LEFT(tempP, tempR);
					PUT_PARENT(tempR, tempP);
				}
			}
		}
		else
		{
			if ((void *)GET_RIGHT(bp) == NIL)
			{
				if ((void *)GET_LEFT(GET_PARENT(bp)) == bp)
					PUT_LEFT(GET_PARENT(bp), GET_LEFT(bp));
				else
					PUT_RIGHT(GET_PARENT(bp), GET_LEFT(bp));
                PUT_PARENT(GET_LEFT(bp), GET_PARENT(bp));
			}
			else
			{
				void *temp = (void *)GET_RIGHT(bp);
				while ((void *)GET_LEFT(temp) != NIL)
				    temp = (void *)GET_LEFT(temp);
				void *bpL = (void *)GET_LEFT(bp);
				void *bpR = (void *)GET_RIGHT(bp);
				void *bpP = (void *)GET_PARENT(bp);
				void *tempR = (void *)GET_RIGHT(temp);
				void *tempP = (void *)GET_PARENT(temp);
				
				if ((void *)GET_LEFT(bpP) == bp)
					PUT_LEFT(bpP, temp);
				else
					PUT_RIGHT(bpP, temp);
			    PUT_PARENT(temp, bpP);

				PUT_LEFT(temp, bpL);
				PUT_PARENT(bpL, temp);
				if (temp != bpR)
				{
					PUT_RIGHT(temp, bpR);
					PUT_PARENT(bpR, temp);
					PUT_LEFT(tempP, tempR);
					PUT_PARENT(tempR, tempP);
				}
			}
		}
	}
    else
    {
	    void *temp = (void *)GET_BROTHER(bp);
		if (bp == root)
		{
			root = temp;
			PUT_PARENT(temp, NIL);
		}
		else
		{
		    if ((void *)GET_LEFT(GET_PARENT(bp)) == bp)
				PUT_LEFT(GET_PARENT(bp), temp);
			else
				PUT_RIGHT(GET_PARENT(bp), temp);
			PUT_PARENT(temp, GET_PARENT(bp));
		}
		PUT(LEFT(temp), GET(LEFT(bp)));
        PUT(RIGHT(temp), GET(RIGHT(bp)));
		PUT_PARENT(GET_LEFT(bp), temp);
	    PUT_PARENT(GET_RIGHT(bp), temp);
	}
}
