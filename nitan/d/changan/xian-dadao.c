//Room: xian-dadao.c

inherit ROOM;

void create ()
{
        set ("short", "西安大道");
        set("long", @LONG
長安城的主街西安大道頗為熱鬧，除了本城的居民外，還有不少
外來的旅客和商人。西安大道再向西就是長安城的永泰道口、西城門，
往東是故皇宮的扶風道。
LONG );
        set("exits", 
        ([ //sizeof() == 2
                "east" : "/d/changan/fufeng3",
                "west" : "/d/changan/xian-daokou",
        ]));

        set("outdoors", "changan");
        set("coor/x", -10750);
	set("coor/y", 1920);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}