// jiaohuaji.c 叫化雞

inherit ITEM;
inherit F_FOOD;

void create()
{
        set_name("叫化雞", ({"jiaohuaji", "ji", "chicken"}));
        set_weight(300);
        set("taskobj", 1);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", "一只烤得香噴噴的叫化雞\n");
                set("unit", "只");
                set("value", 0);
        }
}
