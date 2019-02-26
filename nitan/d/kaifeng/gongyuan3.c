inherit ROOM;

void create()
{
        set("short", "開封貢院");
        set("long", @LONG
過了州橋，街道邊一處高深的大院，威武的石獅守衞兩邊門楣上
『貢院』兩字作深紅色，每月上旬，此處將進行舉人的開考，門邊牆
上貼了張告示。
LONG );
        set("objects", ([
                  __DIR__"npc/zhukao3" : 1,
        ]));
        set("no_clean_up", 0);
        set("exits", ([
                  "east" : __DIR__"road2",
        ]));
        set("outdoors", "kaifeng");

	set("coor/x", -5060);
	set("coor/y", 2250);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}