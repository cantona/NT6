// nuomi.c

inherit ITEM;
inherit F_FOOD;

void create()
{
        set_name("糯米燒賣", ({"nuomi shaomai", "shaomai" }) );
        set_weight(50);//一兩
        if( clonep() ) 
                set_default_object(__FILE__);
        else {
                set("unit", "個");
                set("value", 20);
                set("food_remaining", 1);
                set("food_supply", 40);
        }
        setup();
}