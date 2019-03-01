#include <room.h>
#include <ansi.h>
inherit ROOM;

void create()
{
            set("short", "殿堂");
            set("long", @LONG
走到大殿之後，見是一座較小的殿堂，殿中情景卻尤為可
怖，數十具骸骨一堆堆相互糾結，骸骨大都直立如生時，有的
手中握有兵刃，有的卻是空手。西側有一扇小石門。
LONG);
        set("objects", ([
                __DIR__"obj/yudao" : random(2),
                __DIR__"obj/yujian" : random(2),
                __DIR__"obj/skeleton" : random(3) + 1,
        ]));

        set("exits", ([ 
                "south" : __DIR__"dadian",
                "west" : __DIR__"yushi",
            ]));
            create_door("west", WHT "小石門" NOR, "east", DOOR_CLOSED);
            setup();
}
