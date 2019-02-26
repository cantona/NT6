//mishi.c  by winder

#include <room.h>

inherit ROOM;

void create()
{        
        set("short", "祕室");
        set("long",
"這是一間祕室。據説唐門的暗器製法以及毒藥的煉法就收藏在這裏。\n"
"但是屋裏什麼都沒有，不知傳聞是否屬實。這時，一陣異味擦肩而過，不\n"
"是香，不是臭，更不是酸甜苦辣，只是一種感覺。難道，唐七味以嗅覺發\n"
"暗器的絕技，就是來自這裏。南面是唐門的後院。\n"
);        
        set("exits", ([
                "south" : __DIR__"houyuan",
        ]));
        setup();
        replace_program(ROOM);
}