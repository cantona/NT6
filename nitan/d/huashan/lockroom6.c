#include <ansi.h>
inherit ROOM;
inherit __DIR__"tsr_room.c";

void create()
{
        set("short", "石室");
        set("long", @LONG
這是一間寬敞的石室，只見四周空曠無比，不遠處有一塊形狀奇
特的石桌（desk）。
LONG );
        set("exits", ([
                "out" : __DIR__"s",
        ]));
        set("room_id", "number/lockroom6");
        set("item_desc", ([
             "desk" : NOR + WHT "一張形狀奇特的石桌，似乎連接著什麼機關！\n" NOR,
        ]));
        set("no_clean_up", 0);
        setup();
}


