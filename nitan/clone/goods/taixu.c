#include <ansi.h>

inherit TESSERA;

void create()
{
        set_name(HIY "上古·太虛" NOR, ({"tai xu", "tai", "xu"}));
        set_weight(50);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("long", HIY "一塊金黃色的太虛，擁有無窮變化的魔力，這\n"
                            "便是傳説中的至寶——上古太虛，相傳為上古\n"
                            "時代，黃帝得九天玄女所送南北精鐵煉製而成。\n"
                            "上古神物，已經通靈。\n" NOR);
                set("value", 10000000);
                set("unit", "塊");
                set("can_be_enchased", 1);
                set("magic/type", "metal");
                set("magic/power", 1000);
        }
        set("enchase/SN", 5 + random(5));
        set("enchase/type", "all");
        set("enchase/weapon_prop", ([
                "add_metal" : 50,
                "add_skill" : 30,
        ]));
        setup();
}

int query_autoload() { return 1; }
