// Room: /d/xiangyang/eastroad1.c
// Date: Jan. 8 1999 by Winder

inherit ROOM;

void create()
{
        set("short", "東內大街");
        set("long", @LONG
這是一條青石鋪就的大街。西面是一堵蓋着紅色琉璃瓦的高牆，
裏面是襄陽守城大將王堅的府邸大院。東面是是一座鏢局，北面是用
青石鋪的大街道。南面是一個大的十字街道，只見人來人往，非常熱
鬧。
LONG );
        set("outdoors", "xiangyang");

        set("no_clean_up", 0);
        set("exits", ([
                "east"  : __DIR__"biaoju",
                "south" : __DIR__"eastjie2",
                "north" : __DIR__"eastroad2",
        ]));
        set("coor/x", -7800);
	set("coor/y", -760);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}