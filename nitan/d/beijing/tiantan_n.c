#include <room.h>
inherit ROOM;

void create()
{
        set("short", "天壇北門");
        set("long", @LONG
這裏是天壇的北門，站在這裏已經可以清楚的望見天壇中間那座
最高的建築——皇穹宇，相傳每當皇帝祭天之後，總是到那裏向着無
數個神位叩頭以致謝意。從天壇北門往北則通往著名的凡陛橋。
LONG );
        set("exits", ([
                "south" : "/d/beijing/tiantan",
                "north" : "/d/beijing/tianqiao",
        ]));
        set("objects", ([
                "/d/beijing/npc/girl2" : 1,
        ]));
        set("outdoors", "beijing");
	set("coor/x", -2800);
	set("coor/y", 7640);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}