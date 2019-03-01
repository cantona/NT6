// Room: /d/taishan/longmen.c
// Last Modified by winder on Aug. 25 2001

#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", "龍門");
        set("long", @LONG
此處山勢陡峭，登山的人一個不小心很容易便會跌墮到崖谷之中。
西巖有清道光年間魏祥摹刻狂草“龍門”大字。坊址東為大龍峪，雨季
眾水歸峽，飛泉若瀉。
LONG );
        set("exits", ([
                "northup"   : __DIR__"jinman18",
                "southdown" : __DIR__"man18",
        ]));
        set("objects", ([
                __DIR__"npc/chi" : 1,
        ]));
        set("outdoors", "taishan");
        set("coor/x", 30);
	set("coor/y", 260);
	set("coor/z", 160);
	setup();
}

void init()
{
        object me = this_player();
        
        if( userp(me) && random((int)me->query_skill("dodge")) <= 10) 
        {
                me->receive_damage("qi", 50);
                me->receive_wound("qi",  50);
                message_vision(HIR"$N一不小心腳下踏了個空... 啊...！\n"NOR, me);
                me->move(__DIR__"daizong");
                tell_object(me, HIR"你從山上滾了下來，只覺得渾身無處不疼，還受了幾處傷。\n"NOR);
                message("vision",HIR"只見"+query("name", me)+"從山上骨碌碌地滾了下來，躺在地上半天爬不起來！\n"NOR,environment(me),me);
        }
}