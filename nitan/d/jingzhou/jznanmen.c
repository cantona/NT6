inherit ROOM;

void create()
{
        set("short", "荊州南門" );
        set("long", @LONG
你來到荊州的南門，荊州歷來都是軍事要地，因此城牆堅實無比，
城樓高高聳立，由此向南，是去雲南的路，不過那邊山高路遠，很不
好走，你可得多多注意一些。
LONG );
        set("objects", ([
                "/d/city/npc/bing" : 4,
                "/d/beijing/npc/ducha" : 1,
                "/clone/npc/walker" : 1,
        ]));
        set("exits", ([
                "north" :__DIR__"nandajie2",
                "south" :__DIR__"nanshilu",
        ]));

        set("outdoors", "jingzhou");

        set("coor/x", -7100);
	set("coor/y", -2080);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}