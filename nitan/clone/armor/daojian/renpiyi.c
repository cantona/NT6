

#include <armor.h>
#include <ansi.h>

inherit CLOTH;


void create()
{
        set_name(NOR + WHT "天降﹒人皮寶衣" NOR, ({ "renpi baoyi", "renpi", "baoyi" }) );
        set_weight(3000);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "件");
                set("long", NOR + WHT "傳說這是一件由人皮制成的寶衣，上面似乎記錄了某種奇特的武學。\n" NOR);
                set("material", "steel");
                set("value", 80000000);
                set("armor_prop/armor", 3000);
                set("armor_prop/parry", 200);
                set("special/desc", "有效招架提高200級。\n" +
                                    "穿上後可施展刀劍歸真之「萬馬奔騰」\n"
                );
                set("armor_prop/daojian_ben", 1);
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
