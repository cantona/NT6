//wkantai3.c  by winder

#include <room.h>

inherit ROOM;

void create()
{        
        set("short", "西較武場看台");
        set("long",
"這是唐門的西較武場看台。雖然對於看比武大賽來説，這裏不是最佳\n"
"的位置，但是這裏是喝彩聲最響的地方。因為聚在這裏的，通常是唐門的\n"
"晚輩弟子，最隨便，最衝動，也最有激情。北面，是西較武場的中間看台。\n"
);        
        set("no_steal", "1");
        set("no_fight", "1");
        set("exits", ([
                "north" : __DIR__"wkantai2",
        ]));
        setup();
        replace_program(ROOM);
}