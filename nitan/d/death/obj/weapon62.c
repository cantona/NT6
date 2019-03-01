#include <ansi.h>
#include <weapon.h>

inherit SWORD;

void create()
{
        set_name(WHT "蒼穹神劍" NOR, ({ "cangqiong jian", "cangqiong", "jian", "sword" }) );
        set_weight(4000);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "柄");
                set("value", 3800000);
                set("material", "steel");
                set("long", HIW "\n蒼穹神劍乃九穹七獄神兵之一。\n" NOR);
                set("wield_msg", HIR "$N輕輕抖出$n" HIR "，剎時雷聲轟鳴，一股殺氣直聶九霄。\n" );
        }
        init_sword(210);
        setup();
}