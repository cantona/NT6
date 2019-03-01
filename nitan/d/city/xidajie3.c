inherit ROOM;

void create()
{
        set("short", "西大街");
        set("long", @LONG
你走在西大街上，感到這裡的街面要比別處的幹凈、整潔。大概
因為靠近衙門、兵營可受保護的緣故，富人們都喜歡住在這裡。東邊
靜悄悄地沒有幾個行人，西邊是西城門通往郊外。南邊是一座鏢局，
北邊的樓上寫著『天寶閣』，那裡是人們讀書消遣的好去處。
LONG );
        set("outdoors", "city");
        set("no_clean_up", 0);
        set("exits", ([
                "east"  : __DIR__"xidajie2",
                "south" : __DIR__"biaoju",
                "west"  : __DIR__"ximen",
                "north" : __DIR__"tianbaoge",
        ]));

        set("objects", ([
                "/clone/npc/walker" : 1,
                __DIR__"npc/gongzi" : 1,
        ]));

	set("coor/x", -30);
	set("coor/y", 0);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}