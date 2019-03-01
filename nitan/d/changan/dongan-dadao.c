//Room: dongan-dadao.c

inherit ROOM;

void create ()
{
        set ("short", "東安大道");
        set("long", @LONG
長安城的主街東安大道頗為熱鬧，除了本城的居民外，還有不少
外來的旅客和商人。東安大道再向東就是長安城的連德道口、東城門，
往西是故皇宮的馮詡道。往北就是大名鼎鼎的俠義盟總部了。
LONG );
        set("exits", 
        ([ //sizeof() == 2
                "west" : "/d/changan/fengxu3",
                "east" : "/d/changan/dongan-daokou",
                "north" : "/d/changan/xym_zb",
        ]));

        set("outdoors", "changan");
        set("coor/x", -10690);
	set("coor/y", 1930);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}