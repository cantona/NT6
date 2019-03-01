// Last Modified by winder on Nov. 20 2001
// Room: /d/nanyang/yidao.c

inherit ROOM;

void create()
{
        set("short", "大驛道");
        set("long", @LONG
你走在一條塵土飛揚的大驛道上。四周人來人往。挑擔子的行商，
趕著大車的馬夫，上京趕考的書生，熙熙攘攘，非常熱鬧。不時還有兩
三騎快馬從身邊飛馳而過，揚起一路塵埃。馬上的人個個身著勁裝，衣
甲鮮明，有的還隨身佩帶著刀劍，看來都是些習武的江湖人。道路兩旁
是整整齊齊的楊樹林。看來揚州快到了。
LONG );
        set("exits", ([
                "south" : "/d/city/beimen",
                "north" : __DIR__"yidao1",
        ]));
        set("outdoors", "yangzhou");
        set("no_clean_up", 0);
        set("coor/x", 0);
	set("coor/y", 40);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}
