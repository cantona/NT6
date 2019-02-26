//Cracked by Kafei
// yijing.c

inherit ITEM;

void create()
{
        set_name( "易經《説卦篇》", ({ "jing", "yi jing" }));
        set_weight(200);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "本");
                set("long", "這是一冊易經。上面寫着：\n
　　昔者，聖人之作易也，幽贊神明而生蓍。
　　觀變於陰陽，而立卦；發揮於剛柔，而生爻；和順於道德，而理於
義；窮理盡性，以至於命。
\n");
                set("value", 200);
                set("material", "paper");
                set("skill", ([
                        "name":        "qimen-wuxing",        // name of the skill
                        "exp_required":        0,        // minimum combat experience required
                        "jing_cost": 15,         // jing cost every time study this
                        "difficulty":        20,        // the base int to learn this skill
                        "max_skill":        60,        // the maximum level you can learn
                ]) );
        }
}