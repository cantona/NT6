
#include <armor.h>
#include <ansi.h>

inherit HEAD;
 
void create()
{
        set_name(HIW "水晶冠" NOR, ({ "shuijing guan", "shuijing", "guan" }) );
        set_weight(1000);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("material", "steel");
                set("unit", "頂");
                set("long", HIM "這是一頂用水晶雕琢而成的頭冠，手工精巧無比，人間罕有。\n" 
                            HIC "佩帶後可提高研究及學習次數上限10%。\n" NOR);
                set("value", 3500000);
                set("armor_prop/armor", 100);
                set("armor_prop/yanjiu_times", 10);
                set("special/desc", HIR "佩帶後可提高研究及學習次數上限10%。" NOR);
                set("require", ([
                        "int"             :  30,
                        "exp"             :  5000000,
                ]));
        }
        setup();
}

int query_autoload()
{
        return 1;
}
