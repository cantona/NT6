#include <room.h>
inherit ROOM;

void create()
{
        set("short", "地西大街");
        set("long", @LONG
這裏是北京城地安門的西街。街道是整整齊齊的楊樹林，道上行
人絡繹不絕，車輛馬匹穿插其中。大街上有閒逛的遊人，上京趕考的
考生，揹負着擔子的挑夫以及正在玩耍着的幼童構出了一幅繁忙熱鬧
的盛世景象。北方是一座富麗堂皇的巨宅，那就是當朝第一大臣，被
御封為『滿洲第一勇士』的鰲狠的府邸。向南經過西單北大街可以通
往西單。西方接西四北大街。
LONG );
       set("exits", ([
                "north" : "/d/beijing/aofu_men",
                "south" : "/d/beijing/di_3",
                "east" : "/d/beijing/di_5",
                "west" : "/d/beijing/shi_3",
        ]));
        set("objects", ([
                "/d/beijing/npc/boy2" : 1,
        ]));
        set("outdoors", "beijing");
	set("coor/x", -2820);
	set("coor/y", 7730);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}