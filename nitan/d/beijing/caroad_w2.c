#include <room.h>
inherit ROOM;

void create()
{
        set("short", "西長安街");
        set("long", @LONG
熱鬧的西長安大街是紫禁城的交通要道，寬闊的青石大道向東西
兩頭延伸，街道上行人不斷，繁華的盛世景象不言而喻。在這裏可以
遠遠望見東邊那一堵堵高大厚實的古城牆，便是著名的天安門廣場了。
從這裏轉北就是西單了，那也是京城裏的繁華地段。南邊茶鋪裏不時
傳來一陣陣喧雜的吵鬧聲。
LONG );
       set("exits", ([
                "west" : "/d/beijing/caroad_w1",
                "east" : "/d/beijing/cagc_w",
                "north" : "/d/beijing/xi_2",
                "south" : "/d/beijing/gaosheng",
        ]));
        set("objects", ([
                "/d/beijing/npc/boy2" : 1,
                "/d/beijing/npc/richman1" : 1,
                "/d/beijing/npc/shusheng1" : 1,
        ]));
        set("outdoors", "beijing");
	set("coor/x", -2820);
	set("coor/y", 7670);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}