// Room: /d/shaolin/shulin1.c
// Date: YZC 96/01/19

inherit ROOM;

void create()
{
        set("short", "松樹林");
        set("long", @LONG
這是一片松樹林。幾十丈高的大松樹簇在一塊，密實的枝葉象一
蓬蓬巨傘恆伸向天空，把陽光遮得絲毫也無。尺把厚的松針積在地上，
一腳踩下去，半天拔不出來。
LONG );
        set("exits", ([
                "east" : __DIR__"shulin"+(random(10)+2),
                "south" : __DIR__"shulin2",
                "west" : __DIR__"guangchang1e",
                "north" : __DIR__"shulin"+(random(10)+2),
        ]));
        set("outdoors", "shaolin");
        set("objects",([
                __DIR__"obj/fake-gold" : 1,
        ]));
        setup();
        replace_program(ROOM);
}
