// Room: /d/taishan/taohua.c
// Last Modified by winder on Aug. 25 2001

inherit ROOM;

void create()
{
        set("short", "桃花澗");
        set("long", @LONG
桃花澗，又名櫻桃園，清人曾頌：“櫻桃生澗底，石上多古苔。山
下花已落，山頭花未開。”澗中石坪廣闊，斷崖跌宕，溪水潺潺而來，
瀅洄湍急而去，或為瀑，或為潭，或潛流，匯為深廣碧池，名碧泉灣。
今澗內桃、櫻均無，唯楊、槐滿谷，柏林夾岸，石峽飛流，瀑水如簾。
LONG );
        set("exits", ([
                "northup" : __DIR__"doumo",
                "south"   : __DIR__"wanxianlou",
        ]));
        set("no_clean_up", 0);
        set("outdoors", "taishan");
        set("coor/x", 70);
	set("coor/y", 120);
	set("coor/z", 40);
	setup();
        replace_program(ROOM);
}