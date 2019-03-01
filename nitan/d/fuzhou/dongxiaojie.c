// Room: /d/fuzhou/dongxiaojie.c
// may. 12 1998 Java

inherit ROOM;

void create()
{
        set("short", "東小街");
        set("long", @LONG
街道兩側，榕木參天。福州盛夏苦熱，廣植榕樹以納涼爽，別名“
榕城”。東面就出城了，西面是城中心。
LONG );
        set("exits", ([
                "east"    : __DIR__"dongmen",
                "west"    : __DIR__"dongdajie",
        ]));
        set("objects", ([
                "/clone/npc/walker"  : 1,
        ]));
        set("outdoors", "fuzhou");
        set("no_clean_up", 0);
	set("coor/x", -60);
	set("coor/y", -6180);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}