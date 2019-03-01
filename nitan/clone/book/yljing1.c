// yljing1.c 雲龍經

inherit ITEM;

void create()
{
        set_name( "雲龍經「上卷」", ({ "jing", "yunlong jing" }));
        set_weight(200);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "本");
                set("long", "這是一冊雲龍經「上卷」，封皮上一條長龍在雲中若隱若現。\n");
                set("value", 500);
                set("material", "paper");
                set("skill", ([
                        "name":        "yunlong-xinfa",        
                        "exp_required":         0,        // minimum combat experience required
                        "jing_cost":    20,         // jing cost every time study this
                        "difficulty":        20,        // the base int to learn this skill
                        "max_skill":        49,        // the maximum level you can learn
                ]) );
        }
}