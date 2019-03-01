// falun.c
// rama modified for hx 05/02

#include <weapon.h>

inherit COMBINED_ITEM;
inherit F_HAMMER;
inherit F_EQUIP;

void set_amount(int v)
{
        object owner = environment();
        if (v >= 0) {
                set("weapon_prop/damage", v * (int)query("base_weapon"));
                set("weapon_prop/dodge", v * (int)query("base_dodge"));
                set("weapon_prop/speed", v * (int)query("base_speed"));
                set("rigidity", v * query("base_rigidity"));
                if (query("equipped") && objectp(owner)) {
                        set_temp("apply/damage", query("weapon_prop/damage"), owner);
                        set_temp("apply/dodge", query("weapon_prop/dodge"), owner);
                        set_temp("apply/speed", query("weapon_prop/speed"), owner);
                }
        }
        ::set_amount(v);
}

void add_amount(int v) { set_amount((int)query_amount()+v); }

int wield() 
{
        object me = environment();
        if (query_amount() > 1 && me && userp(me)){
        if ((me->query_skill("riyue-lun", 1) + me->query_skill("hammer", 1)/2)/query_amount() < 50
        || (me->query_str() - 10 )/5 < query_amount()
        || query_amount() > 5
        || me->query_skill("longxiang", 1) < 101)
                return notify_fail("你使不了那麼多法輪。\n");
        }
        
        return ::wield();
}

void create()
{
        set_name("法輪", ({ "fa lun", "fa", "lun" }) );
//      set_weight(5000);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "副");
                set("base_unit", "只");
                set("base_weight", 6000);
                set("base_speed", -2);
                set("base_dodge", -2);
                set("long", "這是直徑尺半的一個鐵環，上面刻滿了密宗伏魔真言，環內中空。\n");
                set("value", 1000);
                set("material", "iron");
                set("no_sell",1);
                set("base_rigidity", 80);
                set("base_weapon", 25);
                set("wield_msg", "$N拿出一副$n，試了試重量，然後握在手中。\n");
                set("unwield_msg", "$N放下手中的$n。\n");
        }

        init_hammer(25);
        set_amount(1);
        setup();
}
