inherit ROOM;

void create()
{
        set("short", "四海錢莊");
        set("long", @LONG
四海錢莊乃洛陽城最大的錢莊。也是非常有名的老字號。老板正是中
國第一巨賈，紅頂商人胡雪源，乃山西人氏，這家錢莊從他的爺爺的爺爺
的爺爺的爺爺那輩開始辦起，一直傳到他手裡，聲譽非常好，在全國各地
都有分店。它發行的銀票通行全國。錢莊的門口掛有一塊牌子(paizi)。
LONG);
        set("no_clean_up", 0);
        set("exits", ([
                "north" : __DIR__"wroad1",
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
                __DIR__"npc/hu" : 1
        ]));

	set("coor/x", -7000);
	set("coor/y", 2170);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}