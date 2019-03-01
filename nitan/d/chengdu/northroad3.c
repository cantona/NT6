// Room: northroad3.c
// Date: Feb.14 1998 by Java

inherit ROOM;
void create()
{
        set("short", "北大街");
        set("long", @LONG
你走在北大街的青石地上，發現這裡熱鬧非凡。原來東北角就是
金牛武館，據說每個武師都有絕活。許多江湖人物都慕名前來，搬運
行李被褥的人不絕如縷。往東南是東大街，一直向西的是北大街。
LONG );
        set("outdoors", "chengdu");
        set("exits", ([
            "west"       : __DIR__"northroad2",
            "southeast"  : __DIR__"eastroad1",
            "northeast"  : __DIR__"wuguan",
        ]));
        set("objects", ([
            "/d/huashan/npc/haoke" : 2,
            "/d/taishan/npc/jian-ke" : 1,
        ]));
//        set("no_clean_up", 0);
        set("coor/x", -15210);
	set("coor/y", -1810);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}