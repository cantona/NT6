// Room: /d/huashan/jzroad7.c

#include <room.h>
inherit ROOM;

void create()
{
        set("short", "峭壁");
        set("long", @LONG
你走在峭壁邊的小路上。一側是密密的叢林，外側卻是極深的陡
壁。山風凜冽，幾乎要把你刮落崖去。
LONG );
        set("exits", ([ /* sizeof() == 4 */
            "eastdown" : __DIR__"jzroad6",
            "southup"  : __DIR__"shangu",
        ]));
        set("outdoors", "huashan");
        set("no_clean_up", 0);

        setup();
        replace_program(ROOM);
}
