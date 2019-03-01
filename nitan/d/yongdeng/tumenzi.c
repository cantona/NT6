// Room: /huanghe/tumenzi.c
// Java Sep. 22 1998

#include <room.h>

inherit ROOM;

void create()
{
        set("short", "土門子");
        set("long", @LONG
土門子也是以前駐軍的地方，周圍全是沙漠，中間一塊小小的綠洲，
本來這裡有當地的牧民居住，可是前不久來了一伙馬賊佔據了這裡以這
裡為大本營四出劫掠，無惡不作。
LONG );
        set("exits", ([
                "south"     : __DIR__"wuwei",
                "northeast" : __DIR__"shixiazi",
        ]));
        set("no_clean_up", 0);
        set("outdoors", "yongdeng");
        set("coor/x", -16110);
	set("coor/y", 4250);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}