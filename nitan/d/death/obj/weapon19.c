#include <ansi.h>
#include <weapon.h>

inherit STAFF;

void create()
{
        set_name(MAG "七星杖·寂滅" NOR, ({ "ji mie", "qixingzhang", "zhang", "staff" }) );
        set_weight(22000);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "根");
                set("value", 2600000);
                set("material", "steel");
                set("long", HIW "\n七星杖·寂滅乃九穹七獄神兵之一。\n" NOR);
                set("wield_msg", HIR "$N輕輕抖出$n" HIR "，剎時雷聲轟鳴，一股殺氣直聶九霄。\n" NOR);
        }
        init_staff(150);
        setup();
}
