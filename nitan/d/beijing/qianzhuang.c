inherit ROOM;

void create()
{
        set("short", "天下錢莊");
        set("long", @LONG
天下錢莊是京城裏最大的一所錢莊，已經有過百年的歷史了，信
譽相當的好。錢莊的大門正對着一個高高的櫃枱，錢莊的老闆正在櫃
台後面清理着帳目，櫃枱左邊的牆上掛着一個牌子(paizi)。
LONG );
        set("item_desc", ([
        "paizi" : "\n本莊有利息，至少百分之一。\n
      存錢        deposit或者cun\n
      取錢        withdraw或者qu\n
      錢幣兑換    convert或者duihuan\n
      查帳        check或者chazhang\n",
        ]));
        set("exits", ([
                "south" : "/d/beijing/di_5",
        ]));
        set("no_clean_up", 0);
        set("no_fight", 0);
        set("no_beg", 1);
        set("objects", ([
                "/d/beijing/npc/tiegongji" : 1
        ]));

	set("coor/x", -2810);
	set("coor/y", 7740);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}