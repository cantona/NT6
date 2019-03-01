#include <room.h>
inherit ROOM;

void create()
{
        set("short", "四合院");
        set("long", @LONG
四合院是北京民居的典型，楊柳胡同中的這個四合院看來已經過
了一段很長久的歷史了。四合院的大門破舊不堪，大門原本漆著的顏
色已無法辨認，門上還貼著一幅殘破的對子，字跡模糊不清，猜想也
就無非是些『萬事如意』什麼的。你剛跨進四合院的大門，院內的居
民用奇怪的眼神上下打量著你，沒事還是趁早離開吧。
LONG );
       set("exits", ([
                "east" : "/d/beijing/yangliu1",
        ]));
        set("objects", ([
                "/d/beijing/npc/jumin1" : 1,
               "/clone/npc/walker"  : 1, 
        ]));
        set("outdoors", "beijing");
	set("coor/x", -2840);
	set("coor/y", 7660);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}