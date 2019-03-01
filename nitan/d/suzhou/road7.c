// Room: /d/suzhou/road7.c
// Last Modified by Winder on May. 15 2001
inherit ROOM;

void create()
{
        set("short", "湖畔大道");
        set("long",@long
你走在一條青石大道上，人來人往非常繁忙，不時地有人騎著馬匆
匆而過。大道兩旁有一些小貨攤，似乎是一處集市。北邊通向靈巖山。
南邊的青石大道通向湖邊。
long);
        set("outdoors", "suzhou");
        set("exits",([
                "north" : __DIR__"lingyanshan",
                "south" : __DIR__"road6",
        ]));
        set("no_clean_up", 0);
	set("coor/x", 1110);
	set("coor/y", -1150);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}