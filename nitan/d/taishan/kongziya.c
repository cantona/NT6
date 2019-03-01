// Room: /d/taishan/kongziya.c
// Last Modified by Winder on Aug. 25 2001

inherit ROOM;

void create()
{
        set("short", "孔子崖");
        set("long", @LONG
孔子崖位于天街東首路北山崗上。傳孔子與顏子登泰山至此，孔子
東南望，看見 吳國都城門下的一匹白馬，此處遂名孔子崖或稱望吳峰。
崖上有“泰山喬岳”、“高山仰止”諸刻。
LONG );
        set("exits", ([
                "northdown" : __DIR__"kongzimiao",
                "southdown" : __DIR__"tianjie",
        ]));
        set("no_clean_up", 0);
        set("outdoors", "taishan");
        set("coor/x", 40);
	set("coor/y", 310);
	set("coor/z", 220);
	setup();
        replace_program(ROOM);
}