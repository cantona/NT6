

#include <ansi.h>

inherit ITEM;

void create()
{
        set_name(HIY "菊花" NOR, ({ "penglai juhua" }) );
        set_weight(100);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "朵");
                set("value", 1);
                set("long", HIY "這是一朵菊花，花瓣呈現出各種不同的顏色，據説只有蓬萊仙島才有。\n" NOR);
        }

        setup();
}

int query_autoload()
{
        return 1;
}