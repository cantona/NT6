//Room: qixiang6.c

inherit ROOM;

void create ()
{
        set ("short", "麒祥街");
        set("long", @LONG
麒祥街是長安城北一條東西向的大道，街面寬敞潔淨，街上十分
熱鬧，人來人往川流不息。大街的兩旁商家雲集，大大小小的店鋪比
鄰而立。北邊是一家藥店，往東就到了和連德大道交叉的連德北口。
LONG );
        set("exits", 
        ([ //sizeof() == 4
                "south" : "/d/changan/weapon-shop",
                "north" : "/d/changan/yaopu",
                "west" : "/d/changan/qixiang5",
                "east" : "/d/changan/liande-beikou",
        ]));

        set("outdoors", "changan");
        set("coor/x", -10690);
	set("coor/y", 1970);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}