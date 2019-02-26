//Room: qixiang2.c

inherit ROOM;

void create ()
{
        set ("short", "麒祥街");
        set("long", @LONG
麒祥街是長安城北一條東西向的大道，街面寬敞潔淨，街上十分
熱鬧，人來人往川流不息。大街的兩旁商家雲集，大大小小的店鋪比
鄰而立。街的北邊熙熙攘攘的是一家茶館，茶館的對面是一家水果店。
LONG );
        set("exits", 
        ([ //sizeof() == 4
                "south" : "/d/changan/fruit-shop",
                "north" : "/d/changan/tea-shop",
                "west" : "/d/changan/qixiang1",
                "east" : "/d/changan/qixiang3",
        ]));

        set("outdoors", "changan");
        set("coor/x", -10740);
	set("coor/y", 1960);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}