//mishi.c  by winder

#include <room.h>

inherit ROOM;

void create()
{        
        set("short", "秘室");
        set("long",
"這是一間秘室。據說唐門的暗器制法以及毒藥的煉法就收藏在這裡。\n"
"但是屋裡什麼都沒有，不知傳聞是否屬實。這時，一陣異味擦肩而過，不\n"
"是香，不是臭，更不是酸甜苦辣，只是一種感覺。難道，唐七味以嗅覺發\n"
"暗器的絕技，就是來自這裡。南面是唐門的後院。\n"
);        
        set("exits", ([
                "south" : __DIR__"houyuan",
        ]));
        setup();
        replace_program(ROOM);
}