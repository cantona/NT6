#include <room.h>
inherit ROOM;

void create()
{
        set("short", "休息室");
        set("long", @LONG
這是福壽庵接待峨嵋女俠們的休息室，峨嵋女弟子回山之前通常
在此借宿一宿，好備足體力上山。房內擺有一張桌，靠牆設有幾張木
牀。
LONG );
        set("exits", ([
                "south" : __DIR__"fsazhaitang",
        ]));
        create_door("south", "門", "north", DOOR_CLOSED);
        set("sleep_room", 1);
        set("no_fight", 1);
        set("no_clean_up", 0);
        set("coor/x", -450);
        set("coor/y", -230);
        set("coor/z", 70);
        set("coor/x", -450);
        set("coor/y", -230);
        set("coor/z", 70);
        setup();
}
