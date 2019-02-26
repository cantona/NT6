#include <ansi.h>

inherit TESSERA;

void create()
{
        set_name(HIB "上古·虎魄" NOR, ({"tiger soul", "tiger", "soul"}));
        set_weight(50);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("long", HIB "\n一塊藍色的虎魄，無暇的表面射魄出奇幻的光\n"
                            "澤。其中彷彿藴藏着無窮的魔力，這便是傳説\n"
                            "中的至寶，兇中之兇的——上古虎魄，相傳為\n"
                            "上古時代，蚩尤所得異物煉製而成。上古神物，\n"
                            "已經通靈。\n" NOR);
                set("value", 10000000);
                set("unit", "塊");
                set("can_be_enchased", 1);
                set("magic/type", "wood");
                set("magic/power", 1000);
        }
        set("enchase/SN", 5 + random(5));
        set("enchase/type", "all");
        set("enchase/weapon_prop", ([
                "add_wood"  : 50,
                "add_skill" : 30,
        ]));
        setup();
}

int query_autoload() { return 1; }
