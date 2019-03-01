// Room: /lingzhou/deling.c
// Java. Sep 21 1998

#include <room.h>

inherit ROOM;
void create()
{
        set("short", "德陵");
        set("long", @LONG
這就是李元昊的父親趙德明的陵墓。寬十米高五米，為整個王陵中
最高大也是最完整的建築。陵前左右各有兩個石人武士護衛，陵前有漢
白玉欄桿圍成的平台，上面石桌石凳一應俱全。
LONG );
        set("exits", ([
                "south"   : __DIR__"chiling",
                "north"   : __DIR__"gongling",
        ]));
        set("objects", ([
                __DIR__"npc/shiwushi" : 2,
        ]));
        set("outdoors", "lingzhou");
        set("coor/x", -6235);
        set("coor/y", 3005);
        set("coor/z", -10);
        setup();
        replace_program(ROOM);
}