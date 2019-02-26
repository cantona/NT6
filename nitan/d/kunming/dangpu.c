inherit ROOM;

void create()
{
        set("short", "當鋪");
        set("long", @LONG
這是一家很有些歷史的老當鋪了，高高的櫃枱後面座着當
鋪的老闆，正用一種奇怪的眼光看着你，一個當鋪夥計正在劈
劈啪啪的打着算盤，見你來了，也不招呼一下。櫃枱的頂上掛
着一塊牌子。
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