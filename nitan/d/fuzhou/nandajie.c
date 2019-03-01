// Room: /d/fuzhou/nandajie.c
// may. 12 1998 Java

inherit ROOM;

void create()
{
        set("short", "南大街");
        set("long", @LONG
街道兩側，榕木參天。福州盛夏苦熱，廣植榕樹以納涼爽，別名“
榕城”。西面是府衙，東面是一家閩菜館。
LONG );
        set("exits", ([
                "south"   : __DIR__"nanmendou",
                "north"   : __DIR__"dongjiekou",
                "east"    : __DIR__"weizhongwei",
                "west"    : __DIR__"yamen",
        ]));
        set("objects", ([
                __DIR__"npc/xiaofan" : 1,
        ]));
        set("outdoors", "fuzhou");
	set("coor/x", -80);
	set("coor/y", -6190);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}