// Room: /d/xiakedao/road7.c
  
#include <ansi.h>

inherit ROOM;

void create()
{
        set("short", "夾鱉石");
        set("long", @LONG
這裡便是夾鱉石。此處山勢陡峭，行人到此無不心驚膽顫，不
敢大聲說話，只求平安過去。登山的人一個不小心，很容易便會跌
墮到崖谷之中。
LONG );
        set("outdoors", "xiakedao");
        set("exits", ([
                "southup"   : __DIR__"road8",
                "northdown" : __DIR__"road6",
        ]));
        set("no_clean_up", 0);
        set("outdoors", "xiakedao");
        set("coor/x", -3110);
        set("coor/y", -22130);
        set("coor/z", 20);
        setup();
}

void init()
{
        object me = this_player();

        if( random((int)me->query_skill("dodge",1)) <= 15)
        {
                me->receive_damage("qi", 50);
                me->receive_wound("qi",  50);
                message_vision(HIR"$N一不小心腳下踏了個空，... 啊...!\n"NOR, me);
                me->move(__DIR__"road3");
                tell_object(me, HIR"你從山上滾了下來，只覺得渾身無處不疼，還受了幾處傷。\n"NOR);
                message("vision",HIR"只見"+query("name", me)+"從山上骨碌碌地滾了下來，躺在地上半天爬不起來!\n"NOR,environment(me),me);
        }
}