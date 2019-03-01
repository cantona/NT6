// taiji-book.c

inherit ITEM;

void create()
{
        set_name("太極拳經", ({ "taiji book", "book" }));
        set_weight(600);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "本");
                set("long", @LONG
這是一本發黃的手抄典籍。是張三豐親手抄錄的。翻開首頁，每頁都有招式圖譜。

    o,     o,    o     o      o     o      o
    )-'   /|'    )-'   )-'   (-'    )-'    )-'
    >\     >\    >\   / >     >\   / >    / >


LONG);
                set("value", 8000);
                set("material", "paper");
                set("skill", ([
                        "name":          "taiji-quan",        // name of the skill
		        "family_name" :   "武當派",
                        "exp_required":        10000,        // minimum combat experience required
                        "jing_cost":        30,        // jing cost every time study this
                        "difficulty":        20,        // the base int to learn this skill
                        "max_skill":        30,// the maximum level you can learn
                        "min_skill":        0        // the maximum level you can learn
                ]) );
        }
}
