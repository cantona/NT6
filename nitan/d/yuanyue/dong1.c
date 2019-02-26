// This program is a part of NITAN MudLIB

inherit ROOM;
#include <room.h> 

void create()
{
        set("short", "山隙中");
        set("long", @LONG
這裏陰森黝暗，伸手不見五指，又極潮濕，僅容一人通過。向前
方望去，卻不知有多深遠。
LONG );
        set("exits", ([ /* sizeof() == 2 */
                "eastup" : __DIR__"dong0",
                "west" : __DIR__"gu",
 
        ]));
         
        set("coor/x",140);
        set("coor/y",0);
        set("coor/z",10);
        setup();
        replace_program(ROOM);
}
