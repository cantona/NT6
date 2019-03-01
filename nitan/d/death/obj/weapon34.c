#include <ansi.h>
#include <weapon.h>

inherit WHIP;

void create()
{
        set_name(HIY "神蛟絲﹒噬月" NOR, ({ "shi yue", "shenjiaosi", "suo", "whip" }) );
        set_weight(4000);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "根");
                set("value", 3200000);
                set("material", "steel");
                set("long", HIW "\n神蛟絲﹒噬月乃九穹七獄神兵之一。\n" NOR);
                set("wield_msg", HIR "$N輕輕抖出$n" HIR "，剎時雷聲轟鳴，一股殺氣直聶九霄。\n" );
        }
        init_whip(180);
        setup();
}