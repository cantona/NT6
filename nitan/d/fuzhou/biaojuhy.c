// Room: /city/biaojuhy.c

inherit ROOM;

void create()
{
        set("short", "後院");
        set("long", @LONG
這裡是鏢局伙計們辛苦之余，休息放鬆的院子。院子的中央橫七豎
八的架著幾根竹竿，想必是用來晾曬衣服的。院子的周圍有幾間小房，
是平時鏢師伙計們休息的所在。
LONG );
        set("exits", ([
                "south" : __DIR__"biaojuzt",
                "north" : __DIR__"biaojucf",
                "east"  : __DIR__"biaojuxf",
                "west"  : __DIR__"biaojuxf1",
        ]));
        set("objects", ([
                __DIR__"npc/zheng" : 1,
        ]));
        set("outdoors", "fuzhou");
	set("coor/x", -101);
	set("coor/y", -6151);
	set("coor/z", -1);
	setup();
        replace_program(ROOM);
}