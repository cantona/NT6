// Room: /d/suzhou/tianpingshan.c
// Last Modified by winder on Mar. 8 2001

#include <ansi.h>;
#include <room.h>;
inherit ROOM;

void create()
{
        set("short", "天平山");
        set("long",@long
過了靈巖山，距離幾裏地就到了天平山。它為蘇州西南諸山之最高
峯。此山因地勢平坦如砥而得名。又因山勢高峻，白霧繚繞，也稱“白
雲山”。具載：宋仁宗趙禎將天平山賜與范文正公，故也稱“範文山”。
long);
        set("outdoors", "suzhou");
        set("exits",([
                "northeast" : __DIR__"qsgdao",
                "north" : __DIR__"shihu",
                "southeast" : __DIR__"lingyanshan",
                "eastup" : __DIR__"baiyunquan",
        ]));
        set("no_clean_up", 0);
	set("coor/x", 1100);
	set("coor/y", -1130);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}