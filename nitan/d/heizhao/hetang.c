// Room: /heizhao/hetang.c
// Date: Dec. 8 1999 by Winder

inherit ROOM;
#include <ansi.h>;
void create()
{
        set("short", "荷塘");
        set("long", @LONG
高山上有這樣的荷塘，本就希罕，塘中更茂然長滿紅紅白白的
荷花。塘邊堤岸上種了不少棕櫚樹，在山風中伸展搖晃著，嘩啦作
響。塘中污泥約有三尺來深，荷塘正中一條小石橋通往對面。
LONG );
        set("outdoors", "taoyuan");
        set("no_clean_up", 0);
        set("exits", ([
                "south"  : __DIR__"yideng9",
                "north"  : __DIR__"shiqiao",
        ]));
        set("coor/x", -5020);
        set("coor/y", -1220);
        set("coor/z", 40);
        setup();
        replace_program(ROOM);
}