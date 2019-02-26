#include <room.h>
inherit ROOM;

void create()
{
        set("short", "地西大街");
        set("long", @LONG
這裏是北京城地安門的西街。街道是整整齊齊的楊樹林，道上行
人絡繹不絕，車輛馬匹穿插其中。大街上有閒逛的遊人，上京趕考的
考生，揹負着擔子的挑夫以及正在玩耍着的幼童構出了一幅繁忙熱鬧
的盛世景象。從這裏一直往北可以到達當朝第一大臣鰲狠的府邸。向
南經過西單北大街可以通往西單。西邊則是熱鬧的地安門西街廣場。
LONG );
       set("exits", ([
                "north" : "/d/beijing/di_4",
                "south" : "/d/beijing/di_1",
                "east" : "/d/beijing/di_xigc",
        ]));
        set("objects", ([
                "/d/beijing/npc/tiaofu" : 1,
                "/d/beijing/npc/dipi" : 1,
        ]));
        set("outdoors", "beijing");
	set("coor/x", -2820);
	set("coor/y", 7720);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}