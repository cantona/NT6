//club.c

inherit ITEM;

void create()
{
        set_name("棍法通解", ({"shu", "book" }));
        set_weight(100);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "本");
                set("long","這是一本修習棍法的武經。\n裏面記載着少林派弟子數百年的練功心得，上面畫着各式舞棍的小人。\n");
                set("value", 500);
                set("material", "book");
                set("skill", ([
                        "name":        "club",        // name of the skill
                        "exp_required":        0,        // minimum combat experience required
                        "jing_cost":        20,        // jing cost every time study this
                        "difficulty":        20,        // the base int to learn this skill
                        "max_skill":        100        // the maximum level you can learn
                ]) );
        }
}