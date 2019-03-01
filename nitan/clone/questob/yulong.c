// yulong.c

inherit ITEM;

void create()
{
        set_name("玉龍□", ({ "yulong jue", "jue" }));
        set_weight(500);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "塊");
                set("no_sell", "這...這是什麼東西？我可不敢要。\n");
                set("long", "這是一塊有缺口的玉環，上面紋著一條龍。\n");
                set("value", 1);
                set("material", "jade");
        }
        setup();
}