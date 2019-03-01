// Copyright (C) 2003, by Lonely. All rights reserved.
// This software can not be used, copied, or modified 
// in any form without the written permission from authors.

#include <ansi.h>
#include <room.h>

inherit BUILD_ROOM;
string look_shu();

void create()
{
        set("short", HIY "名人堂" NOR);
        set("long", @LONG
這裡就是泥潭的名人堂。在這裡供奉的有大俠，也有魔頭，也有
不是大俠不是魔頭的玩家。無論是哪一位，都曾冠絕一時，都有一個
長長而驚心動魄的故事，每一個故事都曾很深遠地影響了一代甚至兩
三代玩家。雖然他們都曾經轟轟烈烈掀起滿江湖的風雨，如今，他們
再也不會在江湖出現了。他們都已經退出江湖，但他們的俠影魔蹤很
長時間以後仍是一個傳說。
LONG );

        set("no_fight", "1");
        set("no_steal", "1");
        set("no_beg", "1");
        set("no_sleep_room", "1");
        set("no_clean_up", 0);

        set("exits", ([
                "down" : __DIR__"wumiao2",
        ]));
        set("objects", ([
                // __DIR__"npc/mingren/gzf" : 1,
        ]));
	set("coor/x", -10);
	set("coor/y", 20);
	set("coor/z", 20);
	setup();
}