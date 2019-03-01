// female-shoe.c
// Last Modified by winder on May. 25 2001

#include <armor.h>;
#include <ansi.h>;

inherit BOOTS;

string* shoename = ({
        HIM"繡花小鞋"NOR,
        "布鞋",
});
string* shoeid = ({
        "flower shoes",
        "cloth shoes",
});
string* shoelong = ({
        "這是一雙女人穿的縫制得很精美的繡花鞋。\n",
        "這是一雙很普通的粗布鞋。\n",
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
        //        set("long", shoelong[i]);
                set("value", 0);
                set("armor_prop/armor", 1 );
                set("female_only", 1);
        }
        setup();
}