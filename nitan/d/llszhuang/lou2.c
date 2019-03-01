#include <ansi.h>
inherit ROOM;
void create()
{
        set("short",CYN"接 天 樓"NOR);
        set("long",
"這是接天樓的第二層，樓的內壁上全是精美的壁畫，可你現在肯定沒\n"
"有功夫欣賞。。\n"
);

        set("exits", ([ /* sizeof() == 2 */
          "up" : __DIR__"lou3",
          "down": __DIR__"lou1",
        ]));
        set("no_magic", "1");

        set("objects", ([
                        __DIR__"npc/sunsanhui" : 1,
                ])
        );

        setup();
}
