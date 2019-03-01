//changjian 
#include <weapon.h>

inherit SWORD;

void create()
{
        set_name("長劍", ({ "changjian","sword" , "chang jian" , "jian" }) );
        set_weight(7000);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "把");
                set("long", "這是一把看起相當普通的長劍。\n");
                set("value" , 1000);
                set("material", "steel");
        }
        init_sword(25);

// These properties are optional, if you don't set them, it will use the
// default values.

        set("wield_msg", "$N「唰」地一聲抽出一把$n握在手中。\n");
        set("unwield_msg", "$N將手中的$n插入腰間的劍鞘。\n");

        setup();
}