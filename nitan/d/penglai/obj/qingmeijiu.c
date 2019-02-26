

#include <ansi.h>

inherit ITEM;

void create()
{
        set_name(HIY "青梅酒" NOR, ({ "penglai qingmeijiu" }) );
        set_weight(100);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "瓶");
                set("value", 1);
                set("long", HIY "這是一瓶精心釀製的青梅酒，雖然裝在瓶中，卻依然無法掩蓋其香氣。\n" NOR);
        }

        setup();
}

int query_autoload()
{
        return 1;
}