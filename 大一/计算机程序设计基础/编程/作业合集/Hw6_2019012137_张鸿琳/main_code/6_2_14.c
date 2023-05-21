#include <stdio.h>
#include <stdlib.h>

int main()
{
    int a,b;
    typedef enum{_,X,O}TICK_TACK_TOE;
    TICK_TACK_TOE tick_tack_toe_phase[3][3]={{X,X,X},{_,_,_},{O,O,O}};
    a=0;
    while(a<=2)
    {
        b=0;
        while(b<=2)
        {
            if(tick_tack_toe_phase[a][b]==O)
            {
                printf("O ");
            }
            else if(tick_tack_toe_phase[a][b]==X)
            {
                printf("X ");
            }
            else
            {
                printf("- ");
            }
            b++;
        }
        printf("\n");
        a++;
    }
    return 0;
}
