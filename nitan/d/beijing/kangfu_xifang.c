#include <room.h>
inherit ROOM;

void create()
{
        set("short", "西廂房");
        set("long", @LONG
這裡是康親王府的左邊的一個廂房，是供王府的客人居住的。這
裡站著一個身材瘦高的武師，兩手別在腰後，似乎有一身好武功。
LONG );
        set("exits", ([
                "east" : "/d/beijing/kangfu_zoulang2",
        ]));

        set("objects", ([
                "/d/beijing/npc/qiyuankai" : 1,
        ]));

        set("sleep_room", "1");
        set("outdoors", "beijing");
	set("coor/x", -2810);
	set("coor/y", 7720);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}