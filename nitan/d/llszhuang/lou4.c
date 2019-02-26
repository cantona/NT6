#include <ansi.h>
inherit ROOM;
void create()
{
        set("short",CYN"接 天 樓"NOR);
        set("long",
"這是接天樓的第四層，窗外夜幕低垂，星光點點，在這大雪後的純美\n"
"世界上舞躍閃爍，像在為俯仰着道諸般一切的接天樓上正在發生的盛事，\n"
"奏起了寂靜偉大的樂章。\n"
);

        set("exits", ([ /* sizeof() == 2 */
          "up" : __DIR__"lou5",
          "down": __DIR__"lou3",
        ]));
        set("no_magic", "1");

        set("objects", ([
                        __DIR__"npc/zhouwushu" : 1,
                ])
        );

        setup();
}
