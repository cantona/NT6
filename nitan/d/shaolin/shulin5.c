// Room: /d/shaolin/shulin5.c
// Date: YZC 96/01/19

inherit ROOM;

void create()
{
        set("short", "鬆樹林");
        set("long", @LONG
地的鬆樹林。幾十丈高的大鬆樹簇在一塊，密實的枝葉象一蓬蓬
巨傘恆伸向天空，把陽光遮得絲毫也無。尺把厚的鬆針積在地上，一
腳踩下去，半天拔不出來。你似乎迷失了方向，象沒頭蒼蠅般到處亂
闖。
LONG );
        set("exits", ([
                "east" : __DIR__"shulin"+(random(10)+2),
                "south" : __DIR__"shulin4",
                "west" : __DIR__"shulin"+(random(10)+2),
                "north" : __DIR__"shulin6",
        ]));
        set("outdoors", "shaolin");
        setup();
        replace_program(ROOM);
}
