#include <ansi.h>
inherit ROOM;
void create()
{
        set("short",CYN"接 天 樓"NOR);
        set("long",
"這是接天樓的第六層，夜風襲人，在這瓊樓玉宇之上，便是內功深厚\n"
"之人，也不免有些高處不勝寒之感。\n"
);

        set("exits", ([ /* sizeof() == 2 */
          "up" : __DIR__"lou7",
          "down": __DIR__"lou5",
        ]));
        set("no_magic", "1");

        set("objects", ([
                        __DIR__"npc/zhengqimie" : 1,
                ])
        );

        setup();
}
