// Room: /d/xiangyang/northroad2.c
// Date: Jan. 8 1999 by Winder

inherit ROOM;

void create()
{
        set("short", "北內大街");
        set("long", @LONG
這是一條用青石鋪就的大道。只見北面不時的有馬車飛奔而出，
噢，北面是車行。向西就是丁字街口，東面也是一個大街口，你好像
看到一條大街通向南面。南面是一堵上蓋紅色琉璃瓦的高牆，裏面是
襄陽守城大將王堅的府邸。
LONG );
        set("outdoors", "xiangyang");

        set("no_clean_up", 0);
        set("exits", ([
                "east"  : __DIR__"jiekou2",
                "west"  : __DIR__"dingzi",
                "north" : __DIR__"majiu",
        ]));
        set("coor/x", -7800);
	set("coor/y", -740);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}