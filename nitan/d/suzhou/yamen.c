// Room: /d/suzhou/yamen.c
// Date: May 31, 98  Java

inherit ROOM;

void create()
{
        set("short", "正堂");
        set("long", @LONG
這裡就是蘇州府衙。堂上東西有兩根楹柱，掛著一幅對聯，但是你
根本無心細看。正牆上懸掛一個橫匾，上面橫書“正大光明”四個金光
閃閃的大字。一長溜“肅靜”“回避”的牌子分列兩側。知府正坐在文
案後批閱文書，師爺隨侍在後。
LONG );
        set("outdoors", "suzhou");
//        set("no_clean_up", 0);
        set("exits", ([
                "north"  : __DIR__"neizhai",
                "south"  : __DIR__"yamengate",
                "east"   : __DIR__"dongting",
                "west"   : __DIR__"xiting",
        ]));
        set("objects", ([
                __DIR__"npc/feng": 1,
                __DIR__"npc/shiye": 1,
                __DIR__"npc/yayi": 4,
        ]));
	set("coor/x", 1100);
	set("coor/y", -1040);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}