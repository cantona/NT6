// book-silk.c

inherit ITEM;

void create()
{
        set_name("薄絹", ({ "silk", "shu", "book" }));
        set_weight(50);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "束");
                set("long", "這是一冊易筋經修行篇。\n由一束薄絹釘成，裡面密密麻麻的畫了不少打坐吐吶的姿勢。\n");
                set("value", 500);
                set("material", "silk");
                set("skill", ([
                        "name":        "force",        // name of the skill
                        "exp_required":        0,        // minimum combat experience required
                        "jing_cost":        10,        // jing cost every time study this
                        "difficulty":        20,        // the base int to learn this skill
                        "max_skill":        29        // the maximum level you can learn
                ]) );
        }
}