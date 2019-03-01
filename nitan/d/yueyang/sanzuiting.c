// Room: /d/yueyang/sanzuiting.c
// Last Modifyed by Winder on Dec. 4 2001

inherit ROOM;

void create()
{
        set("short", "三醉亭");
        set("long", @LONG
三醉亭，位于岳陽樓北側，為主樓輔亭之一。四方形高三丈，二層
二檐，歇山頂，碧瓦紅柱華麗而莊重。傳說八仙之一的呂洞賓曾三次到
岳陽神遊，為這裡秀美的山、水所迷，每次均在樓內喝得酩酊大醉。亭
內陳設淡雅，一樓廳內屏上繪制有呂洞賓醉酒圖。
LONG );
        set("outdoors", "yueyang");
        set("no_clean_up", 0);
        set("exits", ([
                "south" : __DIR__"yueyanglou1",
        ]));
        set("objects", ([
                CLASS_D("gaibang")+"/bangzhong" : 2,
        ]));
	set("coor/x", -6240);
	set("coor/y", -2990);
	set("coor/z", 20);
	setup();
        replace_program(ROOM);
}