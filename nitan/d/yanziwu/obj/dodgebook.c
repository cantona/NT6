// dodogbook.c

inherit ITEM;

void create()
{
        set_name("輕功篇", ({ "dodgebook", "shu", "book" }));
        set_weight(100);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "本");
                set("long",
                        "輕功篇\n"
                        "這是一本還施水閣的輕功藏本，書色泛黃，有不少的批註。\n");
                set("value", 500);
                set("material", "paper");
                set("skill", ([
                        "name": "dodge",        // name of the skill
                        "exp_required": 10000,  // minimum combat experience required
                        "jing_cost":    1,      // jing cost every time study this
                        "difficulty":   20,     // the base int to learn this skill
                        "max_skill":    100     // the maximum level you can learn
                ]) );
        }
}