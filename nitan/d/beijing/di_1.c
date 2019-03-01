#include <room.h>
inherit ROOM;

void create()
{
        set("short", "地西大街");
        set("long", @LONG
這裡是北京城地安門的西街。街道是整整齊齊的楊樹林，道上行
人絡繹不絕，車輛馬匹穿插其中。大街上有閒逛的遊人，上京趕考的
考生，背負著擔子的挑夫以及正在玩耍著的幼童構出了一幅繁忙熱鬧
的盛世景象。從這裡一直往北可以到達當朝第一大臣鰲狠的府邸。向
南經過西單北大街可以通往西單。
LONG );
       set("exits", ([
                "north" : "/d/beijing/di_3",
                "east" : "/d/beijing/di_2",
                "south" : "/d/beijing/bei_4",
        ]));
        set("objects", ([
                "/d/beijing/npc/youren" : 1,
                "/d/beijing/npc/shusheng2" : 1,
                "/d/beijing/npc/kid1" : 1,
        ]));
        set("outdoors", "beijing");
	set("coor/x", -2820);
	set("coor/y", 7710);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}