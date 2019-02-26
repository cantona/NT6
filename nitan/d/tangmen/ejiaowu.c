//ejiaowu.c  by winder

#include <room.h>

inherit ROOM;

void create()
{        
        set("short", "東較武場");
        set("long",
"這是唐門的東較武場。一片開闊平坦的空地，最適合比試武功。不要\n"
"看平日冷冷清清，唐門定期舉行的比武大會，有一半的賽事在這裏進行。\n"
"較場東側，排放了幾個兵器架。較場的西面，並排着三個看台，比賽時候\n"
"那驚天動地的喝彩聲，全都來自這裏。\n"
);        
        set("no_steal", "1");
        set("no_fight", "1");
        set("exits", ([
                "west" : __DIR__"ekantai2",
        ]));
        set("outdoors", "tangmen");
        setup();
        replace_program(ROOM);
}