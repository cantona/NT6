#include <ansi.h>
#include <weapon.h>

inherit BLADE;

void create()
{
        set_name(YEL "玄金斬·虛空" NOR, ({ "xu kong", "xuanjinzhan", "blade", "dao" }) );
        set_weight(4000);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "柄");
                set("value", 3300000);
                set("material", "steel");
                set("long", HIW "\n玄金斬·虛空乃九穹七獄神兵之一。\n" NOR);
                set("wield_msg", HIR "$N輕輕抖出$n" HIR "，剎時雷聲轟鳴，一股殺氣直聶九霄。\n" );
        }
        init_blade(195);
        setup();
}