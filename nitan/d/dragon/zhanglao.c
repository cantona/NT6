inherit ROOM; 
#include <ansi.h> 
void create()
{
        set("short", "長老室");
        set("long",
"[1;32m這是精靈長老所在的房間，一個白胡子的精靈族老人正坐在\n"
"窗前沉思著什麼。\n"
);
        set("exits", ([ /* sizeof() == 4 */
   "west" : __DIR__"village",
   "southeast" : __DIR__"xiuxishi",
   ]));

        set("no_magic", 1);
        setup();
        replace_program(ROOM);

}
