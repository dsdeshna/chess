#include<stdio.h>
#include<ctype.h>
#include<stdlib.h>

/// structure to store all current positions of pieces
struct positions
{
    int piece,position;
};
/// array of structures for 32 pieces each
typedef struct positions positions;

int returnposition(int a,struct positions *pp) ///return pos if piece is given
{
    int i;
    for(i=0;i<32;i++)
    {
        if (pp[i].piece==a)
            return pp[i].position;
    }
}
int returnpiece(int a,int b,struct positions *pp) ///return piece if pos is given
{
    int i;
    for(i=0;i<32;i++)
    {
        if (pp[i].position==((10*a)+b))
            return pp[i].piece;
    }
}
int borw(int x) ///checking if piece is black or white
{
    if (x<=16&&x>=1)
        return 1;
    else if (x>=17&&x<33)
        return 0;
}
/// //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int main()
{
    int pob=32,pobf=0;
    int bcheck=0,wcheck=0,bcmate=0,wcmate=0;
    printf("\nRULES\n1) Moves/positions are to be entered in the specified format (eg: A1, e4, etc)\n");
    printf("2) No space is to be given between the characters\n");
    printf("3) A plus symbol (+) is to added to the final position if you're keeping check for the opponent (eg: A2+, e5+)\n");
    printf("4) A hash (#) is to be given if you've done a checkmate (e: A7#, b9#)\n\n");
    int c[8][8]={0},i,j;
    char pieces[34]=" KQBBNNRRPPPPPPPPkqbbnnrrpppppppp";
    char ho[10]="ABCDEFGH";
    int x[8]={23,21,19,18,17,20,22,24};
    int y[8]={7,5,3,2,1,4,6,8};
    for(i=0;i<8;i++)
    {
        c[0][i]=x[i];
        c[7][i]=y[i];
        c[6][i]=i+9;
        c[1][i]=i+25;
    }

    ///printing the chess board
    printf("\n      A   B   C   D   E   F   G   H");
    printf("\n    ---------------------------------\n");
    for (i=0;i<8;i++)
    {
        printf("  %d | ",8-i);
        for(j=0;j<8;j++)
            printf("%c | ",pieces[c[i][j]]);
        printf("%d ",8-i);
        printf("\n    ---------------------------------\n");
    }
    printf("      A   B   C   D   E   F   G   H\n");

    ///white and black omg
    int wb=0;

    /// the game loop
    while(1)
    {
        positions pos[pob];
        /// using the integer value from earlier to store current positions of pieces in structures??
        int ind=0;
        for (i=0;i<8;i++)
        {
            for(j=0;j<8;j++)
            {
                if (c[i][j]!=0)
                {
                    pos[ind].piece=c[i][j];
                    pos[ind++].position=(10*i)+j;
                }
            }
        }
        if (wb%2==0) ///WHITE - EVEN
        {
            if (wcmate)
            {
                printf("\nBLACK HAS CHECKMATED WHITE\n\nBLACK WINS!\n");
                break;
            }
            if (wcheck)
                printf("\nWHITE KING IS IN CHECK\n");
            bcheck=0;
            printf("\nWHITE'S TURN\n");
            /// currpos - current position
            char currpos[3];
            printf("enter initial position of piece to move: ");
            scanf("%s",currpos);
            currpos[0]=toupper(currpos[0]);
            if (currpos[0]>'H'&& currpos[1]>8)
            {
                printf("ENTERED POSITION DOES NOT EXIST. TRY AGAIN\n");
                continue;
            }
            int xi=8-currpos[1]+48,yi;
            for (i=0;i<8;i++)
            {
                if (currpos[0]==ho[i])
                    yi=i;
            }

            ///square empty
            if (c[xi][yi]==0)
            {
                printf("SQUARE EMPTY. TRY AGAIN\n");
                continue;
            }

            /// currpiece has the current piece the user has chosen to move
            int currpiece=returnpiece(xi,yi,&pos);

            ///black can't move white turn
            if (!borw(currpiece))
            {
                printf("BLACK CAN'T MOVE DURING WHITE'S TURN\n");
                continue;
            }

            /// future position??
            char finpos[3];
            printf("enter position to move to: ");
            scanf("%s",finpos);
            if (finpos[2]=='+')
                bcheck=1;
            else if (finpos[2]=='#')
                bcmate=1;
            finpos[0]=toupper(finpos[0]);
            if (finpos[0]>'H'&& finpos[1]>8)
            {
                printf("ENTERED POSITION DOES NOT EXIST. TRY AGAIN\n");
                continue;
            }
            int xf=8-finpos[1]+48,yf;
            for (i=0;i<8;i++)
            {
                if (finpos[0]==ho[i])
                    yf=i;
            }
            /// initial and final position same - no move
            if (xi==xf&&yi==yf)
            {
                printf("A MOVE HAS TO BE MADE. TRY AGAIN\n");
                continue;
            }
            /// FOR WHITE QUEEN
            if (currpiece==2)
            {
                if (yf>yi&&xf==xi)///right
                {
                    int l=0,t=0;
                    for (i=yi+1;i<yf;i++)
                    {
                        if (c[xf][i]!=0)
                            l=1;
                    }
                    if (c[xf][yf]!=0)
                    {
                        ///finpiece for knowing if piece at finalpos can be cut
                        int finpiece=returnpiece(xf,yf,&pos);
                        if (borw(finpiece) || finpiece==17)
                            t=1;
                        else
                            pob--;
                    }
                    if (l+t)
                    {
                        printf("MOVE NOT POSSIBLE, TRY AGAIN\n");
                        continue;
                    }
                }
                else if (yf<yi&&xf==xi) ///left
                {
                    int l=0,t=0;
                    for (i=yi-1;i>yf;i--)
                    {
                        if (c[xf][i]!=0)
                            l=1;
                    }
                    if (c[xf][yf]!=0)
                    {
                        ///finpiece for knowing if piece at finalpos can be cut
                        int finpiece=returnpiece(xf,yf,&pos);
                        if (borw(finpiece) || finpiece==17)
                            t=1;
                        else
                            pob--;
                    }
                    if (l+t)
                    {
                        printf("MOVE NOT POSSIBLE, TRY AGAIN\n");
                        continue;
                    }
                }
                else if (xf>xi&&yf==yi) ///down
                {
                    int l=0,t=0;
                    for (i=xi+1;i<xf;i++)
                    {
                        if (c[i][yf]!=0)
                            l=1;
                    }
                    if (c[xf][yf]!=0)
                    {
                        ///finpiece for knowing if piece at finalpos can be cut
                        int finpiece=returnpiece(xf,yf,&pos);
                        if (borw(finpiece) || finpiece==17)
                            t=1;
                        else
                            pob--;
                    }
                    if (l+t)
                    {
                        printf("MOVE NOT POSSIBLE, TRY AGAIN\n");
                        continue;
                    }
                }
                else if (xf<xi&&yf==yi) ///up
                {
                    int l=0,t=0;
                    for (i=xi-1;i>xf;i--)
                    {
                        if (c[i][yf]!=0)
                            l=1;
                    }
                    if (c[xf][yf]!=0)
                    {
                        ///finpiece for knowing if piece at finalpos can be cut
                        int finpiece=returnpiece(xf,yf,&pos);
                        if (borw(finpiece) || finpiece==17)
                            t=1;
                        else
                            pob--;
                    }
                    if (l+t)
                    {
                        printf("MOVE NOT POSSIBLE, TRY AGAIN\n");
                        continue;
                    }
                }
                else if ((xf+yf==xi+yi)&&xf<xi) ///dia right up
                {
                    int l=0,t=0;
                    for (i=xi-1;i>xf;i--)
                    {
                        if (c[i][xi+yi-i]!=0)
                            l=1;
                    }
                    if (c[xf][yf]!=0)
                    {
                        ///finpiece for knowing if piece at finalpos can be cut
                        int finpiece=returnpiece(xf,yf,&pos);
                        if (borw(finpiece) || finpiece==17)
                            t=1;
                        else
                            pob--;
                    }
                    if (l+t)
                    {
                        printf("MOVE NOT POSSIBLE, TRY AGAIN\n");
                        continue;
                    }
                }
                else if ((xf+yf==xi+yi)&&xf>xi) ///dia left down
                {
                    int l=0,t=0;
                    for (i=xi+1;i<xf;i++)
                    {
                        if (c[i][xi+yi-i]!=0)
                            l=1;
                    }
                    if (c[xf][yf]!=0)
                    {
                        ///finpiece for knowing if piece at finalpos can be cut
                        int finpiece=returnpiece(xf,yf,&pos);
                        if (borw(finpiece) || finpiece==17)
                            t=1;
                        else
                            pob--;
                    }
                    if (l+t)
                    {
                        printf("MOVE NOT POSSIBLE, TRY AGAIN\n");
                        continue;
                    }
                }
                else if (((xf-yf==xi-yi)||xf-yf==yi-xi)&&xf>xi) ///dia right down
                {
                    int l=0,t=0;
                    for (i=1;xf-i>xi;i++)
                    {
                        if (c[xi+i][yi+i]!=0)
                            l=1;
                    }
                    if (c[xf][yf]!=0)
                    {
                        ///finpiece for knowing if piece at finalpos can be cut
                        int finpiece=returnpiece(xf,yf,&pos);
                        if (borw(finpiece) || finpiece==17)
                            t=1;
                        else
                            pob--;
                    }
                    if (l+t)
                    {
                        printf("MOVE NOT POSSIBLE, TRY AGAIN\n");
                        continue;
                    }
                }
                else if (((xf-yf==xi-yi)||xf-yf==yi-xi)&&xf<xi) ///dia left up
                {
                    int l=0,t=0;
                    for (i=1;xi-i>xf;i++)
                    {
                        if (c[xi-i][yi-i]!=0)
                            l=1;
                    }
                    if (c[xf][yf]!=0)
                    {
                        ///finpiece for knowing if piece at finalpos can be cut
                        int finpiece=returnpiece(xf,yf,&pos);
                        if (borw(finpiece) || finpiece==17)
                            t=1;
                        else
                            pob--;
                    }
                    if (l+t)
                    {
                        printf("MOVE NOT POSSIBLE, TRY AGAIN\n");
                        continue;
                    }
                }
                else ///if out of range of queen's moving possibilities?
                {
                    printf("QUEEN CANNOT MOVE TO THAT POSITION. TRY AGAIN\n");
                    continue;
                }
                c[xf][yf]=currpiece;
                c[xi][yi]=0;
            }
            ///FOR WHITE ROOK
            else if (currpiece==7||currpiece==8)
            {
                if (yf>yi&&xf==xi)///right
                {
                    int l=0,t=0;
                    for (i=yi+1;i<yf;i++)
                    {
                        if (c[xf][i]!=0)
                            l=1;
                    }
                    if (c[xf][yf]!=0)
                    {
                        ///finpiece for knowing if piece at finalpos can be cut
                        int finpiece=returnpiece(xf,yf,&pos);
                        if (borw(finpiece) || finpiece==17)
                            t=1;
                        else
                            pob--;
                    }
                    if (l+t)
                    {
                        printf("MOVE NOT POSSIBLE, TRY AGAIN\n");
                        continue;
                    }
                }
                else if (yf<yi&&xf==xi) ///left
                {
                    int l=0,t=0;
                    for (i=yi-1;i>yf;i--)
                    {
                        if (c[xf][i]!=0)
                            l=1;
                    }
                    if (c[xf][yf]!=0)
                    {
                        ///finpiece for knowing if piece at finalpos can be cut
                        int finpiece=returnpiece(xf,yf,&pos);
                        if (borw(finpiece) || finpiece==17)
                            t=1;
                        else
                            pob--;
                    }
                    if (l+t)
                    {
                        printf("MOVE NOT POSSIBLE, TRY AGAIN\n");
                        continue;
                    }
                }
                else if (xf>xi&&yf==yi) ///down
                {
                    int l=0,t=0;
                    for (i=xi+1;i<xf;i++)
                    {
                        if (c[i][yf]!=0)
                            l=1;
                    }
                    if (c[xf][yf]!=0)
                    {
                        ///finpiece for knowing if piece at finalpos can be cut
                        int finpiece=returnpiece(xf,yf,&pos);
                        if (borw(finpiece) || finpiece==17)
                            t=1;
                        else
                            pob--;
                    }
                    if (l+t)
                    {
                        printf("MOVE NOT POSSIBLE, TRY AGAIN\n");
                        continue;
                    }
                }
                else if (xf<xi&&yf==yi) ///up
                {
                    int l=0,t=0;
                    for (i=xi-1;i>xf;i--)
                    {
                        if (c[i][yf]!=0)
                            l=1;
                    }
                    if (c[xf][yf]!=0)
                    {
                        ///finpiece for knowing if piece at finalpos can be cut
                        int finpiece=returnpiece(xf,yf,&pos);
                        if (borw(finpiece) || finpiece==17)
                            t=1;
                        else
                            pob--;
                    }
                    if (l+t)
                    {
                        printf("MOVE NOT POSSIBLE, TRY AGAIN\n");
                        continue;
                    }
                }
                else ///if out of range of rook's moving possibilities?
                {
                    printf("ROOK CANNOT MOVE TO THAT POSITION. TRY AGAIN\n");
                    continue;
                }
                c[xf][yf]=currpiece;
                c[xi][yi]=0;
            }
            ///FOR WHITE BISHOP
            else if (currpiece==3||currpiece==4)
            {
                if ((xf+yf==xi+yi)&&xf<xi) ///dia right up
                {
                    int l=0,t=0;
                    for (i=xi-1;i>xf;i--)
                    {
                        if (c[i][xi+yi-i]!=0)
                            l=1;
                    }
                    if (c[xf][yf]!=0)
                    {
                        ///finpiece for knowing if piece at finalpos can be cut
                        int finpiece=returnpiece(xf,yf,&pos);
                        if (borw(finpiece) || finpiece==17)
                            t=1;
                        else
                            pob--;
                    }
                    if (l+t)
                    {
                        printf("MOVE NOT POSSIBLE, TRY AGAIN\n");
                        continue;
                    }
                }
                else if ((xf+yf==xi+yi)&&xf>xi) ///dia left down
                {
                    int l=0,t=0;
                    for (i=xi+1;i<xf;i++)
                    {
                        if (c[i][xi+yi-i]!=0)
                            l=1;
                    }
                    if (c[xf][yf]!=0)
                    {
                        ///finpiece for knowing if piece at finalpos can be cut
                        int finpiece=returnpiece(xf,yf,&pos);
                        if (borw(finpiece) || finpiece==17)
                            t=1;
                        else
                            pob--;
                    }
                    if (l+t)
                    {
                        printf("MOVE NOT POSSIBLE, TRY AGAIN\n");
                        continue;
                    }
                }
                else if (((xf-yf==xi-yi)||xf-yf==yi-xi)&&xf>xi) ///dia right down
                {
                    int l=0,t=0;
                    for (i=1;xf-i>xi;i++)
                    {
                        if (c[xi+i][yi+i]!=0)
                            l=1;
                    }
                    if (c[xf][yf]!=0)
                    {
                        ///finpiece for knowing if piece at finalpos can be cut
                        int finpiece=returnpiece(xf,yf,&pos);
                        if (borw(finpiece) || finpiece==17)
                            t=1;
                        else
                            pob--;
                    }
                    if (l+t)
                    {
                        printf("MOVE NOT POSSIBLE, TRY AGAIN\n");
                        continue;
                    }
                }
                else if (((xf-yf==xi-yi)||xf-yf==yi-xi)&&xf<xi) ///dia left up
                {
                    int l=0,t=0;
                    for (i=1;xi-i>xf;i++)
                    {
                        if (c[xi-i][yi-i]!=0)
                            l=1;
                    }
                    if (c[xf][yf]!=0)
                    {
                        ///finpiece for knowing if piece at finalpos can be cut
                        int finpiece=returnpiece(xf,yf,&pos);
                        if (borw(finpiece) || finpiece==17)
                            t=1;
                        else
                            pob--;
                    }
                    if (l+t)
                    {
                        printf("MOVE NOT POSSIBLE, TRY AGAIN\n");
                        continue;
                    }
                }
                else ///if out of range of bishop's moving possibilities?
                {
                    printf("BISHOP CANNOT MOVE TO THAT POSITION. TRY AGAIN\n");
                    continue;
                }
                c[xf][yf]=currpiece;
                c[xi][yi]=0;
            }
            ///FOR WHITE KNIGHT
            else if (currpiece==5||currpiece==6)
            {
                if ((abs(xf-xi)==2&&abs(yi-yf)==1)||(abs(yf-yi)==2&&abs(xi-xf)==1))
                {
                    int t=0;
                    if (c[xf][yf]!=0)
                    {
                        ///finpiece for knowing if piece at finalpos can be cut
                        int finpiece=returnpiece(xf,yf,&pos);
                        if (borw(finpiece) || finpiece==17)
                            t=1;
                        else
                            pob--;
                    }
                    if (t)
                    {
                        printf("MOVE NOT POSSIBLE, TRY AGAIN\n");
                        continue;
                    }
                }
                else ///if out of range of knight's moving possibilities?
                {
                    printf("KNIGHT CANNOT MOVE TO THAT POSITION. TRY AGAIN\n");
                    continue;
                }
                c[xf][yf]=currpiece;
                c[xi][yi]=0;
            }
            ///FOR WHITE PAWNS
            else if (currpiece>=9&&currpiece<=16)
            {
                if ((xi-xf)==1&&abs(yi-yf)==1&&c[xf][yf]!=0)
                {
                    int t=0;
                    ///finpiece for knowing if piece at finalpos can be cut
                    int finpiece=returnpiece(xf,yf,&pos);
                    if (borw(finpiece) || finpiece==17)
                        t=1;
                    else
                        pob--;
                    if (t)
                    {
                        printf("MOVE NOT POSSIBLE, TRY AGAIN\n");
                        continue;
                    }
                }
                else if (yi==yf&&xf<xi&&c[xf][yf]==0)
                {
                    if ((abs(xi-xf)==1)||(abs(xi-xf)==2&&xi==6))
                    {
                        c[xf][yf]=currpiece;
                        c[xi][yi]=0;
                    }
                    else
                    {
                        printf("PAWN CANNOT MOVE TO THAT POSITION. TRY AGAIN\n");
                        continue;
                    }
                }
                else ///if out of range of pawn's moving possibilities?
                {
                    printf("PAWN CANNOT MOVE TO THAT POSITION. TRY AGAIN\n");
                    continue;
                }
                c[xf][yf]=currpiece;
                c[xi][yi]=0;
            }
            ///FOR WHITE KING
            else if (currpiece==1)
            {
                if ((abs(xf-xi)==1&&yf==yi)||(abs(yf-yi)==1&&xf==xi)||(abs(xi-xf)==1&&abs(yi-yf)==1))
                {
                    int t=0;
                    if (c[xf][yf]!=0)
                    {
                        ///finpiece for knowing if piece at finalpos can be cut
                        int finpiece=returnpiece(xf,yf,&pos);
                        if (borw(finpiece) || finpiece==17)
                            t=1;
                        else
                            pob--;
                    }
                    if (t)
                    {
                        printf("MOVE NOT POSSIBLE, TRY AGAIN\n");
                        continue;
                    }
                }
                else ///if out of range of knight's moving possibilities?
                {
                    printf("KING CANNOT MOVE TO THAT POSITION. TRY AGAIN\n");
                    continue;
                }
                c[xf][yf]=currpiece;
                c[xi][yi]=0;
            }
            positions pos[pob];
            ind=0;
            for (i=0;i<8;i++)
            {
                for(j=0;j<8;j++)
                {
                    if (c[i][j]!=0)
                    {
                        pos[ind].piece=c[i][j];
                        pos[ind++].position=(10*i)+j;
                    }
                }
            }
        }

        else ///BLACK - ODD
        {
            if (bcmate)
            {
                printf("\nWHITE HAS CHECKMATED BLACK\n\nWHITE WINS!\n");
                break;
            }
            if (bcheck)
                printf("\nBLACK KING IS IN CHECK\n");
            wcheck=0;
            printf("\nBLACK'S TURN\n");
            /// current position
            char currpos[3];
            printf("enter initial position of piece to move: ");
            scanf("%s",currpos);
            currpos[0]=toupper(currpos[0]);
            if (currpos[0]>'H'&& currpos[1]>8)
            {
                printf("ENTERED POSITION DOES NOT EXIST. TRY AGAIN\n");
                continue;
            }
            int xi=8-currpos[1]+48,yi;
            for (i=0;i<8;i++)
            {
                if (currpos[0]==ho[i])
                    yi=i;
            }
            ///square empty
            if (c[xi][yi]==0)
            {
                printf("SQUARE EMPTY. TRY AGAIN\n");
                continue;
            }
            /// currpiece has the current piece the user has chosen to move
            int currpiece=returnpiece(xi,yi,&pos);

            ///white can't move black turn
            if (borw(currpiece))
            {
                printf("WHITE CAN'T MOVE DURING BLACK'S TURN\n");
                continue;
            }

            /// future position??
            char finpos[3];
            printf("enter position to move to: ");
            scanf("%s",finpos);
            if (finpos[2]=='+')
                wcheck=1;
            else if (finpos[2]=='#')
                wcmate=1;
            finpos[0]=toupper(finpos[0]);
            if (finpos[0]>'H'&& finpos[1]>8)
            {
                printf("ENTERED POSITION DOES NOT EXIST. TRY AGAIN\n");
                continue;
            }
            int xf=8-finpos[1]+48,yf;
            for (i=0;i<8;i++)
            {
                if (finpos[0]==ho[i])
                    yf=i;
            }
            /// initial and final position same - no move
            if (xi==xf&&yi==yf)
            {
                printf("A MOVE HAS TO BE MADE. TRY AGAIN\n");
                continue;
            }

            /// FOR BLACK QUEEN
            if (currpiece==18)
            {
                if (yf>yi&&xf==xi)///right
                {
                    int l=0,t=0;
                    for (i=yi+1;i<yf;i++)
                    {
                        if (c[xf][i]!=0)
                            l=1;
                    }
                    if (c[xf][yf]!=0)
                    {
                        ///finpiece for knowing if piece at finalpos can be cut
                        int finpiece=returnpiece(xf,yf,&pos);
                        if (!borw(finpiece) || finpiece==1)
                            t=1;
                        else
                            pob--;
                    }
                    if (l+t)
                    {
                        printf("MOVE NOT POSSIBLE, TRY AGAIN\n");
                        continue;
                    }
                }
                else if (yf<yi&&xf==xi) ///left
                {
                    int l=0,t=0;
                    for (i=yi-1;i>yf;i--)
                    {
                        if (c[xf][i]!=0)
                            l=1;
                    }
                    if (c[xf][yf]!=0)
                    {
                        ///finpiece for knowing if piece at finalpos can be cut
                        int finpiece=returnpiece(xf,yf,&pos);
                        if (!borw(finpiece) || finpiece==1)
                            t=1;
                        else
                            pob--;
                    }
                    if (l+t)
                    {
                        printf("MOVE NOT POSSIBLE, TRY AGAIN\n");
                        continue;
                    }
                }
                else if (xf>xi&&yf==yi) ///down
                {
                    int l=0,t=0;
                    for (i=xi+1;i<xf;i++)
                    {
                        if (c[i][yf]!=0)
                            l=1;
                    }
                    if (c[xf][yf]!=0)
                    {
                        ///finpiece for knowing if piece at finalpos can be cut
                        int finpiece=returnpiece(xf,yf,&pos);
                        if (!borw(finpiece) || finpiece==1)
                            t=1;
                        else
                            pob--;
                    }
                    if (l+t)
                    {
                        printf("MOVE NOT POSSIBLE, TRY AGAIN\n");
                        continue;
                    }
                }
                else if (xf<xi&&yf==yi) ///up
                {
                    int l=0,t=0;
                    for (i=xi-1;i>xf;i--)
                    {
                        if (c[i][yf]!=0)
                            l=1;
                    }
                    if (c[xf][yf]!=0)
                    {
                        ///finpiece for knowing if piece at finalpos can be cut
                        int finpiece=returnpiece(xf,yf,&pos);
                        if (!borw(finpiece) || finpiece==1)
                            t=1;
                        else
                            pob--;
                    }
                    if (l+t)
                    {
                        printf("MOVE NOT POSSIBLE, TRY AGAIN\n");
                        continue;
                    }
                }
                else if ((xf+yf==xi+yi)&&xf<xi) ///dia right up
                {
                    int l=0,t=0;
                    for (i=xi-1;i>xf;i--)
                    {
                        if (c[i][xi+yi-i]!=0)
                            l=1;
                    }
                    if (c[xf][yf]!=0)
                    {
                        ///finpiece for knowing if piece at finalpos can be cut
                        int finpiece=returnpiece(xf,yf,&pos);
                        if (!borw(finpiece) || finpiece==1)
                            t=1;
                        else
                            pob--;
                    }
                    if (l+t)
                    {
                        printf("MOVE NOT POSSIBLE, TRY AGAIN\n");
                        continue;
                    }
                }
                else if ((xf+yf==xi+yi)&&xf>xi) ///dia left down
                {
                    int l=0,t=0;
                    for (i=xi+1;i<xf;i++)
                    {
                        if (c[i][xi+yi-i]!=0)
                            l=1;
                    }
                    if (c[xf][yf]!=0)
                    {
                        ///finpiece for knowing if piece at finalpos can be cut
                        int finpiece=returnpiece(xf,yf,&pos);
                        if (!borw(finpiece) || finpiece==1)
                            t=1;
                        else
                            pob--;
                    }
                    if (l+t)
                    {
                        printf("MOVE NOT POSSIBLE, TRY AGAIN\n");
                        continue;
                    }
                }
                else if (((xf-yf==xi-yi)||xf-yf==yi-xi)&&xf>xi) ///dia right down
                {
                    int l=0,t=0;
                    for (i=1;xf-i>xi;i++)
                    {
                        if (c[xi+i][yi+i]!=0)
                            l=1;
                    }
                    if (c[xf][yf]!=0)
                    {
                        ///finpiece for knowing if piece at finalpos can be cut
                        int finpiece=returnpiece(xf,yf,&pos);
                        if (!borw(finpiece) || finpiece==1)
                            t=1;
                        else
                            pob--;
                    }
                    if (l+t)
                    {
                        printf("MOVE NOT POSSIBLE, TRY AGAIN\n");
                        continue;
                    }
                }
                else if (((xf-yf==xi-yi)||xf-yf==yi-xi)&&xf<xi) ///dia left up
                {
                    int l=0,t=0;
                    for (i=1;xi-i>xf;i++)
                    {
                        if (c[xi-i][yi-i]!=0)
                            l=1;
                    }
                    if (c[xf][yf]!=0)
                    {
                        ///finpiece for knowing if piece at finalpos can be cut
                        int finpiece=returnpiece(xf,yf,&pos);
                        if (!borw(finpiece) || finpiece==1)
                            t=1;
                        else
                            pob--;
                    }
                    if (l+t)
                    {
                        printf("MOVE NOT POSSIBLE, TRY AGAIN\n");
                        continue;
                    }
                }
                else ///if out of range of queen's moving possibilities?
                {
                    printf("QUEEN CANNOT MOVE TO THAT POSITION. TRY AGAIN\n");
                    continue;
                }
                c[xf][yf]=currpiece;
                c[xi][yi]=0;
            }
            /// FOR BLACK ROOK
            else if (currpiece==23||currpiece==24)
            {
                if (yf>yi&&xf==xi)///right
                {
                    int l=0,t=0;
                    for (i=yi+1;i<yf;i++)
                    {
                        if (c[xf][i]!=0)
                            l=1;
                    }
                    if (c[xf][yf]!=0)
                    {
                        ///finpiece for knowing if piece at finalpos can be cut
                        int finpiece=returnpiece(xf,yf,&pos);
                        if (!borw(finpiece) || finpiece==1)
                            t=1;
                        else
                            pob--;
                    }
                    if (l+t)
                    {
                        printf("MOVE NOT POSSIBLE, TRY AGAIN\n");
                        continue;
                    }
                }
                else if (yf<yi&&xf==xi) ///left
                {
                    int l=0,t=0;
                    for (i=yi-1;i>yf;i--)
                    {
                        if (c[xf][i]!=0)
                            l=1;
                    }
                    if (c[xf][yf]!=0)
                    {
                        ///finpiece for knowing if piece at finalpos can be cut
                        int finpiece=returnpiece(xf,yf,&pos);
                        if (!borw(finpiece) || finpiece==1)
                            t=1;
                        else
                            pob--;
                    }
                    if (l+t)
                    {
                        printf("MOVE NOT POSSIBLE, TRY AGAIN\n");
                        continue;
                    }
                }
                else if (xf>xi&&yf==yi) ///down
                {
                    int l=0,t=0;
                    for (i=xi+1;i<xf;i++)
                    {
                        if (c[i][yf]!=0)
                            l=1;
                    }
                    if (c[xf][yf]!=0)
                    {
                        ///finpiece for knowing if piece at finalpos can be cut
                        int finpiece=returnpiece(xf,yf,&pos);
                        if (!borw(finpiece) || finpiece==1)
                            t=1;
                        else
                            pob--;
                    }
                    if (l+t)
                    {
                        printf("MOVE NOT POSSIBLE, TRY AGAIN\n");
                        continue;
                    }
                }
                else if (xf<xi&&yf==yi) ///up
                {
                    int l=0,t=0;
                    for (i=xi-1;i>xf;i--)
                    {
                        if (c[i][yf]!=0)
                            l=1;
                    }
                    if (c[xf][yf]!=0)
                    {
                        ///finpiece for knowing if piece at finalpos can be cut
                        int finpiece=returnpiece(xf,yf,&pos);
                        if (!borw(finpiece) || finpiece==1)
                            t=1;
                        else
                            pob--;
                    }
                    if (l+t)
                    {
                        printf("MOVE NOT POSSIBLE, TRY AGAIN\n");
                        continue;
                    }
                }
                else ///if out of range of rook's moving possibilities?
                {
                    printf("ROOK CANNOT MOVE TO THAT POSITION. TRY AGAIN\n");
                    continue;
                }
                c[xf][yf]=currpiece;
                c[xi][yi]=0;
            }
            /// FOR BLACK BISHOP
            else if (currpiece==19||currpiece==20)
            {
                if ((xf+yf==xi+yi)&&xf<xi) ///dia right up
                {
                    int l=0,t=0;
                    for (i=xi-1;i>xf;i--)
                    {
                        if (c[i][xi+yi-i]!=0)
                            l=1;
                    }
                    if (c[xf][yf]!=0)
                    {
                        ///finpiece for knowing if piece at finalpos can be cut
                        int finpiece=returnpiece(xf,yf,&pos);
                        if (!borw(finpiece) || finpiece==1)
                            t=1;
                        else
                            pob--;
                    }
                    if (l+t)
                    {
                        printf("MOVE NOT POSSIBLE, TRY AGAIN\n");
                        continue;
                    }
                }
                else if ((xf+yf==xi+yi)&&xf>xi) ///dia left down
                {
                    int l=0,t=0;
                    for (i=xi+1;i<xf;i++)
                    {
                        if (c[i][xi+yi-i]!=0)
                            l=1;
                    }
                    if (c[xf][yf]!=0)
                    {
                        ///finpiece for knowing if piece at finalpos can be cut
                        int finpiece=returnpiece(xf,yf,&pos);
                        if (!borw(finpiece) || finpiece==1)
                            t=1;
                        else
                            pob--;
                    }
                    if (l+t)
                    {
                        printf("MOVE NOT POSSIBLE, TRY AGAIN\n");
                        continue;
                    }
                }
                else if (((xf-yf==xi-yi)||xf-yf==yi-xi)&&xf>xi) ///dia right down
                {
                    int l=0,t=0;
                    for (i=1;xf-i>xi;i++)
                    {
                        if (c[xi+i][yi+i]!=0)
                            l=1;
                    }
                    if (c[xf][yf]!=0)
                    {
                        ///finpiece for knowing if piece at finalpos can be cut
                        int finpiece=returnpiece(xf,yf,&pos);
                        if (!borw(finpiece) || finpiece==1)
                            t=1;
                        else
                            pob--;
                    }
                    if (l+t)
                    {
                        printf("MOVE NOT POSSIBLE, TRY AGAIN\n");
                        continue;
                    }
                }
                else if (((xf-yf==xi-yi)||xf-yf==yi-xi)&&xf<xi) ///dia left up
                {
                    int l=0,t=0;
                    for (i=1;xi-i>xf;i++)
                    {
                        if (c[xi-i][yi-i]!=0)
                            l=1;
                    }
                    if (c[xf][yf]!=0)
                    {
                        ///finpiece for knowing if piece at finalpos can be cut
                        int finpiece=returnpiece(xf,yf,&pos);
                        if (!borw(finpiece) || finpiece==1)
                            t=1;
                        else
                            pob--;
                    }
                    if (l+t)
                    {
                        printf("MOVE NOT POSSIBLE, TRY AGAIN\n");
                        continue;
                    }
                }
                else ///if out of range of bishop's moving possibilities?
                {
                    printf("BISHOP CANNOT MOVE TO THAT POSITION. TRY AGAIN\n");
                    continue;
                }
                c[xf][yf]=currpiece;
                c[xi][yi]=0;
            }
            ///FOR BLACK KNIGHT
            else if (currpiece==21||currpiece==22)
            {
                if ((abs(xf-xi)==2&&abs(yi-yf)==1)||(abs(yf-yi)==2&&abs(xi-xf)==1)) ///
                {
                    int t=0;
                    if (c[xf][yf]!=0)
                    {
                        ///finpiece for knowing if piece at finalpos can be cut
                        int finpiece=returnpiece(xf,yf,&pos);
                        if (!borw(finpiece) || finpiece==1)
                            t=1;
                        else
                            pob--;
                    }
                    if (t)
                    {
                        printf("MOVE NOT POSSIBLE, TRY AGAIN\n");
                        continue;
                    }
                }
                else ///if out of range of knight's moving possibilities?
                {
                    printf("KNIGHT CANNOT MOVE TO THAT POSITION. TRY AGAIN\n");
                    continue;
                }
                c[xf][yf]=currpiece;
                c[xi][yi]=0;
            }
            ///FOR BLACK PAWNS
            else if (currpiece>=25&&currpiece<=32)
            {
                if ((xf-xi)==1&&abs(yi-yf)==1&&c[xf][yf]!=0)
                {
                    int t=0;
                    ///finpiece for knowing if piece at finalpos can be cut
                    int finpiece=returnpiece(xf,yf,&pos);
                    if (!borw(finpiece) || finpiece==1)
                        t=1;
                    else
                            pob--;
                    if (t)
                    {
                        printf("MOVE NOT POSSIBLE, TRY AGAIN\n");
                        continue;
                    }
                }
                else if (yi==yf&&xf>xi&&c[xf][yf]==0)
                {
                    if ((abs(xi-xf)==1)||(abs(xi-xf)==2&&xi==1))
                    {
                        c[xf][yf]=currpiece;
                        c[xi][yi]=0;
                    }
                    else
                    {
                        printf("PAWN CANNOT MOVE TO THAT POSITION. TRY AGAIN\n");
                        continue;
                    }
                }
                else ///if out of range of pawn's moving possibilities?
                {
                    printf("PAWN CANNOT MOVE TO THAT POSITION. TRY AGAIN\n");
                    continue;
                }
                c[xf][yf]=currpiece;
                c[xi][yi]=0;
            }
            ///FOR BLACK KING
            else if (currpiece==17)
            {
                if ((abs(xf-xi)==1&&yf==yi)||(abs(yf-yi)==1&&xf==xi)||(abs(xi-xf)==1&&abs(yi-yf)==1))
                {
                    int t=0;
                    if (c[xf][yf]!=0)
                    {
                        ///finpiece for knowing if piece at finalpos can be cut
                        int finpiece=returnpiece(xf,yf,&pos);
                        if (!borw(finpiece) || finpiece==1)
                            t=1;
                        else
                            pob--;
                    }
                    if (t)
                    {
                        printf("MOVE NOT POSSIBLE, TRY AGAIN\n");
                        continue;
                    }
                }
                else ///if out of range of knight's moving possibilities?
                {
                    printf("KING CANNOT MOVE TO THAT POSITION. TRY AGAIN\n");
                    continue;
                }
                c[xf][yf]=currpiece;
                c[xi][yi]=0;
            }
        }

        ///printing the chess board
        printf("\n      A   B   C   D   E   F   G   H");
        printf("\n    ---------------------------------\n");
        for (i=0;i<8;i++)
        {
            printf("  %d | ",8-i);
            for(j=0;j<8;j++)
                printf("%c | ",pieces[c[i][j]]);
            printf("%d ",8-i);
            printf("\n    ---------------------------------\n");
        }
        printf("      A   B   C   D   E   F   G   H\n");
        wb++;
    }
}
