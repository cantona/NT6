
#include <armor.h>
#include <ansi.h>

inherit HEAD;
 
void create()
{
        set_name(HIW "水晶冠" NOR, ({ "shuijing guan3", "shuijing", "guan3" }) );
        set_weight(1000);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("material", "steel");
                set("unit", "頂");
                set("long", HIM "這是一頂用水晶雕琢而成的頭冠，手工精巧無比，人間罕有。\n" 
                            HIC "佩帶後可提高研究及學習次數上限20%。\n" NOR);
                set("value", 3500000);
                set("armor_prop/armor", 100);
                set("armor_prop/up_yanjiu_times", 20);
                set("special/desc", HIR "佩帶後可提高研究及學習次數上限20%。" NOR);
                set("limit", ([
                        "int"             :  40,
                        "exp"             :  8000000,
                ]));
        }
        setup();
}

int query_autoload()
{
        return 1;
}