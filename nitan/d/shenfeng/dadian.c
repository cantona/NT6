inherit ROOM;
#include <room.h>

void create()
{
            set("short", "大殿");
            set("long", @LONG
你走到殿口，只見大殿中也到處都是骸骨，玉刀玉劍散滿
了一地，想來當日必曾有過一場激戰。殿中地下到處是大大小
小的玉製武器，刀槍劍戟都有，只是形狀奇特，與中土習見的
迥然不同。骸骨前面有一塊十分光滑的石板。
LONG);
        set("objects", ([
                __DIR__"obj/yufu" : random(3),
                __DIR__"obj/yudao" : random(3),
                __DIR__"obj/yujian" : random(3),
                __DIR__"obj/skeleton" : random(5) + 3,
                __DIR__"obj/skeleton1" : 1,
        ]));
            set("exits", ([ 
                "west" : __DIR__"yongdao4",
                "north" : __DIR__"diantang",
        ]));
            setup();
}