#include <ansi.h>
inherit ROOM;
void create()
{
        set("short",CYN"接 天 樓"NOR);
        set("long",
"前方是一座高若三十來丈，座落在樹木蒼蒼的小平頂山上九層的高樓\n"
"，其台基邊緣有雕刻精細的荷葉凈瓶石欄桿，周圍出廊，與附近的山莊樓\n"
"台相連起來，儼然一體。這些樓閣亭台規模弘整、布局相連，形成了一個\n"
"龐大的建築組。人處其內，有種迷失了個人的渺小感覺．\n"
);

        set("exits", ([ /* sizeof() == 2 */
          "east" : __DIR__"dynamic/jiuqu9",
          "enter": __DIR__"lou1",
          "west": __DIR__"shishi",
        ]));
        set("no_magic", "1");

        set("objects", ([
                        __DIR__"npc/zhaoyishang" : 1,
                ])
        );

        setup();
}
