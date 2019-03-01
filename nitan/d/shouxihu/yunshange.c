// Room: /yangzhou/yunshange.c
// Last Modified by Winder on Jul. 20 2000
#include <ansi.h>;
inherit ROOM;

void create()
{
        set("short","雲山閣");
        set("long",@LONG
雲山閣，面南五楹，閣高于地面不及一丈，中間設台階上下，外中
柱懸掛書魏嘉瑛聯(lian)。
LONG );
        set("item_desc", ([
                "lian" : HIG"
        檻        閣
        前        外
        春        秋
        色        聲
        長        蜀
        堤        嶺
        柳        鬆
\n"NOR,
        ]));

        set("exits", ([
                "south"     : __DIR__"lianxingsi",
        ]));
        set("no_clean_up", 0);
        set("coor/x", -20);
        set("coor/y", 70);
        set("coor/z", 0);
        setup();
        replace_program(ROOM);
}