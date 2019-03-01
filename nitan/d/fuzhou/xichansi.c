// Room: /d/fuzhou/xichansi.c
// Date: May 12, 98  Java

inherit ROOM;

void create()
{
        set("short", "西禪寺");
        set("long", @LONG
西禪寺始建于樑朝，寺中玉佛樓玉佛為整玉雕就，寶相莊嚴，從來
香火不絕。香客往來，但有所求，多得靈驗。
LONG );
        set("exits", ([
                "north" : __DIR__"xixiaojie",
        ]));
        set("objects", ([
                "/d/wudang/npc/guest" : 1,
        ]));
        set("outdoors", "fuzhou");
        set("no_clean_up", 0);
	set("coor/x", -110);
	set("coor/y", -6190);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}