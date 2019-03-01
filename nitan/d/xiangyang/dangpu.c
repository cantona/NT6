// Room: /d/xiangyang/dangpu.c
// Date: Jan. 8 1999 by Winder

inherit ROOM;

void create()
{
        set("short", "當舖");
        set("long", @LONG
這是家遠近聞名的當舖，三開間的門面，一塊寫著『邱航當舖』
四個金字的黑匾，足足七尺高的紫檀木的櫃台被磨得光可照人，你一
進去就有一種壓抑和悲悵的感覺，櫃台後的老板邱航頭也不抬的只顧
撥拉著算盤，櫃台上方掛著一塊花木牌子(paizi) 。據街坊們說鐵面
當舖給的價還不算最壞，並且從不問貨的來處，除了活人什麼都收，
所以生意很不錯。
LONG );
        set("item_desc", ([
                "paizi" : "公平交易\n
sell        賣 
buy         買
pawn        當
expiate     贖
value       估價
",
        ]));

        //set("no_fight", 1);
        set("no_beg", 1);
        set("exits", ([
                "north" : __DIR__"westjie1",
        ]));
        set("objects", ([
                __DIR__"npc/qiuhang" : 1,
        ]));
        set("coor/x", -7830);
	set("coor/y", -780);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}
