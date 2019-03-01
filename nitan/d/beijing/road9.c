inherit ROOM;

void create()
{
        set("short", "大驛道");
        set("long", @LONG
你走在一條塵土飛揚的大驛道上。四周人來人往。挑擔子的、行
商的、趕著大車的馬夫、上京趕考的書生，熙熙攘攘，非常熱鬧。不
時還有兩三騎快馬從身邊飛馳而過，揚起一路塵埃。馬上的人個個身
著勁裝，衣甲鮮明，有的還隨身佩帶著刀劍。看來都是些習武的江湖
人。道路兩旁是整整齊齊的楊樹林。
LONG );
        set("exits", ([
                "north" : "/d/beijing/road8",
                "south" : "/d/beijing/road10",
        ]));
        set("objects",([
                "/d/taishan/npc/tangzi" : 2,
        ]));
        set("outdoors", "beijing");
	set("coor/x", -2770);
	set("coor/y", 7560);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}