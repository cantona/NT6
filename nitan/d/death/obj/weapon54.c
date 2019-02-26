#include <ansi.h>
#include <weapon.h>

inherit BLADE;

void create()
{
        set_name(YEL "玄金斬·九餛陽" NOR, ({ "jiu hunyang", "xuanjinzhan", "blade", "dao" }) );
        set_weight(4000);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "柄");
                set("value", 3000000);
                set("material", "steel");
                set("long", HIW "\n玄金斬·九餛陽乃九穹七獄神兵之一。\n" NOR);
                set("wield_msg", HIR "$N輕輕抖出$n" HIR "，剎時雷聲轟鳴，一股殺氣直聶九霄。\n" );
        }
        init_blade(180);
        setup();
}