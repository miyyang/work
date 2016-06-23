#ifndef MYTYPE_H
#define MYTYPE_H

#include<QString>

#define CACHE_SIZE 4
#define CACHE_NUM 4
#define MEM_SIZE 32



enum MSI{M=0,S,I};
//const QString MSI_Str[3]={"独占","共享","失效"};

enum snooping_status{NO_ACTION,READ_HIT,WRITE_HIT,READ_MISS,
                     WRITE_MISS,INVALID,SHARED,MODIFIED};

const QString status_str[8]={"","read hit","write hit","read miss",
                          "write miss","invalid","shared","exclusive"};
#endif // MYTYPE_H
