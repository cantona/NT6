// jinfw.c

inherit ITEM;

void create()
{
        set_name("金飯碗", ({ "jin fanwan", "fanwan" }));
        set_weight(1600);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "個");
                set("no_sell", "這...這是什麼東西？我可不敢要。\n");
                set("long", "黃金打造的飯碗，沉重之極，上面還刻着幾個字。\n");
                set("value", 1);
                set("material", "gold");
        }
        setup();
}
