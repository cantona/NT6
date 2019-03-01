#include <room.h>
inherit ROOM;

void create()
{
        set("short", "地西大街");
        set("long", @LONG
這裡是北京城地安門的西街。街道是整整齊齊的楊樹林，道上行
人絡繹不絕，車輛馬匹穿插其中。大街上有閒逛的遊人，上京趕考的
考生，背負著擔子的挑夫以及正在玩耍著的幼童構出了一幅繁忙熱鬧
的盛世景象。北邊是地安門西街的廣場。南邊警備深嚴，不時有官兵
進進出出，原來那裡就是京城的特務機構西廠的大門所在地。
LONG );
       set("exits", ([
                "north" : "/d/beijing/di_xigc",
                "west" : "/d/beijing/di_1",
                "south" : "/d/beijing/xichang_men",
        ]));
        set("objects", ([
                "/d/beijing/npc/bing3" : 1,
        ]));
        set("outdoors", "beijing");
	set("coor/x", -2810);
	set("coor/y", 7710);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}