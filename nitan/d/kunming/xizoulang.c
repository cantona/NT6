inherit ROOM;

void create()
{
        set("short",  "西走廊" );
        set("long", @LONG
這裏是一條幹淨的走廊，從兩面看去，可以欣賞到花園裏
的風景，只見各種假山怪石，奇花異草，足見王府之氣派。
LONG);
        set("exits", ([
                "west"   :__DIR__"xizoulang1",
                "east"   :__DIR__"wangfu1"
        ]));
        set("objects", ([
                "/d/zhongzhou/npc/jiading" : 2,
        ]));
	set("coor/x", -16850);
	set("coor/y", -7180);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);         
}