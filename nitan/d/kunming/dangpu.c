inherit ROOM;

void create()
{
        set("short", "當舖");
        set("long", @LONG
這是一家很有些歷史的老當舖了，高高的櫃台後面座著當
舖的老板，正用一種奇怪的眼光看著你，一個當舖伙計正在劈
劈啪啪的打著算盤，見你來了，也不招呼一下。櫃台的頂上掛
著一塊牌子。
LONG);
        set("no_fight", 1);
        set("no_beg",1);
        set("item_desc", ([
                "paizi" : "公平交易\n",
        ]));
        set("objects", ([
                __DIR__"npc/liu" : 1,
        ]));
        set("exits", ([
                "east" : __DIR__"nandajie1",
        ]));

	set("coor/x", -16850);
	set("coor/y", -7220);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}