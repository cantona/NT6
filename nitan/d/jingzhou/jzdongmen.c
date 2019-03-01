inherit ROOM;

void create()
{
        set("short", "荊州東門" );
        set("long", @LONG
這裡便是荊州西門，荊州歷來都是軍事要地，因此城牆堅實無比，
城樓高高聳立，來往的人很多，荊州也是從蜀地進入中原的必經之路，
所以各色人等混雜，你還是小心一點。東去則是通往武昌的交通要道。
LONG );
        set("objects", ([
                "/d/city/npc/bing" : 4,
                "/d/beijing/npc/ducha" : 1,
        ]));
        set("exits", ([
                "east" : __DIR__"guandao3",
                "west" : __DIR__"dongdajie2",
        ]));
        set("outdoors", "jingzhou");

        set("coor/x", -7070);
	set("coor/y", -2050);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}