// Room: /huanghe/qingcheng.c
// Java. Sep 21 1998

#include <room.h>

inherit ROOM;
void create()
{
        set("short", "青城");
        set("long", @LONG
青城位於靖遠以南三百二十里，西南八十里就是蘭州，名為青城，
其實只是個小鎮，因為地處北去西夏的要衝，許多往來西夏和大宋的商
旅都必須經過這兒，人來人往很是熱鬧。
LONG );
        set("exits", ([
                "north" : __DIR__"shamo",
                "east"  : "/d/huanghe/hetao",
        ]));
        set("no_clean_up", 0);
        set("outdoors", "yongdeng");
        set("coor/x", -10000);
        set("coor/y", 800);
        set("coor/z", 0);
        setup();
        replace_program(ROOM);
}