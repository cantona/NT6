// /d/xiakedao/shiroom05.c 俠客島 石室5

inherit ROOM;

int do_study(string arg);
void create()
{
        set("short", "石室");
        set("long", @LONG
一位仙風道骨的老者正和一位高大的西域人切磋武功，兩人均是
虛持空劍，招式忽快忽慢，陣陣勁風將室內得火把激盪得明暗不定，
石壁(wall)上圖案亦是班駁陸離。
LONG );
        set("exits", ([
                "south" : __DIR__"shihole2",
        ]));
        set("item_desc", ([
                "wall" : @WALL
牆的正上方刻着「十步殺一人」幾個大字。其下的圖案卻是一副工筆
山水，畫的是山邊密林，那樹木的枝條長短不一，前後縱橫，倒也筆
力雄健，栩栩如生。圖旁有無數小注。
WALL
        ]));
        set("objects", ([
                __DIR__"master/ouyangfeng" : 1,
                __DIR__"master/ding"       : 1,
        ]));
/*
歐陽鋒説道：十步一人，百步十人，人力有限，如何殺呢。
歐陽鋒開始認真考慮這個問題。

歐陽鋒突然挺身倒下，手中蛇杖一招「蛇遊蟒走」，貼着地皮纏向丁春秋的左腿！
結果重重地擊中，丁春秋「哇」地一聲吐出一口鮮血！
( 丁春秋看起來可能受了點輕傷。 )

歐陽鋒突然雙手撐地，雙足夾住蛇杖，裹着一陣風聲打向丁春秋！
結果只聽見「砰」地一聲巨響，丁春秋像一捆稻草般飛了出去！！
( 丁春秋動作似乎開始有點不太靈光，但是仍然有條不紊。 )
*/
        set("no_clean_up", 0);
        set("no_fight", 1);
        set("no_beg", 1);
        set("coor/x", -3090);
        set("coor/y", -25190);
        set("coor/z", 0);
        setup();
}

#include "/d/xiakedao/shiroom.h"