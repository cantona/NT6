// guanyin.c

inherit ITEM;

void create()
{
        set_name("官印", ({ "guan yin", "yin" }));
        set_weight(500);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "方");
                set("no_sell", "這...這是什麼東西？我可不敢要。\n");
                set("long", "這是官員的印章。\n");
                set("value", 1);
                set("material", "ivory");
        }
        setup();
}