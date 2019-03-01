// xuantie-jian.c 玄鐵重劍
// Last Modified by winder on Sep. 7 2001

#include <weapon.h>;
#include <ansi.h>;
inherit SWORD;
inherit F_UNIQUE;

void create()
{
        set_name(WHT"玄鐵重劍"NOR, ({ "iron sword", "jian", "sword" }) );
        set_weight(50000);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "把");
                set("long",WHT@LONG
這把劍長三尺有余，黑黝黝的，竟有七八十斤重。劍兩邊劍鋒都是鈍口，
劍尖更圓圓的似是個半球。
LONG
NOR);
                set("value", 100000);
                set("material", "iron");
        }
        init_sword(160);
        set("no_drop", "這樣東西不能離開你。\n");
        set("no_put","如此寶劍如何能亂放？\n");
        set("wield_msg", "只聽見「鐺」地一巨響，$N拔出了一把黑黝黝的武林重寶──$n。\n");
        set("unequip_msg", "$N將手中的$n插入背上的劍鞘。\n");
        setup();
}
