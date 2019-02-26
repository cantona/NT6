inherit ROOM;

void create()
{
        set("short", "休息室");
        set("long", @LONG
房間裏除了幾個凳子椅子，沒有擺設任何東西，但也不提供任何服務，
這裏是茶樓老闆特地為那些來來往往於大街上的遊客準備的，供他們休息
之用，不收取任何費用，可見老闆的心地善良。
LONG);
        set("no_clean_up", 0);
        set("exits", ([
                  "east" : __DIR__"chalou",
        ]));
        set("objects", ([
                "/d/beijing/npc/kid1" : 1,
                "/d/beijing/npc/old2" : 1,
        ]));
	set("coor/x", -7010);
	set("coor/y", 2160);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}