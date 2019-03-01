inherit ITEM;

void create()
{
        set_name( "天羽奇劍劍譜", ({ "jian pu", "pu" }));
        set_weight(200);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "本");
                set("long", "這是一本天羽奇劍劍譜，上面畫着一些紛繁複雜的招式及修練法門。\n");
                set("value", 500);
                set("no_put", 1);
                set("material", "paper");
                set("skill", ([
                        "name":        "tianyu-qijian",        
                        "exp_required":        100000,        // minimum combat experience required
                        "jing_cost":    30,         // jing cost every time study this
                        "difficulty":        30,        // the base int to learn this skill
                        "max_skill":        150,        // the maximum level you can learn
                        "min_skill":        50,        // the minimum level you can learn
                        "family_name":        "靈鷲宮",
                ]) );
        }
}