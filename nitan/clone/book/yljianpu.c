// yljianpu.c

inherit ITEM;

void create()
{
set_name( "雲龍劍譜",({ "shu","book"}));
        set_weight(200);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "本");
                set("long","這是一本雲龍劍譜，封皮上一條長龍在雲中若隱若現。\n");
                set("value", 500);
                set("material", "paper");
                set("skill", ([
                        "name": "yunlong-jian",  //name of the skill
                        "exp_required": 10000 , //minimum combat experience required
                        "jing_cost": 20+random(20),// jing cost every time study this
                        "difficulty":        30,        // the base int to learn this skill
                        "max_skill":        49,        // the maximum level you can learn
                        "min_skill":        20        // the minimum level you can learn
                ]) );
        }
}