// Room: /d/taishan/yidao.c
// Last Modified by Winder on Aug. 25 2001

inherit ROOM;

void create()
{
        set("short", "大驛道");
        set("long", @LONG
你走在一條塵土飛揚的大驛道上。四周人來人往。挑擔子的行商，
趕著大車的馬夫，上京趕考的書生，熙熙攘攘，非常熱鬧。不時還有兩
三騎快馬從身邊飛馳而過，揚起一路塵埃。道路兩旁是整整齊齊的楊樹
林。
LONG );
        set("exits", ([
                "west" : "/d/city/dongmen",
                "east" : __DIR__"yidao1",
        ]));
        set("objects",([
                __DIR__"npc/tiao-fu" : 3,
        ]));
         set("outdoors", "jiangnan");
        set("coor/x", 50);
	set("coor/y", 0);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}