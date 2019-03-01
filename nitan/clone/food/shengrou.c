// .c

inherit ITEM;
inherit F_FOOD;

void create()
{
        set_name("生肉包子", ({"shengou baozi", "baozi" }) );
        set_weight(50);//一兩
        if( clonep() ) 
                set_default_object(__FILE__);
        else {
                set("unit", "個");
                set("value", 30);
                set("food_remaining", 1);
                set("food_supply", 30);
        }
        setup();
}