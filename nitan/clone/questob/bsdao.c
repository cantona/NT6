// bsdao.c

inherit ITEM;

void create()
{
        set_name("寶石刀", ({ "baoshi dao", "dao" }));
        set_weight(700);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "對");
                set("no_sell", "這...這是什麼東西？我可不敢要。\n");
                set("long", "一對鑲滿寶石的小刀，昂貴的飾品。\n");
                set("value", 1);
                set("material", "jade");
        }
        setup();
}