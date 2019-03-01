// yusword.c

#include <weapon.h>
#include <ansi.h>
inherit SWORD;
void create()
{
        set_name(HIG "玉環劍" NOR, ({ "yuhuan jian", "yuhuan", "sword" }) );
        set_weight(700);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "把");
                set("long", "這是一把翠玉色的劍。\n");
                set("value", 200000);
                set("material", "steel");
                set("rigidity", 2000);
                set("wield_msg", "$N從劍鞘中抽出一把$n握在手中。\n");
                set("unwield_msg", "$N將手中的$n插入腰間的劍鞘。\n");
        }
        init_sword(40);
        setup();
}