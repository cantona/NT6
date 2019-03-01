// Room: /d/xiangyang/eastroad2.c
// Date: Jan. 8 1999 by Winder

inherit ROOM;

void create()
{
        set("short", "東內大街");
        set("long", @LONG
這是一條青石舖就的大街。西面是一堵蓋著紅色琉璃瓦的高牆，
裡面是襄陽守城大將王堅的府邸大院。東面是忠烈祠，因為十余年來，
為保衛襄陽、抵抗蒙古軍的侵略而犧牲的人特別多，前往上香祭奠的
人絡繹不絕。北面是一個十字街道，只見人來人往，非常熱鬧，南面
是用青石舖的街道。
LONG );
        set("outdoors", "xiangyang");

        set("no_clean_up", 0);
        set("exits", ([
                "east"  : __DIR__"zhonglie",
                "south" : __DIR__"eastroad1",
                "north" : __DIR__"jiekou2",
        ]));
        set("coor/x", -7800);
	set("coor/y", -750);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}