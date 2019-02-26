// Room: /d/quanzhou/shisun.c
// Last Modified by winder on May. 29 2001

inherit ROOM;

void create()
{
        set("short", "石筍");
        set("long", @LONG
這是泉州西面的一處地貌奇觀，經千年風蝕形成的石筍千奇百怪，
似劍、似刀、似錐，形態各異。洞壑縱橫，不知所終。南面的山谷中有
一所草菴。
LONG );
        set("outdoors", "quanzhou");
        set("no_clean_up", 0);
        set("exits", ([
                "south" : __DIR__"shangu",
                "north" : __DIR__"luanshigang",
        ]));
	set("coor/x", -930);
	set("coor/y", -7730);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}