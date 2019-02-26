// Room: /u/zqb/tiezhang/xzfeng.c
#include <ansi.h>

inherit ROOM;

void create()
{
    set("short", RED"小指峯"NOR);
        set("long", @LONG
你已登上了小指峯的峯頂。縱目遠眺，但見遠處四峯已淹沒在濃濃的迷
霧之中。這裏的高度恰在雲霧之中，你只能看清身前幾米的景物。不知不覺
中你的衣服已被水氣沁濕，涼風襲來，凍得你瑟瑟發抖。
LONG        );
        set("exits", ([ /* sizeof() == 1 */
  "southdown" : __DIR__"pubu",
]));
        set("no_clean_up", 0);

        setup();
        replace_program(ROOM);
}