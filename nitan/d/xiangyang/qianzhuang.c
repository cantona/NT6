// Room: /d/xiangyang/qianzhuang.c
// Date: Jan. 8 1999 by Winder

inherit ROOM;

void create()
{
        set("short", "錢莊");
        set("long", @LONG
這裡是襄陽的錢莊，因為這裡商業相當發達，各地的商號都和這
裡有銀錢來往。錢莊裡有很多人在存取錢，也有人在兌換銀兩。看著
這麼多的錢財滾來滾去，真是讓人眼饞啊。但眼下大敵當前，全城一
致抵御元兵。錢莊的業務由華山弟子接管，支援大俠郭靖和郭夫人。
牆上貼著一個牌子(paizi)。
LONG );
        set("item_desc", ([
                "paizi" : @TEXT
     本錢莊提供以下服務：
      存錢        deposit或者cun
      取錢        withdraw或者qu
      錢幣兌換    convert或者duihuan
      查帳        check或者chazhang
TEXT
        ]));
        set("exits", ([
                "east" : __DIR__"southjie1",
        ]));
        set("objects", ([
                __DIR__"npc/huangzhen" : 1,
        ]));
        set("coor/x", -7830);
	set("coor/y", -780);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}