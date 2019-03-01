// Room: wuguanchen.c
// Date: Feb.14 1998 by Java

inherit ROOM;
void create()
{
        set("short", "金牛武館二部");
        set("long", @LONG
這裡是「金牛武館」教授二部，師傅龍銓教授如下技能：基本輕
功，基本內功，基本招架，基本爪法，基本刀法。
LONG );
        set("objects", ([
                __DIR__"npc/longquan" : 1,
        ]));
        set("no_fight",0);
        set("no_steal",1);
        set("no_beg",1);
        set("exits", ([
                "north" : __DIR__"wuguan",
        ]));
        set("coor/x", -15200);
	set("coor/y", -1810);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}