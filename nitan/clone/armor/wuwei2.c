
#include <armor.h>
#include <ansi.h>

inherit NECK;

void create()
{
        set_name(HIY "無為" NOR, ({ "wu wei2", "wu", "wei2" }));
        set_weight(500);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "串");
                set("value", 200000);
                set("material", "gold");
                set("armor_prop/joblv", 1);
                set("armor_prop/damage", 100);
                set("armor_prop/str", 3);
                set("special/desc", HIR "可破格提升轉世職業技能1級。" NOR);
                set("limit", ([ 
                                        "exp" : 20000000,
                                        "scborn" : 1,
                ]));
        }
        setup();
}        

int query_autoload()
{
        return 1;
}