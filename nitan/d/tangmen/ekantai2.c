//ekantai2.c  by winder

#include <room.h>

inherit ROOM;

void create()
{        
        set("short", "東較武場看台");
        set("long",
"這是唐門的東較武場看台。看台上除了幾排座位外，中間設了三張金\n"
"鑄銀雕的太師椅。觀看比武大賽的最佳位置，就在這個看台上。當然，唐\n"
"門主持大賽的掌權者們的座位，也就設在這裏。你站在看台上，鬥志激昂。\n"
"這裏的東面，是東較武場，南北各有一個看台。西面是東較武場的入口。\n"
);        
        set("no_steal", "1");
        set("no_fight", "1");
        set("exits", ([
                "west"  : __DIR__"erukou",
                "north" : __DIR__"ekantai1",
                "south" : __DIR__"ekantai3",
                "east"  : __DIR__"ejiaowu",

        ]));
        setup();
        replace_program(ROOM);
}