// qingcai-fentiao.c 青菜粉條
// Last Modified by Sir on May. 22 2001

inherit ITEM;
inherit F_FOOD;

void create()
{
        set_name("粉條", ({"qingcai fentiao","fentiao"}));
        set_weight(200);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", "一盆白綠相間，清香可口的青菜粉條。\n");
                set("unit", "盆");
                set("value", 150);
                set("food_remaining", 4);
                set("food_supply", 40);
        }
}