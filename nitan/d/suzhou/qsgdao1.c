// Room: /d/suzhou/qsgdao1.c
// Last Modified by Winder on May. 15 2001
inherit ROOM;

void create()
{
        set("short", "青石官道");
        set("long",@long
你走在一條青石大道上，人來人往非常繁忙，不時地有人騎着馬匆
匆而過。大道兩旁有一些小貨攤，似乎是一處集市。
long);
        set("outdoors", "suzhou");
        set("exits",([
                "south" : __DIR__"qsgdao",
                "north" : __DIR__"qsgdao2",
                "east"  : "/d/item/road1",
        ]));
        set("no_clean_up", 0);
	set("coor/x", 1110);
	set("coor/y", -1110);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}