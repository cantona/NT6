// /d/xiakedao/shiroom06.c 俠客島 石室6

inherit ROOM;

int do_study(string arg);
void create()
{
        set("short", "石室");
        set("long", @LONG
這間石室中卻恰巧無人觀看圖譜，端的是冷冷清清，隔壁傳來隱
隱的喧囂。牆上火把靜靜地燃燒着，偶爾發出輕微的畢駁之聲，空中
有陣陣松脂的氣味，石壁(wall)也被燻黑了幾處。
LONG );
        set("exits", ([
                "north" : __DIR__"shihole2",
        ]));
        set("item_desc", ([
                "wall" : @WALL
牆的正上方刻着「千里不留行」幾個大字。字的下方刻有圖案，乃是
一條普通的驛道。遠處一架馬車若隱若現，道上煙塵四起，漸漸地與
空中的雲霧交織成一片。旁邊的註解甚多，一時也辨認不清。
WALL
        ]));
        set("no_clean_up", 0);
        set("no_fight", 1);
        set("no_beg", 1);
        set("coor/x", -3090);
        set("coor/y", -25210);
        set("coor/z", 0);
        setup();

}

#include "/d/xiakedao/shiroom.h"