#include <room.h>
inherit ROOM;

void create()
{
        set("short", "地東大街");
        set("long", @LONG
這裏是北京城地安門的東街。街道是整整齊齊的楊樹林，道上行
人絡繹不絕，車輛馬匹穿插其中。大街上有閒逛的遊人，上京趕考的
考生，揹負着擔子的挑夫以及正在玩耍着的幼童構出了一幅繁忙熱鬧
的盛世景象。北邊是京城國子監的所在地。南邊是地安門的東街廣場。
LONG );
       set("exits", ([
                "north" : "/d/beijing/guozijian",
                "south" : "/d/beijing/di_donggc",
                "east" : "/d/beijing/dong_3",
                "west" : "/d/beijing/di_dajie1",
        ]));
        set("objects", ([
                "/d/beijing/npc/bing2" : 1,
                "/d/beijing/npc/taijian" : 1,
        ]));
        set("outdoors", "beijing");
	set("coor/x", -2790);
	set("coor/y", 7730);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}