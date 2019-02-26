// jiandao.c 五毒剪
// Last Modified by winder on Sep. 7 2001

#include <weapon.h>;
#include <ansi.h>;
inherit F_UNIQUE;
inherit HOOK;

void create()
{
        set_name("五毒剪", ({ "wudu jian", "jian" }));
        set_weight(5000);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "柄");
                set("long", "這是一柄奇門兵器，好似一隻大剪刀，上面餵了劇毒。\n");
                set("value", 10000);
                set("material", "steel");
                set("wield_msg", "$N「唰」的一聲掏出一柄$n握在手中。\n");
                set("unwield_msg", "$N將手中的$n掛在腰間。\n");
        }
        init_hook(130);
        setup();
}