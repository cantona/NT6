// food: /d/xingxiu/npc/obj/nang.c
// Jay 3/17/96

inherit ITEM;
inherit F_FOOD;

void create()
{
        set_name("□", ({"nang", "cake"}));
        set_weight(80);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", "這是維吾爾族人日常吃的一種面餅\n");
                set("unit", "個");
                set("value", 50);
                set("food_remaining", 3);
                set("food_supply", 20);
        }
}