#include <ansi.h>

inherit TESSERA;

void create()
{
        set_name(WHT "玄冰﹒寒鐵" NOR, ({"ice steel", "han tie", "tie"}));
        set_weight(50);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("long", WHT "一塊亮晶晶的金屬，據說是在上古玄冰中孕育\n"
                                "出的寒鐵。擁有無窮的魔力，上古神物，已經\n"
                                "通靈。\n" NOR);
                set("value", 10000000);
                set("unit", "塊");
                set("can_be_enchased", 1);
                set("magic/type", "water");
                set("magic/power", 1000);
        }
        set("enchase/SN", 5 + random(5));
        set("enchase/type", "all");
        set("enchase/weapon_prop", ([
                "add_water" : 50,
                "add_skill" : 30,
        ]));
        setup();
}

int query_autoload() { return 1; }
