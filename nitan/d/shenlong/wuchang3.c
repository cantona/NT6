// wuchang3.c

inherit ROOM;

void create()
{
	set("short", "練武場");
	set("long", @LONG
這是一個比西面更為寬大的練武場，許多手執短劍的少年少女在這裏
練功。有的也在一旁觀看，似乎在揣摩什麼。
LONG );
	set("exits", ([
		"west" : __DIR__"wuchang",
	]));
        set("for_family", "神龍教");
        setup();
	replace_program(ROOM);
}
