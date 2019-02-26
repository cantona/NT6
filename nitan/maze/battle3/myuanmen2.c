#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", "轅門外"NOR);
        set("long", @LONG
這裏就是「蒙古」軍營駐紮地了，遠遠地可以看見大營內飛揚的
塵土，不時有幾匹快馬飛奔進出，你正欲再看，忽然嗖地一枚冷箭從
你頭上飛過，還是趕快離開的好。
LONG );

        set("no_magic", "1");
        set("exits", ([ /* sizeof() == 5 */   
               "south" :   __DIR__"mying4",
        ]));    

        set("objects", ([

        ]));
    
        setup();
        replace_program(ROOM);
}
