// baoshishan.c
// Date: Nov.1997 by Venus
#include <room.h>
inherit ROOM;
void create()
{
        set("short", "寶石山");
        set("long", @LONG
寶石山不是很高，山上多奇峰怪石。其中高矗者就是“秦始皇纜
船石”，山路旁有一座亭子“來鳳亭”，亭前有塊卵形大石，臨空擱
置在山巔，叫落星石，又稱壽星石。再往北上就到了保淑塔，往南下
便回到大道了。
LONG);
        set("exits", ([
            "northup"   : __DIR__"baoshuta",
            "southdown" : __DIR__"road8",
        ]));
        set("objects", ([
            __DIR__"obj/shitou": 1,
            __DIR__"obj/eluanshi": 1,
        ]));
        set("outdoors", "xihu");
//        set("no_clean_up", 0);
	set("coor/x", 810);
	set("coor/y", -1990);
	set("coor/z", 10);
	setup();
        replace_program(ROOM);
}