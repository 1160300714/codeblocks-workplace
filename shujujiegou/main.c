#include <stdio.h>
#include <stdlib.h>

#define MAXSIZE 100
typedef struct SqList{
    int elem;
    int length;
};

void main()
{
    struct SqList a = {222,111};

    printf("%d",a.length);
}
