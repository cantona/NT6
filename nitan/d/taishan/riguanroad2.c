// Room: /d/taishan/riguanroad2.c
// Last Modified by Winder on Aug. 25 2001

inherit ROOM;

void create()
{
        set("short", "日觀小路");
        set("long", @LONG
這裡是日觀峰小路，自峰頂東下，聯結東天門。此處山勢陡峭，兩
邊下臨深谷，一不小心都會掉了下去。
LONG );
        set("exits", ([
                "east"  : __DIR__"dongtian",
                "west"  : __DIR__"dongling",
        ]));
        set("outdoors", "taishan");
        set("no_clean_up", 0);
        set("coor/x", 70);
	set("coor/y", 300);
	set("coor/z", 190);
	setup();
        replace_program(ROOM);
}