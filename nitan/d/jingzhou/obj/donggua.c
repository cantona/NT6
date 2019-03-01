#include <ansi.h>
inherit ITEM;
inherit F_FOOD;

void create()
{
        set_name(HIC"冬瓜鱉裙羹"NOR, ({"donggua"}));
        set_weight(1000);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", "這是“四季美飯莊”的一道名菜，選用肥美的雄鱉裙邊和嫩冬瓜，再加雞湯，清燉而成。\n");
                set("unit", "碗");
                set("value", 500);
                set("food_remaining", 1);
                set("food_supply", 100);
        }
}
