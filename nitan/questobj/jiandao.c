// jiandao.c 五毒剪
#include <weapon.h>
inherit SWORD;
#include <ansi.h>
void create()
{
        set_name("五毒剪", ({ "jian dao", "gou" }));
        set_weight(5000);
        set("taskobj", 1);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "柄");
                set("long", "這是一柄奇門兵器，好似一只大剪刀，上面喂了劇毒。\n"
);
                set("value", 0);
                set("material", "steel");
                set("wield_msg", "$N「唰」的一聲掏出一柄$n握在手中。\n");
                set("unwield_msg", "$N將手中的$n掛在腰間。\n");
        }
        setup();
}