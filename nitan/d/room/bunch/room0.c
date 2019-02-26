// Create by BUNCH_D written by Lonely

#include <ansi.h>
inherit ROOM;

int is_bunch_room() { return 1; } 

void create()
{
        set("short", "空房間 - 請使用 cshort 來編輯標題");
        set("long", "這是一間什麼也沒有的空房間，請利用 clong 來編輯房間敍述。\n");
        
        set("exits", ([
                "north" : __DIR__"room1",
                "south" : __DIR__"entry",
        ]));

        setup();
}