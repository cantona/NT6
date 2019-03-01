// Room: /d/fuzhou/pingshan.c
// Date: May 12, 98  Java

inherit ROOM;

void create()
{
        set("short", "福州屏山");
        set("long", @LONG
屏山古稱越王山，橫亙福州城北，山下華林寺，構法考究。屏山上
俯瞰榕城，歷歷如畫。
LONG );
        set("exits", ([
                "southdown" : __DIR__"beidajie",
        ]));
        set("outdoors", "fuzhou");
        set("no_clean_up", 0);
	set("coor/x", -80);
	set("coor/y", -6160);
	set("coor/z", 10);
	setup();
        replace_program(ROOM);
}