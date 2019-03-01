// Room: /d/quanzhou/duduxiang.c
// Last Modified by winder on May. 29 2001

inherit ROOM;

void create()
{
        set("short", "都督巷");
        set("long", @LONG
這是泉州的一條小巷，清凈整潔。遠遠可見巷底紅牆高砌，把守森
嚴，顯然不是普通的住家。
LONG );
        set("outdoors", "quanzhou");
        set("exits", ([
                "west" : __DIR__"northroad3",
                "east" : __DIR__"dudufu",
        ]));
        set("objects", ([
                "/d/city/npc/bing" : 2,
        ]));
	set("coor/x", -890);
	set("coor/y", -7640);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}