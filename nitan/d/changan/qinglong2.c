//Room: qinglong2.c

inherit ROOM;

void create ()
{
        set ("short", "青龍街");
        set("long", @LONG
青龍街是長安城中心大街，青石板路筆直的伸展出去，一路上行
人比肩，笙歌處處。景物之美，直如神仙境地。往北就是故皇宮的金
水橋了，南面有一條大路通向長安城南門。
LONG );
        set("exits", 
        ([ //sizeof() == 4
                "north" : "/d/changan/bridge2",
                "south" : "/d/changan/nanan-dadao",
                "west" : "/d/changan/qinglong1",
                "east" : "/d/changan/qinglong3",
        ]));

        set("objects", ([ //sizeof() == 3
               "/clone/npc/walker"  : 1, 
        ]));
        set("outdoors", "changan");
        set("coor/x", -10720);
	set("coor/y", 1910);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}