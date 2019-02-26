#include <room.h>
inherit ROOM;

void create()
{
        set("short", "東長安街");
        set("long", @LONG
熱鬧的東長安大街是紫禁城的交通要道，寬闊的青石大道向東西
兩頭延伸，街道上行人不斷，繁華的盛世景象不言而喻。在這裏可以
遠遠望見西邊那一堵堵高大厚實的古城牆，便是著名的天安門廣場了。
北面是京城最為繁華熱鬧的王府井大街。從南邊傳來一股濃烈的煙草
氣味，原來那裏是一家煙草店。東邊是一家雜貨鋪。
LONG );
       set("exits", ([
                "north" : "/d/beijing/wang_2",
                "south" : "/d/beijing/yancao",
                "east" : "/d/beijing/zahuo",
                "west" : "/d/beijing/caroad_e1",
        ]));
        set("objects", ([
                "/d/beijing/npc/old1" : 1,
                "/d/beijing/npc/hunhun" : 1,
        ]));
        set("outdoors", "beijing");
	set("coor/x", -2770);
	set("coor/y", 7670);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}