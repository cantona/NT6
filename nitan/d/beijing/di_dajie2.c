#include <room.h>
inherit ROOM;

void create()
{
        set("short", "地安門大街");
        set("long", @LONG
這裡是北京城的地安門大街。街道是整整齊齊的楊樹林，道上行
人絡繹不絕，車輛馬匹穿插其中。大街上有閒逛的遊人，上京趕考的
考生，背負著擔子的挑夫以及正在玩耍著的幼童構出了一幅繁忙熱鬧
的盛世景象。北邊過地安門到達京城的城郊，南邊是熱鬧的地安門廣
場。
LONG );
       set("exits", ([
                "north" : "/d/beijing/di_anmen",
                "south" : "/d/beijing/di_dajie1",
        ]));
        set("objects", ([
                "/d/beijing/npc/dipi" : 1,
                "/d/beijing/npc/tiaofu" : 2,
        ]));

        set("outdoors", "beijing");
	set("coor/x", -2800);
	set("coor/y", 7740);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}