// Room in 高麗
#include <ansi.h>
inherit ROOM;

void create()
{
        set("short","漁船");
        set("long", @LONG
漁船都連在一齊，而且都幾乎是一模一樣的，看得你頭暈眼花。忽
然一個暗浪湧來，你一個不穩，‘啊。。。’，你幾乎掉下了海去。
LONG
        );
        set("exits", ([
        "north" : __FILE__,
        "west" : __FILE__,
        "south" : __DIR__"yuchuan",
        "northwest" : __DIR__"yucun",
        ]));
        setup();
        replace_program(ROOM);
}

