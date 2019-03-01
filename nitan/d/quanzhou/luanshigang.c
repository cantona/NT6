// Room: /d/quanzhou/luanshigang.c
// Last Modified by winder on May. 29 2001

inherit ROOM;

void create()
{
        set("short", "亂石崗");
        set("long", @LONG
這裡樹木陰森，礫石嶙峋，坡陡坑深，地勢險要，歷來是土匪盤據
的地方。
LONG );
        set("outdoors", "quanzhou");
        set("exits", ([
                "south" : __DIR__"shisun",
                "east"  : __DIR__"diaoqiao",
        ]));
        set("objects", ([
                "/d/wudang/npc/tufei1" : 1,
                "/d/wudang/npc/tufei2" : 1,
                "/d/wudang/npc/tufeitou" : 1,
        ]));
	set("coor/x", -930);
	set("coor/y", -7720);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}