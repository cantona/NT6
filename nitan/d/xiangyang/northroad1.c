// Room: /d/xiangyang/northroad1.c
// Date: Jan. 8 1999 by Winder

inherit ROOM;

void create()
{
        set("short", "北內大街");
        set("long", @LONG
這是一條用青石鋪就的大道。只見北面是一條鋪面很大的雜貨鋪，
聽説裏面能買到許多東西。向東就是丁字街口，西面也是一個大街口，
你好像看到一條大街通向南面。南面是一堵上蓋紅色琉璃瓦的高牆，
裏面是襄陽安撫使呂文德安排給他的布衣客卿、人稱郭大俠郭靖的府
邸。
LONG );
        set("outdoors", "xiangyang");

        set("no_clean_up", 0);
        set("exits", ([
                "west"  : __DIR__"jiekou1",
                "east"  : __DIR__"dingzi",
                "north" : __DIR__"xinluofang",
        ]));
        set("coor/x", -7820);
	set("coor/y", -740);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}