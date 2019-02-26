// /d/xiakedao/shiroom15.c 俠客島 石室15
inherit ROOM;

int do_study(string arg);
void create()
{
        set("short", "石室");
        set("long", @LONG
這裏酒氣濃重，地上拋棄了不少酒袋或葫蘆。東側兩人説話已經
含糊不清，兀自向嘴裏不停倒酒，踉蹌地模仿石壁(wall)上的圖案。
距二人丈許外一個女子掩鼻而立，面帶厭惡之色。
LONG );
        set("exits", ([
                "west"  : __DIR__"shihole4",
        ]));
        set("item_desc", ([
                "wall" : @WALL
牆的正上方刻着「眼花耳熱後」幾個大字。下面刻的是魯智深醉鬧山
門的故事，畫中的胖和尚大醉如泥，惟妙惟肖。空中又繪着無數落葉，
隨風飛舞。
WALL
        ]));
        set("no_clean_up", 0);
        set("no_fight", 1);
        set("no_beg", 1);
        set("coor/x", -3080);
        set("coor/y", -25400);
        set("coor/z", 0);
        setup();
}

#include "/d/xiakedao/shiroom.h"