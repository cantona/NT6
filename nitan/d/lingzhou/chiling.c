// Room: /lingzhou/chiling.c
// Java. Sep 21 1998

#include <room.h>

inherit ROOM;
void create()
{
        set("short", "赤陵");
        set("long", @LONG
這是西夏前身平夏部開國之主拓跋赤辭的陵墓，因為年代久遠而看
上去有點破敗，不大的石制墳頭，幾棵小草從石縫裡伸出頭來看著你，
陵前的兩棵鬆柏倒長得非常高大。畢竟是幾百年前種的呀。
LONG );
        set("exits", ([
                "south"   : __DIR__"wangling",
                "north"   : __DIR__"deling",
        ]));
        set("no_clean_up", 0);
        set("outdoors", "lingzhou");
        set("coor/x", -6235);
        set("coor/y", 2995);
        set("coor/z", -10);
        setup();
        replace_program(ROOM);
}