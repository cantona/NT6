//  Room:  /d/changan/zhongnan.c
#include <room.h>

inherit BUNCH_ROOM; 

void  create  ()
{
        set  ("short",  "終南山口");
        set  ("long",  @LONG
終南山又稱太乙山，距長安城八十多裡，素有“錦秀巨屏拱長安”
之說。據傳老子曾在山中講經。這條大官道穿越終南山口，兩面秀峰入
雲，這裡卻沒有一條路可以上山。西面是往長安的大道，東面前往中原

LONG);
        set("exits",  ([  /*  sizeof()  ==  4  */
            "east"  :  __DIR__"road2",
            "west"  :  __DIR__"road3",
            "north"  :  __DIR__"questroom",    
        ]));
        set("outdoors", "guanzhong");

        set("no_clean_up", 0);
        set("coor/x", -10630);
	set("coor/y", 1920);
	set("coor/z", 0);
	setup();
}
