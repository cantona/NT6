// Room: /heizhao/shiqiao.c
// Date: Dec. 8 1999 by Winder

inherit ROOM;
#include <ansi.h>;
void create()
{
        set("short", "小石橋");
        set("long", @LONG
這是一座青石舖砌的小石橋，長虹臥波般連通荷塘兩岸。站在
橋上俯視，荷塘水面隨風皺眉。偶有幾只青蛙從田田蓮葉上鑽入水
底，帶動著一陣陣漣漪。南面望去，荷塘外群山下伏，層霧繚繞，
雲遠天清。
LONG );
        set("outdoors", "taoyuan");
        set("no_clean_up", 0);
        set("exits", ([
                "south"   : __DIR__"hetang",
                "northup" : __DIR__"chanyuan",
        ]));
        set("coor/x", -5020);
        set("coor/y", -1210);
        set("coor/z", 40);
        setup();
        replace_program(ROOM);
}