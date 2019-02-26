// Room: /d/taishan/baiyun.c
// Last Modified by Winder on Aug. 25 2001

inherit ROOM;

void create()
{
        set("short", "白雲洞");
        set("long", @LONG
白雲洞，又名雲窩，因地處懸崖，下有絕澗，危巖多竅、白雲繚繞
而名。洞內明人題“卧雲”、“鎖雲”，洞南深谷峻削，名百丈崖。
LONG );
        set("exits", ([
                "eastup" : __DIR__"xiangshan",
        ]));
        set("no_clean_up", 0);
        set("outdoors", "taishan");
        set("coor/x", 30);
	set("coor/y", 290);
	set("coor/z", 200);
	setup();
        replace_program(ROOM);
}