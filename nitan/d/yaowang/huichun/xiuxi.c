
#include <room.h>
inherit ROOM;

void create()
{
        set("short", "休息室");
        set("long", @LONG
這裏是回春堂的休息室，這裏是讓藥局跑堂和醫師休息的地方。
房間內放着整排的牀鋪，如果你累了，可以在這裏睡一會兒。
LONG );
        set("no_fight", 1);
        set("sleep_room", 1);
        set("exits", ([
                "east" : __DIR__"beiting",
        ]));

        create_door("east", "木門", "west", DOOR_CLOSED);
        setup();
}
