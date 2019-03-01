// /d/taiwan/dahai.c
// Last Modifyed by Ahda on Jan. 4 2002

#include <ansi.h>
inherit ROOM;
 
void create()
{
        set("short", "大海");
        set("long",@LONG
你正處在茫茫大海之中。你極目遠望，只見海天一線，周圍連個黑
點都沒有。耳邊只有海浪的拍打聲。
LONG);   
        set("outdoors", "taiwan");
        set("no_clean_up", 0);
        setup();
        replace_program(ROOM) ;
}