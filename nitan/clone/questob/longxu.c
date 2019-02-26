// longxu.c

inherit ITEM;

void create()
{
        set_name("龍鬚", ({ "long xu", "xu" }));
        set_weight(600);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "根");
                set("no_sell", "這...這是什麼東西？我可不敢要。\n");
                set("long", "一根青綠色的鬚毛，長而粗壯，據説是龍鬚。\n");
                set("value", 1);
                set("material", "silk");
        }
        setup();
}