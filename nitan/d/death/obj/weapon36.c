#include <ansi.h>
#include <weapon.h>

inherit WHIP;

void create()
{
        set_name(CYN "烏龍神蛟絲" NOR, ({ "wulong si", "shenjiaosi", "si", "whip" }) );
        set_weight(4000);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "根");
                set("value", 3900000);
                set("material", "steel");
                set("long", HIW "\n烏龍神蛟絲乃九穹七獄神兵之一。\n" NOR);
                set("wield_msg", HIR "$N輕輕抖出$n" HIR "，剎時雷聲轟鳴，一股殺氣直聶九霄。\n" );
        }
        init_whip(220);
        setup();
}