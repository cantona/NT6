#include <room.h>
inherit ROOM;

void create()
{
        set("short", "西四北大街");
        set("long", @LONG
這裡是京城的西四北大街，青石舖砌道路貫通南北，街道上的行
人熙熙攘攘。西方一條寬闊的大官道上馬蹄聲不斷，塵土飛揚。向南
通過西四北大街接西單北大街。
LONG );
       set("exits", ([
                "north" : "/d/beijing/shi_3",
                "south" : "/d/beijing/shi_1",
                "west" : "/d/beijing/guandao_1",
        ]));
        set("objects", ([
                "/d/beijing/npc/boy1" : 1,
        ]));
        set("outdoors", "beijing");
	set("coor/x", -2830);
	set("coor/y", 7720);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}