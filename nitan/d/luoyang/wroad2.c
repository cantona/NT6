inherit ROOM;

void create()
{
        set("short", "武德道");
        set("long", @LONG
這是一條略窄的青石板街道，向東西兩頭延伸。居住在這條街上的大
都是一些武林人士，因此習武之風極勝，到處可見練武之人，武館，武場，
鏢局也比比皆是，為了安全，官府在這裏佈置了官兵。北邊是文人墨客常
來拜祭的孔廟，南面是一些初入江湖的人常來龍騰武館。
LONG);
        set("outdoors", "luoyang");
        set("no_clean_up", 0);
        set("exits", ([
                "east" : __DIR__"wroad1",
                  "north" : __DIR__"kongmiao",
                  "south" : __DIR__"wuguan",
                  "west" : __DIR__"wroad3",
        ]));
        set("objects", ([
                "/d/beijing/npc/boy3" : 1,
        ]));
	set("coor/x", -7010);
	set("coor/y", 2180);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}