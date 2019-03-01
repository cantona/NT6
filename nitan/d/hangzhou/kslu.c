// kslu.c

#include <room.h>

inherit BUNCH_ROOM;

void create()
{
        set("short", "碎石路");
        set("long", @LONG
這是一條碎石子舖就的路，路上人來人往，趕著大車，看來是在
運什麼東西。地上零零散散的遺落了一些藍色的石頭。往東就是江南
盛產銅礦的寶山了。
LONG );
        set("exits", ([
                "west" : __DIR__"road17",
                "east" : __DIR__"kslu2",
        ]));
        set("outdoors", "hangzhou");
	set("coor/x", 780);
	set("coor/y", -2110);
	set("coor/z", 0);
	setup();
}
