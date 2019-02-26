// Room: /d/taishan/yidao3.c
// Last Modified by Winder on Aug. 25 2001

inherit ROOM;

void create()
{
        set("short", "大驛道");
        set("long", @LONG
你走在一條塵土飛揚的大驛道上。四周人來人往。挑擔子的行商，
趕着大車的馬伕，上京趕考的書生，熙熙攘攘，非常熱鬧。不時還有兩
三騎快馬從身邊飛馳而過，揚起一路塵埃。道路兩旁是整整齊齊的楊樹
林。
LONG );
        set("exits", ([
                "south" : __DIR__"yidao2",
                "north" : __DIR__"taishanjiao",
        ]));
        set("objects",([
                __DIR__"npc/dao-ke" : 1,
        ]));
        set("outdoors", "jiangnan");
        set("coor/x", 70);
	set("coor/y", 20);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}