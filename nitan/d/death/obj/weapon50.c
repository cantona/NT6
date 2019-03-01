#include <ansi.h>
#include <weapon.h>

inherit BLADE;

void create()
{
        set_name(HIG "碧海殘□" NOR, ({ "bihai canjue", "bihai", "blade", "dao" }) );
        set_weight(4000);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "柄");
                set("value", 1700000);
                set("material", "steel");
                set("long", HIW "\n碧海殘□乃九穹七獄神兵之一。\n" NOR);
                set("wield_msg", HIR "$N輕輕抖出$n" HIR "，剎時雷聲轟鳴，一股殺氣直聶九霄。\n" );
        }
        init_blade(140);
        setup();
}