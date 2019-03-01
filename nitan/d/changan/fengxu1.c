//Room: fengxu1.c

inherit ROOM;

void create ()
{
        set ("short", "馮詡道");
        set("long", @LONG
馮詡道是長安城中心大街，青石板路筆直的伸展出去，一路上行
人比肩，笙歌處處。景物之美，直如神仙境地。
LONG );
        set("exits", 
        ([ //sizeof() == 2
                "west" : "/d/changan/baihu3",
                "south" : "/d/changan/fengxu2",
        ]));

        set("outdoors", "changan");
        set("coor/x", -10700);
	set("coor/y", 1950);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}