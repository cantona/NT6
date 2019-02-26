inherit ROOM;

void create()
{
        set("short", "武德道");
        set("long", @LONG
這是一條略窄的青石板街道，向東西兩頭延伸。在往東就是洛陽的中
心廣場了。居住在這條街上的大都是一些武林人士，因此習武之風而極勝，
到處可見練武之人，武館，武場，鏢局也比比皆是，為了安全，官府在這
里布置了官兵。北邊是高麗商人的住所——新羅坊，向南是赫赫有名的四
海錢莊。
LONG);
        set("outdoors", "luoyang");
        set("no_clean_up", 0);
        set("exits", ([
                  "east" : __DIR__"center",
                  "north" : __DIR__"xinluofang",
                  "south" : __DIR__"huqing",
                  "west" : __DIR__"wroad2",
        ]));
        set("objects", ([
                "/clone/npc/xunbu" : 1,
        ]));
	set("coor/x", -7000);
	set("coor/y", 2180);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}