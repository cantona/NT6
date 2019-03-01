// Room: /d/wuxi/road11.c
// Winder 2000/02/22 

inherit ROOM;
#include <ansi.h>;
void create()
{
        set("short", "黿頭渚");
        set("long", @LONG
太湖三萬六千頃，無限風光在黿頭。來到這裡，你不由地驚嘆人
間竟有如此風景絕佳之處。只見奇山異石，突入太湖碧波之中，層層
巨石 (shi)，半臥湖面，驚濤拍岸，黛浪細騰。登峰遠眺，只覺萬頃
水波疊泛金漚，窮盡目力，心境闊然。
LONG );
        set("outdoors", "wuxi");
        set("no_clean_up", 0);
        set("item_desc", ([
                "shi" : "四個蒼勁有力的大字：  "HIG"包孕吳越\n"NOR,
        ]));
        set("exits", ([
                "east"   : __DIR__"road12",
                "north"  : __DIR__"road10",
        ]));
        set("coor/x", 1040);
	set("coor/y", -810);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}