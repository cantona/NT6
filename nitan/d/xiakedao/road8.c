// Room: /d/xiakedao/road8.c


#include <ansi.h>

inherit ROOM;
void create()
{
        set("short", "一線天");
        set("long", @LONG
這裏便是一線天。此處山勢甚是陡峭，兩旁都是無底的深淵，
中間是一條近似九十度的坡形山路。行人到此無不心驚膽顫，只盯
着自己的腳，生怕一不小心掉下深淵。
LONG );
        set("exits", ([
                "southup"   : __DIR__"wangyun",
                "northdown" : __DIR__"road7",
        ]));
        set("no_clean_up", 0);
        set("outdoors", "xiakedao");
        set("coor/x", -3110);
        set("coor/y", -22140);
        set("coor/z", 30);
        setup();
}

void init()
{
        object me = this_player();

        if( random((int)me->query_skill("dodge",1))<= 30)
        {
                me->receive_damage("qi", 50);
                me->receive_wound("qi",  50);
                message_vision(HIR"$N一不小心腳下踏了個空，... 啊...!\n"NOR, me);
                me->move(__DIR__"road5");
                tell_object(me, HIR"你從山上滾了下來，只覺得渾身無處不疼，還受了幾處傷。\n"NOR);
                message("vision",HIR"只見"+query("name", me)+"從山上骨碌碌地滾了下來，躺在地上半天爬不起來!\n"NOR,environment(me),me);
        }
}