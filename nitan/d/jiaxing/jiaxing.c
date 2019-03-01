// Room: /d/jiaxing/jiaxing.c
// Last Modified by winder on Nov. 17 2000


inherit ROOM;

void create()
{
        set("short", "嘉興城");
        set("long", @LONG
這裡是江南名城嘉興。城東是風景如畫的南湖。城北早先有座醉仙
樓，當年全真七子之一的丘處機和江南七怪就在那裡盟約尋找忠良之後。
不知道什麼原因店主把它遷到揚州了。
LONG );
        set("exits", ([
                "west"  : __DIR__"jnroad2",
                "east"  : __DIR__"nanhu",
                "south" : __DIR__"jxnanmen",
        ]));
        set("outdoors", "jiaxing");
        set("no_clean_up", 0);
	set("coor/x", 1190);
	set("coor/y", -1770);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}