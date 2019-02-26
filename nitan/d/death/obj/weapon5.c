#include <ansi.h>
#include <weapon.h>

inherit CLUB;

void create()
{
        set_name(HIW "如意棍·千鈞" NOR, ({ "qian jun", "ruyi gun","club","gun" }));
        set_weight(20000);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "杆");
                set("value", 2400000);
                set("material", "steel");
                set("long", HIW "\n如意棍·千鈞乃九穹七獄神兵之一。\n" NOR);
                set("wield_msg", HIR "$N輕輕抖出$n" HIR "，剎時雷聲轟鳴，一股殺氣直聶九霄。\n" NOR);
        }
        init_club(160);
        setup();
}

