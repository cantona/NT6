// qingguang-jian.c 青光劍
// Last Modified by winder on Sep. 7 2001

#include <weapon.h>;
#include <ansi.h>;
inherit SWORD;
inherit F_UNIQUE;

void create()
{
        set_name(HIC"青光劍"NOR, ({ "qingguang jian", "jian", "sword" }) );
        set_weight(2000);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "把");
                set("long",HIC"這把劍長約四尺，青光閃閃，的確是把利器。\n"NOR);
                set("value", 10000);
                set("material", "steel");
        }
        init_sword(120);
        set("no_drop", "這樣東西不能離開你。\n");
        set("no_put","如此寶劍如何能亂放？\n");
        set("wield_msg", "只聽見「颼」地一聲，$N的手中已經多了一把青光四射寒氣逼人的利劍——$n。\n");
        set("unequip_msg", "$N將手中的$n插入腰間的劍鞘。\n");
        setup();
}