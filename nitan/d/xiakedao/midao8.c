// midao8.c 密道

#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", "密道");
        set("long", @LONG
這是一條長長的密道，地面和石壁滿是灰塵，好象很久沒人來過了。
LONG );
        set("exits", ([
                "southdown" : __DIR__"midao7"
        ]));
        set("no_clean_up", 0);
        set("coor/x", -3090);
        set("coor/y", -25000);
        set("coor/z", -20);
        setup();
}

void init()
{
        object me = this_player();
        if( random((int)me->query_skill("dodge",1)) <= 80)
        {
                me->receive_damage("qi", 50);
                me->receive_wound("qi",  50);
                message_vision(HIR"$N一不小心踩到地上的一個暗紐，... 啊...！\n"NOR, me);
                me->move(__DIR__"road3");
                tell_object(me, HIR"你從山上滾了下來，只覺得渾身無處不疼，還受了幾處傷。\n"NOR);
                message("vision",HIR"只見"+query("name", me)+"從山上骨碌碌地滾了下來，躺在地上半天爬不起來！\n"NOR,environment(me),me);
        }
}