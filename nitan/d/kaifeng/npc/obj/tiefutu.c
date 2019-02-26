#include <ansi.h>
inherit ITEM;

void create()
{
        set_name(YEL "青銅浮屠" NOR, ({ "futu" }) );
        set_weight(500000);
        set_max_encumbrance(800);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "座");
                set("long", "這是佛門中的浮屠，上面雕刻着金剛經。\n");
                set("value", 50);
        }
}