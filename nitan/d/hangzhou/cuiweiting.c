// cuiweiting.c
// Date: Nov.1997 by Venus
#include <room.h>
inherit ROOM;
void create()
{
        set("short", "翠微亭");
        set("long", @LONG
翠微亭建在飛來峯的半山間，是名將韓世忠為紀念岳飛而建的。
岳飛有“經年塵土滿征衣，特特尋芳上翠微”的詩句，故亭名“翠微”。
西邊是下山的路。
LONG);
        set("exits", ([
                "westdown"  : __DIR__"qinglindong",
        ]));
        set("no_clean_up", 0);
        set("outdoors", "hangzhou");
	set("coor/x", 760);
	set("coor/y", -2070);
	set("coor/z", 20);
	setup();
        replace_program(ROOM);
}