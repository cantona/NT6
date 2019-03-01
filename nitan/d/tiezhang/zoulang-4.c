#include <room.h>
inherit ROOM;

void create()
{
        set("short", "走廊");
        set("long", @LONG
你走在一條走廊上。北面似乎有個黑暗的小屋，還隱隱傳來一些酣聲。
LONG    );
        set("exits", ([ 
                "west" : __DIR__"zoulang-1",
                "north" : __DIR__"xxs",
        ]));

        create_door("north", "木門", "south", DOOR_CLOSED);

        set("no_clean_up", 0);

        setup();
}