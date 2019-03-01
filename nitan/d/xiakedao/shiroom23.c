// /d/xiakedao/shiroom23.c 俠客島 石室23

inherit ROOM;

int do_study(string arg);
void create()
{
        set("short", "石室");
        set("long", @LONG
石室中有三個蒲團，僅正中蒲團坐有一人，正與一個面色焦黃的
女子對掌。那女子似是行有餘力，尚有閒暇不時瞟一眼石壁(wall)，
空着的左手也在虛擬作勢。一個書生手持筆墨，在地下隨寫隨抹，搖
頭晃腦地很是得意。
LONG );
        set("exits", ([
                "west" : __DIR__"shihole6",
        ]));

        set("item_desc", ([
                "wall" : @WALL
幾個大字「誰能書閣下」在右側直排。左邊圖上繪的是一名高瘦老者，
正自端坐撫琴。只見他左手捻弦，右手虛揚，面上的微笑也甚是優雅。
一行淡淡的注云：李侍郎致酒行：空將箋上兩行書。又注：《道德經》
雲：反者道之動，弱者道之用。
WALL
        ]));
        set("no_clean_up", 0);
        set("no_fight", 1);
        set("no_beg", 1);
        set("coor/x", -3080);
        set("coor/y", -25600);
        set("coor/z", 0);
        setup();
}

#include "/d/xiakedao/shiroom.h"