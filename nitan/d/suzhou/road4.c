// Room: /d/suzhou/road4.c
// Date: May 31, 98  Java

inherit ROOM;

void create()
{
        set("short", "青石大道");
        set("long", @LONG
你走在一條青石大道上，人來人往非常繁忙，不時地有人騎着馬匆
匆而過。大道兩旁有一些小貨攤，似乎是一處集市。東面就是蘇州城了。
西北方通向寒山寺。
LONG );
        set("outdoors", "suzhou");
        set("no_clean_up", 0);
        set("exits", ([
                "northwest" : __DIR__"hanshansi",
                "south"     : __DIR__"tulu1",
                "east"      : __DIR__"road3",
        ]));
	set("coor/x", 1050);
	set("coor/y", -1060);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}