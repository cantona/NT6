#include <room.h>
inherit ROOM;

void create()
{
        set("short", "西長安街");
        set("long", @LONG
熱鬧的西長安大街是紫禁城的交通要道，寬闊的青石大道向東西
兩頭延伸，街道上行人不斷，繁華的盛世景象不言而喻。在這裡可以
遠遠望見東邊那一堵堵高大厚實的古城牆，便是著名的天安門廣場了。
北面是繁華的西單，左邊不遠處有一家規模不大的客店。南面的街道
逐漸狹窄，便是楊柳胡同的胡同口了。
LONG );
       set("exits", ([
                "east" : "/d/beijing/caroad_w2",
                "west" : "/d/beijing/kedian",
                "north" : "/d/beijing/xi_1",
                "south" : "/d/beijing/yangliu1",
        ]));
        set("objects", ([
                "/d/beijing/npc/kid1" : 1,
                "/d/beijing/npc/haoke1" : 1,
        ]));
        set("outdoors", "beijing");
	set("coor/x", -2830);
	set("coor/y", 7670);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}