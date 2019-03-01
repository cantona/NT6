// dahai.c

#include <ansi.h>

inherit ROOM;
 
void create()
{
        set("short", "大海");
        set("long",@LONG
你正處在茫茫大海之中。你極目遠望，只見海天一線，周圍連個
黑點都沒有，耳邊只有海浪的拍打聲。
LONG);   
        set("no_magic", 1);
        setup();
        replace_program(ROOM) ;
}
