// Room: /d/taishan/xianren.c
// Last Modified by Winder on Aug. 25 2001

inherit ROOM;

void create()
{
        set("short", "仙人橋");
        set("long", @LONG
仙人橋在愛身崖西側。兩崖對峙，下臨深澗，中有三石銜接抵撐而
成橋狀。
LONG );
        set("exits", ([
                "northeast" : __DIR__"aishen",
                "south"     : __DIR__"wanghai",
        ]));
        set("outdoors", "taishan");
        set("no_clean_up", 0);
        set("coor/x", 30);
	set("coor/y", 280);
	set("coor/z", 210);
	setup();
        replace_program(ROOM);
}