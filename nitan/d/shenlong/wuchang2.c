// wuchang2.c

inherit ROOM;

void create()
{
	set("short", "練武場");
	set("long", @LONG
這是一個比北面更為寬大的練武場，許多手執短劍的少年少女在
這裡練功。不同于北面的是這裡的老者很少，幾乎都是一些年輕人在
練習武功。有一些則在竊竊私語，不知道在幹些什麼。一直向北走穿
越整個練功場就到走廊了。
LONG );
	set("exits", ([
		"north" : __DIR__"wuchang",
	]));
        set("for_family", "神龍教");
        setup();
	replace_program(ROOM);
}
