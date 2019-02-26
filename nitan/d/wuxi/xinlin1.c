// Room: /d/wuxi/xinlin1.c
// Winder 2000/02/22 

inherit ROOM;

void create()
{
        set("short", "杏樹林");
        set("long", @LONG
這是一片茂密的杏樹林，一走進來，你彷彿迷失了方向。你走着走
着，你忽然發現這裏的杏樹變稀少了，再向南北看去，那裏隱隱約約地
好像有好多人，你只覺得這裏的空氣有些緊張。
LONG );
        set("outdoors", "wuxi");
        set("no_clean_up", 0);
        set("exits", ([
                "north" : __DIR__"dayifenduo",
                "south" : __DIR__"eastgate",
                "east"  : __FILE__,
                "west"  : __FILE__,
        ]));
        set("coor/x", 1070);
	set("coor/y", -720);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}