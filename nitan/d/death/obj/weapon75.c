#include <ansi.h>
#include <weapon.h>

inherit SWORD;

void create()
{
        set_name(HIC "蹊雲寒□" NOR, ({ "qiyun jian", "qiyun", "jian", "sword" }) );
        set_weight(4000);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "柄");
                set("value", 1200000);
                set("material", "steel");
        }
        init_sword(95);
        setup();
}