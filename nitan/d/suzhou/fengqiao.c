// Room: /d/suzhou/fengqiao.c
// Date: May 31, 98  Java

inherit ROOM;

void create()
{
        set("short", "楓橋");
        set("long", @LONG
寺的北面有一座橋孔呈半圓的單空石橋--楓橋，她跨於運河的楓橋
灣。橋的東面是鐵嶺關，它與白虎關，滸墅關，合稱蘇州三關。
LONG );
        set("outdoors", "suzhou");
        set("no_clean_up", 0);
        set("exits", ([
                "enter" : __DIR__"hanshidian",
                "north" : __DIR__"tielingguan",
        ]));
	set("coor/x", 1050);
	set("coor/y", -1050);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}