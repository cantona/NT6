//Room: qixiang1.c

inherit ROOM;

void create ()
{
        set ("short", "麒祥街");
        set("long", @LONG
麒祥街是長安城北一條東西向的大道，街面寬敞潔淨，街上十分
熱鬧，人來人往川流不息。大街的兩旁商家雲集，大大小小的店鋪比
鄰而立。街的北邊有一座酒樓，對面是一家客棧。
LONG );
        set("exits", 
        ([ //sizeof() == 4
                "south" : "/d/changan/kezhan",
                "north" : "/d/changan/jiulou",
                "west" : "/d/changan/yongtai-beikou",
                "east" : "/d/changan/qixiang2",
        ]));

        set("outdoors", "changan");
        set("coor/x", -10750);
	set("coor/y", 1960);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}