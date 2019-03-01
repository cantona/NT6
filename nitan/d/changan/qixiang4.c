//Room: qixiang4.c

inherit ROOM;

void create ()
{
        set ("short", "麒祥街");
        set("long", @LONG
麒祥街是長安城北一條東西向的大道，街面寬敞潔凈，街上十分
熱鬧，人來人往川流不息。大街的兩旁商家雲集，大大小小的店舖比
鄰而立。北邊是一家錢莊，可以聽到叮叮當當的金銀聲音。
LONG );
        set("exits", 
        ([ //sizeof() == 4
                "south" : "/d/changan/qunyulou",
                "north" : "/d/changan/bank",
                "west" : "/d/changan/beian-daokou",
                "east" : "/d/changan/qixiang5",
        ]));

        set("outdoors", "changan");
        set("coor/x", -10710);
	set("coor/y", 1970);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}