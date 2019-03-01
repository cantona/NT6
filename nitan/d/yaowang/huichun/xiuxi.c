
#include <room.h>
inherit ROOM;

void create()
{
        set("short", "休息室");
        set("long", @LONG
這裡是回春堂的休息室，這裡是讓藥局跑堂和醫師休息的地方。
房間內放著整排的床舖，如果你累了，可以在這裡睡一會兒。
LONG );
        set("no_fight", 1);
        set("sleep_room", 1);
        set("exits", ([
                "east" : __DIR__"beiting",
        ]));

        create_door("east", "木門", "west", DOOR_CLOSED);
        setup();
}
