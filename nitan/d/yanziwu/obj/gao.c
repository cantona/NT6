// gao.c

inherit ITEM;
inherit F_FOOD;

void create()
{
             set_name("四色點心", ({ "gao" }));
            set_weight(1500);
            if (clonep())
                    set_default_object(__FILE__);
            else {
                  set("long", "四色點心形狀精雅,似乎是用來玩賞一般\n");
                  set("unit", "塊");
                  set("value", 50);
                  set("food_remaining", 4);
                  set("food_supply", 20);
             }
}
