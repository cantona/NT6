// longxu.c

inherit ITEM;

void create()
{
        set_name("龍須", ({ "long xu", "xu" }));
        set_weight(600);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "根");
                set("no_sell", "這...這是什麼東西？我可不敢要。\n");
                set("long", "一根青綠色的須毛，長而粗壯，據說是龍須。\n");
                set("value", 1);
                set("material", "silk");
        }
        setup();
}