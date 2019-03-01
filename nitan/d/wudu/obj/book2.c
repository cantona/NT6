inherit ITEM;

void create()
{
        set_name("拆招秘術", ({ "book" }));
        set_weight(50);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "本");
                set("long", "這是一本薄薄的小冊，上面繪了許多互相打鬥的人像。\n");
                set("value", 0);
                set("material", "paper");
                set("skill", ([
                        "name": "parry",        // name of the skill
                        "exp_required": 0,      // minimum combat experience required
                        "jing_cost":    20,     // jing cost every time study this
                        "difficulty":   20,     // the base int to learn this skill
                        "max_skill":    50      // the maximum level you can learn
                ]) );
        }
}