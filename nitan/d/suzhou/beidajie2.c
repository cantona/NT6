// Room: /d/suzhou/beidajie2.c
// Date: May 31, 98  Java

inherit ROOM;

void create()
{
        set("short", "北大街");
        set("long", @LONG
這是一條寬闊的青石街道，向南北兩頭延伸。北邊是北城門通向城
外。南邊顯得很繁忙。東邊是一座兩層的樓閣，名為春在樓。西面是一
座廟庵，南面是一條筆直的大街，十分繁華。
LONG );
        set("outdoors", "suzhou");
        set("no_clean_up", 0);
        set("exits", ([
                "east"      : __DIR__"jiudian",
                "west"      : __DIR__"zijinan",
                "north"     : __DIR__"beimen",
                "south"     : __DIR__"beidajie1",
        ]));
	set("coor/x", 1110);
	set("coor/y", -1030);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}