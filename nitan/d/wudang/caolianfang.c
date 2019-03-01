#include <room.h>
inherit ROOM;

void create()
{
        set("short", "操練房");
        set("long", @LONG
這是二樓操練房上，四面八方都是打鬥聲，武當弟子來去匆匆，
都在忙著操練。
LONG );
        set("exits", ([
                "south" : __DIR__"caolian1",
                "north" : __DIR__"caolian2",
                "west" : __DIR__"caolian3",
                "eastdown"  : __DIR__"xilang"
        ]));
        set("objects", ([
                CLASS_D("wudang") + "/yin" : 1
        ]));
        set("coor/x", -390);
        set("coor/y", -300);
        set("coor/z", 100);
        setup();
        replace_program(ROOM);
}