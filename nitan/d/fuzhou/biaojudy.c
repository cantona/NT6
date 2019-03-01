// Room: /city/biaojudy.c

inherit ROOM;

void create()
{
        set("short", "大院");
        set("long", @LONG
大院裡顯得有些凌亂，趟子手和鏢師們進進出出，似乎都在滿地裡
忙碌著什麼。一棵很大的榕樹栽在院子中央，給火辣辣的福州帶來一點
涼爽。
LONG );
        set("exits", ([
                "out"   : __DIR__"biaoju",
                "north" : __DIR__"biaojuzt",
                "east"  : __DIR__"biaojuhc",
                "west"  : __DIR__"biaojucyf",
        ]));
        set("objects", ([
                __DIR__"npc/shi" : 1,
        ]));
        set("outdoors", "fuzhou");
	set("coor/x", -101);
	set("coor/y", -6171);
	set("coor/z", -1);
	setup();
        replace_program(ROOM);
}