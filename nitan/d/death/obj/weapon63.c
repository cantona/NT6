#include <ansi.h>
#include <weapon.h>

inherit SWORD;

void create()
{
        set_name(HIY "金剛劍·鬼龍" NOR, ({ "gui long", "jingangjian", "jian", "sword" }) );
        set_weight(4000);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "柄");
                set("value", 3700000);
                set("material", "steel");
                set("long", HIW "\n金剛劍·鬼龍乃九穹七獄神兵之一。\n" NOR);
                set("wield_msg", HIR "$N輕輕抖出$n" HIR "，剎時雷聲轟鳴，一股殺氣直聶九霄。\n" );
        }
        init_sword(200);
        setup();
}