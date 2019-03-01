#include <armor.h>
#include <ansi.h>

inherit RINGS;

void create()
{
        set_name(MAG "紫血環" NOR, ({ "zixue huan", "zixue", "huan" }));
        set_weight(500);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "枚");
                set("long", MAG "罕見的紫色血玉鍛造而成，入手冰冷刺骨，佩戴後有特殊功效。\n" NOR);
                set("value", 20000000);
                set("material", "gold");
                set("armor_prop/damage", 1000);
                set("armor_prop/int", 10);
                set("armor_prop/add_tihui_gift", 5); // 增加體會獎勵5% giftd.c中處理
                set("special/desc", HIR "殺怪、殺BOSS所得體會獎勵額外增加5%。" NOR);
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

