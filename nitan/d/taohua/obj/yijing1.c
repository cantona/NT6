//Cracked by Kafei
// yijing.c

inherit ITEM;

void create()
{
        set_name( "易經《序卦篇》", ({ "jing", "yi jing" }));
        set_weight(200);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "本");
                set("long", "這是一冊易經。上面寫着：\n
　　有天地，然後有萬物； 有萬物，然後有男女； 有男女，然後有夫婦；
有夫婦，然後有父子；有父子然後有君臣；有君臣，然後有上下；有上下，
然後禮儀有所錯。 夫婦之道，不可以不久也，故受之以恆；物不可窮也，
故受之以未濟終焉。
\n");
                set("value", 200);
                set("material", "paper");
                set("skill", ([
                        "name":        "qimen-wuxing",        // name of the skill
                        "exp_required":        0,        // minimum combat experience required
                        "jing_cost": 10,         // jing cost every time study this
                        "difficulty":        20,        // the base int to learn this skill
                        "max_skill":        30,        // the maximum level you can learn
                ]) );
        }
}