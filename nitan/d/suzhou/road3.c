// Room: /d/suzhou/road3.c
// Date: May 31, 98  Java

inherit ROOM;

void create()
{
        set("short", "青石大道");
        set("long", @LONG
你走在一條青石大道上，人來人往非常繁忙，不時地有人騎著馬匆
匆而過。大道兩旁有一些小貨攤，似乎是一處集市。向東面望去，就可
以看到蘇州城的城牆了。
LONG );
        set("outdoors", "suzhou");
        set("no_clean_up", 0);
        set("exits", ([
                "west"  : __DIR__"road4",
                "east"  : __DIR__"road2",
        ]));
	set("coor/x", 1060);
	set("coor/y", -1060);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}