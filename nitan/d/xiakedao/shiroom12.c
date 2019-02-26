// /d/xiakedao/shishi12.c 俠客島 石室12

inherit ROOM;

int do_study(string arg);
void create()
{
        set("short", "石室");
        set("long", @LONG
大約是刀法僅繪於此石室之故，這裏層層疊疊站了不少人。刀光
霍霍，一名藏僧手持大環刀，呼喝之聲不絕，與三個少年正鬥得走馬
燈相仿。其中綠衣的少年背靠石壁(wall)，似乎極是吃力。
LONG );
        set("exits", ([
                "east"  : __DIR__"shihole3",
        ]));
        set("item_desc", ([
                "wall" : @WALL
牆的正上方刻着「持觴勸侯嬴」幾個大字。下面的圖卻似與詩句毫不
相干。那畫中是一個手持柴刀的樵夫，臂上肌肉隆起。幾十條木柴或
橫或直，雜亂地散落在他面前。圖的四周亦是密密的數百字小注。
WALL
        ]));
        set("no_clean_up", 0);
        set("no_fight", 1);
        set("no_beg", 1);
        set("coor/x", -3100);
        set("coor/y", -25300);
        set("coor/z", 0);
        setup();
}

#include "/d/xiakedao/shiroom.h"