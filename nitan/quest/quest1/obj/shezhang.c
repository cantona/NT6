//shezhang.c
#include <weapon.h>
inherit STAFF;

void create()
{
        set_name("蛇杖", ({ "she zhang", "zhang" }));
        set_weight(10000);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "根");
                set("long", "這是一根蛇杖, 杖頭一條小蛇, 紅舌伸縮, 十分詭異。\n");
                set("value", 300);
                set("material", "leather");
                set("wield_msg", "$N「唰」的一聲提起一根$n握在手中。\n");
                set("unwield_msg", "$N將手中的$n收回背後。\n");
        }
        init_staff(100, TWO_HANDED);
        setup();
}
