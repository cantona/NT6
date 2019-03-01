// Room: /u/zqb/tiezhang/shanlu-7.c
#include <ansi.h>

inherit ROOM;

string look_dazi();

void create()
{
        set("short", "山路");
        set("long", @LONG
你走在一條崎嶇的山路上，道旁山峰壁立，長草過腰，中間一條羊腸小
路，僅容一人勉強過去。前面有一片茂密的鬆林。路旁的石壁上刻著幾個大
字(dazi)。
LONG        );
        set("exits", ([ /* sizeof() == 2 */
  "north" : __DIR__"sslin-1",
  "southdown" : __DIR__"shanlu-6",
]));

    set("item_desc",([
        "dazi"         :       (: look_dazi :),
    ]));
        set("no_clean_up", 0);
        set("outdoors", "tiezhang");

        setup();
}

string look_dazi()
{
        return
        "\n"
"    鐵掌幫重地    \n"    
        "\n"
 "    擅入者----    \n"
RED"              死！    \n"NOR
        "\n";
}