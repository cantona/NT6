#include <ansi.h>
inherit ROOM;
void create()
{
        set("short",CYN"接 天 樓"NOR);
        set("long",
"這是接天樓的第一層，窗外松林蔽日，使得這裏看起來十分的昏暗。\n"
);

        set("exits", ([ /* sizeof() == 2 */
          "up" : __DIR__"lou2",
          "out": __DIR__"lou0",
        ]));
        set("no_magic", "1");

        set("objects", ([
                        __DIR__"npc/qianerbai" : 1,
                ])
        );

        setup();
}
