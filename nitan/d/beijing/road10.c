inherit ROOM;

void create()
{
	set("short", "小道");
        set("long", @LONG
你走在一條塵土飛揚的大驛道上。四周人來人往。挑擔子的、行
商的、趕著大車的馬夫、上京趕考的書生，熙熙攘攘，非常熱鬧。不
時還有兩三騎快馬從身邊飛馳而過，揚起一路塵埃。道路兩旁是整整
齊齊的楊樹林。東邊就是大海之濱了。
LONG );
        set("exits", ([
                "east"  : __DIR__"haigang",
                "south"  : "/d/ruzhou/beimen",
                "north" : __DIR__"road9",
        ]));
        set("objects",([
                "/d/taishan/npc/tiao-fu" : 1,
        ]));
         set("outdoors", "beijing");
	set("coor/x", -2770);
	set("coor/y", 7550);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}
