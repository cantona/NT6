// baihong-jian.c 白虹劍

#include <weapon.h>

inherit SWORD;
// inherit F_UNIQUE;
void create()
{
        set_name("白虹劍", ({ "baihong jian", "baihong", "sword" }) );
        set_weight(10000);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "把");
                set("long","這是把又薄又輕的軟劍，劍身上隱隱的透出白光，當真鋒利無比。\n");
                set("value", 3000);
                // set("unique", 1);
                set("rigidity", 3);
                set("sharpness", 3);
                set("material", "blacksteel");
                set("weapon_prop/parry",2);
                set("wield_neili", 500);
                set("wield_maxneili", 900);
                set("wield_str", 22);
                set("treasure",1);
                set("wield_msg", "只聽見「嗡」地一聲，白光頓現，$N將腰間解下的$n抖得筆直。\n");
                set("unequip_msg", "$N將手中的$n卷入腰間。\n");
        }
        init_sword(70);
        setup();
}