// Date: Java 97/04/9

inherit ROOM;
#include <room.h>;
void create()
{
        set("short", "石室");
        set("long", @LONG
這是一條小小的甬道，周圍都是石壁，極為堅硬，看來不是什麼
武功能打破的。石室裡伸手不見無指，順著石壁你摸索著好象周圍有
石門。
LONG );
        set("exits", ([
                "south" : __DIR__"midao6",
                "north" : __DIR__"midao2",
                "east"  : __DIR__"midao11",
                "west"  : __DIR__"midao9",
        ]));
        set("no_clean_up", 0);
        set("no_drop", 1);
        setup();
        create_door("south", "石門", "north", DOOR_CLOSED);
        create_door("north", "石門", "south", DOOR_CLOSED);
        create_door("east",  "石門", "west",  DOOR_CLOSED);
        create_door("west",  "石門", "east",  DOOR_CLOSED);
}
