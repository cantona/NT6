// Room: /d/quanzhou/laojunyan.c
// Last Modified by winder on May. 29 2001

inherit ROOM;

void create()
{
        set("short", "老君巖");
        set("long", @LONG
這裏山不高而云霧繚繞，周圍開曠遼闊，碧草如茵，風景宜人。因
有道教教主老君石像，故稱老君巖。它是一天然巨石雕琢而成。天下老
君石像無大過斯者，故又號稱“老子天下第一”。石像左手依膝，右手
憑几，兩眼平視，雙耳垂肩，臉含笑容，蒼髯飛動，一幅老人慈祥，安
樂的神態。民俗雲：「摸到老君鼻，吃到一百二」。
LONG );
        set("outdoors", "quanzhou");
        set("no_clean_up", 0);
        set("exits", ([
                "southdown" : __DIR__"qianshouyan",
                "eastup"    : __DIR__"nantaiyan",
        ]));
	set("coor/x", -930);
	set("coor/y", -7520);
	set("coor/z", 20);
	setup();
        replace_program(ROOM);
}