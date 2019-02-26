// yuquan.c
// Date: Nov.1997 by Venus
#include <room.h>
inherit ROOM;
void create()
{
        set("short", "玉泉");
        set("long", @LONG
玉泉寺建在玉泉山上，原名清漣寺。走進玉泉寺，只見這裏有幾個水池(pond)。
朝東就是出寺下山的路。
LONG);
        set("exits", ([
                "eastdown"  : __DIR__"road5",
                "north"     :  __DIR__"quanbian-xiaojing",
        ]));
        set("item_desc", ([
                "pond": "池旁的石碑刻着“古珍珠泉”，池內偶有小水泡上湧，好像一串珍珠\n",
        ]));
        set("objects" , ([
                __DIR__"npc/you-ke" : 1,
                __DIR__"npc/yuenv"  : 1,
        ]));
        set("outdoors", "xihu");
	set("coor/x", 770);
	set("coor/y", -2010);
	set("coor/z", 10);
	setup();
        replace_program(ROOM);
}