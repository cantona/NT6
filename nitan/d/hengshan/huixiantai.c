// Room: /d/hengshan/huixiantai.c
// Date: Oct. 2 1997 by That

#include <room.h>
inherit ROOM;
void create()
{
        set("short", "會仙台");
        set("long", @LONG
走出北岳殿，就能看見一個石窟，緊靠在絕壁中鑿出的一個小室，
就是會仙台。台上排列群仙雕像，密密麻麻，不能勝數。
LONG);
        set("exits", ([ /* sizeof() == 4 */
                "eastdown"  : __DIR__"beiyuedian",
                "up" : "/d/reborn/jitan4",
        ]));
        set("no_clean_up", 0);
        set("coor/x", 20);
        set("coor/y", 3180);
        set("coor/z", 80);
        setup();
        replace_program(ROOM);
}
