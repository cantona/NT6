// force_book.c 內功心法

inherit ITEM;

void create()
{
        set_name("太極十三勢", ({ "shu", "book" }));
        set_weight(600);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "本");
                set("long", "這是一本線裝書，裡面密密麻麻的畫了不少打坐吐吶的姿勢。\n");
                set("value", 500);
                set("material", "paper");
                set("skill", ([
                        "name":        "force",        // name of the skill
                        "exp_required":        0,        // minimum combat experience required
                        "jing_cost":        30,        // jing cost every time study this
                        "difficulty":        10,        // the base int to learn this skill
                        "max_skill":        29,        // the maximum level you can learn
                        "min_skill":        10        // the maximum level you can learn
                ]) );
        }
}