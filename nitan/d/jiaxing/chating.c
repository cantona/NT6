// Room: /d/jiaxing/chating.c
// Last Modified by winder on Nov. 17 2000

inherit ROOM;

void create()
{
        set("short", "茶亭");
        set("long", @LONG
這是一家路邊的小茶亭，趕山路的人常在此處歇歇腳。亭子裡有幾
張桌子和幾支條凳。周圍是一片樹林。
LONG );
        set("exits", ([
                "northeast" : "/d/shiliang/road2",
                "northwest" : "/d/shiliang/shandao1",
                "west"      : __DIR__"jnroad4",
        ]));
        set("objects", ([
                CLASS_D("riyue")+"/xiang" : 1,
        ]));
        set("outdoors", "shiliang");
	set("coor/x", 1200);
	set("coor/y", -1790);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}