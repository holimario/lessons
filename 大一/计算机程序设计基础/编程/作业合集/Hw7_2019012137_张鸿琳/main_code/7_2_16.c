#include <stdio.h>
#include "../library_code/zylib.h"
#include "../library_code/zyrandom.h"
#include "../library_code/dynarray.h"
#include <stdlib.h>

void DiSort(BOOL ascending,DYNAMIC_INTEGERS q)
{
    int k,i,max,t,min;
    if(ascending==TRUE){
    for(i=DiGetCount(q);i>0;i--)
    {
        max=DiGetElement(q,0);
        t=0;
        for(k=1;k<=i-1;k++)
    {
        if(max<=DiGetElement(q,k))
        {
            max=DiGetElement(q,k);
            t=k;
        }
    }
    DiSetElement(q,t,DiGetElement(q,i-1));
    DiSetElement(q,i-1,max);
    }
    }
    else if(ascending==FALSE)
    {
       for(i=DiGetCount(q);i>0;i--)
    {
        min=DiGetElement(q,0);
        t=0;
        for(k=0;k<=i-1;k++)
    {
        if(min>=DiGetElement(q,k))
        {
            min=DiGetElement(q,k);
            t=k;
        }
    }
    DiSetElement(q,t,DiGetElement(q,i-1));
    DiSetElement(q,i-1,min);
    }
    }
    else
    {
        PrintErrorMessage(TRUE," ‰»Î”–ŒÛ");
    }
}

int main()
{
    int n=3,h;
    DYNAMIC_INTEGERS a;
    a=DiCreate(n);
    h=GetIntegerFromKeyboard();
    DiAddElement(a,h);
    h=GetIntegerFromKeyboard();
    DiAddElement(a,h);
    h=GetIntegerFromKeyboard();
    DiAddElement(a,h);
    DiSort(FALSE,a);
    printf("%d %d %d",DiGetElement(a,0),DiGetElement(a,1),DiGetElement(a,2));
    return 0;
}
