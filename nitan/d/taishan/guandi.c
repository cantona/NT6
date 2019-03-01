// Room: /d/taishan/guandi.c
// Last Modified by winder on Aug. 25 2001

inherit ROOM;

void create()
{
        set("short", "關帝廟");
        set("long", @LONG
一天門坊前路西是關帝廟，祀三國時蜀漢名將關羽。明清時山西鹽
商常在此聚會祭祀，奉福神，故又名山西會館。廟東院有古柏一株，牆
外碣書“漢柏第一”。
LONG );
        set("exits", ([
                "northeast" : __DIR__"yitian",
        ]));
        set("no_clean_up", 0);
        set("coor/x", 60);
	set("coor/y", 80);
	set("coor/z", 30);
	setup();
        replace_program(ROOM);
}