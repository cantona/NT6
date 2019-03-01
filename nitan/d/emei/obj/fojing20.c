// fojing20.c

inherit ITEM;

string* titles = ({
//      "般若經",
//      "維摩經",
//      "法華經",
//      "華嚴經",
        "無量壽經",
        "大般涅磐經",
        "阿含經",
        "金剛經",
        "波羅蜜多心經",
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
                        "name": "mahayana",  // name of the skill
                        "exp_required": 0,  // minimum combat experience required
                        "jing_cost":    10,     // jing cost every time study this
                        "difficulty":   10,     // the base int to learn this skill
                        "max_skill":    50     // the maximum level you can learn
                ]) );
        }
}