#include <ansi.h>
inherit ROOM;
 
void create()
{
        set("short", "藍天");
        set("long",@LONG
四周是藍藍的天，潔白的雲在飄；地上的行人看起來象螞蟻。哇......
好爽啊。你心中有一種感覺：君臨天下一覽人間小！
LONG);   
        set("outdoors", "taohua");
        set("no_clean_up", 0);
        setup();
        replace_program(ROOM);
}