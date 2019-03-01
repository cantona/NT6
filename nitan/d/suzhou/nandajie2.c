// Room: /d/suzhou/nandajie2.c
// Date: May 31, 98  Java

inherit BUILD_ROOM;

void create()
{
        set("short", "南大街");
        set("long", @LONG
你走在一條繁華的街道上，向南北兩頭延伸。北邊通往城南大街
的中心地段，東面是聽雨軒，西面是留園，望南面，是蘇州城的南城
門。所謂上有天堂，下有蘇杭，此言的確不錯。如果在這裡生活絕對
是人間福地。
LONG );
        set("outdoors", "suzhou");
        set("no_clean_up", 0);
        set("exits", ([
                "east"  : __DIR__"tingyu",
                "west"  : __DIR__"liuyuan",
                "north" : __DIR__"nandajie1",
                "south" : __DIR__"nanmen",
        ]));
	set("coor/x", 1110);
	set("coor/y", -1080);
	set("coor/z", 0);
	setup();
}
