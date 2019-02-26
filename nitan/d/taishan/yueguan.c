// Room: /d/taishan/yueguan.c
// Last Modified by Winder on Aug. 25 2001

inherit ROOM;

void create()
{
        set("short", "月觀峯");
        set("long", @LONG
月觀峯是位於南天門西面的山嶺，與日觀峯東西對峙而名。此處怪
石攢簇，最高的地方一石卓立，名為君子峯。古人言可在此望越國，故
又稱越觀峯。天晴氣朗時，夜晚可觀濟南府城萬家燈火，俗稱望府山。
山頂有月觀亭；往北走便是泰山的西天門。
LONG );
        set("exits", ([
                "east"    : __DIR__"nantian",
                "northup" : __DIR__"xitian",
        ]));
        set("no_clean_up", 0);
        set("outdoors", "taishan");
        set("coor/x", 20);
	set("coor/y", 300);
	set("coor/z", 200);
	setup();
        replace_program(ROOM);
}