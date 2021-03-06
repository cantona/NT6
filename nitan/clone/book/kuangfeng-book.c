// xuedao-book.c

inherit BOOK;

void create()
{
        set_name("狂風刀法祕籍", ({ "kuangfeng book", "book" }));
        set_weight(200);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "本");
                set("long","這是一本薄薄的小冊子，上面寫着狂風刀法祕籍四個小字。\n");
                set("no_sell", 1);
                set("material", "silk");
                set("skill", ([
                        "name": "kuangfeng-blade",      //name of the skill
                        "exp_required": 100000, //minimum combat experience required
                        "jing_cost": 50,        // jing cost every time study this
                        "difficulty": 32,       // the base int to learn this skill
                        "max_skill": 180,       // the maximum level you can learn
                ]) );
        }
}