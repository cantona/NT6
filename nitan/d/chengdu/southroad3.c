// Room: southroad3.c
// Date: Feb.14 1998 by Java

inherit ROOM;
void create()
{
        set("short", "南大街");
        set("long", @LONG
你走在南大街堅實的青石板地面上，各色人等往來其中，很是喧
鬧。有時你可能會見到一些江湖裝束的人物，他們口音各異，服飾也
五花八門，可是中氣都很足，可不是好惹的。往東長長的大道就是南
大街。西南方是個很巍峨的建築群，人進人出，十分熱鬧。西北通往
西大街。
LONG );
        set("outdoors", "chengdu");
        set("exits", ([
            "northwest"  : __DIR__"westroad1",
            "southwest"  : __DIR__"wuhoucigate",
            "east"       : __DIR__"southroad2",
        ]));
        set("objects", ([
            "/d/taishan/npc/jian-ke": 2,
            "/d/taishan/npc/dao-ke" : 1,
        ]));
//        set("no_clean_up", 0);
        set("coor/x", -15230);
	set("coor/y", -1850);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}