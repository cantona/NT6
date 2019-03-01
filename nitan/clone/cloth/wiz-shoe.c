// wiz-shoe.c
// Last Modified by winder on May. 25 2001
 
#include <armor.h>;
#include <ansi.h>;

inherit BOOTS;

string* shoename = ({
        HIB"天師靴"NOR,
        HIG"步雲履"NOR,
        HIY"眾神之車"NOR,
});
string* shoeid = ({
        "wizard shoe",
        "cloth shoes",
        "skin shoes",
});
string* shoelong = ({
        "這是一雙巫師隨常使用的皮靴。\n",
        "這是一雙用上好龍皮作的皮靴。\n",
        "這是一雙白玉鑲就的飛騰之靴。\n",
});

void create()
{
        int i = random(sizeof(shoename));

        set_name(shoename[i], ({ shoeid[i], "shoe" }));
        set_weight(900);
        set("long", shoelong[i]);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("material", "cloth");
                set("unit", "雙");
       //         set("long", shoelong[i]);
                set("value", 0);
                set("armor_prop/armor", 100);
        }
        setup();
}