
#include <armor.h>
#include <ansi.h>

inherit RINGS;

void create()
{
        set_name(MAG "煉獄" HIR "血環" NOR, ({ "lianyu xuehuan", "lianyu", "xuehuan" }));
        set_weight(500);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "枚");
                set("long", MAG "紫黑色的指環，血色的暗紋，散發著陣陣陰寒之氣，令人心神顫抖。 \n" NOR);
                set("value", 20000000);
                set("material", "gold");
                set("armor_prop/damage", 4000);
                set("armor_prop/int", 20);
                set("armor_prop/add_tihui_gift", 5); // 增加體會獎勵5% giftd.c中處理
                set("armor_prop/add_tihui_xiaolv", 5); // 增加體會汲取效率5% jiqu.c中處理
                set("special/desc", HIR "殺怪、殺BOSS所得體會獎勵額外增加5%，" 
                                        "提升實戰體會汲取效率5%"NOR);
                set("limit", ([ 
                         "exp" : 100000000,
                         "scborn" : 1,
                ]));

        }
        setup();
}

int query_autoload()
{
        return 1;
}

