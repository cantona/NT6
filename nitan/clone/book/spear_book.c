// spear_book.c

inherit ITEM;

void create()
{
        set_name( "岳家槍法", ({ "paper" , "shu", "book" }));
        set_weight(200);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "本");
                set("long","這是一本岳家槍法殘本，是嶽武穆送給上官幫主的。可惜年深月久，書以有些殘破了。\n");
                set("value", 100);
                set("material", "paper");
                set("skill", ([
                        "name": "spear",        // name of the skill
                        "exp_required": 1000,   // minimum combat experience required
                        "jing_cost":    20,     // jing cost every time study this
                        "difficulty":   20,     // the base int to learn this skill
                        "max_skill":    99,     // the maximum level you can learn
                        "min_skill":    30,     // the minimum level you can learn
                ]) );
        }
}
