#include <room.h>
inherit ROOM;

void create()
{
        set("short", "儲藏室");
        set("long", @LONG
這裡是個儲藏室，四周密不透風，只有一扇關閉著的大門。
LONG );
        set("exits", ([
                "west" : __DIR__"yuanzi",
        ]));
        create_door("west", "木門", "east", DOOR_CLOSED);
        set("coor/x", -49970);
        set("coor/y", 20010);
        set("coor/z", 20);
        setup();
}
