// Room: /d/gumu/shishi3.c
// Last Modifyed by Winder on Jan. 14 2002

#include <ansi.h>
inherit ROOM;

void create()
{ 
        set("short",HIB"石室"NOR);
        set("long", @LONG
古墓中陰沉的石室，只聽見遠遠傳來你腳步的回音，空盪盪的感覺
使你心中只有恐懼，甚至忘記孤獨。你不知身處何地，四周如此漆黑一
片，只能靠摸索前行。
LONG        );
        set("exits", ([
                "east"  : __DIR__"shishi"+(1+random(3)),
                "west"  : __DIR__"shishi"+(1+random(3)),
                "south" : __DIR__"shishi"+(1+random(3)),
                "north" : __DIR__"shishi"+(1+random(3)),
        ]));
        set("no_clean_up", 0);
        set("coor/x", -3210);
        set("coor/y", -40);
        set("coor/z", 80);
        setup();
}

void init()
{
        object me = this_player();
        if( userp(me) && query("jing", me)<200 )
        {
                me->move(__DIR__"shishi0"); 
                message("vision", me->name()+"昏昏沉沉地走了過來。\n",environment(me), ({me}));
                write(HIR"你慢慢發現自己體力不支.....\n"NOR);
                me->unconcious();
        }
        if( !query_temp("steps", me) && userp(me) )
                set_temp("steps", keys(query("exits"))[random(sizeof(query("exits")))], me);
}

int valid_leave(object me, string dir)
{
        if( dir != "up")
        me->receive_damage("jing", 10 + random(10));
        if( dir != query_temp("steps", me))set_temp("step", 0, me);
        else addn_temp("step", 1, me);
        if( query_temp("step", me)>3+random(3) )
        {
                me->move(__DIR__"shishi5");
                delete_temp("step", me);
                delete_temp("steps", me);
                me->start_busy(2);
                return notify_fail("你累得半死，終於發現前方有一道光亮。\n");
        }
        return ::valid_leave(me,dir);
}