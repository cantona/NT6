////Room: qixiang3.c

inherit ROOM;

void create ()
{
        set ("short", "麒祥街");
        set("long", @LONG
麒祥街是長安城北一條東西向的大道，街面寬敞潔淨，街上十分
熱鬧，人來人往川流不息。大街的兩旁商家雲集，大大小小的店鋪比
鄰而立。街的北邊是一家賭場，出出入入的人有喜有憂。賭場的老闆
為了方便客人，就又在麒祥街對面開了一家當鋪。
LONG );
        set("exits", 
        ([ //sizeof() == 4
                "south" : "/d/changan/dangpu",
                "north" : "/d/changan/duchang",
                "west" : "/d/changan/qixiang2",
                "east" : "/d/changan/beian-daokou",
        ]));

        set("outdoors", "changan");
        set("coor/x", -10730);
	set("coor/y", 1960);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}