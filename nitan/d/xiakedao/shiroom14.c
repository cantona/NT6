// /d/xiakedao/shiroom14.c 俠客島 石室14
inherit ROOM;

int do_study(string arg);
void create()
{
        set("short", "石室");
        set("long", @LONG
這裡光線黯淡，水珠時而從頭頂的石壁上滴下，略略有些霉氣把
石室照得明亮。壁上刻得有圖有字。右側一位老乞丐正在對著獨自石
壁(wall)練拳，拳勁十足。
LONG );
        set("exits", ([
                "north" : __DIR__"shihole4",
        ]));
        set("item_desc", ([
                "wall" : @WALL
這面牆的字跡卻與眾不同，幾個大字「五岳倒為輕」刻在正中。在大
字的比劃中間，是密密的一段段小注，深淺不一。遠遠看去，卻又頗
似圖畫。識得一行注是：象曰：山下有澤，損，君子以懲忿窒欲。
WALL
        ]));
        set("objects", ([
                __DIR__"master/hong"   : 1,
        ]));
        set("no_clean_up", 0);
        set("no_fight", 1);
        set("no_beg", 1);
        set("coor/x", -3090);
        set("coor/y", -25410);
        set("coor/z", 0);
        setup();
}

#include "/d/xiakedao/shiroom.h"