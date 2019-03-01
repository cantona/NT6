//Cracked by Kafei
#include <room.h>
inherit ROOM;

void create()
{
        set("short", "山頂");
        set("long", @LONG
這是山峰的頂上，一大塊平地，開墾成二十來畝山田，種著禾稻，
一柄鋤頭拋在田邊，半坡上斜出一塊巖石(rock)，一頭黃牛仰臥其上，
四蹄亂蹬，卻翻不過身來。下面一人擺起丁字步，雙手牢牢的托住了
巖石。
LONG );

        set("exits", ([
                "down" : __DIR__"yideng4",
        ]));
        set("item_desc", ([
                "rock" : "這頭牛少說也有三百斤上下，巖石的份量瞧來也不在那牛之下，雖有\n一半靠著山坡，但那人穩穩托住，也算得是神力驚人。\n",
        ]));
        set("no_fight", "1");
        set("objects", ([
                CLASS_D("dali") + "/farmer" : 1, 
        ]));

        set("invalid_startroom", 1);
        set("coor/x", -38000);
        set("coor/y", -80000);
        set("coor/z", 200);
        setup();
}