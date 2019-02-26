#include <room.h>
inherit ROOM;

void create()
{
        set("short", "東長安廣場");
        set("long", @LONG
這裏是天安門右邊的東長安街廣場，寬闊的長安大街向東西兩頭
延伸，這裏京城裏最熱鬧繁華的地段，既是交通要道，也是京城百姓
們的聚點， 廣場上車水馬龍，熱鬧非凡。小販們沿街叫賣着自己的貨
物。一些遊手好閒的人常常在這裏溜溜達達。這裏可以望見西邊高大
厚實的古城牆，那裏便是天安門廣場了。東邊則是東長安大街。
LONG );
       set("exits", ([
                "east" : "/d/beijing/caroad_e1",
                "west" : "/d/beijing/tiananmen",
        ]));
        set("objects", ([
                "/d/beijing/npc/shusheng1" : 2,
                "/d/beijing/npc/xianren" : 1,
        ]));
        set("outdoors", "beijing");
	set("coor/x", -2790);
	set("coor/y", 7670);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}