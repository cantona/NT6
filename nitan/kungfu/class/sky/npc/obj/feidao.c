#include <weapon.h>
#include <ansi.h>

inherit THROWING;

void create()
{
        set_name(HIW "小李飛刀" NOR, ({ "xiaoli feidao", "feidao" }) );
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "柄");
                set("value", 6000);
                set("base_unit", "柄");
                set("base_weight", 300);
                set("base_value", 0);
                set("material", "iron");
                set("long", HIW "一柄看似普通的飛刀，刀柄上刻了個小小的“李”字。\n" NOR);
                set("wield_msg", HIW "$N" HIW "手臂微微一抖，手中已多了柄明晃晃的飛刀。\n" NOR);
                set("unwield_msg",HIW "$N" HIW "手臂微微一抖，手中的飛刀便已消逝不見。\n" NOR);
        }
        set_amount(1);
        init_throwing(300);
        setup();
}

