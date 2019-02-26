// kslu2.c

#include <room.h>

inherit ROOM;

void create()
{
        set("short", "碎石路");
        set("long", @LONG
這是一條碎石子鋪就的路，路上人來人往，趕着大車，看來是在
運什麼東西。地上零零散散的遺落了一些藍色的石頭。往東就是江南
盛產銅礦的寶山了。
LONG );
        set("exits", ([
                "west" : __DIR__"kslu",
                "east" : __DIR__"kuangshan",
        ]));
        set("outdoors", "hangzhou");
	set("coor/x", 790);
	set("coor/y", -2110);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}