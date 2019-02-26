// Room: /d/huashan/yuntai.c
#include <room.h>
inherit ROOM;

void create()
{
        set("short", "雲台峯");
        set("long", @LONG
太華北峯又名雲台峯，它和南面的諸峯連成一條崎嶇的長嶺，構
成了一條魚椎脊似的登峯天梯。香爐峯和樑張峯拱立左右，崢嶸兀突。
雲台四面都是懸崖絕壁，十分險峻。峯頂建有真武宮，朝南通道上立
着石牌樓兩座，高鑲『北峯頂』三字。
LONG );
        set("exits", ([ /* sizeof() == 4 */
            "southdown" : __DIR__"canglong",
        ]));
        set("outdoors", "huashan");
        setup();
}
 
void init()
{
        object me = this_player();
        if( query_temp("xunshan", me))set_temp("xunshan/yuntai", 1, me);
        return;
}