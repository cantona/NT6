// Room: /yangzhou/shuiyun.c
// Last Modified by Winder on Jul. 20 2000
#include <ansi.h>;
inherit ROOM;

void create()
{
        set("short","水雲勝概");
        set("long",@LONG
水雲勝概位於長春橋西，蓮花橋東，昔為清黃履暹別墅，為黃園的
北半部分。面南三楹，中間懸孫軼青題寫的“水雲勝概”匾，外柱懸掛
李白、杜甫詩句集聯(lian)。外廊設木板坐欄。
LONG );
        set("outdoors", "shouxihu");
        set("item_desc", ([
                "lian" : HIG"
        桃        野
        花        竹
        飛        上
        綠        青
        水        霄
\n"NOR,
        ]));

        set("exits", ([
                "east"      : __DIR__"changchunqiao",
                "south"     : __DIR__"lianhuaqiao",
                "southwest" : __DIR__"baitaqingyun",
                "southdown" : __DIR__"pingtai3",
        ]));
        set("no_clean_up", 0);
        set("coor/x", -10);
        set("coor/y", 110);
        set("coor/z", 0);
        setup();
        replace_program(ROOM);
}