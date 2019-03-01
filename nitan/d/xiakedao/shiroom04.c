// /d/xiakedao/shiroom04.c 俠客島 石室4

inherit ROOM;

int do_study(string arg);
void create()
{
        set("short", "石室");
        set("long", @LONG
此洞中仍是較為擁擠。有幾人腳踏北鬥七星方位，或正或逆地行
走；一名老者端坐于北極星位閉目打坐，頭頂隱隱透出絲絲白氣另有
兩個黃衫女子並肩而立，在石壁(wall)上指指點點。
LONG );
        set("exits", ([
                "east" : __DIR__"shihole1"
        ]));
        set("item_desc", ([
                "wall" : @WALL
牆的正上方刻著「颯沓如流星」幾個大字。字的下方刻有一張黃道星
空圖，其中北鬥七星大而明顯。旁有圖注：雖雲“流星”，然動從靜
中求，毋舍本逐末也。又一行小注：春雪似錦秋風颯。
WALL
        ]));
        set("no_clean_up", 0);
        set("no_fight", 1);
        set("no_beg", 1);
        set("coor/x", -3100);
        set("coor/y", -25100);
        set("coor/z", 0);
        setup();
}

#include "/d/xiakedao/shiroom.h"