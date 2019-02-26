// Room: /d/taishan/riguanroad1.c
// Last Modified by Winder on Aug. 25 2001

inherit ROOM;

void create()
{
        set("short", "日觀山路");
        set("long", @LONG
這裏是日觀峯小路，自峯頂東下，聯結東天門。此處山勢陡峭，兩
邊下臨深谷，一不小心都會掉了下去。
LONG );
        set("exits", ([
                "eastdown" : __DIR__"dongling",
                "westup"   : __DIR__"riguan",
        ]));
        set("outdoors", "taishan");
        set("no_clean_up", 0);
        set("coor/x", 50);
	set("coor/y", 300);
	set("coor/z", 200);
	setup();
        replace_program(ROOM);
}