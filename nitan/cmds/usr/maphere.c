// 即時地圖 maphere.c
// Modify by zjpwxh@sjpl 2004.4.24
// Modify by zjpwxh@sjpl 2004.6.2
// 改進了搜索算法，以廣度遍歷代替遞歸
// 由于嚴重影響速度（遞歸調用導致！），所以進行此命令的使用者應該減少氣血

#include <ansi.h>
#define MaxX 11
#define MaxY 22
#define MinX 7
#define MinY 14
inherit F_CLEAN_UP;

nosave int X,Y;
nosave mixed m;
nosave string *rfile;
nosave mapping *data;
int draw_room(int,int,object);
void set_room(int,int,object);
void set_x_y(int,int,int);

int main(object me, string arg)
{
        object where;
        int i,j,k,l,n,p,x,y;
        int lineu,lined,linef;
        string *text;
        string tmp;

        if( arg && arg == "-min" ) {
                X = 5;
                Y = 6;
        } else {
                if( !wizardp(me) && query("qi", me) < 100 )
                        return notify_fail("你的體力不太好，先休息一下吧！\n");

                if( !wizardp(me) )
                        addn("qi",-50,me);

                if( arg && arg == "-m" ) {
                        X=MaxX;
                        Y=MaxY;
                } else {
                        X=MinX;
                        Y=MinY;
                }
        }

        where=environment(me);
        if(!objectp(where))
                return notify_fail("對不起，不知道你到底在哪裡呀！找巫師吧！\n");

        if(base_name(where)[0..1] == "/f")
                return notify_fail("副本裡無法通過該指令獲取地圖信息！\n");

        tmp = HIY"即時地圖"HIW"(地圖大小："HIM+X+HIW"/"HIR+Y+HIW")"HIM"[建議使用 1024 X 768 分辨率]：\n\n"NOR;
        m = allocate(2*X+1);
        data = allocate((2*X+1)*(2*Y+1));
        rfile = ({});
        for(i=0;i<2*X+1;i++)
        {
                m[i]=allocate(2*Y+1);
                for(j=0;j<2*Y+1;j++)
                        m[i][j]=" ";
        }

        draw_room((2*X+1)/2,(2*Y+1)/2,where);

        for(l=0,linef=1;l<2*Y+1;l++)
        {
                for(n=0;n<2*X+1;n++)
                {
                        if( m[n][l]!=" ")
                                p++;
                }
                if(!p && linef)
                {
                        lineu++;
                        linef=1;
                }
                else    linef=0;
                p=0;
        }
        for(l=2*Y,linef=1;l>=0;l--)
        {
                for(n=0;n<2*X+1;n++)
                {
                        if( m[n][l]!=" ")
                                p++;
                }
                if(!p && linef)
                {
                        lined++;
                        linef=1;
                }
                else    linef=0;
                p=0;
        }

        for(i=lineu;i<2*Y+1-lined;i++)
        {
                for(j=0;j<2*X+1;j++)
                {
                        if( m[j][i]==" " && i%2 && j%2 )
                                tmp+="        ";
                        else
                        {
                                //如果此項為空，並且此時j為偶數列，則輸出空格
                                if( m[j][i]==" " && !(j%2) )
                                        tmp+="  ";
                                else
                                {
                                        if( m[j][i]==" " )
                                                tmp+="        ";

                                        else
                                                tmp+=m[j][i];
                                }
                        }
                }
                tmp+="\n";
        }
        text=explode(tmp, "\n");
        for(i=k; k<sizeof(text); k++)
                write(text[k] + "\n");
        write(HIM"["HIC"溫磬提示："HIG"("HIB"藍底"HIG"亮綠色的代表你目前所處房間)，"HIY"(黃色的代表有不規則出口的房間)，"HIM"]\n"NOR);

        return 1;
}

object find_room(string path)
{
        object ob;
        if( objectp(ob=find_object(path)) || objectp(ob=load_object(path)) )
                return ob;
        return 0;
}

//←↑→↓□□□□
int draw_path(int x,int y,string direc)
{
        string str;
        int xx=0,yy=0;
        switch(direc)
        {
                case "south":
                case "north":              str="   ｜   ";break;
                case "southdown":          str="   ↓   ";break;
                case "northup":            str="   ↑   ";break;
                case "southup":            str="   ↑   ";break;
                case "northdown":          str="   ↓   ";break;
                case "east":
                case "west":               str="─";break;
                case "eastdown":
                case "eastup":             str="→";break;
                case "westdown":
                case "westup":             str="←";break;
                case "southeast":
                case "northwest":          str="＼";break;
                case "southwest":
                case "northeast":          str="／";break;
                default:
                        return 0;
        }
        if(sscanf(direc,"%*ssouth%*s"))
                yy++;
        if(sscanf(direc,"%*snorth%*s"))
                yy--;
        if(sscanf(direc,"%*seast%*s"))
                xx++;
        if(sscanf(direc,"%*swest%*s"))
                xx--;
        if( x+xx<=0 || y+yy<=0 || x+xx>=2*X || y+yy>=2*Y )
                return 0;
        m[x+xx][y+yy]=HIW+str+NOR;
        return 1;
}

