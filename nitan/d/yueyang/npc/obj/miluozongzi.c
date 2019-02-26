// miluozongzi.c 汨羅粽子

#include <ansi.h>;
inherit ITEM;
inherit F_FOOD;

void create()
{
        set_name(YEL"汨羅粽子"NOR, ({"miluo zongzi", "zongzi"}));
        set_weight(500);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long","這是一隻香甜的汨羅粽子。每到端午，這裏的百姓都要划龍舟灑粽子，數千年來相沿成俗。\n");
                set("unit", "只");
                set("value", 300);
                set("food_remaining", 15);
                set("food_supply", 20);
        }
}