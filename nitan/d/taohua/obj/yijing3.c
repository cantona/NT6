//Cracked by Kafei
// yijing.c

inherit ITEM;

void create()
{
        set_name( "易經《雜卦篇》", ({ "jing", "yi jing" }));
        set_weight(200);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "本");
                set("long", "這是一冊易經。上面寫着：\n
　　乾剛，坤柔。
　　震起也，艮止也。
　　兑見，而巽伏也。
　　離上，而坎下也。 
\n");
                set("value", 200);
                set("material", "paper");
                set("skill", ([
                        "name":        "qimen-wuxing",        // name of the skill
                        "exp_required":        0,        // minimum combat experience required
                        "jing_cost": 20,         // jing cost every time study this
                        "difficulty":        30,        // the base int to learn this skill
                        "max_skill":        90,        // the maximum level you can learn
                ]) );
        }
}