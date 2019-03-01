inherit ROOM;

void create()
{
        set("short", "碎石路" );
        set("long", @LONG
一條碎石舖成的路，平坦寬闊，路的兩面。綠樹成蔭，來往的人
累了都到樹下去乘乘涼，歇歇腳，一些小販也乘機在這裡買點吃喝的
東西。
LONG );
        set("exits", ([
                "east" : __DIR__"nanshilu",
                "west" : __DIR__"qingshilu2",
           ]));

        set("no_clean_up", 0);
        set("outdoors", "jingzhou");
        set("coor/x", -7110);
	set("coor/y", -2090);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}