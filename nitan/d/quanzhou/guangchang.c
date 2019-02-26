// Room: /d/quanzhou/guangchang.c
// Last Modified by winder on May. 29 2001

inherit ROOM;

void create()
{
        set("short", "中心廣場");
        set("long", @LONG
這是泉州的中心地帶，樹蔭濃郁，整齊劃一。廣場中人山人海，摩
肩接踵，來來往往的人羣中時常可見不同膚色的胡人。泉州因其廣植刺
桐樹，又名「刺桐城」，是「海上絲綢之路」的起點。數以萬計的外國
商賈、使節和宗教信徒遠涉重洋來到此地，其中不少人就定居於此。
LONG );
        set("outdoors", "quanzhou");
        set("no_clean_up", 0);
        set("exits", ([
                "east"  : __DIR__"eastroad1",
                "west"  : __DIR__"westroad1",
                "south" : __DIR__"southroad1",
                "north" : __DIR__"northroad1",
        ]));
        set("objects", ([
                __DIR__"npc/huren" : 1,
                __DIR__"npc/xiaofan" : 1,
                "/clone/npc/walker" : 1,
                "/d/city/npc/liumangtou" : 1,
        ]));
	set("coor/x", -900);
	set("coor/y", -7670);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}