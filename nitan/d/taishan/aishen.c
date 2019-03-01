// Room: /d/taishan/aishen.c
// Last Modified by Winder on Aug. 25 2001

inherit ROOM;

void create()
{
        set("short", "愛身崖");
        set("long", @LONG
位于日觀峰南邊，便是愛身崖。愛身崖原名舍身崖，它三面陡峭，
下臨深淵。舊時常有人為袪父母病災，祈求神靈，跳崖獻身。明萬歷初
年巡撫何起鳴在崖側築牆阻攔，更名愛身崖。
LONG );
        set("exits", ([
                "up"        : __DIR__"zhanlutai",
                "north"     : __DIR__"riguan",
                "southwest" : __DIR__"xianren",
        ]));
        set("outdoors", "taishan");
        set("no_clean_up", 0);
        set("coor/x", 40);
	set("coor/y", 290);
	set("coor/z", 210);
	setup();
        replace_program(ROOM);
}