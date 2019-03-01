// Room: /d/gaochang/road.c
// Last Modified by Winder on Jul. 15 2000

inherit ROOM;
#include <ansi.h>;

void create ()
{
        set ("short", "沙丘小路");
        set ("long",
"注意：由此處向北！將進入高昌迷宮地域，不知走法和沒有作好準
備的玩家請考慮清楚是否還要向北行。
              
                    "HIR"高   昌   迷   宮\n\n\n"NOR

);

        set("outdoors", "gaochang");
        set("exits", ([ /* sizeof() == 2 */
                "north" : __DIR__"shulin1",
//                "west" : "/d/xingxiu/shanjiao",
                "south" : "/d/hasake/shulin1",
        ]));
        set("objects", ([ /* sizeof() == 2 */
                __DIR__"npc/liwenxiu" : 1,
        ]));

        set("coor/x", -38000);
        set("coor/y", 10000);
        set("coor/z", 0);
        setup();
        replace_program(ROOM);
}