// Room: /d/taishan/daimiao.c
// Last Modified by winder on Aug. 25 2001

inherit ROOM;

void create()
{
        set("short", "岱廟");
        set("long", @LONG
泰山腳下岱廟，是東嶽福神東華帝君的道場。從南到北依次貫穿正
陽門、配天門、仁安門、天貺殿、後寢宮、厚載門，東側輔以漢柏院、
東御座，西側佐以唐槐院、雨花道院，極其宏大壯麗，東嶽大帝的靈感
可見。往北就是岱宗坊。
LONG );
        set("exits", ([
                "north" : __DIR__"daizong",
                "south" : __DIR__"yaocan",
        ]));
        set("no_clean_up", 0);
        set("coor/x", 70);
	set("coor/y", 50);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}