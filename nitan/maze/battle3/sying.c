#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", "宋軍大營"NOR);
        set("long", @LONG
這裏就是「大宋」軍營了，一面大旗高高樹起，上面書着一個鬥
大的隸書「宋」字，前面不遠就是宋軍元帥的帳營了。
LONG );

        set("no_magic", "1");
        set("exits", ([ /* sizeof() == 5 */
               "south" :   __DIR__"sying1",
               "north" :   __DIR__"syuanmen1",
        ]));

        set("objects", ([

        ]));

        setup();
        replace_program(ROOM);
}

