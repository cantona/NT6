// Room: /d/suzhou/xidajie1.c
// Date: May 31, 98  Java

inherit ROOM;

void create()
{
        set("short", "西大街");
        set("long", @LONG
這是一條寬闊的青石板街道，向東西兩頭延伸。西大街是衙門所在，
行人稀少，靜悄悄地很是冷清。東邊是滄浪亭和寶帶橋，南邊是兵營。
北邊就是衙門了。
LONG );
        set("outdoors", "suzhou");
        set("no_clean_up", 0);
        set("exits", ([
                "west"      : __DIR__"xidajie2",
                "north"     : __DIR__"yamengate",
                "south"     : __DIR__"bingyinggate",
                "southeast" : __DIR__"baodaiqiao",
                "northeast" : __DIR__"canlangting",
                "northwest" : __DIR__"szyunhe",
        ]));
	set("coor/x", 1100);
	set("coor/y", -1060);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}