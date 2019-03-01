// Room: /d/fuzhou/nanmen.c
// Date: May 12 1998 Java

inherit ROOM;

void create()
{
        set("short", "福州南門");
        set("long", @LONG
這裡是福州南門。往南望，是一片平展的平原。一片低矮的小樹，
夾雜著一片片甘蔗林、芭蕉林。一條平直的大道從林中通過，道邊一列
列的荔枝樹和龍眼樹。
LONG );
        set("exits", ([
                "south" : __DIR__"zhongzhou",
                "north" : __DIR__"nanmendou",
        ]));
        set("objects", ([
                "/clone/npc/walker"  : 1,
        ]));
        set("no_clean_up", 0);
        set("outdoors", "fuzhou");
	set("coor/x", -80);
	set("coor/y", -6210);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}