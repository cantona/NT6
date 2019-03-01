inherit ROOM;
#include <ansi.h>;

void create()
{
        set("short", "山道");
        set("long", @LONG
這裡已經看不到襄陽了，滿眼望去，盡是曲曲折折的山道，大軍
行到此處，人畜都開始有些吃力起來。
LONG );
        set("outdoors", "xiangyang");
        set("no_magic",1);

        set("exits", ([
                "north"  : __DIR__"shanlu2",
                "south"  : __DIR__"shanlu2",
        ]));

        setup();
}

void init()
{
        object me=this_player();

        if (! me->is_busy())
        me->start_busy(random(2));


        if( query_temp("yidao/mark_steps", me)>11 )
        {
         me->move(__DIR__"dhunya");
         delete_temp("yidao", me);
         tell_object(me,YEL"一路風塵僕僕之後，斷魂崖已經近在眼前了......\n"NOR);
         return;
        } 

        if( query_temp("yidao/mark_steps", me)<-11 )
        {
         me->move(__DIR__"wsling");
         delete_temp("yidao", me);
         tell_object(me,YEL"一路風塵僕僕之後，烏石嶺已經近在眼前了......\n"NOR); 
         return;
        }

        tell_object(me,YEL"你指揮著大軍，行進在曲折的山道上......\n"NOR); 
}

int valid_leave(object me,string dir)
{
       if( dir == "south" )
       addn_temp("yidao/mark_steps", -random(2), me);
       if(  dir == "north" )
       addn_temp("yidao/mark_steps", random(2), me);
       return ::valid_leave(me,dir);
}
