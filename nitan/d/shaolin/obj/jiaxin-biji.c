// jiaxin-biji.c 夾心荸薺

inherit ITEM;
inherit F_FOOD;

void create()
{
        set_name("夾心荸薺", ({"jiaxin biji", "biji"}));
        set_weight(200);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", "一盆形態精巧別致，外脆裡嫩，而又別有風味的夾心荸薺。\n");
                set("unit", "盆");
                set("value", 150);
                set("food_remaining", 4);
                set("food_supply", 40);
        }
}