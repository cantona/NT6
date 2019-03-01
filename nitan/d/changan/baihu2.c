//Room: baihu2.c

inherit ROOM;

void create ()
{
        set ("short", "白虎街");
        set("long", @LONG
白虎街是長安城中心大街，青石板路筆直的伸展出去，一路上行
人比肩，笙歌處處。景物之美，直如神仙境地。往南就是故皇宮的金
水橋了，北面有一條大路通向長安城北門。
LONG );
        set("exits", 
        ([ //sizeof() == 4
                "south" : "/d/changan/bridge1",
                "north" : "/d/changan/beian-dadao",
                "west" : "/d/changan/baihu1",
                "east" : "/d/changan/baihu3",
        ]));

        set("objects", ([ //sizeof() == 3
               "/clone/npc/walker"  : 1, 
        ]));
        set("outdoors", "changan");
        set("coor/x", -10720);
	set("coor/y", 1950);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}