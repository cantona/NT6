// Room: /d/hengshan/huixiantai.c
// Date: Oct. 2 1997 by That

#include <room.h>
inherit ROOM;
void create()
{
        set("short", "見性峰山道");
        set("long", @LONG
你走在見性峰山脊小路上，聽著山下廟宇的鐘鼓，眼前白雲漂盪，
感覺幽逸極了。
LONG);
        set("exits", ([ /* sizeof() == 4 */
                "southdown"  : __DIR__"beiyuedian",
                "northup"    : __DIR__"shandao2",
        ]));
        set("no_clean_up", 0);
        set("coor/x", 30);
        set("coor/y", 3190);
        set("coor/z", 80);
        setup();
        replace_program(ROOM);
}
