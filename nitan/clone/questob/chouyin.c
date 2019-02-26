// chouyin.c

inherit ITEM;

void create()
{
        set_name("綢印", ({ "chou yin", "yin" }));
        set_weight(600);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "方");
                set("no_sell", "這...這是什麼東西？我可不敢要。\n");
                set("long", "綢子製成的印章，稀世罕見。\n");
                set("value", 1);
                set("material", "silk");
        }
        setup();
}