inherit ROOM;

void create()
{
        set("short", "青石路");
        set("long", @LONG
一條青石大道，青石鋪成，平坦寬闊，遠遠的可以看見昆
明瞭。
LONG);
        set("outdoors", "kunming");
        set("exits", ([
                "west" : __DIR__"qingshilu2", 
                "east"  :__DIR__"qingshilu",
        ]));
        set("objects", ([
                "/d/beijing/npc/tangzi" : 1,
        ]));
	set("coor/x", -16800);
	set("coor/y", -7210);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}