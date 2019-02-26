#include <room.h>

inherit ROOM;

void create()
{
        set("short", "小路");
        set("long", @LONG
這是一條小土路，兩旁雜草叢生，非常荒涼，看樣子很少有
人來這裏。南面是一扇小木門，背面是一片荊棘叢。
LONG
        );
        set("exits", ([ /* sizeof() == 2 */
  "north" : __DIR__"jingji1",
  "south" : __DIR__"tulu3",
]));

        set("outdoors", "yaowang");
        setup();
        create_door("south", "木門", "north", DOOR_CLOSED);
}
