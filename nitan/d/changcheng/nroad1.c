// Room: /d/changcheng/nroad1.c
// Last Modified by Winder on Aug. 25 2000

#include <room.h>
inherit BUNCH_ROOM;

void create()
{
        set("short", "大驛道");
        set("long", @LONG
你走在一條塵土飛揚的大驛道上。四周人來人往。挑擔子的、行商
的、趕着大車的馬伕、大多數人都是向南去京城，熙熙攘攘，非常熱鬧。
不時還有兩三騎快馬從身邊飛馳而過，揚起一路塵埃。道路兩旁是整整
齊齊的楊樹林。從這裏遠遠的就可以望見北京城的北城門。
LONG );
        set("outdoors", "changcheng");
        set("exits", ([
                "south" : "/d/beijing/anding",
                "north" : __DIR__"nroad2",
        ]));
        set("no_clean_up", 0);
        set("coor/x", -190);
        set("coor/y", 4500);
        set("coor/z", 0);
        setup();
}
