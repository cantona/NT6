inherit ROOM;

void create()
{
        set("short", "武德道");
        set("long", @LONG
這是一條略窄的青石板街道，向東西兩頭延伸。居住在這條街上的大
都是一些武林人士，因此習武之風極勝，到處可見練武之人，武館，武場，
鏢局也比比皆是，為了安全，官府在這裏佈置了官兵。北邊是官府放置的
巡捕房和牢房，西南方向居住着當時威震武林金刀王家，王家乃是洛陽的
大户人家，在武林中又聲名顯赫，因此門前總是有許多武林人士等候拜訪。
LONG);
        set("outdoors", "luoyang");
        set("no_clean_up", 0);
        set("exits", ([
                  "east" : __DIR__"wroad2",
                "south" : __DIR__"wanggate",
                  "north" : __DIR__"xunbu",
                  "west" : __DIR__"wroad4",
        ]));

        set("objects", ([
                "/d/city/npc/liumang" : 2,
                "/d/city/npc/liumangtou" : 1,
                __DIR__"npc/wangbofen" : 1,
        ]));
	set("coor/x", -7020);
	set("coor/y", 2180);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}