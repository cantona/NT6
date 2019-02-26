
inherit ITEM;

void create()
{
        set_name("血刀譜", ({ "xuedao book", "book" }));
        set_weight(200);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "本");
                set("long","這是一本薄薄的絲織小冊子，上面寫着血刀譜三個小字。\n");
                set("no_sell", 1);
                set("material", "silk");
                set("skill", ([
                        "name": "xuedao-daofa",//name of the skill
                        "family_name" : "血刀門",
                        "exp_required": 5000000,  //minimum combat experience required
                        "jing_cost": 100,        // jing cost every time study this
                        "difficulty": 100,       // the base int to learn this skill
                        "max_skill": 200,       // the maximum level you can learn
                        "min_skill": 0,        // the minimum level you can learn
                ]) );
        }
}
