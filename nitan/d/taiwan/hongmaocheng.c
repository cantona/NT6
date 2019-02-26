// Room: /d/taiwan/homgmaocheng.c
// Last Modifyed by Ahda on Jan. 4 2002

#include <ansi.h>;
inherit ROOM;

void create()
{
        set("short", "紅毛城");
        set("long", @LONG
紅毛城，位於“五虎岡”第二岡嶺上，緊臨淡水河北岸，東、西、
南三面都是陡坡，形勢險要，是明末清初，西方海權強國西、荷所建的
城堡。
LONG );
        set("exits", ([
                "south" : __DIR__"danshui",
        ]));
        set("objects", ([
                __DIR__"npc/hongmao": 1,
        ]));
        set("outdoors", "taiwan");
        set("coor/x", 2540);
        set("coor/y", -6960);
        set("coor/z", 0);
        setup();
        replace_program(ROOM);
}
