//Cracked by Kafei
// staff_book.c 棒法圖解

inherit ITEM;

void create()
{
        set_name("棒法圖解", ({ "staff book", "book" }));
        set_weight(600);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "冊");
                set("long", "這是一本線裝書，裡面密密麻麻的畫了不少舞棒的姿勢。\n");
                set("value", 200);
                set("material", "paper");
                set("skill", ([
                        "name":        "staff",        // name of the skill
                        "exp_required":        1000,        // minimum combat experience required
                        "jing_cost":        30,        // jing cost every time study this
                        "difficulty":        10,        // the base int to learn this skill
                        "max_skill":        30        // the maximum level you can learn
                ]) );
        }
}