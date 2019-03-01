// yuhuan.c
#include <weapon.h>
#include <ansi.h>
inherit BLADE;

void create()
{
        set_name( HIG "玉環刀" NOR, ({ "yuhuan dao", "yuhuan", "blade" }) );
        set_weight(1000);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "把");
                set("long", "這是一把通體深碧色的刀。");
                set("value", 400000);
                set("rigidity", 200);
                set("material", "steel");
        }
        init_blade(40);
        set("wield_msg", "$N從刀鞘中抽出一把$n握在手中。\n");
        set("unwield_msg", "$N將手中的$n插回刀鞘中。\n");
        setup();
}
