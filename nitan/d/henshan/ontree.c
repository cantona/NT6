#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", "古樹上");
        set("long", @LONG
你極目遠眺，四周盡是懸崖峭壁。一條樹藤(teng)從高處垂下。
忽然見你看見前面峭壁上似乎有一個山洞(hole)，但是距離甚遠卻是
怎麼也過不去。
LONG );
        set("exits", ([ 
               "down" : __DIR__"xuanyadi",
               "up"   : __DIR__"ontree2"
           ]));

        set("item_desc", ([
               "hole"    : HIC "\n太遠了，看得不太清楚，看來得想個辦法過去。\n"        NOR,
           
               "teng"    : YEL"\n這些樹藤看起來很結實，似乎是從樹頂垂下來的。\n" NOR,
        ]));


        setup();
        replace_program(ROOM);
}