// female-cloth.c
// Last Modified by winder on May. 25 2001

#include <armor.h>;
#include <ansi.h>;
inherit CLOTH;

string* clothname = ({
        HIM"粉紅綢衫"NOR,
        HIW"白綢衫"NOR,
        HIG"湖綠長裙"NOR,
        HIY"鵝黃夾襖"NOR,
        HIB"青衫小袖"NOR,
        HIC"天青小袂"NOR,
        HIR"散花衣"NOR,
        MAG"紫紗小夾衫"NOR,
});
string* clothid = ({
        "pink cloth",
        "white cloth",
        "green skirt",
        "yellow coat",
        "blue shan",
        "qing mei",
        "flower cloth",
        "purple jiashan",
});
string* clothlong = ({
        "這件粉紅色的綢衫上面繡着幾隻黃鵲，聞起來還有一股淡香。\n",
        "這是一件輕盈飄動的白綢輕衫。\n",
        "這是一件清新可人的湖綠長裙。\n",
        "這是一件女孩喜歡的鵝黃夾襖。\n",
        "這是一件小巧玲瓏的青衫小袖。\n",
        "這是一件用金線繡着幾朵梅花的天青小袂。\n",
        "這件紅色的散花衣輕輕爽爽，很是飄逸。\n",
        "這是一件紫紗小夾衫。\n",
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
              //  set("long", clothlong[i]);
                set("unit", "件");
                set("value", 0);
                set("material", "cloth");
                set("armor_prop/armor", 1);
                set("armor_prop/per", 3);
                set("female_only", 1);
        }
        setup();
}
