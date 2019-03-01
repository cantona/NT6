// 天山折梅手法圖

inherit ITEM;

void create()
{
        set_name( "天山折梅手法圖上卷", ({ "shoufa tu1", "tu1" }));
        set_weight(200);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "幅");
                set("long", "這是一幅天山折梅手法圖，上面畫着一些紛繁複雜的招式。\n");
                set("value", 500);
                set("no_put", 1);
                set("material", "paper");
                set("skill", ([
                        "name":        "zhemei-shou",        
                        "family_name":        "靈鷲宮",        
                        "exp_required":        10000,        // minimum combat experience required
                        "jing_cost":    20,         // jing cost every time study this
                        "difficulty":        20,        // the base int to learn this skill
                        "max_skill":        49,        // the maximum level you can learn
                        "min_skill":    10,
                ]) );
        }
}