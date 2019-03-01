// road14.c
// Date: Nov.1997 by Venus
#include <room.h>
inherit ROOM;
void create()
{
        set("short", "青石大道");
        set("long", @LONG
沿湖大道旁店舖林立，長街故樸，屋舍鱗次櫛比，道上人來車往，
一片太平熱鬧景象。西邊有一花園，遊人進進出出，十分熱鬧。東邊
是名醫胡慶余開的藥舖。
LONG);
        set("exits", ([
            "northeast" : __DIR__"road13",
            "southwest" : __DIR__"road15",
            "east"      : __DIR__"yaodian",
            "west"      : __DIR__"qingbomen",
        ]));
        set("objects", ([
            __DIR__"honghua/wen" :1,
            __DIR__"honghua/luo" :1,
        ]));
        set("outdoors", "xihu");
	set("coor/x", 820);
	set("coor/y", -2080);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}