//zhandao1.c
inherit ROOM;
#include <ansi.h>

void create()
{
        set("short", "棧道");
        set("long", @LONG
這裏是通往明教的棧道，腳下茂林生雲，極其艱險。
LONG );
        set("exits", ([
                "northup"   : __DIR__"zhandao2",
                "southdown" : __DIR__"lhqhoumen",
        ]));
        set("outdoors", "mingjiao");
        setup();
        replace_program(ROOM);
}

void init()
{
        object me = this_player();
        
        if (interactive(me) && random((int)me->query_skill("dodge")) <= 10) 
        {
                me->receive_damage("qi", 50);
                me->receive_wound("qi",  50);
message_vision(HIR"$N一不小心腳下踏了個空，... 啊...！\n"NOR, me);
                me->move(__DIR__"lhqpaifang");
                tell_object(me, HIR "你從棧道跌了下來，好疼 !還受了傷。\n" NOR);
message("vision",HIR"只見"+query("name", me)+"從棧道上撲通一聲跌了下來，躺在地上半天爬不起來！\n"NOR,environment(me),me);
        }
}
