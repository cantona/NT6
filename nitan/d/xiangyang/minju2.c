// Room: /d/xiangyang/minju2.c
// Date: Jan. 8 1999 by Winder

inherit ROOM;

void create()
{
        set("short", "民居");
        set("long", @LONG
這是一家比較有錢人的住房，房子主人正在家裡忙這忙那，看見
你進來，急忙站起身向你打招呼。
LONG );
        set("no_clean_up", 0);

        set("exits", ([
                "east" : __DIR__"jiedao",
        ]));
        set("coor/x", -7810);
	set("coor/y", -780);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}