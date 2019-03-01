#include <ansi.h>

inherit ROOM;

void create()
{
    set("short", "長廊");
        set("long", @LONG
這是條長長的走廊，四處黑沉沉的。
LONG );
    set("exits", ([
        "north" : "/d/beijing/zhuang9",
        "south" : "/d/beijing/zhuang5",
    ]));
    set("objects", ([
        "/d/shenlong/npc/dizi": 1,
    ]));
    set("outdoors", "beijing");
    set("coor/x", 90);
        set("coor/y", 4730);
        set("coor/z", 0);
        setup();
    replace_program(ROOM); 
}