// Room: /d/yueyang/dianjiangtai.c
// Last Modifyed by Winder on Dec. 4 2001

inherit ROOM;

void create()
{
        set("short", "點將台");
        set("long", @LONG
下了石階來到水邊一個平台，此台便是三國大將魯肅在此點兵發令
的“點將台”。點將台南側不遠有一系鐵鏈的大鐵枷，這條碩大無朋的
大鐵枷據說是攔江御敵用的。
LONG );
        set("outdoors", "yueyang");
        set("no_clean_up", 0);
        set("exits", ([
                "north" : __DIR__"shijie7",
        ]));
	set("coor/x", -6230);
	set("coor/y", -3020);
	set("coor/z", -10);
	setup();
        replace_program(ROOM);
}