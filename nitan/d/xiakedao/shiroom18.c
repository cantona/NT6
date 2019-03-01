// /d/xiakedao/shiroom18.c 俠客島 石室18

inherit ROOM;

int do_study(string arg);
void create()
{
        set("short", "石室");
        set("long", @LONG
石室之中平平無奇，也是數人切磋武功，或指點石壁(wall)相互
辯論。偶爾眾人默然，便聽到頭頂傳來潺潺的水聲，想必此處乃是溪
流之下。腳下石磚上遍佈青苔，若不小心便要滑倒。
LONG );
        set("exits", ([
                "north" : __DIR__"shihole5",
        ]));
        set("item_desc", ([
                "wall" : @WALL
此牆上「邯鄲先震驚」幾個大字刻在左側直排。右面圖案甚為奇特，
乃是一隻巨足踏在平地，別無他物。巨足之上肌肉的紋理有百餘條之
多，相互交錯，倒也活靈活現。底部有注：壯於趾，徵兇，有孚。
WALL
        ]));
        set("no_clean_up", 0);
        set("no_fight", 1);
        set("no_beg", 1);
        set("coor/x", -3090);
        set("coor/y", -25510);
        set("coor/z", 0);
        setup();
}

#include "/d/xiakedao/shiroom.h"