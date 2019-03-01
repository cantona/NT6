inherit ROOM;

void create()
{
        set("short", "小路");
        set("long", @LONG
這裡是一條小路，頗為不平，兩邊聳立著一些怪石，奇形
怪狀，甚是有趣 。
LONG);
        set("outdoors", "kunming");
        set("exits", ([
                "north" : __DIR__"yunnan4", 
                "south"  :__DIR__"shilin",
        ]));
        set("objects", ([
                "/d/beijing/npc/boy3" : 1,
                "/clone/npc/walker" : 1,
        ]));
	set("coor/x", -16770);
	set("coor/y", -7190);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}