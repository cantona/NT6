// coin.c

#include <weapon.h>
#include <ansi.h>

inherit MONEY;
inherit F_EQUIP;

void create()
{
        set_name(HIY "銅板" NOR, ({"coin", "coins", "coin_money" }));
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("money_id", "coin");
                set("long", "這是流通中單位最小的貨幣，約要一百個銅板才值得一兩銀子。\n");
                set("unit", "串");
                set("base_value", 1);
                set("base_unit", "個");
                set("base_weight", 30);
                set("consistence", 100);

                set("weapon_prop/damage", 10);
                set("flag", 2);
                set("wield_msg", "$N從袖口取出一串$n拋了拋，握在手中。\n");
                set("unwield_msg", "$N將手中的$n放回兜裏。\n");
                set("skill_type", "throwing");
                if( !query("actions") ) {
                    set("actions", (: call_other,WEAPON_D, "query_action" :));
                    set("verbs", ({ "throw" }) );
                }
        }
        set_amount(1);
}
