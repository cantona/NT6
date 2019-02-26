// Room: /d/shaolin/zhonglou5.c
// Date: YZC 96/01/19

inherit ROOM;

void create()
{
        set("short", "鐘樓五層");
        set("long", @LONG
一眼望去，只見藍天白雲，青山列列，令人將塵俗之氣，頓為一
一掃。南至前三殿，北到方丈樓，整個少林寺盡在眼底。北面竹林隨
風起伏，猶如一片竹海。東西面圍繞全寺的是密密匝匝的松林，一眼
往不到邊。
LONG );
        set("exits", ([
                "up" : __DIR__"zhonglou6",
                "down" : __DIR__"zhonglou4",
        ]));
        set("no_clean_up", 0);
        setup();
        replace_program(ROOM);
}
