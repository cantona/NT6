// jinyd.c

inherit ITEM;

void create()
{
        set_name("金腰帶", ({ "jin yaodai", "yaodai" }));
        set_weight(5000);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "個");
                set("no_sell", "這...這是什麼東西？我可不敢要。\n");
                set("long", "純金腰帶，重得令人無法穿戴，上面紋著一條龍。\n");
                set("value", 1);
                set("material", "gold");
        }
        setup();
}