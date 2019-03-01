// xyta.c

inherit ITEM;

void create()
{
        set_name("象牙塔", ({ "xiangya ta", "ta" }));
        set_weight(900);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "尊");
                set("no_sell", "這...這是什麼東西？我可不敢要。\n");
                set("long", "這是來自暹邏國的貢品，象牙制品。\n");
                set("value", 1);
                set("material", "ivory");
        }
        setup();
}