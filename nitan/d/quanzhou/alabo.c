// Room: /d/quanzhou/alabo.c
// Last Modified by winder on May. 29 2001

inherit ROOM;

void create()
{
        set("short", "阿拉伯宅區");
        set("long", @LONG
由于泉州與世界的商貿往來，許多阿拉伯人來到此地居住和勞作，
久而久之形成了這聚居地。遠遠望去白色的圓形尖頂突兀而起，顯得格
外搶眼。
LONG );
        set("outdoors", "quanzhou");
        set("exits", ([
                "northwest" : __DIR__"southroad2",
                "south"     : __DIR__"qingjingsi",
        ]));
        set("objects", ([
                __DIR__"npc/alabo" : 1,
        ]));
	set("coor/x", -890);
	set("coor/y", -7700);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}