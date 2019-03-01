//Cracked by Kafei
// zhusun 竹筍

inherit ITEM;

void create()
{
        set_name("竹筍", ({"zhu sun", "bamboo shoot", "shoot"}));
        set_weight(80);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", "一把新鮮嫩綠的竹筍。\n");
                set("unit", "把");
                set("value", 0);
        }
}