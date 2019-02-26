inherit ROOM;

void create()
{
        set("short", "武德道");
        set("long", @LONG
再往西就要到西內城門了，遠遠望去，可以看見守城的官兵正在檢查
排隊出城的路人，也許是太靠近城門的緣故，這裏的人已不如前面那麼多
了。北邊有一家書店，名曰“老僧書店”，南邊是一條幽靜的碎石小路。
LONG);
        set("outdoors", "luoyang");
        set("no_clean_up", 0);
        set("exits", ([
                  "east" : __DIR__"wroad4",
                  "north" : __DIR__"shudian",
                  "south" : __DIR__"suishi12",
                  "west" : __DIR__"xidoor",
        ]));
        set("objects", ([
                "/d/beijing/npc/kid1" : 1,
        ]));
	set("coor/x", -7040);
	set("coor/y", 2180);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}