//wkantai1.c  by winder

#include <room.h>

inherit ROOM;

void create()
{        
        set("short", "西較武場看台");
        set("long",
"這是唐門的西較武場看台。雖然對于看比武大賽來說，這裡不是最佳\n"
"的位置，但是這裡是喝彩聲最響的地方。因為聚在這裡的，通常是唐門的\n"
"晚輩弟子，最隨便，最沖動，也最有激情。南面，是西較武場的中間看台。\n"
);        
        set("no_steal", "1");
        set("no_fight", "1");
        set("exits", ([
                "south" : __DIR__"wkantai2",
        ]));
        setup();
        replace_program(ROOM);
}