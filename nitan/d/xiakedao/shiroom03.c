// /d/xiakedao/shiroom03.c 俠客島 石室3

inherit ROOM;

int do_study(string arg);
void create()
{
        set("short", "石室");
        set("long", @LONG
洞中風聲勁急，數道身影正在洞中迅速異常地奔跑，直帶得滿
室生風。一人身法輕靈飄逸，另一人則古樸穩健，更有一人無甚特
異之處，卻也十分迅捷。幾人奔跑中兀自不停爭論，而語氣甚是平
靜。旁邊石壁(wall)上也是有圖有字。
LONG );
        set("exits", ([
                "west"  : __DIR__"shihole1",
        ]));
        set("item_desc", ([
                "wall" : @WALL
牆的正上方刻著「銀鞍照白馬」幾個大字。字的下方刻著一匹駿馬，
昂首奔行，腳下雲氣彌漫，便如是在天空中飛行一般。只見一團團雲
霧似乎在不斷向前排湧，直如意欲破壁飛出。
WALL
        ]));
        set("no_clean_up", 0);
        set("no_fight", 1);
        set("no_beg", 1);
        set("coor/x", -3080);
        set("coor/y", -25100);
        set("coor/z", 0);
        setup();
}

#include "/d/xiakedao/shiroom.h"