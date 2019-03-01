#include <weapon.h>
#include <ansi.h>

inherit THROWING;

void create()
{
        set_name(HIR "斕蜈金針" NOR, ({ "lanwu jinzhen", "lanwu", "jinzhen", "zhen" }) );
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "些");
                set("value", 0);
                set("base_unit", "根");
                set("base_weight", 200);
                set("base_value", 0);
                set("material", "iron");
                set("long", HIR "這是一些血紅色的細長金針，長約寸許。\n" NOR);
        }
        set_amount(50);
        init_throwing(50);
        setup();
}