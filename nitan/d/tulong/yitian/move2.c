#include <ansi.h>

inherit ROOM;

void create()
{
        set("short", "小路");
        set("long", @LONG
這是一條蜿蜒的小路，北面可以遠遠的望見萬安寺的塔間。
LONG );

        set("outdoors", "beijing");
        setup();
}