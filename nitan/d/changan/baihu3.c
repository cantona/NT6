//Room: baihu3.c

inherit ROOM;

void create ()
{
        set ("short", "白虎街");
        set("long", @LONG
青龍街是長安城中心大街，青石板路筆直的伸展出去，一路上行
人比肩，笙歌處處。景物之美，直如神仙境地。北面東邊傳出朗朗的
讀書聲，那裡是當朝的學府國子監。
LONG );
        set("exits", 
        ([ //sizeof() == 3
                "north" : "/d/changan/guozijian",
                "west" : "/d/changan/baihu2",
                "east" : "/d/changan/fengxu1",
        ]));

        set("outdoors", "changan");
        set("coor/x", -10710);
	set("coor/y", 1950);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}