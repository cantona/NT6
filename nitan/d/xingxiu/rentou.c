// Room: /d/xingxiu/.c
// Last Modified by winder on Apr. 25 2001
inherit ROOM;

void create()
{
        set("short", "人頭疙瘩");
        set("long", @LONG
這裏是黃黏土地帶。是風蝕台地得自然景象。周圍皆人跡罕至的戈
壁灘。因地處風帶線上，常年多颳大風，泥土剝蝕，留下堅硬和有紅柳
草根的部分，形成土墩，星羅棋佈，酷似人頭，故有此稱。
LONG);
        set("outdoors", "silu");
        set("exits", ([
                "southdown" : __DIR__"shazhou",
                "southeast" : __DIR__"yanzhishan",
        ]));
        set("no_clean_up", 0);
        set("coor/x", -23000);
        set("coor/y", 1000);
        set("coor/z", 100);
        setup();
//        replace_program(ROOM);
}

#include "/d/xingxiu/job2.h";
