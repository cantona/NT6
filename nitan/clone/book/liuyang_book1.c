inherit ITEM;

void create()
{
        set_name( "天山六陽掌法圖上冊", ({ "zhangfa tu1", "tu1" }));
        set_weight(200);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "本");
                set("long", "這是六陽掌法上冊，上面畫着一些紛繁複雜的招式及修練法門。\n");
                set("value", 500);
                set("no_put", 1);
                set("material", "paper");
                set("skill", ([
                        "name":        "liuyang-zhang",        
                        "exp_required":        10000,        // minimum combat experience required
                        "jing_cost":    20,         // jing cost every time study this
                        "difficulty":        20,        // the base int to learn this skill
                        "max_skill":        49,        // the maximum level you can learn
                        "min_skill":        10,        // the maximum level you can learn
                        "family_name":        "靈鷲宮",
                ]) );
        }
}