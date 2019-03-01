// Room: /d/wuxi/eastroad2.c
// Winder 2000/02/22 

inherit ROOM;

void create()
{
        set("short", "東林路");
        set("long", @LONG
東林路是通向無錫東門外的一條大街，這條街沒有什麼河道穿過，
路面十分寬闊平整。西邊是衙門口，那裡的人不多。北邊傳來一陣陣朗
朗的讀書聲。南邊是打鐵舖，叮叮當當的聲音老遠就能聽到。
LONG );
        set("outdoors", "wuxi");
        set("no_clean_up", 0);
        set("exits", ([
                "north" : __DIR__"shuyuangate",
                "south" : __DIR__"datiepu",
                "east"  : __DIR__"eastgate",
                "west"  : __DIR__"eastroad1",
        ]));
        set("objects", ([
                __DIR__"npc/polan" : 1,
        ]));
        set("coor/x", 1060);
	set("coor/y", -730);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}