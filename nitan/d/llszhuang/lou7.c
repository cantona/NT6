#include <ansi.h>
inherit ROOM;
void create()
{
        set("short",CYN"接 天 樓"NOR);
        set("long",
"這是接天樓的第七層，處于此處，真有伸手即可摘下星辰的感覺，你\n"
"的靈覺不住地擴大，直至象要和天地融為一體。\n"
);

        set("exits", ([ /* sizeof() == 2 */
          "up" : __DIR__"lou8",
          "down": __DIR__"lou6",
        ]));
        set("no_magic", "1");

        set("objects", ([
                        __DIR__"npc/wangbashuai" : 1,
                ])
        );

        setup();
}
