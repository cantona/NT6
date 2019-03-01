// Room: /d/huashan/jzroad6.c

#include <room.h>
inherit ROOM;

void create()
{
        set("short", "樹林外");
        set("long", @LONG
樹林外，赫然站着一個漢子，在陰森森的林子邊上，憑添一股煞
氣。西上是登山的路，東邊就進入森林了。
LONG );
        set("exits", ([ /* sizeof() == 4 */
            "enter"   : __DIR__"jzroad5",
            "westup"  : __DIR__"jzroad7",
        ]));
        set("objects", ([
             CLASS_D("huashan") + "/cheng-buyou": 1,
        ]));
//        set("no_clean_up", 0);

        setup();
        replace_program(ROOM);
}
