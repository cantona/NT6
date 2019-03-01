#include <ansi.h>
inherit ROOM;
inherit __DIR__"jiguan_room.c";

void create()
{
        set("short", "石室");
        set("long", @LONG
這是一間寬敞的石室，只見四周空曠無比，不遠處有一塊形狀奇
特的石桌（desk）。
LONG );
        set("maze", 1);
        set("no_magic", 1);
        set("virtual_room", 1);
        set("no_clean_up", 1);
        set("room_id", "number/lockroom4");
        set("item_desc", ([
                "desk" : NOR + WHT "一張形狀奇特的石桌，似乎連接著什麼機關！\n" NOR,
        ]));
        setup();
}