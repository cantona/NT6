#include <room.h>
inherit ROOM;

void create()
{
        set("short", "西長安廣場");
        set("long", @LONG
這裏是天安門左邊的西長安街廣場，寬闊的長安大街向東西兩頭
延伸，這裏京城裏最熱鬧繁華的地段，既是交通要道，也是京城百姓
們的聚點， 廣場上車水馬龍，熱鬧非凡。小販們沿街叫賣着自己的貨
物。一些遊手好閒的人常常在這裏溜溜達達。這裏可以望見東邊高大
厚實的古城牆，那裏便是天安門廣場了。西邊則是寬闊的西長安大街。
LONG );
       set("exits", ([
                "west" : "/d/beijing/caroad_w2",
                "east" : "/d/beijing/tiananmen",
                "north" : "/d/beihai/ximen",
        ]));
        set("objects", ([
                "/d/beijing/npc/girl4" : 1,
                "/d/beijing/npc/girl2" : 1,
                "/d/beijing/npc/shusheng2" : 1,
        ]));
        set("outdoors", "beijing");
	set("coor/x", -2810);
	set("coor/y", 7670);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}