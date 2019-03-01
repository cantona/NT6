// qin.c 白玉瑤琴
// Last Modified by winder on Sep. 7 2001

#include <weapon.h>;
#include <ansi.h>;
inherit SWORD;
inherit F_UNIQUE;

void create()
{
        set_name(HIW"白玉瑤琴"NOR, ({ "yao qin", "qin"}));
        set_weight(6000);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "具");
                set("long", "這是一具用白玉做成的瑤琴。\n");
                set("value", 2000);
                set("material", "steel");
                set("wield_msg", "$N從背後將$n拿在手中。\n");
                set("unwield_msg", "$N將手中的$n放回背後。\n");
        }
        init_sword(100);
        setup();
}
