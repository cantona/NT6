#include <weapon.h>
inherit SWORD;
#include <ansi.h>
void create()
{
        set_name(HIR "五毒神剪" NOR, ({ "wudu shenjian", "jian", "shenjian" }));
        set_weight(5000);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "柄");
                set("long", "這是一柄奇門兵器，好似一只大剪刀。\n");
                set("value", 10000);
                set("material", "steel");
                set("wield_msg", "$N「唰」的一聲掏出一柄$n握在手中。\n");
                set("unwield_msg", "$N將手中的$n掛在腰間。\n");
        }
        init_sword(70);
        setup();
}