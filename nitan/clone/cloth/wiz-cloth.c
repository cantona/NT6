// wiz-cloth.c
// Last Modified by winder on May. 25 2001

#include <armor.h>;
#include <ansi.h>;

inherit CLOTH;

string* clothname = ({
        HIB"天師袍"NOR,
        HIC"無縫天衣"NOR,
        HIY"黃金戰甲"NOR,
});
string* clothid = ({
        "wizard cloth",
        "wizard cloth",
        "wizard cloth",
});
string* clothlong = ({
        "這是一件巫師隨常穿的休閒衣服。\n",
        "這是一件織女銀梭織就的無縫天衣。\n",
        "這是一件黃金打造的無敵戰甲。\n",
});

void create()
{
        int i = random(sizeof(clothname));

        set_name(clothname[i], ({ clothid[i], "cloth" }));
        set_weight(1000);
        set("long", clothlong[i]);
        if( clonep() )
                set_default_object(__FILE__);
        else {
        //        set("long", clothlong[i]);
                set("unit", "件");
                set("value", 0);
                set("material", "cloth");
                set("armor_prop/armor", 100);
                set("armor_prop/per", 300);
        }
        setup();
}
