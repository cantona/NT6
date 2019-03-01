

#include <ansi.h>

inherit ITEM;

void create()
{
        set_name(HIM "蓬萊蟠桃" NOR, ({ "penglai pantao" }) );
        set_weight(100);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "個");
                set("value", 1);
                set("long", HIM "這是一個蓬萊蟠桃，據說每二百年才結果。\n" NOR);
        }

        setup();
}

int query_autoload()
{
        return 1;
}