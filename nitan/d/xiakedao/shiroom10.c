// /d/xiakedao/shiroom10.c 俠客島 石室10

inherit ROOM;

int do_study(string arg);
void create()
{
        set("short", "石室");
        set("long", @LONG
這裡卻也安靜。右面地上一人橫臥，似是過度疲倦，已經沉沉
睡去。一個布衣男子袖手而立，呆呆地望著石壁(wall)出神他身旁
站著一位美貌少婦。旁邊的火把將要燃盡，搖曳不定。地上橫七豎
八丟棄了一些破損的兵刃。
LONG );
        set("exits", ([
                "north" : __DIR__"shihole3",
        ]));
        set("item_desc", ([
                "wall" : @WALL
牆的正上方刻著「脫劍膝前橫」幾個大字。字的下方未見圖畫，只是
大大小小，以各種字體寫滿了注釋。一行草書是：杜工部詩雲：一舞
劍器動四方。又一行隸書入石甚深：江南山水通志：嶺南有石，瘦長
似劍傳有神異，土人多膜拜。名為橫另有寥寥幾個蠅頭小楷：戴，而
後脫之。
WALL
        ]));
        set("objects", ([
                __DIR__"master/hongantong" : 1,
                __DIR__"master/suquan"    : 1,
        ]));
/*
  神龍教開山祖師 洪安通(Hong antong)
  神龍教教主夫人 蘇荃(Su quan)
*/
        set("no_clean_up", 0);
        set("no_fight", 1);
        set("no_beg", 1);
        set("coor/x", -3090);
        set("coor/y", -25310);
        set("coor/z", 0);
        setup();
}

#include "/d/xiakedao/shiroom.h"