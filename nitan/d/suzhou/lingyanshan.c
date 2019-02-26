// Room: /d/suzhou/lingyanshan.c
// Last Modified by winder on May. 15 2001
inherit ROOM;

void create()
{
        set("short", "靈巖山");
        set("long",@long
這裏因山上有狀如靈芝的巨石，故名靈巖山。這裏山勢挺拔秀麗，
奇石嶙峋，有甚多的吳宮遺蹟，享有“吳中第一峯”的美譽。
long);
        set("outdoors", "suzhou");
        set("objects",([
                __DIR__"obj/xiao-shuzhi" : 1,
                __DIR__"obj/da-shitou" : 1,
        ]));
        set("exits",([
                "south"     : __DIR__"road7",
                "eastup"    : __DIR__"yingxiaoting",
                "northwest" : __DIR__"tianpingshan",
        ]));
	set("coor/x", 1110);
	set("coor/y", -1140);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}