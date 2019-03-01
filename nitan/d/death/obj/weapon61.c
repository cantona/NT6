#include <ansi.h>
#include <weapon.h>

inherit SWORD;

void create()
{
        set_name(CYN "軒轅神劍" NOR, ({ "xuanyuan jian", "xuanyuan", "jian", "sword" }) );
        set_weight(4000);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "柄");
                set("value", 4000000);
                set("material", "steel");
                set("long", HIW "\n軒轅神劍乃九穹七獄神兵之一。\n" NOR);
                set("wield_msg", HIR "$N輕輕抖出$n" HIR "，剎時雷聲轟鳴，一股殺氣直聶九霄。\n" );
        }
        init_sword(220);
        setup();
}