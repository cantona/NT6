// Room: /d/shaolin/shulin7.c
// Date: YZC 96/01/19

inherit ROOM;

void create()
{
        set("short", "松樹林");
        set("long", @LONG
你眼前驟然一黑，朦朧中，只見左右前後，到處都是鋪天蓋地的
松樹林。幾十丈高的大松樹簇在一塊，密實的枝葉象一蓬蓬巨傘恆伸
向天空，把陽光遮得絲毫也無。尺把厚的松針積在地上，一腳踩下去，
半天拔不出來。你似乎迷失了方向，象沒頭蒼蠅般到處亂闖。
LONG );
        set("exits", ([
                "east" : __DIR__"shulin8",
                "south" : __DIR__"shulin"+(random(10)+2),
                "west" : __DIR__"shulin"+(random(10)+2),
                "north" : __DIR__"shulin6",
        ]));
        set("outdoors", "shaolin");
        setup();
        replace_program(ROOM);
}
