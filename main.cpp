    #include <iostream>
    #include <graphics.h>
    #include <winbgim.h>
    #include <windows.h>
    #include <mmsystem.h>
    #include <stdio.h>
    #include <cmath>
    #include <time.h>
    #include <stdlib.h>

    using namespace std;

    int px1=601,py1=401,px2=1101,py2=701,a[30][30],b[30][30];
    short COL1=RED,COL2=YELLOW,marime=0,mus=0,lim=2;
    POINT p;
    bool first_time=true;

    void delet(int x[][30],int n)//Lucia Bejan
    {
        int i,j;
        for(i=1;i<=n;i++)
            for(j=1;j<=n;j++)
            x[i][j]=0;
    }

    void copiere(int x[][30],int y[][30],int n)//Lucia Bejan
    {
        for(int i=1;i<=n;i++)
            for(int j=1;j<=n;j++)
            x[i][j]=y[i][j];
    }

    void fil(int x[][30],int n,int i,int j,int tok)//Emanuel Iacob
    {
        x[i][j]=-1;
        if(i>1&&x[i-1][j]==tok) fil(x,n,i-1,j,tok);
        if(i<n&&x[i+1][j]==tok) fil(x,n,i+1,j,tok);
        if(j>1&&x[i][j-1]==tok) fil(x,n,i,j-1,tok);
        if(j<n&&x[i][j+1]==tok) fil(x,n,i,j+1,tok);
    }

    int verifsol(int x[][30],int n,int tok)//Emanuel Iacob
    {
        if(tok==1)
        {
            for(int j=1;j<=n;j++)
                if(x[n][j]==-1) return 1;
        }
        else
        {
            for(int i=1;i<=n;i++)
                if(x[i][n]==-1) return 1;
        }
        return 0;
    }

    void optionsmenu();
    void classicgraph();
    void mainmenu();
    void aboutmenu();

    void determinacerc(int x,int y,int xc[],int yc[],int k1,int k2,int &x1,int &y1,int &mi,int &mj)//Emanuel Iacob
    {
        cout<<"BUNICA";
        x1=y1=0;
       int mini=10000,i;
       for(i=1;i<=k1;i++)
        {
            unsigned rez=abs(xc[i]-x);
            if(rez<=mini)
            {
                mini=rez;
                x1=xc[i];
                mj=i;
            }
        }
        mini=10000;
        for(i=1;i<=k2;i++)
        {
            unsigned rez=abs(yc[i]-y);
            if(rez<=mini)
            {
                mini=rez;
                y1=yc[i];
                mi=i;

            }
        }
        /*determina cercul la care este click-ul curent*/
    }

    void classicgraph()//Emanuel Iacob (partea de algoritmica) , Lucia Bejan (partea grafica)
    {
        int xc[10],yc[10],xb[10],yb[10],k1=0,k2=0,k=0,k0=0;
        bool finish=false;
        cleardevice();
        if(mus==0) PlaySound(TEXT("in_game.wav"),NULL,SND_FILENAME|SND_LOOP|SND_ASYNC);
        int i,j;
        for(i=1;i<=7;i+=2)
            for(j=2;j<=6;j+=2)
            a[i][j]=1;
        for(i=2;i<=6;i+=2)
            for(j=1;j<=7;j+=2)
            a[i][j]=2;
            /*deseneaza toate cercurile*/
        if(lim==2)
        {settextstyle(2,0,20);
        outtextxy(10,10,"PLAYER 1'S TURN");
        rectangle(10,100,110,200);
        outtextxy(1150,10,"PLAYER 2'S TURN");
        }
        else if(lim==1)
        {
            settextstyle(2,0,20);
        outtextxy(10,10,"RAND JUCATOR 1");
        rectangle(10,100,110,200);
        outtextxy(1150,10,"RAND JUCATOR 2");
        }
        rectangle(1490,100,1590,200);
        setfillstyle(SOLID_FILL,COL1);
        for(j=400;j<=1150;j+=250)
        {
            for(i=300;i<=700;i+=200)
            {
            if(k0<3) yb[++k0]=i;
            circle(j,i,50);
            floodfill(j,i,WHITE);
            setcolor(COL1);
            circle(j,i,50);
            setcolor(WHITE);
            }
            xb[++k]=j;/*salveaza coordonatele lui x si y*/
        }
        setfillstyle(SOLID_FILL,COL2);
        for(j=525;j<=1025;j+=250)
        {
            for(i=200;i<=800;i+=200)
            {
            if(k2<4) yc[++k2]=i;
            circle(j,i,50);
            floodfill(j,i,WHITE);
            setcolor(COL2);
            circle(j,i,50);
            setcolor(WHITE);
            }
            xc[++k1]=j;
        }
        settextstyle(3,0,8);
        if(lim==2)
        {outtextxy(20,920,"BACK");}
        else if(lim==1)
        {
          settextstyle(3,0,6);
          outtextxy(20,920,"INAPOI");
          settextstyle(3,0,8);
        }
        rectangle(10,890,210,990);
        rectangle(1300,870,1590,930);
        rectangle(10,225,250,350);
        outtextxy(30,250,"UNDO");
        int fcx,fcy,scx,scy,x1,y1,rand=0;
        int draw_x1,draw_y1,draw_x2,draw_y2,mi1,mj1,mi2,mj2,pressedonce=1,moved=0;
        int cdx1,cdy1,cdx2,cdy2,cmi1,cmj1;
        fcx=fcy=scx=scy=-5;
        settextstyle(2,0,8);
        if(lim==2)
        outtextxy(1300,450,"Press first circle.");
        else if (lim==1) outtextxy(1300,450,"Apasati primul cerc.");
        while(true)
        {
        Sleep(75);
        settextstyle(2,0,8);
        if(rand==0)
        {
            setfillstyle(SOLID_FILL,BLACK);
            floodfill(1540,150,BLACK);
            setfillstyle(SOLID_FILL,COL1);
            circle(60,150,20);
            floodfill(60,150,WHITE);
        }
        else
        {
            setfillstyle(SOLID_FILL,BLACK);
            floodfill(60,150,BLACK);
            setfillstyle(SOLID_FILL,COL2);
            circle(1540,150,20);
            floodfill(1540,150,WHITE);/*pune cerculet in dreptului jucatorului curent*/
        }
        GetCursorPos(&p);
            if(GetAsyncKeyState(VK_LBUTTON))
            {
                if(mus==1) PlaySound(TEXT("click.wav"),NULL,SND_FILENAME|SND_ASYNC|SND_NOSTOP);
                if(p.x>=10&&p.x<=250&&p.y>=225&&p.y<=350&&!pressedonce&&moved&&!finish)//undo
                         {
                             pressedonce=1;
                             setlinestyle(0,0,3);
                             setcolor(BLACK);
                            if(cdy1<cdy2)
                            line(cdx1,cdy1+50,cdx2,cdy2-50);
                        else if(cdy1>cdy2)
                            line(cdx1,cdy1-50,cdx2,cdy2+50);
                            setcolor(BLACK);
                          if(cdx1<cdx2)
                            line(cdx1+50,cdy1,cdx2-50,cdy2);
                        else if(cdx1>cdx2)
                            line(cdx1-50,cdy1,cdx2+50,cdy2);
                            a[cmi1][cmj1]=0;
                            rand=1-rand;
                            setcolor(WHITE);
                            setlinestyle(0,0,1);
                         }
                if(p.x>=10&&p.x<=210&&p.y>=890&&p.y<=1050)
                {
                    first_time=true;
                    delet(a,7);
                    mainmenu();
                    break;
                }
                if(!finish)
                {
                if(rand==1&&getpixel(p.x,p.y)==COL2)
                {
                setcolor(BLACK);
                settextstyle(2,0,8);
                if(lim==1)
                {
                outtextxy(1310,900,"MISCARE INVALIDA!");
                }
                else if(lim==2)
                {
                     outtextxy(1310,900,"INVALID MOVE");
                }//Scrie cu negru "miscare invalida" ca sa dispara textul din casuta!
                setcolor(WHITE);
                if(getpixel(p.x,p.y)!=BLACK&&getpixel(p.x,p.y)!=WHITE)
                {
                    if(fcx==-5)/*daca nu s a apasat deja pt prima data*/
                    {
                        fcx=p.x;
                        fcy=p.y;
                        setcolor(BLACK);
                        if(lim==2)
                        outtextxy(1300,450,"Press first circle.");
                        else if (lim==1) outtextxy(1300,450,"Apasati primul cerc.");
                        setcolor(WHITE);
                        if(lim==2)
                        outtextxy(1300,500,"Press second circle.");
                        else if(lim==1) outtextxy(1300,500,"Apasati al doilea cerc.");
                    }
                    else if(getpixel(p.x,p.y)==COL2)
                {
                    scx=p.x;
                    scy=p.y;
                    determinacerc(fcx,fcy,xc,yc,k1,k2,draw_x1,draw_y1,mi1,mj1);
                    determinacerc(scx,scy,xc,yc,k1,k2,draw_x2,draw_y2,mi2,mj2);
                    mi1=1+2*(mi1-1);
                    mi2=1+2*(mi2-1);
                    mj1=2+2*(mj1-1);
                    mj2=2+2*(mj2-1);
                    mi1=(mi1+mi2)/2;
                    mj1=(mj1+mj2)/2;
                    if(((draw_x1==draw_x2)^(draw_y1==draw_y2))&&a[mi1][mj1]==0&&abs(mi1-mi2)<=2&&abs(mj1-mj2)<=2)
                        //xor verifica daca e sau pe aceeasi linie,sau pe acceasi coloana; a[mi1][mj1] verifica daca nu e deja o linie intre cele 2 cercuri;
                        //celelalte doua conditii asigura sa nu se traseze o linie intre doua cercuri care nu sunt alaturate
                    {
                        moved=1;
                        cdx1=draw_x1;
                        cdx2=draw_x2;
                        cdy1=draw_y1;
                        cdy2=draw_y2;
                        cmi1=mi1;
                        cmj1=mj1;
                        pressedonce=0;
                    a[mi1][mj1]=1;
                    setlinestyle(0,0,3);
                    setcolor(COL2);
                    if(draw_x1==draw_x2)
                    {
                        if(draw_y1<draw_y2)
                            line(draw_x1,draw_y1+50,draw_x2,draw_y2-50);
                        else
                            line(draw_x1,draw_y1-50,draw_x2,draw_y2+50);
                    }
                    else
                    {
                        if(draw_x1<draw_x2)
                            line(draw_x1+50,draw_y1,draw_x2-50,draw_y2);
                        else
                            line(draw_x1-50,draw_y1,draw_x2+50,draw_y2);

                    }
                    setlinestyle(0,0,1);
                    setcolor(WHITE);
                    rand=1-rand;
                    copiere(b,a,7);
                    fil(b,7,1,2,1);
                    fil(b,7,1,4,1);
                    fil(b,7,1,6,1);
                    if(verifsol(b,7,1))
                    {
                            settextstyle(2,0,20);
                            setcolor(COL2);
                            if(lim==2)
                                {
                                 outtextxy(550,10,"THE WINNER IS: P2");
                                }

                            else if(lim==1)
                                {
                                    outtextxy(540,10,"CASTIGATORUL ESTE: P2");
                                }
                            setcolor(WHITE);
                            PlaySound(NULL, 0, 0);
                            PlaySound(TEXT("win.wav"),NULL,SND_FILENAME|SND_ASYNC|SND_NOSTOP);
                            finish=true;
                    }
                        settextstyle(2,0,8);
                        setcolor(BLACK);
                         if(lim==2)
                        outtextxy(1300,500,"Press second circle.");
                        else if(lim==1) outtextxy(1300,500,"Apasati al doilea cerc.");
                        setcolor(WHITE);
                        if(lim==2)
                        outtextxy(1300,450,"Press first circle.");
                        else if (lim==1) outtextxy(1300,450,"Apasati primul cerc.");
                    }
                    else
                    {
                        setcolor(BLACK);
                         if(lim==2)
                        outtextxy(1300,500,"Press second circle.");
                        else if(lim==1) outtextxy(1300,500,"Apasati al doilea cerc.");
                        setcolor(WHITE);
                        if(lim==2)
                        outtextxy(1300,450,"Press first circle.");
                        else if (lim==1) outtextxy(1300,450,"Apasati primul cerc.");
                        settextstyle(2,0,8);
                        if(lim==1)
                {
                outtextxy(1310,900,"MISCARE INVALIDA!");
                }
                else if(lim==2)
                {
                     outtextxy(1310,900,"INVALID MOVE");
                }
                    }
                    fcx=fcy=-5;
                }
                }
                }
                else if(rand==0&&getpixel(p.x,p.y)==COL1)
                {
                setcolor(BLACK);
                settextstyle(2,0,8);
                if(lim==1)
                {
                outtextxy(1310,900,"MISCARE INVALIDA!");
                }
                else if(lim==2)
                {
                     outtextxy(1310,900,"INVALID MOVE");
                }
                setcolor(WHITE);
                if(getpixel(p.x,p.y)!=BLACK&&getpixel(p.x,p.y)!=WHITE)
                {
                    if(fcx==-5)
                    {
                        fcx=p.x;
                        fcy=p.y;
                        setcolor(BLACK);
                        if(lim==2)
                        outtextxy(1300,450,"Press first circle.");
                        else if (lim==1) outtextxy(1300,450,"Apasati primul cerc.");
                        setcolor(WHITE);
                         if(lim==2)
                        outtextxy(1300,500,"Press second circle.");
                        else if(lim==1) outtextxy(1300,500,"Apasati al doilea cerc.");
                    }
                    else if(getpixel(p.x,p.y)==COL1)
                {
                    scx=p.x;
                    scy=p.y;
                    determinacerc(fcx,fcy,xb,yb,k,k0,draw_x1,draw_y1,mi1,mj1);
                    determinacerc(scx,scy,xb,yb,k,k0,draw_x2,draw_y2,mi2,mj2);
                    mi1=2+2*(mi1-1);
                    mi2=2+2*(mi2-1);
                    mj1=1+2*(mj1-1);
                    mj2=1+2*(mj2-1);
                    mi1=(mi1+mi2)/2;
                    mj1=(mj1+mj2)/2;
                    if(((draw_x1==draw_x2)^(draw_y1==draw_y2))&&a[mi1][mj1]==0&&abs(mi1-mi2)<=2&&abs(mj1-mj2)<=2)
                    {
                        moved=1;
                        cdx1=draw_x1;
                        cdx2=draw_x2;
                        cdy1=draw_y1;
                        cdy2=draw_y2;
                        cmi1=mi1;
                        cmj1=mj1;
                        pressedonce=0;
                    a[mi1][mj1]=2;
                    for(i=1;i<=7;i++)
                            {
                                for(j=1;j<=7;j++)
                                    cout<<a[i][j]<<" ";
                                cout<<"\n";
                            }
                    setlinestyle(0,0,3);
                    setcolor(COL1);
                    if(draw_x1==draw_x2)
                    {
                        if(draw_y1<draw_y2)
                            line(draw_x1,draw_y1+50,draw_x2,draw_y2-50);
                        else
                            line(draw_x1,draw_y1-50,draw_x2,draw_y2+50);

                        if(p.x>=10&&p.x<=250&&p.y>=225&&p.y<=350)//undo

                        {
                            setcolor(BLACK);

                            if(draw_y1<draw_y2)
                            line(draw_x1,draw_y1+50,draw_x2,draw_y2-50);
                        else
                            line(draw_x1,draw_y1-50,draw_x2,draw_y2+50);

                        a[mi1][mj1]=0;
                        rand=1-rand;

                        }
                    }
                    else
                    {
                        if(draw_x1<draw_x2)
                            line(draw_x1+50,draw_y1,draw_x2-50,draw_y2);
                        else
                            line(draw_x1-50,draw_y1,draw_x2+50,draw_y2);

                            if(p.x>=10&&p.x<=250&&p.y>=225&&p.y<=350)//undo
                            {
                                setcolor(BLACK);

                        if(draw_x1<draw_x2)
                            line(draw_x1+50,draw_y1,draw_x2-50,draw_y2);
                        else
                            line(draw_x1-50,draw_y1,draw_x2+50,draw_y2);

                            a[mi1][mj1]=0;
                            rand=1-rand;
                            }
                    }
                    setlinestyle(0,0,1);
                    setcolor(WHITE);
                    rand=1-rand;
                    copiere(b,a,7);
                    fil(b,7,2,1,2);
                    fil(b,7,4,1,2);
                    fil(b,7,6,1,2);
                    if(verifsol(b,7,2))
                    {
                            settextstyle(2,0,20);
                            setcolor(COL1);
                            if(lim==2)
                                {
                                 outtextxy(550,10,"THE WINNER IS: P1");
                                }

                            else if(lim==1)
                                {
                                    outtextxy(540,10,"CASTIGATORUL ESTE: P1");
                                }
                            PlaySound(NULL, 0, 0);
                            PlaySound(TEXT("win.wav"),NULL,SND_FILENAME|SND_ASYNC|SND_NOSTOP);
                            setcolor(WHITE);
                            finish=true;
                    }
                        settextstyle(2,0,8);
                        setcolor(BLACK);
                         if(lim==2)
                        outtextxy(1300,500,"Press second circle.");
                        else if(lim==1) outtextxy(1300,500,"Apasati al doilea cerc.");
                        setcolor(WHITE);
                        if(lim==2)
                        outtextxy(1300,450,"Press first circle.");
                        else if (lim==1) outtextxy(1300,450,"Apasati primul cerc.");
                    }
                    else
                    {
                        setcolor(BLACK);
                         if(lim==2)
                        outtextxy(1300,500,"Press second circle.");
                        else if(lim==1) outtextxy(1300,500,"Apasati al doilea cerc.");
                        setcolor(WHITE);
                        if(lim==2)
                        outtextxy(1300,450,"Press first circle.");
                        else if (lim==1) outtextxy(1300,450,"Apasati primul cerc.");
                        settextstyle(2,0,8);
                        if(lim==1)
                {
                outtextxy(1310,900,"MISCARE INVALIDA!");
                }
                else if(lim==2)
                {
                     outtextxy(1310,900,"INVALID MOVE");
                }
                    }
                    fcx=fcy=-5;
                }
                }
                }
            }
            }
        }

    }

    void CPU_classicgraph()//Emanuel Iacob (partea de algoritmica) , Lucia Bejan (partea grafica)
    {
        srand(time(NULL));
        int xc[10],yc[10],xb[10],yb[10],k1=0,k2=0,k=0,k0=0;
        bool finish=false;
        cleardevice();
        if(mus==0) PlaySound(TEXT("in_game.wav"),NULL,SND_FILENAME|SND_LOOP|SND_ASYNC);
        int i,j;
        for(i=1;i<=7;i+=2)
            for(j=2;j<=6;j+=2)
            a[i][j]=1;
        for(i=2;i<=6;i+=2)
            for(j=1;j<=7;j+=2)
            a[i][j]=2;
            /*deseneaza toate cercurile*/
        if(lim==2)
        {settextstyle(2,0,20);
        outtextxy(10,10,"PLAYER 1'S TURN");
        rectangle(10,100,110,200);
        outtextxy(1150,10,"PLAYER 2'S TURN");
        }
        else if(lim==1)
        {
            settextstyle(2,0,20);
        outtextxy(10,10,"RAND JUCATOR 1");
        rectangle(10,100,110,200);
        outtextxy(1150,10,"RAND JUCATOR 2");
        }
        rectangle(1490,100,1590,200);
        setfillstyle(SOLID_FILL,COL1);
        for(j=400;j<=1150;j+=250)
        {
            for(i=300;i<=700;i+=200)
            {
            if(k0<3) yb[++k0]=i;
            circle(j,i,50);
            floodfill(j,i,WHITE);
            setcolor(COL1);
            circle(j,i,50);
            setcolor(WHITE);
            }
            xb[++k]=j;/*salveaza coordonatele lui x si y*/
        }
        setfillstyle(SOLID_FILL,COL2);
        for(j=525;j<=1025;j+=250)
        {
            for(i=200;i<=800;i+=200)
            {
            if(k2<4) yc[++k2]=i;
            circle(j,i,50);
            floodfill(j,i,WHITE);
            setcolor(COL2);
            circle(j,i,50);
            setcolor(WHITE);
            }
            xc[++k1]=j;
        }
        settextstyle(3,0,8);
        if(lim==2)
        {outtextxy(20,920,"BACK");}
        else if(lim==1)
        {
          settextstyle(3,0,6);
          outtextxy(20,920,"INAPOI");
          settextstyle(3,0,8);
        }
        rectangle(10,890,210,990);
        rectangle(1300,870,1590,930);
        rectangle(10,225,250,350);
        outtextxy(30,250,"UNDO");
        int fcx,fcy,scx,scy,x1,y1,ran=0;
        int draw_x1,draw_y1,draw_x2,draw_y2,mi1,mj1,mi2,mj2,pressedonce=1,moved=0;
        int cdx1,cdy1,cdx2,cdy2,cmi1,cmj1;
        int cpux1,cpuy1,cpux2,cpuy2,cpumi1,cpumj1;
        fcx=fcy=scx=scy=-5;
        settextstyle(2,0,8);
        if(lim==2)
        outtextxy(1300,450,"Press first circle.");
        else if (lim==1) outtextxy(1300,450,"Apasati primul cerc.");
        while(true)
        {
        Sleep(75);
        settextstyle(2,0,8);
        if(ran==0)
        {
            setfillstyle(SOLID_FILL,BLACK);
            floodfill(1540,150,BLACK);
            setfillstyle(SOLID_FILL,COL1);
            circle(60,150,20);
            floodfill(60,150,WHITE);
        }
        else
        {
            setfillstyle(SOLID_FILL,BLACK);
            floodfill(60,150,BLACK);
            setfillstyle(SOLID_FILL,COL2);
            circle(1540,150,20);
            floodfill(1540,150,WHITE);/*pune cerculet in dreptului jucatorului curent*/
        }
        GetCursorPos(&p);
        if(GetAsyncKeyState(VK_LBUTTON))
            {
                if(mus==1) PlaySound(TEXT("click.wav"),NULL,SND_FILENAME|SND_ASYNC|SND_NOSTOP);
                 if(p.x>=10&&p.x<=250&&p.y>=225&&p.y<=350&&!pressedonce&&moved&&!finish)//undo
                         {
                             pressedonce=1;
                             setlinestyle(0,0,3);
                             setcolor(BLACK);
                            if(cdy1<cdy2)
                            line(cdx1,cdy1+50,cdx2,cdy2-50);
                        else if(cdy1>cdy2)
                            line(cdx1,cdy1-50,cdx2,cdy2+50);
                            setcolor(BLACK);
                          if(cdx1<cdx2)
                            line(cdx1+50,cdy1,cdx2-50,cdy2);
                        else if(cdx1>cdx2)
                            line(cdx1-50,cdy1,cdx2+50,cdy2);
                            a[cmi1][cmj1]=0;
                             setcolor(BLACK);
                            if(cpuy1<cpuy2)
                            line(cpux1,cpuy1+50,cpux2,cpuy2-50);
                        else if(cpuy1>cpuy2)
                            line(cpux1,cpuy1-50,cpux2,cpuy2+50);
                            setcolor(BLACK);
                          if(cpux1<cpux2)
                            line(cpux1+50,cpuy1,cpux2-50,cpuy2);
                        else if(cpux1>cpux2)
                            line(cpux1-50,cpuy1,cpux2+50,cpuy2);
                            a[cpumi1][cpumj1]=0;
                            setcolor(WHITE);
                            setlinestyle(0,0,1);
                         }
                else if(p.x>=10&&p.x<=210&&p.y>=890&&p.y<=1050)
                {
                    first_time=true;
                    delet(a,7);
                    mainmenu();
                    break;
                }

                else if(!finish&&ran==0&&getpixel(p.x,p.y)==COL1)
                {
                setcolor(BLACK);
                settextstyle(2,0,8);
                if(lim==1)
                {
                outtextxy(1310,900,"MISCARE INVALIDA!");
                }
                else if(lim==2)
                {
                     outtextxy(1310,900,"INVALID MOVE");
                }
                setcolor(WHITE);
                if(getpixel(p.x,p.y)!=BLACK&&getpixel(p.x,p.y)!=WHITE)
                {
                    if(fcx==-5)
                    {
                        fcx=p.x;
                        fcy=p.y;
                        setcolor(BLACK);
                        if(lim==2)
                        outtextxy(1300,450,"Press first circle.");
                        else if (lim==1) outtextxy(1300,450,"Apasati primul cerc.");
                        setcolor(WHITE);
                        if(lim==2)
                        outtextxy(1300,500,"Press second circle.");
                        else if(lim==1) outtextxy(1300,500,"Apasati al doilea cerc.");
                    }
                    else if(getpixel(p.x,p.y)==COL1)
                {
                    scx=p.x;
                    scy=p.y;
                    determinacerc(fcx,fcy,xb,yb,k,k0,draw_x1,draw_y1,mi1,mj1);
                    determinacerc(scx,scy,xb,yb,k,k0,draw_x2,draw_y2,mi2,mj2);
                    mi1=2+2*(mi1-1);
                    mi2=2+2*(mi2-1);
                    mj1=1+2*(mj1-1);
                    mj2=1+2*(mj2-1);
                    mi1=(mi1+mi2)/2;
                    mj1=(mj1+mj2)/2;
                    if(((draw_x1==draw_x2)^(draw_y1==draw_y2))&&a[mi1][mj1]==0&&abs(mi1-mi2)<=2&&abs(mj1-mj2)<=2)
                    {
                        fcx=fcy=-5;
                        moved=1;
                        cdx1=draw_x1;
                        cdx2=draw_x2;
                        cdy1=draw_y1;
                        cdy2=draw_y2;
                        cmi1=mi1;
                        cmj1=mj1;
                        pressedonce=0;
                    a[mi1][mj1]=2;
                    setlinestyle(0,0,3);
                    setcolor(COL1);
                    if(draw_x1==draw_x2)
                    {
                        if(draw_y1<draw_y2)
                            line(draw_x1,draw_y1+50,draw_x2,draw_y2-50);
                        else
                            line(draw_x1,draw_y1-50,draw_x2,draw_y2+50);
                    }
                    else
                    {
                        if(draw_x1<draw_x2)
                            line(draw_x1+50,draw_y1,draw_x2-50,draw_y2);
                        else
                            line(draw_x1-50,draw_y1,draw_x2+50,draw_y2);
                    }
                    }
                    setlinestyle(0,0,1);
                    setcolor(WHITE);
                    ran=1-ran;
                    copiere(b,a,7);
                    fil(b,7,2,1,2);
                    fil(b,7,4,1,2);
                    fil(b,7,6,1,2);
                    if(verifsol(b,7,2))
                    {
                            settextstyle(2,0,20);
                            setcolor(COL1);
                            if(lim==2)
                                {
                                 outtextxy(550,10,"THE WINNER IS: P1");
                                }

                            else if(lim==1)
                                {
                                    outtextxy(540,10,"CASTIGATORUL ESTE: P1");
                                }
                            PlaySound(NULL, 0, 0);
                            PlaySound(TEXT("win.wav"),NULL,SND_FILENAME|SND_ASYNC|SND_NOSTOP);
                            setcolor(WHITE);
                            finish=true;
                    }
                        settextstyle(2,0,8);
                        setcolor(BLACK);
                        if(lim==2)
                        outtextxy(1300,500,"Press second circle.");
                        else if(lim==1) outtextxy(1300,500,"Apasati al doilea cerc.");
                        setcolor(WHITE);
                        if(lim==2)
                        outtextxy(1300,450,"Press first circle.");
                        else if (lim==1) outtextxy(1300,450,"Apasati primul cerc.");
                    }
                    else
                    {
                        setcolor(BLACK);
                        if(lim==2)
                        outtextxy(1300,500,"Press second circle.");
                        else if(lim==1) outtextxy(1300,500,"Apasati al doilea cerc.");
                        setcolor(WHITE);
                        if(lim==2)
                        outtextxy(1300,450,"Press first circle.");
                        else if (lim==1) outtextxy(1300,450,"Apasati primul cerc.");
                        settextstyle(2,0,8);
                if(lim==1)
                {
                outtextxy(1310,900,"MISCARE INVALIDA!");
                }
                else if(lim==2)
                {
                     outtextxy(1310,900,"INVALID MOVE");
                }
                    }

                }
                }
            }
        else if(!finish&&ran==1)
        {
            int plasat=0;
            while(plasat==0)
            {
                int draw_x1,draw_y1,draw_x2,draw_y2,mi1,mj1,mi2,mj2;
                mj1=rand()%3+1;
                mi1=rand()%4+1;
                draw_x1=xc[mj1];
                draw_y1=yc[mi1];
                int xy=rand()%2;
                if(xy==0)
                    {
                        mj2=mj1;
                        int plusminus=rand()%2;
                        if(plusminus==0)
                        {
                            if(mi1 + 1 > 4) mi2=1;
                            else mi2=mi1+1;
                        }
                        else
                        {
                            if(mi1 - 1 < 1) mi2=4;
                            else mi2=mi1+1;
                        }
                    }
                    else
                    {
                        mi2=mi1;
                        int plusminus=rand()%2;
                        if(plusminus==0)
                        {
                            if(mj1 + 1 > 3) mj2=1;
                            else mj2=mj1+1;
                        }
                        else
                        {
                            if(mj1 - 1 < 1) mj2=3;
                            else mi2=mj1+1;
                        }
                    }
                    int ok;
                    if(mj2>=1&&mj2<=3&&mi2>=1&&mi2<=4)ok=1;
                    else ok=0;
                    if(ok)
                    {
                    draw_x2=xc[mj2];
                    draw_y2=yc[mi2];
                    mi1=1+2*(mi1-1);
                    mi2=1+2*(mi2-1);
                    mj1=2+2*(mj1-1);
                    mj2=2+2*(mj2-1);
                    mi1=(mi1+mi2)/2;
                    mj1=(mj1+mj2)/2;
                    if(((draw_x1==draw_x2)^(draw_y1==draw_y2))&&a[mi1][mj1]==0&&abs(mi1-mi2)<=2&&abs(mj1-mj2)<=2)
                    {
                        moved=1;
                        cpux1=draw_x1;
                        cpux2=draw_x2;
                        cpuy1=draw_y1;
                        cpuy2=draw_y2;
                        cpumi1=mi1;
                        cpumj1=mj1;
                        pressedonce=0;
                    plasat=1;
                    a[mi1][mj1]=1;
                    setlinestyle(0,0,3);
                    setcolor(COL2);
                    if(draw_x1==draw_x2)
                    {
                        if(draw_y1<draw_y2)
                            line(draw_x1,draw_y1+50,draw_x2,draw_y2-50);
                        else
                            line(draw_x1,draw_y1-50,draw_x2,draw_y2+50);

                    }
                    else
                    {
                        if(draw_x1<draw_x2)
                            line(draw_x1+50,draw_y1,draw_x2-50,draw_y2);
                        else
                            line(draw_x1-50,draw_y1,draw_x2+50,draw_y2);
                    }
                    setlinestyle(0,0,1);
                    setcolor(WHITE);
                    ran=1-ran;
                    copiere(b,a,7);
                    fil(b,7,1,2,1);
                    fil(b,7,1,4,1);
                    fil(b,7,1,6,1);
                    if(verifsol(b,7,1))
                    {
                            settextstyle(2,0,20);
                            setcolor(COL2);
                            if(lim==2)
                                {
                                 outtextxy(550,10,"THE WINNER IS: P2");
                                }

                            else if(lim==1)
                                {
                                    outtextxy(540,10,"CASTIGATORUL ESTE: P2");
                                }
                            PlaySound(NULL, 0, 0);
                            PlaySound(TEXT("lose.wav"),NULL,SND_FILENAME|SND_ASYNC|SND_NOSTOP);
                            setcolor(WHITE);
                            finish=true;
                    }
                }
            }
            }
            }
        }
    }

    void CPU_biggergraph()//Implementarea 11x11 in grafica realizata de Lucia Bejan
    {
        srand(time(NULL));
        int xc[10],yc[10],xb[10],yb[10],k1=0,k2=0,k=0,k0=0;
        bool finish=false;
        cleardevice();
        if(mus==0) PlaySound(TEXT("in_game.wav"),NULL,SND_FILENAME|SND_LOOP|SND_ASYNC);
        int i,j;
        for(i=1;i<=11;i+=2)
            for(j=2;j<=10;j+=2)
            a[i][j]=1;
        for(i=2;i<=10;i+=2)
            for(j=1;j<=11;j+=2)
            a[i][j]=2;
            /*deseneaza toate cercurile*/
        if(lim==2)
        {settextstyle(2,0,20);
        outtextxy(10,10,"PLAYER 1'S TURN");
        rectangle(10,100,110,200);
        outtextxy(1150,10,"PLAYER 2'S TURN");
        }
        else if(lim==1)
        {
            settextstyle(2,0,20);
        outtextxy(10,10,"RAND JUCATOR 1");
        rectangle(10,100,110,200);
        outtextxy(1150,10,"RAND JUCATOR 2");
        }
        rectangle(1490,100,1590,200);
        setfillstyle(SOLID_FILL,COL1);
        for(j=380;j<=1180;j+=150)
        {
            for(i=280;i<=900;i+=150)
            {
            if(k0<5) yb[++k0]=i;
            circle(j,i,30);
            floodfill(j,i,WHITE);
            setcolor(COL1);
            circle(j,i,30);
            setcolor(WHITE);
            }
            xb[++k]=j;/*salveaza coordonatele lui x si y*/
        }
        setfillstyle(SOLID_FILL,COL2);
        for(j=450;j<=1150;j+=150)
        {
            for(i=200;i<=950;i+=150)
            {
            if(k2<6) yc[++k2]=i;
            circle(j,i,30);
            floodfill(j,i,WHITE);
            setcolor(COL2);
            circle(j,i,30);
            setcolor(WHITE);
            }
            xc[++k1]=j;
        }
        settextstyle(3,0,8);
        if(lim==2)
        {outtextxy(20,920,"BACK");}
        else if(lim==1)
        {
          settextstyle(3,0,6);
          outtextxy(20,920,"INAPOI");
          settextstyle(3,0,8);
        }
        rectangle(10,890,210,990);
        rectangle(1300,870,1590,930);
        rectangle(10,225,250,350);
        outtextxy(30,250,"UNDO");
        int fcx,fcy,scx,scy,x1,y1,ran=0;
        int draw_x1,draw_y1,draw_x2,draw_y2,mi1,mj1,mi2,mj2,pressedonce=1,moved=0;
        int cdx1,cdy1,cdx2,cdy2,cmi1,cmj1;
        int cpux1,cpuy1,cpux2,cpuy2,cpumi1,cpumj1;
        fcx=fcy=scx=scy=-5;
        settextstyle(2,0,8);
        if(lim==2)
        outtextxy(1300,450,"Press first circle.");
        else if (lim==1) outtextxy(1300,450,"Apasati primul cerc.");
        while(true)
        {
        Sleep(75);
        settextstyle(2,0,8);
        if(ran==0)
        {
            setfillstyle(SOLID_FILL,BLACK);
            floodfill(1540,150,BLACK);
            setfillstyle(SOLID_FILL,COL1);
            circle(60,150,20);
            floodfill(60,150,WHITE);
        }
        else
        {
            setfillstyle(SOLID_FILL,BLACK);
            floodfill(60,150,BLACK);
            setfillstyle(SOLID_FILL,COL2);
            circle(1540,150,20);
            floodfill(1540,150,WHITE);/*pune cerculet in dreptului jucatorului curent*/
        }
        GetCursorPos(&p);
            if(GetAsyncKeyState(VK_LBUTTON))
            {
                if(mus==1) PlaySound(TEXT("click.wav"),NULL,SND_FILENAME|SND_ASYNC|SND_NOSTOP);
                 if(p.x>=10&&p.x<=250&&p.y>=225&&p.y<=350&&!pressedonce&&moved&&!finish)//undo
                         {
                             pressedonce=1;
                             setlinestyle(0,0,3);
                             setcolor(BLACK);
                            if(cdy1<cdy2)
                            line(cdx1,cdy1+30,cdx2,cdy2-30);
                        else if(cdy1>cdy2)
                            line(cdx1,cdy1-30,cdx2,cdy2+30);
                            setcolor(BLACK);
                          if(cdx1<cdx2)
                            line(cdx1+30,cdy1,cdx2-30,cdy2);
                        else if(cdx1>cdx2)
                            line(cdx1-30,cdy1,cdx2+30,cdy2);
                            a[cmi1][cmj1]=0;
                             setcolor(BLACK);
                            if(cpuy1<cpuy2)
                            line(cpux1,cpuy1+30,cpux2,cpuy2-30);
                        else if(cpuy1>cpuy2)
                            line(cpux1,cpuy1-30,cpux2,cpuy2+30);
                            setcolor(BLACK);
                          if(cpux1<cpux2)
                            line(cpux1+30,cpuy1,cpux2-30,cpuy2);
                        else if(cpux1>cpux2)
                            line(cpux1-0,cpuy1,cpux2+30,cpuy2);
                            a[cpumi1][cpumj1]=0;
                            setcolor(WHITE);
                            setlinestyle(0,0,1);
                         }
                if(p.x>=10&&p.x<=210&&p.y>=890&&p.y<=1050)
                {
                    first_time=true;
                    delet(a,11);
                    mainmenu();
                    break;
                }
                else if(ran==0&&getpixel(p.x,p.y)==COL1)
                {
                setcolor(BLACK);
                settextstyle(2,0,8);
                if(lim==1)
                {
                outtextxy(1310,900,"MISCARE INVALIDA!");
                }
                else if(lim==2)
                {
                     outtextxy(1310,900,"INVALID MOVE");
                }
                setcolor(WHITE);
                if(getpixel(p.x,p.y)!=BLACK&&getpixel(p.x,p.y)!=WHITE)
                {
                    if(fcx==-5)
                    {
                        setcolor(BLACK);
                        if(lim==2)
                        outtextxy(1300,450,"Press first circle.");
                        else if (lim==1) outtextxy(1300,450,"Apasati primul cerc.");
                        setcolor(WHITE);
                        if(lim==2)
                        outtextxy(1300,500,"Press second circle.");
                        else if(lim==1) outtextxy(1300,500,"Apasati al doilea cerc.");
                        fcx=p.x;
                        fcy=p.y;
                    }
                    else if(getpixel(p.x,p.y)==COL1)
                {
                    scx=p.x;
                    scy=p.y;
                    determinacerc(fcx,fcy,xb,yb,k,k0,draw_x1,draw_y1,mi1,mj1);
                    determinacerc(scx,scy,xb,yb,k,k0,draw_x2,draw_y2,mi2,mj2);
                    mi1=2+2*(mi1-1);
                    mi2=2+2*(mi2-1);
                    mj1=1+2*(mj1-1);
                    mj2=1+2*(mj2-1);
                    mi1=(mi1+mi2)/2;
                    mj1=(mj1+mj2)/2;
                    if(((draw_x1==draw_x2)^(draw_y1==draw_y2))&&a[mi1][mj1]==0&&abs(mi1-mi2)<=2&&abs(mj1-mj2)<=2)
                    {
                    fcx=fcy=-5;
                        moved=1;
                        cdx1=draw_x1;
                        cdx2=draw_x2;
                        cdy1=draw_y1;
                        cdy2=draw_y2;
                        cmi1=mi1;
                        cmj1=mj1;
                        pressedonce=0;
                    a[mi1][mj1]=2;
                    setlinestyle(0,0,3);
                    setcolor(COL1);
                    if(draw_x1==draw_x2)
                    {
                        if(draw_y1<draw_y2)
                            line(draw_x1,draw_y1+30,draw_x2,draw_y2-30);
                        else
                            line(draw_x1,draw_y1-30,draw_x2,draw_y2+30);

                            if(p.x>=10&&p.x<=250&&p.y>=225&&p.y<=350)//undo
                            {
                                setcolor(BLACK);

                        if(draw_y1<draw_y2)
                            line(draw_x1,draw_y1+30,draw_x2,draw_y2-30);
                        else
                            line(draw_x1,draw_y1-30,draw_x2,draw_y2+30);

                        a[mi1][mj1]=0;
                        ran=1-ran;

                            }
                    }
                    else
                    {
                        if(draw_x1<draw_x2)
                            line(draw_x1+30,draw_y1,draw_x2-30,draw_y2);
                        else
                            line(draw_x1-30,draw_y1,draw_x2+30,draw_y2);

                       if(p.x>=10&&p.x<=250&&p.y>=225&&p.y<=350)//undo
                       {
                           setcolor(BLACK);

                           if(draw_x1<draw_x2)
                            line(draw_x1+30,draw_y1,draw_x2-30,draw_y2);
                        else

                            line(draw_x1-30,draw_y1,draw_x2+30,draw_y2);

                        a[mi1][mj1]=0;
                        ran=1-ran;
                       }
                    }
                    setlinestyle(0,0,1);
                    setcolor(WHITE);
                    ran=1-ran;
                    copiere(b,a,11);
                    fil(b,11,2,1,2);
                    fil(b,11,4,1,2);
                    fil(b,11,6,1,2);
                    fil(b,11,8,1,2);
                    fil(b,11,10,1,2);
                    if(verifsol(b,11,2))
                    {
                            settextstyle(2,0,20);
                            setcolor(COL1);
                            if(lim==2)
                                {
                                 outtextxy(550,10,"THE WINNER IS: P1");
                                }

                            else if(lim==1)
                                {
                                    outtextxy(540,10,"CASTIGATORUL ESTE: P1");
                                }
                            PlaySound(NULL, 0, 0);
                            PlaySound(TEXT("win.wav"),NULL,SND_FILENAME|SND_ASYNC|SND_NOSTOP);
                            setcolor(WHITE);
                            finish=true;
                    }
                    settextstyle(2,0,8);
                    setcolor(BLACK);
                    if(lim==2)
                    outtextxy(1300,500,"Press second circle.");
                    else if(lim==1) outtextxy(1300,500,"Apasati al doilea cerc.");
                    setcolor(WHITE);
                    if(lim==2)
                    outtextxy(1300,450,"Press first circle.");
                    else if (lim==1) outtextxy(1300,450,"Apasati primul cerc.");
                    }
                    else
                    {
                        setcolor(BLACK);
                        if(lim==2)
                        outtextxy(1300,500,"Press second circle.");
                        else if(lim==1) outtextxy(1300,500,"Apasati al doilea cerc.");
                        setcolor(WHITE);
                        if(lim==2)
                        outtextxy(1300,450,"Press first circle.");
                        else if (lim==1) outtextxy(1300,450,"Apasati primul cerc.");
                        settextstyle(2,0,8);
                        if(lim==1)
                {
                outtextxy(1310,900,"MISCARE INVALIDA!");
                }
                else if(lim==2)
                {
                     outtextxy(1310,900,"INVALID MOVE");
                }
                    }
                    fcx=fcy=-5;
                }
                }
                }
                }
        else if(!finish&&ran==1)
        {
            int plasat=0;
            while(plasat==0)
            {
                int draw_x1,draw_y1,draw_x2,draw_y2,mi1,mj1,mi2,mj2;
                mj1=rand()%5+1;
                mi1=rand()%6+1;
                draw_x1=xc[mj1];
                draw_y1=yc[mi1];
                int xy=rand()%2;
                if(xy==0)
                    {
                        mj2=mj1;
                        int plusminus=rand()%2;
                        if(plusminus==0)
                        {
                            if(mi1 + 1 > 6) mi2=1;
                            else mi2=mi1+1;
                        }
                        else
                        {
                            if(mi1 - 1 < 1) mi2=4;
                            else mi2=mi1+1;
                        }
                    }
                    else
                    {
                        mi2=mi1;
                        int plusminus=rand()%2;
                        if(plusminus==0)
                        {
                            if(mj1 + 1 > 7) mj2=1;
                            else mj2=mj1+1;
                        }
                        else
                        {
                            if(mj1 - 1 < 1) mj2=3;
                            else mi2=mj1+1;
                        }
                    }
                    int ok;
                    if(mj2>=1&&mj2<=5&&mi2>=1&&mi2<=6)ok=1;
                    else ok=0;
                    if(ok)
                    {
                    draw_x2=xc[mj2];
                    draw_y2=yc[mi2];
                    mi1=1+2*(mi1-1);
                    mi2=1+2*(mi2-1);
                    mj1=2+2*(mj1-1);
                    mj2=2+2*(mj2-1);
                    mi1=(mi1+mi2)/2;
                    mj1=(mj1+mj2)/2;
                    if(((draw_x1==draw_x2)^(draw_y1==draw_y2))&&a[mi1][mj1]==0&&abs(mi1-mi2)<=2&&abs(mj1-mj2)<=2)
                    {
                        moved=1;
                        cpux1=draw_x1;
                        cpux2=draw_x2;
                        cpuy1=draw_y1;
                        cpuy2=draw_y2;
                        cpumi1=mi1;
                        cpumj1=mj1;
                        pressedonce=0;
                    plasat=1;
                    a[mi1][mj1]=1;
                    setlinestyle(0,0,3);
                    setcolor(COL2);
                    if(draw_x1==draw_x2)
                    {
                        if(draw_y1<draw_y2)
                            line(draw_x1,draw_y1+30,draw_x2,draw_y2-30);
                        else
                            line(draw_x1,draw_y1-30,draw_x2,draw_y2+30);

                    if(p.x>=10&&p.x<=250&&p.y>=225&&p.y<=350)//undo

                       { setcolor(BLACK);
                       if(draw_y1<draw_y2)
                            line(draw_x1,draw_y1+30,draw_x2,draw_y2-30);
                        else
                            line(draw_x1,draw_y1-30,draw_x2,draw_y2+30);

                    a[mi1][mj1]=0;
                    ran=1-ran;
                       }

                    }
                    else
                    {
                        if(draw_x1<draw_x2)
                            line(draw_x1+30,draw_y1,draw_x2-30,draw_y2);
                        else
                            line(draw_x1-30,draw_y1,draw_x2+30,draw_y2);

                    if(p.x>=10&&p.x<=250&&p.y>=225&&p.y<=350)//undo
                    {    setcolor(BLACK);

                        if(draw_x1<draw_x2)
                            line(draw_x1+30,draw_y1,draw_x2-30,draw_y2);
                        else
                            line(draw_x1-30,draw_y1,draw_x2+30,draw_y2);

                       a[mi1][mj1]=0;
                       ran=1-ran;
                    }

                    }
                    setlinestyle(0,0,1);
                    setcolor(WHITE);
                    ran=1-ran;
                    copiere(b,a,11);
                    fil(b,11,1,2,1);
                    fil(b,11,1,4,1);
                    fil(b,11,1,6,1);
                    fil(b,11,1,8,1);
                    fil(b,11,1,10,1);
                    if(verifsol(b,11,1))
                    {
                            settextstyle(2,0,20);
                            setcolor(COL2);
                            if(lim==2)
                                {
                                 outtextxy(550,10,"THE WINNER IS: P2");
                                }

                            else if(lim==1)
                                {
                                    outtextxy(540,10,"CASTIGATORUL ESTE: P2");
                                }
                            PlaySound(NULL, 0, 0);
                            PlaySound(TEXT("lose.wav"),NULL,SND_FILENAME|SND_ASYNC|SND_NOSTOP);
                            setcolor(WHITE);
                            finish=true;
                    }
                }
            }
            }
            }
        }
    }


    void biggergraph()//Implementarea 11x11 in grafica realizata de Lucia Bejan
    {
        int xc[10],yc[10],xb[10],yb[10],k1=0,k2=0,k=0,k0=0;
        bool finish=false;
        cleardevice();
        if(mus==0) PlaySound(TEXT("in_game.wav"),NULL,SND_FILENAME|SND_LOOP|SND_ASYNC);
        int i,j;
        for(i=1;i<=11;i+=2)
            for(j=2;j<=10;j+=2)
            a[i][j]=1;
        for(i=2;i<=10;i+=2)
            for(j=1;j<=11;j+=2)
            a[i][j]=2;
            /*deseneaza toate cercurile*/
        if(lim==2)
        {settextstyle(2,0,20);
        outtextxy(10,10,"PLAYER 1'S TURN");
        rectangle(10,100,110,200);
        outtextxy(1150,10,"PLAYER 2'S TURN");
        }
        else if(lim==1)
        {
            settextstyle(2,0,20);
        outtextxy(10,10,"RAND JUCATOR 1");
        rectangle(10,100,110,200);
        outtextxy(1150,10,"RAND JUCATOR 2");
        }
        rectangle(1490,100,1590,200);
        setfillstyle(SOLID_FILL,COL1);
        for(j=380;j<=1180;j+=150)
        {
            for(i=280;i<=900;i+=150)
            {
            if(k0<5) yb[++k0]=i;
            circle(j,i,30);
            floodfill(j,i,WHITE);
            setcolor(COL1);
            circle(j,i,30);
            setcolor(WHITE);
            }
            xb[++k]=j;/*salveaza coordonatele lui x si y*/
        }
        setfillstyle(SOLID_FILL,COL2);
        for(j=450;j<=1150;j+=150)
        {
            for(i=200;i<=950;i+=150)
            {
            if(k2<6) yc[++k2]=i;
            circle(j,i,30);
            floodfill(j,i,WHITE);
            setcolor(COL2);
            circle(j,i,30);
            setcolor(WHITE);
            }
            xc[++k1]=j;
        }
        settextstyle(3,0,8);
        if(lim==2)
        {outtextxy(20,920,"BACK");}
        else if(lim==1)
        {
          settextstyle(3,0,6);
          outtextxy(20,920,"INAPOI");
          settextstyle(3,0,8);
        }
        rectangle(10,890,210,990);
        rectangle(1300,870,1590,930);
        rectangle(10,225,250,350);
        outtextxy(30,250,"UNDO");
        int fcx,fcy,scx,scy,x1,y1,rand=0;
        int draw_x1,draw_y1,draw_x2,draw_y2,mi1,mj1,mi2,mj2,pressedonce=1,moved=0;
        int cdx1,cdy1,cdx2,cdy2,cmi1,cmj1;
        fcx=fcy=scx=scy=-5;
        settextstyle(2,0,8);
        if(lim==2)
        outtextxy(1300,450,"Press first circle.");
        else if (lim==1) outtextxy(1300,450,"Apasati primul cerc.");
        while(true)
        {
        Sleep(75);
        settextstyle(2,0,8);
        if(rand==0)
        {
            setfillstyle(SOLID_FILL,BLACK);
            floodfill(1540,150,BLACK);
            setfillstyle(SOLID_FILL,COL1);
            circle(60,150,20);
            floodfill(60,150,WHITE);
        }
        else
        {
            setfillstyle(SOLID_FILL,BLACK);
            floodfill(60,150,BLACK);
            setfillstyle(SOLID_FILL,COL2);
            circle(1540,150,20);
            floodfill(1540,150,WHITE);/*pune cerculet in dreptului jucatorului curent*/
        }
        GetCursorPos(&p);
            if(GetAsyncKeyState(VK_LBUTTON))
            {
                if(mus==1) PlaySound(TEXT("click.wav"),NULL,SND_FILENAME|SND_ASYNC|SND_NOSTOP);
                if(p.x>=10&&p.x<=250&&p.y>=225&&p.y<=350&&!pressedonce&&moved&&!finish)//undo
                         {
                             pressedonce=1;
                             setlinestyle(0,0,3);
                             setcolor(BLACK);
                            if(cdy1<cdy2)
                            line(cdx1,cdy1+30,cdx2,cdy2-30);
                        else if(cdy1>cdy2)
                            line(cdx1,cdy1-30,cdx2,cdy2+30);
                            setcolor(BLACK);
                          if(cdx1<cdx2)
                            line(cdx1+30,cdy1,cdx2-30,cdy2);
                        else if(cdx1>cdx2)
                            line(cdx1-30,cdy1,cdx2+30,cdy2);
                            a[cmi1][cmj1]=0;
                            rand=1-rand;
                            setcolor(WHITE);
                            setlinestyle(0,0,1);
                         }
                if(p.x>=10&&p.x<=210&&p.y>=890&&p.y<=1050)
                {
                    first_time=true;
                    delet(a,11);
                    mainmenu();
                    break;
                }
                if(!finish)
                {
                if(rand==1&&getpixel(p.x,p.y)==COL2)
                {
                setcolor(BLACK);
                settextstyle(2,0,8);
                if(lim==1)
                {
                outtextxy(1310,900,"MISCARE INVALIDA!");
                }
                else if(lim==2)
                {
                     outtextxy(1310,900,"INVALID MOVE");
                } //Scrie cu negru "miscare invalida" ca sa dispara textul din casuta!
                setcolor(WHITE);
                if(getpixel(p.x,p.y)!=BLACK&&getpixel(p.x,p.y)!=WHITE)
                {
                    if(fcx==-5)/*daca nu s a apasat deja pt prima data*/
                    {
                        setcolor(BLACK);
                        if(lim==2)
                        outtextxy(1300,450,"Press first circle.");
                        else if (lim==1) outtextxy(1300,450,"Apasati primul cerc.");
                        setcolor(WHITE);
                        if(lim==2)
                        outtextxy(1300,500,"Press second circle.");
                        else if(lim==1) outtextxy(1300,500,"Apasati al doilea cerc.");
                        fcx=p.x;
                        fcy=p.y;
                    }
                    else if(getpixel(p.x,p.y)==COL2)
                {
                    scx=p.x;
                    scy=p.y;
                    determinacerc(fcx,fcy,xc,yc,k1,k2,draw_x1,draw_y1,mi1,mj1);
                    determinacerc(scx,scy,xc,yc,k1,k2,draw_x2,draw_y2,mi2,mj2);
                    mi1=1+2*(mi1-1);
                    mi2=1+2*(mi2-1);
                    mj1=2+2*(mj1-1);
                    mj2=2+2*(mj2-1);
                    mi1=(mi1+mi2)/2;
                    mj1=(mj1+mj2)/2;
                    if(((draw_x1==draw_x2)^(draw_y1==draw_y2))&&a[mi1][mj1]==0&&abs(mi1-mi2)<=2&&abs(mj1-mj2)<=2)
                        //xor verifica daca e sau pe aceeasi linie,sau pe acceasi coloana; a[mi1][mj1] verifica daca nu e deja o linie intre cele 2 cercuri;
                        //celelalte doua conditii asigura sa nu se traseze o linie intre doua cercuri care nu sunt alaturate
                    {
                        moved=1;
                        cdx1=draw_x1;
                        cdx2=draw_x2;
                        cdy1=draw_y1;
                        cdy2=draw_y2;
                        cmi1=mi1;
                        cmj1=mj1;
                        pressedonce=0;
                    a[mi1][mj1]=1;
                    setlinestyle(0,0,3);
                    setcolor(COL2);
                    if(draw_x1==draw_x2)
                    {
                        if(draw_y1<draw_y2)
                            line(draw_x1,draw_y1+30,draw_x2,draw_y2-30);
                        else
                            line(draw_x1,draw_y1-30,draw_x2,draw_y2+30);

                        if(p.x>=10&&p.x<=250&&p.y>=225&&p.y<=350)//undo
                        {
                            setcolor(BLACK);

                            if(draw_y1<draw_y2)
                            line(draw_x1,draw_y1+30,draw_x2,draw_y2-30);
                        else
                            line(draw_x1,draw_y1-30,draw_x2,draw_y2+30);

                            a[mi1][mj1]=0;
                            rand=1-rand;

                        }

                    }
                    else
                    {
                        if(draw_x1<draw_x2)
                            line(draw_x1+30,draw_y1,draw_x2-30,draw_y2);
                        else
                            line(draw_x1-30,draw_y1,draw_x2+30,draw_y2);

                        if(p.x>=10&&p.x<=250&&p.y>=225&&p.y<=350)//undo
                        {    setcolor(BLACK);

                             if(draw_x1<draw_x2)
                            line(draw_x1+30,draw_y1,draw_x2-30,draw_y2);
                        else
                            line(draw_x1-30,draw_y1,draw_x2+30,draw_y2);

                           a[mi1][mj1]=0;
                           rand=1-rand;
                        }

                    }
                    setlinestyle(0,0,1);
                    setcolor(WHITE);
                    rand=1-rand;
                    copiere(b,a,11);
                    fil(b,11,1,2,1);
                    fil(b,11,1,4,1);
                    fil(b,11,1,6,1);
                    fil(b,11,1,8,1);
                    fil(b,11,1,10,1);
                    if(verifsol(b,11,1))
                    {
                            settextstyle(2,0,20);
                            setcolor(COL2);
                            if(lim==2)
                                {
                                 outtextxy(550,10,"THE WINNER IS: P2");
                                }

                            else if(lim==1)
                                {
                                    outtextxy(540,10,"CASTIGATORUL ESTE: P2");
                                }
                            PlaySound(NULL, 0, 0);
                            PlaySound(TEXT("win.wav"),NULL,SND_FILENAME|SND_ASYNC|SND_NOSTOP);
                            setcolor(WHITE);
                            finish=true;
                    }
                        settextstyle(2,0,8);
                        setcolor(BLACK);
                        if(lim==2)
                        outtextxy(1300,500,"Press second circle.");
                        else if(lim==1) outtextxy(1300,500,"Apasati al doilea cerc.");
                        setcolor(WHITE);
                        if(lim==2)
                        outtextxy(1300,450,"Press first circle.");
                        else if (lim==1) outtextxy(1300,450,"Apasati primul cerc.");
                    }
                    else
                    {
                        setcolor(BLACK);
                        if(lim==2)
                        outtextxy(1300,500,"Press second circle.");
                        else if(lim==1) outtextxy(1300,500,"Apasati al doilea cerc.");
                        setcolor(WHITE);
                        if(lim==2)
                        outtextxy(1300,450,"Press first circle.");
                        else if (lim==1) outtextxy(1300,450,"Apasati primul cerc.");
                        settextstyle(2,0,8);
                        if(lim==1)
                {
                outtextxy(1310,900,"MISCARE INVALIDA!");
                }
                else if(lim==2)
                {
                     outtextxy(1310,900,"INVALID MOVE");
                }
                    }
                    fcx=fcy=-5;
                }
                }
                }
                else if(rand==0&&getpixel(p.x,p.y)==COL1)
                {
                setcolor(BLACK);
                settextstyle(2,0,8);
                outtextxy(1310,900,"MISCARE INVALIDA!");
                setcolor(WHITE);
                if(getpixel(p.x,p.y)!=BLACK&&getpixel(p.x,p.y)!=WHITE)
                {
                    if(fcx==-5)
                    {
                        setcolor(BLACK);
                        if(lim==2)
                        outtextxy(1300,450,"Press first circle.");
                        else if (lim==1) outtextxy(1300,450,"Apasati primul cerc.");
                        setcolor(WHITE);
                        if(lim==2)
                        outtextxy(1300,500,"Press second circle.");
                        else if(lim==1) outtextxy(1300,500,"Apasati al doilea cerc.");
                        fcx=p.x;
                        fcy=p.y;
                    }
                    else if(getpixel(p.x,p.y)==COL1)
                {
                    scx=p.x;
                    scy=p.y;
                    determinacerc(fcx,fcy,xb,yb,k,k0,draw_x1,draw_y1,mi1,mj1);
                    determinacerc(scx,scy,xb,yb,k,k0,draw_x2,draw_y2,mi2,mj2);
                    mi1=2+2*(mi1-1);
                    mi2=2+2*(mi2-1);
                    mj1=1+2*(mj1-1);
                    mj2=1+2*(mj2-1);
                    mi1=(mi1+mi2)/2;
                    mj1=(mj1+mj2)/2;
                    if(((draw_x1==draw_x2)^(draw_y1==draw_y2))&&a[mi1][mj1]==0&&abs(mi1-mi2)<=2&&abs(mj1-mj2)<=2)
                    {
                        moved=1;
                        cdx1=draw_x1;
                        cdx2=draw_x2;
                        cdy1=draw_y1;
                        cdy2=draw_y2;
                        cmi1=mi1;
                        cmj1=mj1;
                        pressedonce=0;
                    a[mi1][mj1]=2;
                    setlinestyle(0,0,3);
                    setcolor(COL1);
                    if(draw_x1==draw_x2)
                    {
                        if(draw_y1<draw_y2)
                            line(draw_x1,draw_y1+30,draw_x2,draw_y2-30);
                        else
                            line(draw_x1,draw_y1-30,draw_x2,draw_y2+30);

                             if(p.x>=10&&p.x<=250&&p.y>=225&&p.y<=350)//undo
                             {
                                 setcolor(BLACK);

                        if(draw_y1<draw_y2)
                            line(draw_x1,draw_y1+30,draw_x2,draw_y2-30);
                        else
                            line(draw_x1,draw_y1-30,draw_x2,draw_y2+30);

                                 a[mi1][mj1]=0;
                                 rand=1-rand;
                             }
                    }
                    else
                    {
                        if(draw_x1<draw_x2)
                            line(draw_x1+30,draw_y1,draw_x2-30,draw_y2);
                        else
                            line(draw_x1-30,draw_y1,draw_x2+30,draw_y2);

                        if(p.x>=10&&p.x<=250&&p.y>=225&&p.y<=350)//undo
                        {
                            setcolor(BLACK);


                        if(draw_x1<draw_x2)
                            line(draw_x1+30,draw_y1,draw_x2-30,draw_y2);
                        else
                            line(draw_x1-30,draw_y1,draw_x2+30,draw_y2);

                          a[mi1][mj1]=0;
                          rand=1-rand;

                        }

                    }
                    setlinestyle(0,0,1);
                    setcolor(WHITE);
                    rand=1-rand;
                    copiere(b,a,11);
                    fil(b,11,2,1,2);
                    fil(b,11,4,1,2);
                    fil(b,11,6,1,2);
                    fil(b,11,8,1,2);
                    fil(b,11,10,1,2);
                    if(verifsol(b,11,2))
                    {
                            settextstyle(2,0,20);
                            setcolor(COL1);
                            if(lim==2)
                                {
                                 outtextxy(550,10,"THE WINNER IS: P1");
                                }

                            else if(lim==1)
                                {
                                    outtextxy(540,10,"CASTIGATORUL ESTE: P1");
                                }
                            PlaySound(NULL, 0, 0);
                            PlaySound(TEXT("win.wav"),NULL,SND_FILENAME|SND_ASYNC|SND_NOSTOP);
                            setcolor(WHITE);
                            finish=true;
                    }
                    settextstyle(2,0,8);
                    setcolor(BLACK);
                    if(lim==2)
                    outtextxy(1300,500,"Press second circle.");
                    else if(lim==1) outtextxy(1300,500,"Apasati al doilea cerc.");
                    setcolor(WHITE);
                    if(lim==2)
                    outtextxy(1300,450,"Press first circle.");
                    else if (lim==1) outtextxy(1300,450,"Apasati primul cerc.");
                    }
                    else
                    {
                        setcolor(BLACK);
                        if(lim==2)
                        outtextxy(1300,500,"Press second circle.");
                        else if(lim==1) outtextxy(1300,500,"Apasati al doilea cerc.");
                        setcolor(WHITE);
                        if(lim==2)
                        outtextxy(1300,450,"Press first circle.");
                        else if (lim==1) outtextxy(1300,450,"Apasati primul cerc.");
                        settextstyle(2,0,8);
                        if(lim==1)
                {
                outtextxy(1310,900,"MISCARE INVALIDA!");
                }
                else if(lim==2)
                {
                     outtextxy(1310,900,"INVALID MOVE");
                }
                    }
                    fcx=fcy=-5;
                }
                }
                }
            }
            }
        }

    }

    void aboutmenu()//Lucia Bejan
    {
        cleardevice();
        rectangle(50,50,300,200);
        settextstyle(8,0,20);
        outtextxy(520,50,"BRIDG-IT!");
        settextstyle(4,0,3);
        outtextxy(875,950,"Emanuel Iacob & Lucia Bejan, FII 2019-2022");
        settextstyle(4,0,4);
        if(lim==2)
        {
        outtextxy(200,250,"This game was invented by David Gale and published");
        outtextxy(150,300,"around 1960.The players move alternately to connect");
        outtextxy(150,350,"the borders of their colors. The player who begins has ");
        outtextxy(150,400,"a big advantage and should always win.");
        outtextxy(150,500,"Against a player, UNDO deletes only the last move");
        outtextxy(150,550,"of the current player.");
        outtextxy(150,600,"Against the computer, UNDO deletes the last 2 moves (P+CPU).");
        settextstyle(3,0,8);
        outtextxy(80,100,"BACK");
        }

        else if(lim==1)
        {
            outtextxy(200,250,"Acest joc a fost inventat de David Gale si publicat");
        outtextxy(150,300,"in 1960.Jucatorii se misca alternativ pentru a conecta");
        outtextxy(150,350,"granitele culorilor lor. Jucatorul care incepe are un");
        outtextxy(150,400,"mare avantaj si ar trebui sa castige mereu.");
        outtextxy(150,500,"Impotriva unui jucator, butonul de UNDO sterge DOAR");
        outtextxy(150,550,"ultima miscare a jucatorului curent.");
        outtextxy(150,600,"Impotriva calculatorului, UNDO sterge ultimele 2 miscari (P+CPU).");
        settextstyle(3,0,8);
        outtextxy(70,100,"INAPOI");

        }
        readimagefile("play_tutorial.jpg",40,700,140,800);
        settextstyle(4,0,4);
       if(lim==2) outtextxy(40,670,"How do I connect the dots?");
        else outtextxy(40,670,"Cum conectez punctele?");
        while(true)
        {
        GetCursorPos(&p);
            if(GetAsyncKeyState(VK_LBUTTON))
            {
                if(mus==1) PlaySound(TEXT("click.wav"),NULL,SND_FILENAME|SND_ASYNC|SND_NOSTOP);
                if(p.x>=50&&p.x<=300&&p.y>=50&&p.y<=200)
                {
                    mainmenu();
                    break;
                }
                if(p.x>=40&&p.x<=140&&p.y>=700&&p.y<=800)
                {
                    Sleep(800);
                    readimagefile("tut0.jpg",470,700,1070,900);
                    Sleep(800);
                    readimagefile("tut1.jpg",470,700,1070,900);
                    Sleep(800);
                    readimagefile("tut2.jpg",470,700,1070,900);
                    Sleep(800);
                    readimagefile("tut3.jpg",470,700,1070,900);
                    Sleep(800);
                }
            }
        }
    }

    void dimensionmenu()
    {
        cleardevice();
        rectangle(50,50,300,200);
        settextstyle(3,0,8);
        if(lim==2)
        outtextxy(80,100,"BACK");
        else
            if(lim==1)
            outtextxy(70,100,"INAPOI");
        settextstyle(8,0,20);
        outtextxy(520,50,"BRIDG-IT!");
        readimagefile("small.jpg",300,300,700,700);
        readimagefile("big.jpg",900,300,1300,700);
        rectangle(300,300,700,700);
        rectangle(900,300,1300,700);
        rectangle(280,280,720,720);
        rectangle(880,280,1320,720);
        settextstyle(2,0,20);
        outtextxy(400,800,"NORMAL");
        if(lim==2)
        outtextxy(1000,800,"BIGGER");
        if(lim==1)
         outtextxy(1000,800,"MAI    MARE");
        setfillstyle(SOLID_FILL,GREEN);
        if(!marime) floodfill(281,281,WHITE);
        else floodfill(881,281,WHITE);
        while(true)
        {
            GetCursorPos(&p);
            if(GetAsyncKeyState(VK_LBUTTON))
            {
                if(mus==1) PlaySound(TEXT("click.wav"),NULL,SND_FILENAME|SND_ASYNC|SND_NOSTOP);
                if(p.x>=300&&p.x<=700&&p.y>=300&&p.y<=700)
                {
                    marime=0;
                    setfillstyle(SOLID_FILL,BLACK);
                    floodfill(881,281,WHITE);
                    setfillstyle(SOLID_FILL,GREEN);
                    floodfill(281,281,WHITE);
                }
                else if(p.x>=900&&p.x<=1300&&p.y>=300&&p.y<=700)
                {
                    marime=1;
                    setfillstyle(SOLID_FILL,BLACK);
                    floodfill(281,281,WHITE);
                    setfillstyle(SOLID_FILL,GREEN);
                    floodfill(881,281,WHITE);
                }
                else if(p.x>=50&&p.x<=300&&p.y>=50&&p.y<=200)
                {
                    optionsmenu();
                    break;
                }
            }
        }

    }

    void colorsmenu()//Emanuel Iacob
    {
        cleardevice();
        rectangle(50,50,300,200);
        settextstyle(3,0,8);
        if(lim==2)
            outtextxy(80,100,"BACK");
         if(lim==1)
            outtextxy(70,100,"INAPOI");
        settextstyle(8,0,20);
        outtextxy(520,50,"BRIDG-IT!");
        outtextxy(30,500,"P1");
        outtextxy(1450,500,"P2");
        line(800,200,800,1600);
        int k1=1,k2=1;
        for(int j=250;j<=800;j+=150)
        {
            for(int i=400;i<=1200;i+=200)
            if(i!=800)
            {
                if(i<800)
                {
                    if(k1==8) k1=14;
                    rectangle(i,j,i+100,j+100);
                    circle(i+50,j+50,30);
                    setfillstyle(SOLID_FILL,k1);
                    floodfill(i+50,j+50,WHITE);
                    k1++;
                }
                else
                {
                    if(k2==8) k2=14;
                    rectangle(i-100,j,i,j+100);
                    circle(i-50,j+50,30);
                    setfillstyle(SOLID_FILL,k2);
                    floodfill(i-50,j+50,WHITE);
                    k2++;
                }
            }
        }
        setfillstyle(SOLID_FILL,LIGHTGREEN);
        floodfill(px1,py1,WHITE);
        floodfill(px2,py2,WHITE);
        int cul;
        while(true)
        {
        GetCursorPos(&p);
        int xcu=p.x,ycu=p.y;
        cul=getpixel(xcu,ycu);
            if(GetAsyncKeyState(VK_LBUTTON))
            {
                if(mus==1) PlaySound(TEXT("click.wav"),NULL,SND_FILENAME|SND_ASYNC|SND_NOSTOP);
                if(p.x>=50&&p.x<=300&&p.y>=50&&p.y<=200)
                {
                    optionsmenu();
                    break;
                }
                if(cul!=BLACK&&cul!=WHITE)
                    {
                        int j;
                        if(xcu<800&&cul!=COL2)
                        {
                            COL1=cul;
                            setfillstyle(SOLID_FILL,BLACK);
                            floodfill(px1,py1,WHITE);
                            setfillstyle(SOLID_FILL,LIGHTGREEN);
                            for(j=xcu;getpixel(j,ycu)!=BLACK;j--);
                            floodfill(j,ycu,WHITE);
                            px1=j;py1=ycu;
                        }
                        else if(xcu>800&&cul!=COL1)
                        {
                            COL2=cul;
                            setfillstyle(SOLID_FILL,BLACK);
                            floodfill(px2,py2,WHITE);
                            setfillstyle(SOLID_FILL,LIGHTGREEN);
                            for(j=xcu;getpixel(j,ycu)!=BLACK;j--);
                            floodfill(j,ycu,WHITE);
                            px2=j;py2=ycu;
                        }
                    }
            }
        }
    }

    void optionsmenu()//Lucia Bejan
    {
        cleardevice();
        rectangle(50,50,300,200);
        settextstyle(3,0,8);
        if(lim==2)
            outtextxy(80,100,"BACK");
         else if(lim==1)
            outtextxy(70,100,"INAPOI");
        rectangle(600,500,1000,650);
        if(lim==2)
        {
        outtextxy(610,530,"DIMENSION");
        rectangle(600,500,1000,650);
        }
        else if(lim==1)
        {
        outtextxy(610,530,"DIMENSIUNE");
        rectangle(600,500,1025,650);
        }
        rectangle(600,200,1000,400);
        if(lim==2)
        {
        outtextxy(660,250,"COLORS");
        rectangle(600,230,1000,350);
        }
        else if(lim==1)
        {
        outtextxy(670,270,"CULORI");
        rectangle(600,230,1000,370);
        }
        settextstyle(8,0,20);
        outtextxy(520,50,"BRIDG-IT!");
        settextstyle(6,0,15);
        if(lim==2)
        outtextxy(1200,450,"LANGUAGE");
        else outtextxy(1200,450,"LIMBA");
        readimagefile("english.jpg",1300,500,1400,600);
        readimagefile("romanian.jpg",1300,650,1400,750);
        settextstyle(8,0,5);
        if(lim==2)
        outtextxy(500,750,"MUSIC");
        else outtextxy(475,750,"MUZICA");
        outtextxy(950,750,"SFX");
        if(mus==0) readimagefile("slide_left.jpg",700,700,900,800);
        else readimagefile("slide_right.jpg",700,700,900,800);
        Sleep(100);
        while(true)
        {
        Sleep(75);
        GetCursorPos(&p);
            if(GetAsyncKeyState(VK_LBUTTON))
            {
                if(mus==1) PlaySound(TEXT("click.wav"),NULL,SND_FILENAME|SND_ASYNC|SND_NOSTOP);
                if(p.x>=50&&p.x<=300&&p.y>=50&&p.y<=200)
                {
                    mainmenu();
                    break;
                }
                else if(p.x>=600&&p.x<=1000&&p.y>=200&&p.y<=400)
                {
                    colorsmenu();
                    break;
                }
                else if(p.x>=600&&p.x<=1000&&p.y>=500&&p.y<=650)
                {
                    dimensionmenu();
                    break;
                }
                else if(p.x>=1300&&p.x<=1400&&p.y>=500&&p.y<=600&&lim==1)
                {
                    lim=2;
                    optionsmenu();
                    break;
                }
                else if(p.x>=1300&&p.x<=1400&&p.y>=650&&p.y<=750&&lim==2)
                {
                    lim=1;
                    optionsmenu();
                    break;
                }
                else if(mus==0&&p.x>=700&&p.x<=900&&p.y>=700&&p.y<=800)
                {
                    PlaySound(NULL, 0, 0);
                    readimagefile("slide_right.jpg",700,700,900,800);
                    first_time=false;
                    mus=1;
                }
                else if(mus==1&&p.x>=700&&p.x<=900&&p.y>=700&&p.y<=800)
                {
                    PlaySound(TEXT("main_menu.wav"),NULL,SND_FILENAME|SND_LOOP|SND_ASYNC|SND_NOSTOP);
                    readimagefile("slide_left.jpg",700,700,900,800);
                    mus=0;
                }
            }
        }
    }

    void selectgamestyle()
    {
        cleardevice();
        rectangle(50,50,300,200);
        settextstyle(3,0,8);
        if(lim==2)
            outtextxy(80,100,"BACK");
         else if(lim==1)
            outtextxy(70,100,"INAPOI");
        settextstyle(8,0,20);
        outtextxy(520,50,"BRIDG-IT!");
        readimagefile("PvP.jpg",200,300,600,700);
        readimagefile("PvCPU.jpg",1000,300,1400,700);
        settextstyle(8,0,5);
        if(lim==2)
        outtextxy(600,800,"Select game mode.");
        else outtextxy(600,800,"Alegeti modul de joc.");
        while(true)
        {
        GetCursorPos(&p);
            if(GetAsyncKeyState(VK_LBUTTON))
            {
                if(mus==1) PlaySound(TEXT("click.wav"),NULL,SND_FILENAME|SND_ASYNC|SND_NOSTOP);
                if(p.x>=200&&p.x<=600&&p.y>=300&&p.y<=700)
                {
                    first_time=true;
                    if(marime==0) classicgraph();
                    else biggergraph();
                    break;
                }
                else if(p.x>=1000&&p.x<=1400&&p.y>=300&&p.y<=700)
                {
                    first_time=true;
                    if(marime==0) CPU_classicgraph();
                    else CPU_biggergraph();
                    break;
                }
                else if(p.x>=50&&p.x<=300&&p.y>=50&&p.y<=200)
                {
                    mainmenu();
                    break;
                }
            }
        }
    }
    void mainmenu()//Emanuel Iacob
    {
        cleardevice();
        settextstyle(8,0,20);
        outtextxy(520,50,"BRIDG-IT!");
        if(first_time)
        {
            PlaySound(NULL, 0, 0);
            if(mus==0) PlaySound(TEXT("main_menu.wav"),NULL,SND_FILENAME|SND_LOOP|SND_ASYNC|SND_NOSTOP);
        }
        first_time=false;
        settextstyle(3,0,8);
        rectangle(1300,850,1500,950);
        if(lim==2)
        outtextxy(1320,860,"EXIT");
        else
        {
            settextstyle(3,0,6);
            outtextxy(1320,860,"IESIRE");
            settextstyle(3,0,8);
        }
        rectangle(600,200,1000,400);
        if(lim==2)
        outtextxy(700,250,"PLAY!");
        else if(lim==1)
           outtextxy(670,250,"JOACA!");
        rectangle(600,450,1000,650);
        if(lim==2)
        outtextxy(650,500,"OPTIONS");
        else if(lim==1)
        outtextxy(650,500,"OPTIUNI");
        rectangle(600,700,1000,900);
        if(lim==2)
        outtextxy(675,750,"ABOUT");
        else
            if(lim==1)
             outtextxy(675,750,"DESPRE");
        while(true)
        {
        GetCursorPos(&p);
            if(GetAsyncKeyState(VK_LBUTTON))
            {
                if(mus==1) PlaySound(TEXT("click.wav"),NULL,SND_FILENAME|SND_ASYNC|SND_NOSTOP);
                if(p.x>=600&&p.x<=1000&&p.y>=200&&p.y<=400)
                {
                    selectgamestyle();
                    break;
                }
                else if(p.x>=600&&p.x<=1000&&p.y>=700&&p.y<=900)
                {
                    aboutmenu();
                    break;
                }
                else if(p.x>=600&&p.x<=1000&&p.y>=450&&p.y<=650)
                {
                    optionsmenu();
                    break;
                }
                else if(p.x>=1300&&p.x<=1500&&p.y>=850&&p.y<=950) break;
            }/*intra in optiune setata daca e in int drept*/
        }
    }

    int main()
    {
        initwindow(1600,1000,"BRIDG IT",-4,-40);
        mainmenu();
        closegraph();
        //Buton de undo
        return 0;
    }
