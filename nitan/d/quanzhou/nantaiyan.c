// Room: /d/quanzhou/nantaiyan.c
// Last Modified by winder on May. 29 2001

inherit ROOM;

void create()
{
        set("short", "南台巖");
        set("long", @LONG
「蒼崖千尺峭空虛」，這是清源山的最高處。一片高聳的巨石屹然
矗立，前面是懸崖峭壁，形勢十分險峻。巖石上鐫刻著「空中台閣」四
大字。臨台建有「魁星閣」，因為山勢高，這裡常含雲吐霧，漫為雲海，
從山下仰視，如在空中。
LONG );
        set("outdoors", "quanzhou");
        set("no_clean_up", 0);
        set("exits", ([
                "eastdown" : __DIR__"qingyuandong",
                "westdown" : __DIR__"laojunyan",
        ]));
	set("coor/x", -920);
	set("coor/y", -7520);
	set("coor/z", 30);
	setup();
        replace_program(ROOM);
}