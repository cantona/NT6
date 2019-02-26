#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", "轅門外"NOR);
        set("long", @LONG
這裏就是「大宋」軍營駐紮地了，遠遠地可以看見一面大旗，上
面書着一個斗大的隸書「宋」字，再走近些就到軍營了，尋常人還是
不要靠近的好，省得被當成細作捉起來。
LONG );

        set("no_magic", "1");
        set("exits", ([ /* sizeof() == 5 */   
               "north" :   __DIR__"sying4",
               "west"  :   __DIR__"yidao",
        ]));    

        set("objects", ([

        ]));
    
        setup();
        replace_program(ROOM);
}
