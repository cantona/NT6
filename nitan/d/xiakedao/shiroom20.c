// /d/xiakedao/shiroom20.c 俠客島 石室20

inherit ROOM;

int do_study(string arg);
void create()
{
        set("short", "石室");
        set("long", @LONG
進得門來，便覺陣陣有形無質的氣浪逼人，功力稍差之人似乎要
站立不穩。幾位老者正在場中互較內功，身上衣衫高高蓬起。幾名旁
觀者均背靠石壁(wall)而立，神色緊張。
LONG );
        set("exits", ([
                "east"  : __DIR__"shihole5",
        ]));
        set("item_desc", ([
                "wall" : @WALL
牆的正上方刻着「煊赫大梁城」幾個大字。下方圖案極為簡單，繪了
一團烈焰騰空而起，遠觀卻又似混沌太極之形。一行註解寫在圖案正
中：剛不可久，柔不可守。圖外亦注：《光武紀》：氣佳哉！鬱郁葱
葱然。
WALL
        ]));
        set("objects", ([
                __DIR__"master/du-nan"   : 1,
                __DIR__"master/du-e" : 1,
                __DIR__"master/du-jie" : 1,
                __DIR__"master/ai-laozhe" : 1,
                __DIR__"master/gao-laozhe" : 1,
        ]));
        set("no_clean_up", 0);
        set("no_fight", 1);
        set("no_beg", 1);
        set("coor/x", -3100);
        set("coor/y", -25500);
        set("coor/z", 0);
        setup();
}

#include "/d/xiakedao/shiroom.h"