inherit ROOM;

void create()
{
        set("short", "碎石路" );
        set("long", @LONG
一條碎石鋪成的路，平坦寬闊，路的兩面。綠樹成蔭，來往的人
累了都到樹下去乘乘涼，歇歇腳，一些小販也乘機在這裏買點吃喝的
東西。從這裏向南看去，隱約可以看見奔騰的長江。
LONG );
        set("exits", ([
                "south" : __DIR__"xiaowu",
                "east" : __DIR__"qingshilu1",
                "southwest" : __DIR__"shandao",
           ]));

        set("no_clean_up", 0);
        set("outdoors", "jingzhou");
        set("objects", ([
                "/d/beijing/npc/girl2" : 1,
        ]));
        set("coor/x", -7120);
	set("coor/y", -2090);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}