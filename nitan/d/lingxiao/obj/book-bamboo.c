// book2.c

inherit ITEM;

void create()
{
        set_name("舊竹片", ({ "bamboo", "shu", "book" }));
        set_weight(100);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "片");
                set("long",
                        "易筋經輕功篇\n"
                        "這是一片兩邊去皮的舊竹片，正面和背面都畫了無數個飛翔縱躍的小圖形。\n");
                set("value", 500);
                set("material", "bamboo");
                set("skill", ([
                        "name":        "dodge",        // name of the skill
                        "exp_required":        0,        // minimum combat experience required
                        "jing_cost":        10,        // jing cost every time study this
                        "difficulty":        20,        // the base int to learn this skill
                        "max_skill":        29        // the maximum level you can learn
                ]) );
        }
}