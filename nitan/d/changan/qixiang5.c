//Room: qixiang5.c

inherit ROOM;

void create ()
{
        set ("short", "麒祥街");
        set("long", @LONG
麒祥街是長安城北一條東西向的大道，街面寬敞潔淨，街上十分
熱鬧，人來人往川流不息。大街的兩旁商家雲集，大大小小的店鋪比
鄰而立。北邊是一家首飾店，南邊就是長安城有名的河洛鏢局。
LONG );
        set("exits", 
        ([ //sizeof() == 4
                "south" : "/d/changan/biaoju-damen",
                "north" : "/d/changan/shoushi-dian",
                "west" : "/d/changan/qixiang4",
                       "east" : "/d/changan/qixiang6",
        ]));

        set("outdoors", "changan");
        set("coor/x", -10700);
	set("coor/y", 1970);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}