// 改用廣度遍歷尋路算法,使地圖的顯示更加合理
int draw_room(int x,int y,object room)
{
        int i,xx,yy;
        int front,rear;
        string *dirs;
        object froom,nroom;
        mapping dir,x_y;
        object *queue;
        front=0;rear=0;

        queue=allocate( (2*X+1)*(2*Y+1) );
        reset_eval_cost();
        if( x<0 || y<0 || !objectp(room) || x>2*X || y>2*Y )
                return 0;

        rfile=rfile + ({ base_name(room) });
        queue[rear]=room;
        set_room(x,y,room);
        set_x_y(x,y,rear);
        rear++;

        while( front < rear )
        {
                reset_eval_cost();
                froom=queue[front];
                x_y=data[front];
                front++;
                if( !objectp(froom) ) return 0;
                dir=query("exits", froom);
                if( !mapp(dir) || sizeof(dir)<1 )
                        return 0;
                dirs=keys(dir);
                for(i=0;i<sizeof(dirs);i++)
                {
                        nroom=find_room(dir[dirs[i]]);
                        if(!objectp(nroom) || member_array(base_name(nroom),rfile)!=-1)
                                continue;
                        xx=0;yy=0;
                        if( sscanf(dirs[i],"%*ssouth%*s"))
                                yy+=2;
                        if( sscanf(dirs[i],"%*snorth%*s"))
                                yy-=2;
                        if( sscanf(dirs[i],"%*seast%*s"))
                                xx+=2;
                        if( sscanf(dirs[i],"%*swest%*s"))
                                xx-=2;
                        if( x_y["xst"]+xx<0 || x_y["yst"]+yy<0 || x_y["xst"]+xx>2*X || x_y["yst"]+yy>2*Y )
                                continue;
                        if( m[x_y["xst"]+xx][x_y["yst"]+yy]!=" ")
                                continue;
                        if( !draw_path(x_y["xst"],x_y["yst"],dirs[i]) || (xx==0&&yy==0))
                                continue;
                        rfile=rfile + ({ base_name(nroom) });
                        queue[rear]=nroom;
                        set_room(x_y["xst"]+xx,x_y["yst"]+yy,nroom);
                        set_x_y(x_y["xst"]+xx,x_y["yst"]+yy,rear);
                        rear++;
                }
        }
}

void set_room(int x,int y,object room)
{
        int i,d,xx,yy,flag;
        string name;
        mapping dir;
        string *dirs;

        // 求取無顏色的房間short描述
        name=filter_color(room->short());

        // 房間的短名字最好在4個漢字以內
        if(strlen(name)>8)  name=name[0..7];

        if(strlen(name)<7) //對不足4個漢字的房間名進行居中處理
        {
                d=8-strlen(name);
                if( d%2 )
                {
                        name+=" ";
                        d--;
                }
                for(i=0;i<d/2;i++)
                        name=" "+name+" ";
        }

        dir=query("exits", room);

        if( !mapp(dir) || sizeof(dir)<1 )
        {
                flag=1;
        }
        else
        {
                dirs=keys(dir);
                for(i=0;i<sizeof(dirs);i++)
                {
                        xx=0;yy=0;
                        if( sscanf(dirs[i],"%*ssouth%*s"))
                                yy+=2;
                        if( sscanf(dirs[i],"%*snorth%*s"))
                                yy-=2;
                        if( sscanf(dirs[i],"%*seast%*s"))
                                xx+=2;
                        if( sscanf(dirs[i],"%*swest%*s"))
                                xx-=2;
                        if( xx==0 && yy==0 )
                                flag=1;
                }
        }

        if((x==(2*X+1)/2)&&(y==(2*Y+1)/2))
                name=HBBLU+HIG+name;
        else if( flag )
                name=HIY+name;

        name+=NOR;
        m[x][y]=name;
}

void set_x_y(int x,int y,int rear)
{
        data[rear]=([
                "xst":x,
                "yst":y,
        ]);
}

int help(object me)
{
        write(@HELP
指令格式：maphere [-m]

本命令幫助玩家了解周圍的房間地圖的分布狀況，並標志出房間之間的連接情況。
連接標志中箭頭所指方向地勢更高，有不規范出口的房間以黃色標志，你所處的
房間以藍底亮綠色來標志！由于房間可能重疊的緣故，有些房間將無法顯示出來。
本命令默認以x=7,y=14 的地圖大小顯示，使用-m選項將以最大化x=11,y=22 顯示。
HELP);
        return 1;
}
