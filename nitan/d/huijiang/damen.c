// Room: /d/huijiang/damen.c
// Last Modified by winder on Sep. 12 2001

inherit ROOM;
#include <ansi.h>;

void create()
{
        set("short", "總舵大門");
        set("long",@LONG
你站在兩扇紅漆大門前，門上釘滿的碗口大小的銅釘，門口的台階
上叉腰站著兩個膀闊腰圓的大漢，往裡看去可以看見一條蜿延曲折的走
廊通向房屋深處。
LONG );
        set("outdoors", "huijiang");
        set("exits", ([
                "enter" : __DIR__"zoulang1" ,
                "south" : __DIR__"xiagu",
        ]));
        set("objects", ([
                __DIR__"npc/dizi" : 2,
                CLASS_D("honghua")+"/wen-tailai" : 1,
                CLASS_D("honghua")+"/luo-bing" : 1,
        ]));        
        set("coor/x", -50060);
        set("coor/y", 9140);
        set("coor/z", 0);
        setup();
}

void init()
{
        object me = this_player();
        if ( interactive( this_player()) &&
                (query("family/family_name", me) != "紅花會") && 
                (!present("honghua ling", me)))
                message_vision(HIG"兩個大漢向$N瞪了一眼，鼻子裡重重的哼了一聲！\n"NOR,me);
        else
                if ( present("honghua ling",me) &&
                        !query("zizhi", present("honghua ling",me))) 
                        message_vision(HIG"兩個大漢躬身向你行了個禮,說道：令主好！\n"NOR,me);
}

int valid_leave(object me, string dir)
{
        if ( (dir == "enter") &&
                (query("family/family_name", me) != "紅花會") && 
                objectp(present("wen tailai", environment(me))) &&
                (!present("honghua ling", me)))
                return notify_fail("文泰來攔住你說：非本會弟兄，不能進去！\n");
        return ::valid_leave(me, dir);
}
