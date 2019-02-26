inherit ROOM;

void create()
{
        set("short", "酒樓");
        set("long", @LONG
這是一家極為普通的酒樓，平日裏就賣些米酒，包子，大
部分來這裏的人都是隨便買點東西就走了，也有些人叫點花生
米，切點熟牛肉來對飲兩盅的。
LONG);
        set("exits", ([
                "west" : __DIR__"nandajie1",
        ]));
        set("objects", ([
                __DIR__"npc/xiaoer2" : 1,
        ]));
	set("coor/x", -16830);
	set("coor/y", -7220);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}