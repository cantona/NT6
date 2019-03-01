// /d/xiakedao/shiroom13.c 俠客島 石室13

inherit ROOM;

int do_study(string arg);
void create()
{
        set("short", "石室");
        set("long", @LONG
石室正中三人席地而坐，各自閉目吐納，隱然是天地人三才的陣
勢。一個書生手持幾根短竹，在地下來回擺弄，似乎正在佔卜。偶爾
抬頭望望石壁(wall)，若有所悟。
LONG );
        set("exits", ([
                "south" : __DIR__"shihole4",
        ]));
        set("item_desc", ([
                "wall" : @WALL
牆的正上方刻著「三杯吐然諾」幾個大字。字的下方卻刻的是一副淡
淡的伏羲八卦圖案，頗有些文不對題。一旁有注：經曰：困于酒食，
朱紱方來，利用享祀。又有注雲：老子曰：致虛極，守靜篤。另有些
篆字小注，語意艱深。
WALL
        ]));
        set("no_clean_up", 0);
        set("no_fight", 1);
        set("no_beg", 1);
        set("coor/x", -3090);
        set("coor/y", -25390);
        set("coor/z", 0);
        setup();
}

#include "/d/xiakedao/shiroom.h"