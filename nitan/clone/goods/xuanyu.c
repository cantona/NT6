#include <ansi.h>

inherit TESSERA;

void create()
{
        set_name(HIG "九地﹒玄玉" NOR, ({"jiudi xuanyu", "jiudi", "xuanyu"}));
        set_weight(50);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("long", HIG "一塊綠色的九地玄玉，擁有能醫重病，又能毒\n"
                            "殺人于一身的至寶──九地玄玉，相傳神農氏\n"
                            "所用神農尺就是用這枚九地玄玉精煉而成。上\n"
                            "古神物，已經通靈。\n" NOR);
                set("value", 10000000);
                set("unit", "塊");
                set("can_be_enchased", 1);
                set("magic/type", "earth");
                set("magic/power", 1000);
        }
        set("enchase/SN", 5 + random(5));
        set("enchase/type", "all");
        set("enchase/weapon_prop", ([
                "add_earth" : 50,
                "add_skill" : 30,
        ]));
        setup();
}

int query_autoload() { return 1; }
