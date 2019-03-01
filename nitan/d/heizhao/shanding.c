// Room: /heizhao/shanding.c
// Date: Dec. 8 1999 by Winder

inherit ROOM;
#include <ansi.h>;
void create()
{
        set("short", "山頂");
        set("long", @LONG
山峰頂上是塊平地，開墾成二十來畝山田，種著禾稻，一柄鋤
頭拋在田邊，一個耕夫上身赤膊，腿上泥污及膝，正在擺布山坡上
一頭仰天臥在一塊巖石上，四足掙紮，站不起來，昂首哀鳴的大黃
牛。
LONG );
        set("outdoors", "taoyuan");
        set("objects", ([
                CLASS_D("dali")+"/yideng/gen" : 1,
                "/d/wudang/npc/cow" : 1,
        ]));
        set("exits", ([
                "down"     : __DIR__"shanlu10",
                "northup"  : __DIR__"shiliang1",
        ]));
        set("coor/x", -5020);
        set("coor/y", -1260);
        set("coor/z", 30);
        setup();
        replace_program(ROOM);
}