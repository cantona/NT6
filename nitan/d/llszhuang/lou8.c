#include <ansi.h>
inherit ROOM;
void create()
{
        set("short",CYN"接 天 樓"NOR);
        set("long",
"這是接天樓的第八層，來到了這裡，就已經脫離了凡俗塵世，來吧，\n"
"醉心于這天地之間最完美無暇的交接吧，讓塵世的一切煩惱遠離而去吧。\n"
"此刻，你就如同天地之間一只沙鷗，心靈自由地盤旋飛翔。\n"
);

        set("exits", ([ /* sizeof() == 2 */
          "up" : __DIR__"lou9",
          "down": __DIR__"lou7",
        ]));
        set("no_magic", "1");

        set("objects", ([
            __DIR__"npc/kuangren1" : 1,
                ])
        );

        setup();
}

