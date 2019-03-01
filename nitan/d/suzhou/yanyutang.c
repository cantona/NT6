// Room: /d/suzhou/yanyutang.c
// Date: May 31, 98  Java

inherit ROOM;

void create()
{
        set("short", "燕譽堂");
        set("long", @LONG
燕譽堂是全園主廳，舊時系園主宴客處。曾經作為御膳房。堂名取
于《詩經》：“式燕且譽，好而無射”。此處建築為鴛鴦廳形狀，高敞
宏麗，堂內陳設富麗精致。
LONG );
        set("outdoors", "suzhou");
        set("no_clean_up", 0);
        set("exits", ([
                "west"      : __DIR__"shizilin",
                "southeast" : __DIR__"zhenquting",
        ]));
        set("objects", ([
                __DIR__"npc/lady3" : 2,
        ]));
	set("coor/x", 1130);
	set("coor/y", -1070);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}