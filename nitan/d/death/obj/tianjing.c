#include <ansi.h>

inherit ITEM;

void create()
{
        set_name(HIW "寰宇天晶" NOR, ({"tian jing", "tian", "jing"}));
        set_weight(10000);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", HIW "\n一塊純白色的水晶，晶瑩剔透，無暇的表面射\n"
                            "出耀眼的光澤。其中彷彿藴藏着千千萬萬的生\n"
                            "命，生命流動不息，散發出宇宙的力量。這便\n"
                            "是傳説中的至寶——寰宇天晶，相傳只有在天\n"
                            "宮中才會出現。\n" NOR);
                set("unit", "塊");
                set("value", 10000000);
                set("no_store", 1);
                set("item_origin", 1);
                set("material_attrib", "tian jing");
                set("material_name", HIW "寰宇天晶" NOR);
                set("can_make", "all");
                set("power_point", 200);
        }
}