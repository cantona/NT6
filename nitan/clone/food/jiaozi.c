//zhengjiao .c

inherit ITEM;
inherit F_FOOD;

void create()
{
        set_name("生肉蒸餃", ({"shengrou zhengjiao", "zhengjiao" }) );
        set_weight(50);//一兩
        if( clonep() ) 
                set_default_object(__FILE__);
        else {
                set("unit", "個");
                set("value", 30);
                set("food_remaining", 1);
                set("food_supply", 40);
        }
        setup();
}