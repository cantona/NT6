#include <room.h>
inherit ROOM;

void create()
{
        set("short", "廂房");
        set("long", @LONG
這裏是海澄公府的左側的一個廂房，供給海澄公府的客人居住。
LONG );
        set("exits", ([
                "east" : "/d/beijing/hai_dayuan",
        ]));

        set("sleep_room", "1");
        set("outdoors", "beijing");
	set("coor/x", -2820);
	set("coor/y", 7630);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}