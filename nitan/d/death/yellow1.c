// yellow1.c 黃泉大道

#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", BLU "黃泉路" NOR);
        set("long",BLU @LONG
“人生自古誰無死”，從古至今，死一直是所有帝王將相，仁人義
士不能避免的結局。眼前就是著名的黃泉大道。就在你身邊，一個個模
模糊糊的身影湧動着，耳邊不乏一陣陣的啼哭之聲可知韶華易逝，青春
難駐，人生在世多麼的短暫，到了這個時候，卻又是多麼的留戀......
LONG NOR);
        set("exits", ([
                "north" : __DIR__"yellow2",
        ]) );
        set("no_fight", 1);
        set("no_clean_up", 0);
        setup();
        replace_program(ROOM);
}
