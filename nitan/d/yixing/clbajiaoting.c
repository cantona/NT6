// /d/yixing/clbajiaoting.c
// Last Modified by winder on Jul. 12 2002

inherit ROOM;

void create()
{
        set("short", "八角亭");
        set("long", @LONG
這是花園中一個小巧的亭子，供賞花時休息之用。亭中石桌石凳
俱全，石桌上還擺放著幾盤點心。院中花卉暗香浮動。幾個假山做得
甚是別致。
LONG );

        set("exits", ([
                "north" : __DIR__"clhuayuan",
                "west"  : __DIR__"clzoulang1",
        ]));
        set("objects", ([
                __DIR__"npc/dingdang" : 1,
        ]));
        set("outdoors", "yixing");
        set("coor/x", 289);
	set("coor/y", -1001);
	set("coor/z", -1);
	setup();

        replace_program(ROOM);
}