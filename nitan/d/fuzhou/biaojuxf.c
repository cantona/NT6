// Room: /city/biaojuxf.c

inherit ROOM;

void create()
{
        set("short", "東廂房");
        set("long", @LONG
房間里布置很簡單，只有一張小牀，一個小几，和幾張方凳。窗台
上放着一個磁杯，杯里插着幾枝無名小花。房間雖不大，但是給人整潔
舒適的感覺。
LONG
        );
        set("exits", ([
                "west" : __DIR__"biaojuhy",
        ]));
        set("objects", ([
                __DIR__"npc/zhu" : 1,
        ]));
	set("coor/x", -91);
	set("coor/y", -6151);
	set("coor/z", -1);
	setup();
        replace_program(ROOM);
}