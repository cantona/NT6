// mace.c
// Last Modified by winder on May. 25 2001

#include <weapon.h>
#include <ansi.h>

inherit MACE;

void create()
{
        set_name("熟銅鐗", ({"copper mace", "mace", "coppermace", "tongjian", "jian"}));
        set_weight(5000);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "柄");
                set("value", 2000);
                set("material", "copper");
                set("long", "一柄沉甸甸的熟銅鐗，上面銅鏽斑斑。\n");
                set("wield_msg", "$N舉起一柄$n，在地上撞出點點火星。\n");
                set("unwield_msg", "$N抹了抹$n上的鏽，把它收了起來。\n");
        }
        init_mace(25);
        setup();
}
