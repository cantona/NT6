// mabudai.c 麻布袋

inherit ITEM;

void create()
{
        set_name("麻布袋", ({ "budai", "dai", "bag" }));
        set_weight(500);
        set_max_encumbrance(10000);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "個");
                set("long", "一隻用麻布織成的袋子，好像可以裝東西。\n");
                set("value", 100);
        }
}

int is_container() { return 1; }