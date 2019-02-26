#include <room.h>
inherit ROOM;

void create()
{
        set("short", "齋堂");
        set("long", @LONG
這裏便是峨嵋福壽庵的齋堂。福壽庵本不大，但由於經常接待其
他庵的弟子，齋堂倒也不小。只見廳內擺滿了長長的餐桌和長凳，幾
位小師太正來回忙碌着佈置素齋。桌上擺了幾盆豆腐，花生，青菜以
及素鴨等美味素食。北面有一扇門。
LONG );
        set("exits", ([
                "east"  : __DIR__"lingwenge",
                "north" : __DIR__"fsaxiuxishi",
        ]));
        create_door("north", "門", "south", DOOR_CLOSED);
        set("no_clean_up", 0);
        set("coor/x", -450);
        set("coor/y", -240);
        set("coor/z", 70);
        setup();
}
