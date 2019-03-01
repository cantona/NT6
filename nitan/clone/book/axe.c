// axe.c

inherit ITEM;

void create()
{
        set_name("段家斧法", ({"shu", "book" }));
        set_weight(100);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "冊");
                set("long", "這是一冊修行斧法的武經。\n"
                        "裡面記載著武學名家大理段氏的獨門絕學段雲斧的根基武功，\n"
                        "畫冊中的小人一把開山大斧使得虎虎有聲、威風八面。\n");
                set("value", 500);
                set("material", "book");
                set("skill", ([
                        "name":        "axe",                // name of the skill
                        "exp_required":        0,        // minimum combat experience required
                        "jing_cost":        15,        // jing cost every time study this
                        "difficulty":        20,        // the base int to learn this skill
                        "max_skill":        100        // the maximum level you can learn
                ]) );
        }
}