inherit ROOM;
#include <ansi.h>;

void create()
{
        set("short", "草原");
        set("long", @LONG
這裡已經漸漸接近蒙古軍營了，大軍行到此處，眼前陡然開闊起
來，放眼望去，四處都是茫茫大草海，讓人不由心生出一種凄涼而豪
壯的感覺。
LONG );
        set("outdoors", "xiangyang");
        set("no_magic",1);

        set("exits", ([
                "east"  : __DIR__"shanlu3",
                "west"  : __DIR__"shanlu3",
        ]));

        setup();
}

void init()
{
        object me=this_player();

        me->start_busy(random(2));


        if( query_temp("yidao/mark_steps", me)>11 )
        {
         me->move(__DIR__"caoyuan");
         delete_temp("yidao", me);
         tell_object(me,YEL"一路風塵僕僕之後，蒙古大草原已經近在眼前了......\n"NOR);
         return;
        } 

        if( query_temp("yidao/mark_steps", me)<-11 )
        {
         me->move(__DIR__"dhunya");
         delete_temp("yidao", me);
         tell_object(me,YEL"一路風塵僕僕之後，斷魂崖已經近在眼前了......\n"NOR); 
         return;
        }
        tell_object(me,HIG"你指揮著大軍，行進在茫茫的草原上......\n"NOR);  
}

int valid_leave(object me,string dir)
{
       if( dir == "west" )
       addn_temp("yidao/mark_steps", -random(2), me);
       if(  dir == "east" )
       addn_temp("yidao/mark_steps", random(2), me);
       return ::valid_leave(me,dir);
}
