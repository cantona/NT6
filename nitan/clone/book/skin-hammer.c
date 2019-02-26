//
//  羊皮書

inherit BOOK;

void create()
{
        set_name( "羊皮卷軸", ({ "skin" }));
        set_weight(200);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "本");
                set("long", "這是一張羊皮質地的卷軸，上面畫着一些古怪的符號。\n");
                set("material", "paper");
                set("skill", ([
                        "name": "hammer",        // name of the skill
                        "exp_required": 200000, // minimum combat experience required
                        "jing_cost":    40,     // jing cost every time study this
                        "difficulty":   40,     // the base int to learn this skill
                        "max_skill":    180,    // the maximum level you can learn
                        //"min_skill":    20,     // the minimum level you can learn
                ]) );
        }
}
