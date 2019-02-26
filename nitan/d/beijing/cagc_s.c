#include <room.h>
inherit ROOM;

void create()
{
        set("short", "長安街廣場");
        set("long", @LONG
這裏便是長安街廣場了，長安街廣場是京城裏最熱鬧、最雜亂的
地段。南方的一座天橋橫跨東西，正是賣雜貨、變把戲、跑江湖的閒
雜人等聚居的所在。寬闊的大道向南北兩頭延伸。從南方經過宏偉的
凡陛橋就是北京城裏的最有名的名勝——天壇了，過天壇再向南方邁
進就是永定門，通往郊外。在這裏可以看見北方不遠處的一堵堵高大
的城牆，那裏便是天安門廣場了。
LONG );
       set("exits", ([
                "south" : "/d/beijing/tianqiao",
                "north" : "/d/beijing/tiananmen",
        ]));
        set("objects", ([
                "/d/beijing/npc/maiyi1" : 1,
                "/d/beijing/npc/xianren" : 2,
        ]));
        set("outdoors", "beijing");
	set("coor/x", -2800);
	set("coor/y", 7660);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}