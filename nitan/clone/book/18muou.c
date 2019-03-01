// 18muou.c

inherit ITEM;

void create()
{
        set_name("十八木偶", ({ "18 muou", "muou" }));
        set_weight(600);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "盒");
                set("long", 
"這是一個小木盒，盒中墊著棉花，並列著三排木偶，神情或喜
悅不禁，或痛哭流淚，或裂嘴大怒，或慈和可親，無一相同。\n");
                set("value", 5000);
                set("material", "wood");
                set("skill", ([
                        "name":              "force",        // name of the skill
                        "exp_required":        0,        // minimum combat experience required
                        "jing_cost":        40,        // jing cost every time study this
                        "difficulty":        20,        // the base int to learn this skill
                        "max_skill":        99,        // the maximum level you can learn
                        "min_skill":        60        // the maximum level you can learn
                ]) );
        }
}