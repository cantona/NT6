// /d/xiakedao/shiroom17.c 俠客島 石室17

inherit ROOM;

int do_study(string arg);
void create()
{
        set("short", "石室");
        set("long", @LONG
這裏鏗鏘之聲不絕，一個身材矮小的漢子手持黃金棍，與使蛾眉
刺的少婦雙戰一個瘦子。那瘦子在一片黃光中身形晃動，絲毫不落下
風。兵刃勁風激盪之下，火把也熄滅了兩支。石壁(wall)上的圖譜隱
約可見。
LONG );
        set("exits", ([
                "south" : __DIR__"shihole5",
        ]));
        set("item_desc", ([
                "wall" : @WALL
牆的正上方刻着「救趙揮金槌」幾個大字。下面的圖畫波瀾壯闊，豪
氣逼人。正是嶽武穆大破金兵，八大錘鬧朱仙鎮。只見刀槍蔽日，血
肉橫飛。旁邊註釋不多，均是筆力雄健。
WALL
        ]));
        set("no_clean_up", 0);
        set("no_fight", 1);
        set("no_beg", 1);
        set("coor/x", -3090);
        set("coor/y", -25490);
        set("coor/z", 0);
        setup();
}

#include "/d/xiakedao/shiroom.h"