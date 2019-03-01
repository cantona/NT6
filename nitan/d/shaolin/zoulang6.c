// Room: /d/shaolin/zoulang6.c
// Date: YZC 96/01/19

inherit ROOM;

void create()
{
        set("short", "走廊");
        set("long", @LONG
這裏是禪房走廊。走廊南側的房頂倚着南面的高牆，另一側則與
北邊和尚院的屋頂相連。南面牆上掛了一付對聯：『悟徹菩提真妙理，
斷魔歸本合元神』。往北通向和尚院。
LONG );
        set("exits", ([
                "west" : __DIR__"zoulang5",
                "east" : __DIR__"fzlou",
                "north" : __DIR__"hsyuan4",
                "south" : __DIR__"wuchang1",
        ]));
        set("no_clean_up", 0);
        setup();
        replace_program(ROOM);
}
