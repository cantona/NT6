inherit ROOM;

void create()
{
        set("short", "南大街");
        set("long", @LONG
南大街乃是城裏的繁華地段，北邊是一個熱鬧的廣場。東邊是一
家打鐵鋪。西邊是荊州的驛館，過往的路人多半都在這裏歇歇腳。
LONG );
        set("outdoors", "jingzhou");
        set("exits", ([
                "east" : __DIR__"datiepu",
                "south" : __DIR__"nandajie2",
                "west" : __DIR__"chaliao",
                "north" : __DIR__"guangchang",
        ]));
        set("objects", ([
                "/d/beijing/npc/youke" : 1,
        ]));
        set("coor/x", -7100);
	set("coor/y", -2060);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}