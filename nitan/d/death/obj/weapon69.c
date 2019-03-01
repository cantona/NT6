#include <ansi.h>
#include <weapon.h>

inherit SWORD;

void create()
{
        set_name(HIM "鳳凰琴" NOR, ({ "fenghuang qin", "fenghuang", "qin", "jian", "sword" }) );
        set_weight(4000);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "柄");
                set("value", 3000000);
                set("material", "steel");
                set("long", HIW "\n鳳凰琴乃九穹七獄神兵之一。\n" NOR);
                set("wield_msg", HIR "$N輕輕抖出$n" HIR "，剎時雷聲轟鳴，一股殺氣直聶九霄。\n" );
        }
        init_sword(160);
        setup();
}