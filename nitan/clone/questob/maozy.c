// maozy.c

inherit ITEM;

void create()
{
        set_name("貓之眼", ({ "mao yan" }));
        set_weight(500);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "塊");
                set("no_sell", "這...這是什麼東西？我可不敢要。\n");
                set("long", "極大的一塊貓眼寶石，周圍嵌着金邊。\n");
                set("value", 1);
                set("material", "stone");
        }
        setup();
}