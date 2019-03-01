// yugy.c

inherit ITEM;

void create()
{
        set_name("玉觀音", ({ "yu guanyin", "guanyin" }));
        set_weight(900);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "個");
                set("no_sell", "這...這是什麼東西？我可不敢要。\n");
                set("long", "這是一尊晶瑩剔透的玉觀音。\n");
                set("value", 1);
                set("material", "jade");
        }
        setup();
}