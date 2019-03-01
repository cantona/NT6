// staff_book.c

inherit BOOK;

void create()
{
        set_name( "棍法通解", ({ "club paper" , "club", "book" }));
        set_weight(200);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "本");
                set("long", "這是一本破紙片，上面畫著舞棍的小人。\n");
                set("value", 100);
                set("material", "paper");
                set("skill", ([
                        "name": "club",         // name of the skill
                        "exp_required": 10000,  // minimum combat experience required
                        "jing_cost":    50,     // jing cost every time study this
                        "difficulty":   22,     // the base int to learn this skill
                        "max_skill":    199,    // the maximum level you can learn
                        "min_skill":    80,     // the minimum level you can learn
                ]));
        }
}