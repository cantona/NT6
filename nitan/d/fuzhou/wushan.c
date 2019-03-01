// Room: /d/fuzhou/wushan.c
// Date: May 12, 98  Java

inherit ROOM;

void create()
{
        set("short", "福州烏山");
        set("long", @LONG
福州古城三山，以城內烏山、于山和屏山三山恃立之故也。烏山上
有烏塔。
LONG );
        set("exits", ([
                "northdown" : __DIR__"xidajie",
        ]));
        set("outdoors", "fuzhou");
        set("no_clean_up", 0);
	set("coor/x", -100);
	set("coor/y", -6190);
	set("coor/z", 10);
	setup();
        replace_program(ROOM);
}