#include <room.h>
inherit ROOM;

void create()
{
        set("short", "北街菜市");
        set("long", @LONG
這裡是京城西單北大街西邊的一個菜市，青石板舖砌著地面。街
的兩邊擺滿了蔬菜攤和水果攤， 小販門大聲吆喝著，京城的百姓都是
從這兒把每天所需的食物購回， 做成一頓頓可口的佳肴。
LONG );
       set("exits", ([
                "east" : "/d/beijing/bei_3",
        ]));
        set("objects", ([
                "/d/beijing/npc/caifan" : 1,
                "/d/beijing/npc/jumin1" : 2,
              "/clone/npc/walker"  : 1, 
        ]));
        set("outdoors", "beijing");
	set("coor/x", -2840);
	set("coor/y", 7700);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}