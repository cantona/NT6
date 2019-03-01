#include <ansi.h>
inherit ROOM;
void create()
{
        set("short",CYN"接 天 樓"NOR);
        set("long",
"這是接天樓的第三層，漸行漸高，窗外的風景不住變幻。\n"
);

        set("exits", ([ /* sizeof() == 2 */
          "up" : __DIR__"lou4",
          "down": __DIR__"lou2",
        ]));
        set("no_magic", "1");

        set("objects", ([
                        __DIR__"npc/lisicui" : 1,
                ])
        );

        setup();
}
