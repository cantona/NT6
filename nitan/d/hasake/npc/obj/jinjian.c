// 金匕首.c

#include <ansi.h>
#include <weapon.h>
inherit SWORD;

void create()
{
        set_name(HIY"金匕首"NOR, ({ "jin bishou", "jian", "bishou" }));
        set_weight(3000);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "柄");
                set("long", "這是一柄金光閃閃的匕首，看上去極其鋒利。\n");
                set("value", 10000);
                set("material", "gold");
                set("wield_msg", "$N無聲無息地摸出一柄$n藏在手中。\n");
                set("unwield_msg", "$N將手中的$n放回衣袖。\n");
        }
        init_sword(37);
        setup();
}