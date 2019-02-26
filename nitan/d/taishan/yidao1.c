// Room: /d/taishan/yidao1.c
// Last Modified by Winder on Aug. 25 2001

inherit ROOM;
void create()
{
        set("short", "大驛道");
        set("long", @LONG
你走在一條塵土飛揚的大驛道上。四周人來人往。挑擔子的行商，
趕着大車的馬伕，上京趕考的書生，熙熙攘攘，非常熱鬧。不時還有兩
三騎快馬從身邊飛馳而過，揚起一路塵埃。馬上的人個個身着勁裝，衣
甲鮮明，有的還隨身佩帶着刀劍，看來都是些習武的江湖人。道路兩旁
是整整齊齊的楊樹林。
LONG );
        set("exits", ([
                "west" : __DIR__"yidao",
                "northeast" : __DIR__"yidao2",
                "southeast" : "/d/jiaxing/jnroad1",
        ]));
        set("objects",([
                __DIR__"npc/tangzi" : 2,
                "/d/quanzhou/npc/hai" : 1,
                "/d/city/npc/xiaoguiz" : 1,
                "/clone/npc/walker" : 1,
        ]));
        set("outdoors", "jiangnan");
        set("coor/x", 60);
	set("coor/y", 0);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}