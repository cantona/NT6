inherit ROOM;

void create()
{
        set("short", "小角門");
        set("long", @LONG
在牆角邊開的一個小門，供寺中的僧人就近出外。門是用松木作
的，原先的紅漆已經剝落得差不多了。一邊的圍牆蹋了半邊，尋常人
都能爬進來，南邊是片菜地，出了角門是條大街。
LONG );
        set("objects", ([
                  __DIR__"npc/zhangsan" : 1,
        ]));

        set("no_clean_up", 0);
        set("exits", ([
                  "south" : __DIR__"caidi5",
                  "north" : __DIR__"eroad",
        ]));
        set("outdoors", "kaifeng");

	set("coor/x", -5030);
	set("coor/y", 2210);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}