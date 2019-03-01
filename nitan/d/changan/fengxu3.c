//Room: fengxu3.c

inherit ROOM;

void create ()
{
        set ("short", "馮詡道");
        set("long", @LONG
馮詡道是長安城中心大街，青石板路筆直的伸展出去，一路上行
人比肩，笙歌處處。景物之美，直如神仙境地。東面有一條大路通往
長安城的東城門。
LONG );
        set("exits", 
        ([ //sizeof() == 3
                "north" : "/d/changan/fengxu2",
                "south" : "/d/changan/fengxu4",
                "east" : "/d/changan/dongan-dadao",
        ]));

        set("outdoors", "changan");
        set("coor/x", -10700);
	set("coor/y", 1930);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}