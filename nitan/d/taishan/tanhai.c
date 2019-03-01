// Room: /d/taishan/tanhai.c
// Last Modified by Winder on Aug. 25 2001

inherit ROOM;

void create()
{
        set("short", "探海石");
        set("long", @LONG
日觀峰北有一塊從山崖向橫突出的巨石，名拱北石，又名探海石。
長約二丈余，向東直指渤海。巨石三面無所憑依，視野廣闊，但除非有
絕高膽色的人，普通人一般都不敢攀登這塊探海石。石上有“絕妙”、
“船石巖”、“醉石”及明人題名等刻。登臨其上可盡賞旭日東升的壯
麗場面，亦可晴覽山色、陰觀雲海。李興祖詩：“才聽天雞報曉聲，扶
桑旭日已初明。蒼茫海氣連雲動，石上遊人別有情。”
LONG );
        set("exits", ([
                "westdown" : __DIR__"riguan",
        ]));
        set("no_clean_up", 0);
        set("outdoors", "taishan");
        set("coor/x", 50);
	set("coor/y", 300);
	set("coor/z", 220);
	setup();
        replace_program(ROOM);
}