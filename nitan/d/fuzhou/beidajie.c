// Room: /d/fuzhou/beidajie.c
// may. 12 1998 Java

inherit ROOM;

void create()
{
        set("short", "北大街");
        set("long", @LONG
街道兩側，榕木參天。福州盛夏苦熱，廣植榕樹以納涼爽，別名“
榕城”。南面是一個大路口，北上就是屏山。
LONG );
        set("exits", ([
                "south"   : __DIR__"dongjiekou",
                "northup" : __DIR__"pingshan",
        ]));
        set("outdoors", "fuzhou");
        set("no_clean_up", 0);
	set("coor/x", -80);
	set("coor/y", -6170);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}