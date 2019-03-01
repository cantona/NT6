#include <ansi.h>
inherit ITEM;

void create()
{
        set_name(HIG "蛇信子" NOR, ({"shexin zi", "shexing", "zi"}));
        set("unit", "顆");
        set("long", HIG "這是一顆植物的果實。\n" NOR);
        set("value", 10);
        set_weight(10);
        setup();
}