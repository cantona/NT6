// zhanqiao.c
// Date: Oct. 2 1997 by That

#include <room.h>
inherit ROOM;
void create()
{
        set("short", "懸空棧橋");
        set("long", @LONG
棧道懸于南北危樓之間，由無數的掾舖成，每節掾寬尺許，九節並
排在一起，每根掾綁在鐵索上，上舖木板，長數十丈，下臨深淵。山風
呼嘯，驚心動魄。
LONG);
        set("exits", ([ /* sizeof() == 4 */
                "south"   : __DIR__"xuankong2",
                "north"   : __DIR__"xuankong1",
        ]));
        set("outdoors", "hengshan");
        set("no_clean_up", 0);
        set("coor/x", 0);
        set("coor/y", 3170);
        set("coor/z", 30);
        setup();
        replace_program(ROOM);
}