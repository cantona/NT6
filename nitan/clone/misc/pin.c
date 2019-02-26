// pin.c 鋼針

#include <weapon.h>
#include <ansi.h>

inherit PIN;

void create()
{
        set_name("鋼針", ({ "pin", "zhen" }));
        set_weight(15);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "根");
                set("long", "這是一用來縫製衣服的針，頗為粗長。\n");
                set("value", 10);
                set("material", "steel");
                set("wield_msg", YEL "$N手一抖，亮出一根$n" YEL "。\n");
                set("unwield_msg", YEL "$N收起了$n" YEL "。\n");
        }

        init_pin(10);
        setup();
}