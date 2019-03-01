#include <ansi.h>

inherit ITEM;

void create()
{
        set_name(HIY "佛" HIM "光" HIC "寶珠" NOR, ({ "foguang baozhu", "foguang", "baozhu" }));
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", HIY "這是一粒閃耀著佛光的寶珠，光芒四射，人間罕有。\n" NOR);
                set("base_unit", "粒");
                set("unit", "粒");
                set("base_value", 100);
                set("base_weight", 1000);
        }
        setup();
}

int query_autoload()
{
        return 1;
}