// male-cloth.c
// Last Modified by winder on May. 25 2001

#include <armor.h>;
#include <ansi.h>;

inherit CLOTH;

string* clothname = ({
        "粗布衣",
        HIB"青衫"NOR,
        BBLK"黑色勁裝"NOR,
        HIC"短打勁裝"NOR,
        HIM"紫蟒袍"NOR,
        BLU"藍馬褂"NOR,
        HIY"明黃錦袍"NOR,
        HIB"天藍長袍"NOR,
});
string* clothid = ({
        "rough cloth",
        "blue cloth",
        "black cloth",
        "bunt cloth",
        "purple cloth",
        "blue cloth",
        "yellow cloth",
        "celeste cloth",
});
string* clothlong = ({
        "這是一件很普通的粗布衣。\n",
        "這是一件很普通的粗布青衫。\n",
        "這是一件很筆挺的黑色勁裝。\n",
        "這是一件很利索的短打勁裝。\n",
        "這是一件很重的紫蟒袍。\n",
        "這是一件很重的藍馬褂。\n",
        "這是一件明黃錦袍。\n",
        "這是一件天藍長袍。\n",
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
       //         set("long", clothlong[i]);
                set("unit", "件");
                set("value", 0);
                set("material", "cloth");
                set("armor_prop/armor", 1);
                set("armor_prop/per", 3);
        }
        setup();
}
