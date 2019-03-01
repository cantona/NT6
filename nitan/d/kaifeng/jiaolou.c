inherit ROOM;

void create()
{
        set("short", "西角樓");
        set("long", @LONG
角樓是建于城牆之上，用于兵衛守望的處所，只在樓的頂端掛上
一盞燈籠，從此遠眺，遠處山水亭台，一一在目，西面下去就是西大
街。來往的行人不斷。
LONG );
        set("no_clean_up", 0);
        set("exits", ([
                  "eastdown" : __DIR__"zhuque",
                  "westdown" : __DIR__"wroad2",
        ]));
        set("outdoors", "kaifeng");

	set("coor/x", -5060);
	set("coor/y", 2240);
	set("coor/z", 10);
	setup();
        replace_program(ROOM);
}