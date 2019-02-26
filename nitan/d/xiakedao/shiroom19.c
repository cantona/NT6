// /d/xiakedao/shiroom19.c 俠客島 石室19

inherit ROOM;

int do_study(string arg);
void create()
{
        set("short", "石室");
        set("long", @LONG
這裏極為低矮，身材稍高之人便要低頭。室內僅餘西北角一支火
把，其餘的均已燃為灰燼，在昏暗的光線中，僅有一人盤膝而坐，對
照石壁(wall)比劃着。只見掌指交替，繁雜無比。
LONG );
        set("exits", ([
                "west"  : __DIR__"shihole5",
        ]));
        set("item_desc", ([
                "wall" : @WALL
牆的正上方刻着「千秋二壯士」幾個大字。下方繪出侯嬴與朱亥二人
攜手而行，正是古風“俠客行”原意。側面一行小楷：子曰：知者樂
水，仁者樂山。知者動，仁者靜。又注：莊子秋水篇：不知何時止而
不盈，尾閭瀉之。
WALL
        ]));
        set("no_clean_up", 0);
        set("no_fight", 1);
        set("no_beg", 1);
        set("coor/x", -3080);
        set("coor/y", -25500);
        set("coor/z", 0);
        setup();
}

#include "/d/xiakedao/shiroom.h"