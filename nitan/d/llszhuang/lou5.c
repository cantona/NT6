#include <ansi.h>
inherit ROOM;
void create()
{
        set("short",CYN"接 天 樓"NOR);
        set("long",
"這是接天樓的第五層，這已經是人世間難以企及的高度，從窗子往外\n"
"望去，遠處萬家燈火，與繁星爭輝，近處山莊左近卻是一片漆黑，不時傳\n"
"來異樣的聲音。\n"
);

        set("exits", ([ /* sizeof() == 2 */
          "up" : __DIR__"lou6",
          "down": __DIR__"lou4",
        ]));
        set("no_magic", "1");

        set("objects", ([
                        __DIR__"npc/wuliupo" : 1,
                ])
        );
       setup();
}
