#include <ansi.h>

inherit ROOM;

void create()
{
    set("short", "莊府大廳");
        set("long", @LONG
這是一間大廳，通往各個房間。東邊的屋裡有女子啼哭之聲隱隱
傳來。
LONG );
    set("exits", ([
        "east" : "/d/beijing/zhuang6",
        "west" : "/d/beijing/zhuang7",
        "north" : "/d/beijing/zhuang8",
        "south" : "/d/beijing/zhuang3",
    ]));
    set("objects", ([
        "/d/shenlong/npc/dizi": 2,
        "/d/shenlong/npc/zhang3": 1,
    ]));
    set("outdoors", "beijing");
    set("coor/x", 100);
        set("coor/y", 4720);
        set("coor/z", 0);
        setup();
    replace_program(ROOM); 
}