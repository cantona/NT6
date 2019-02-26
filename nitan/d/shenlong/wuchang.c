// wuchang.c

inherit ROOM;

void create()
{
	set("short", "練武場");
	set("long", @LONG
這是一個寬大的練武場，有幾個手執短劍的少年少女在這裏練功。
旁邊站着幾人，有男有女，年紀輕的只有二三十歲，老的已有六七十
歲，身上卻不帶兵刃。東邊、南邊是一片更大的練武場，北邊則通向
一條走廊。
LONG );
	set("exits", ([
		"north" : __DIR__"zoulang",
                "south" : __DIR__"wuchang2",
		"east"  : __DIR__"wuchang3",
	]));
        set("for_family", "神龍教");
        setup();
	replace_program(ROOM);
}
