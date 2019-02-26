// Room: /d/shaolin/zoulang7.c
// Date: YZC 96/01/19

inherit ROOM;

void create()
{
        set("short", "走廊");
        set("long", @LONG
這裏是禪房走廊。走廊南側的房頂倚着南面的高牆，另一側則與
北邊和尚院的屋頂相連。南面牆上掛了一付對聯：『靈根孕育源流出，
心性修持大道生』。往北通向和尚院。
LONG );
        set("exits", ([
                "east" : __DIR__"zoulang8",
                "west" : __DIR__"fzlou",
                "north" : __DIR__"hsyuan1",
                "south" : __DIR__"wuchang2",
        ]));
        set("no_clean_up", 0);
        setup();
        replace_program(ROOM);
}
