// poisonbook2.c

inherit ITEM;

void create()
{
        set_name("毒經中篇", ({ "jing", "book" }));
        set_weight(50);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "本");
                set("long", "這是一本薄薄的小冊，上面密密麻麻的寫滿了各種用毒的方法和毒藥的配方。\n");
                set("value", 0);
                set("material", "paper");
                set("skill", ([
                        "name": "five-poison", // name of the skill
                        "exp_required":  100000,// minimum combat experience required
                        "jing_cost":    20,     // jing cost every time study this
                        "difficulty":   25,     // the base int to learn this skill
                        "max_skill":    150     // the maximum level you can learn
                ]) );
        }
}