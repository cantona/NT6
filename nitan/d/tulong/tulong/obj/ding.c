#include <ansi.h>
inherit ITEM;

void create()
{
        set_name(YEL "銅鼎" NOR, ({ "ding"}) );
        set_weight(500);
        set_max_encumbrance(800000);
        set("no_get", 1);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("prep", "in");
                set("unit", "只");
                set("long", HIR "銅鼎中燒着熊熊烈火，火焰衝起一丈來高。\n" NOR);
                set("value", 1);
        }
}

int is_container() { return 1; }
