#include <room.h>
inherit ROOM;

void create()
{
        set("short", "西四北大街");
        set("long", @LONG
這裡是西四北大街的盡頭，青石舖砌大道相當寬闊，街道上的行
人熙熙攘攘，車馬穿流不息。東邊接地西大街，轉南則通過西四北大
街接京城的西單北大街。
LONG );
       set("exits", ([
                "east" : "/d/beijing/di_4",
                "south" : "/d/beijing/shi_2",
        ]));
        set("outdoors", "beijing");
	set("coor/x", -2830);
	set("coor/y", 7730);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}