// shiji3.c
// Modified by Winder June.25 2000

#include <room.h>
inherit ROOM;

void create()
{
        set("short", "石級");
        set("long", @LONG
這是一段向南北方向伸展的石級，四周由於缺乏光亮，難免有點陰
森森的感覺，北面是個月形的銅門，南面是個石室。
LONG );
        set("exits", ([
                "south" : __DIR__"shishi2",
                "north" : __DIR__"tongmen",
        ]));
        create_door("south", "石門", "north", DOOR_CLOSED);
        set("no_clean_up", 0);
        set("coor/x", -50000);
        set("coor/y", -21030);
        set("coor/z", -40);
        setup();
}
