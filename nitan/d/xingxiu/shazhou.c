// Room: /d/xingxiu/shazhou.c
// Last Modified by winder on Apr. 25 2001
inherit ROOM;

void create()
{
        set("short", "沙洲");
        set("long", @LONG
這裏是敦煌城所在地，是絲綢之路上的咽喉重鎮。四面城牆高聳，
另有高出城牆一倍的城墩。城內混居了周圍的多個民族，走在大街上看
到和聽到的無不透着新奇。
LONG);
        set("outdoors", "silu");
        set("exits", ([
                "southeast" : __DIR__"silk4",
                "west"      : __DIR__"tugu",
                "northup"   : __DIR__"rentou",
        ]));
        set("no_clean_up", 0);
        set("coor/x", -23000);
        set("coor/y", 900);
        set("coor/z", 0);
        setup();
//        replace_program(ROOM);
}

#include "/d/xingxiu/job2.h";