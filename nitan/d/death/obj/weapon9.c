#include <ansi.h>
#include <weapon.h>

inherit HAMMER;

void create()
{
        set_name(CYN "冥王破獄錘" NOR, ({ "mingwang chui","mingwang","chui", "hammer" }));
        set_weight(28000);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "把");
                set("value", 3800000);
                set("material", "steel");
                set("long", HIW "\n冥王破獄錘乃九穹七獄神兵之一。\n" NOR);
                set("wield_msg", HIR "$N輕輕抖出$n" HIR "，剎時雷聲轟鳴，一股殺氣直聶九霄。\n" NOR);
        }
        init_hammer(210);
        setup();
}

