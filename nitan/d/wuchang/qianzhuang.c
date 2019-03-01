//Edited by fandog, 02/15/2000
inherit ROOM;
void create()
{
        set("short", "錢莊");
        set("long", @LONG
這是一家老字號的錢莊，已有幾百年的歷史，在全國各地都有分店。
它發行的銀票信譽非常好，通行全國。
    在對面的牆上掛了塊牌子(paizi)。
LONG );
        set("exits", ([
                "east" : __DIR__"hzjie1",
        ]));
        set("item_desc", ([
                "paizi" : @TEXT
     本錢莊提供以下服務：
      存錢        deposit或者cun
      取錢        withdraw或者qu
      錢幣兌換    convert或者duihuan
      查帳        check或者chazhang
TEXT
        ]) );

        set("objects", ([
                __DIR__"npc/chen" : 1
        ]));
        set("no_clean_up", 0);
        set("no_fight", 1);
        set("no_beg", 1);
	set("coor/x", -5100);
	set("coor/y", -1860);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}