// Room: /d/lingzhou/chaifang.c

inherit ROOM;
#include "room.h"
void create()
{
        set("short", "柴房");
        set("long", @LONG
這裏是間不小的柴房，整齊的碼着兩人高的上好木柴，散發着木頭
特有的清香，宮裏的柴火一向都是每月一次從城外的落日林運來。
LONG
        );
        set("exits", ([ /* sizeof() == 2 */
                "south" : __DIR__"yushanfang",
                "east"  : __DIR__"biangate",
        ]));
        create_door("east","木門","west",DOOR_CLOSED);
        set("coor/x", -6265);
        set("coor/y", 2985);
        set("coor/z", 0);
        setup();
}
