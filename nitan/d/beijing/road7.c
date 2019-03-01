inherit ROOM;

void create()
{
        set("short", "大驛道");
        set("long", @LONG
你走在一條塵土飛揚的大驛道上。四周人來人往。挑擔子的、行
商的、趕著大車的馬夫、上京趕考的書生，熙熙攘攘，非常熱鬧。不
時還有兩三騎快馬從身邊飛馳而過，揚起一路塵埃。道路兩旁是整整
齊齊的楊樹林。
LONG );
        set("exits", ([
                "northwest" : "/d/beijing/road6",
                "east" : "/d/beijing/road4",
        ]));
        set("objects", ([
                "/d/huashan/npc/haoke" : 1,
        ]));
         set("outdoors", "beijing");
	set("coor/x", -2780);
	set("coor/y", 7580);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}