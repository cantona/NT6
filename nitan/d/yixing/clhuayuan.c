// /d/yixing/clhuayuan.c
// Last Modified by winder on Jul. 12 2002

inherit ROOM;

void create()
{
        set("short", "花園");
        set("long", @LONG
這個花園是典型的江南風格，精巧細致。園中花卉雖沒有什麼名貴
品種，也是爭奇鬥妍。正中一條石子舖就的小路，上面遍布青苔，甚是
濕滑。向東是一條甬道。
LONG );

        set("exits", ([
                "west"  : __DIR__"clzoulang2",
                "east"  : __DIR__"clyongdao",
                "south" : __DIR__"clbajiaoting",
        ]));
        set("no_clean_up", 0);
        set("outdoors", "yixing");
        set("coor/x", 289);
	set("coor/y", -991);
	set("coor/z", -1);
	setup();
        replace_program(ROOM);
}