// Room: /d/taishan/wanghai.c
// Last Modified by Winder on Aug. 25 2001

inherit ROOM;

void create()
{
        set("short", "望海石");
        set("long", @LONG
仙人橋南是望海石，巨石坦豁如鳥伏臥，石側各有一小水槽，每逢
雨後，水順槽而流 ，如鳥之兩翼。明人林古度書刻“雙流翼注”，袁洪
癒大書“望海”。
LONG );
        set("exits", ([
                "north"    : __DIR__"xianren",
        ]));
        set("objects", ([
                "/d/shaolin/npc/mu-ren" : 5,
        ]));
        set("outdoors", "taishan");
        set("coor/x", 30);
	set("coor/y", 270);
	set("coor/z", 210);
	setup();
        replace_program(ROOM);
}