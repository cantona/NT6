// fojing10.c
// Last Modified by Sir on May. 22 2001

inherit ITEM;

string* titles = ({
        "般若經",
        "維摩經",
        "法華經",
        "華嚴經",
});

void create()
{
        set_name(titles[random(sizeof(titles))], ({ "shu", "book" }));
        set_weight(200);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "本");
                set("long", "這是一冊佛經。\n");
                set("value", 500);
                set("material", "paper");
                set("skill", ([
                        "name":        "buddhism", // name of the skill
                        "exp_required":        0, // minimum combat experience required
                        "jing_cost":        10, // jing cost every time study this
                        "difficulty":        10, // the base int to learn this skill
                        "max_skill":        50 // the maximum level you can learn
                ]) );
        }
}