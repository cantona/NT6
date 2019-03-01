// fojing1.c

inherit ITEM;

string* titles = ({
        "金光明經", 
        "孔雀王咒經",
        "六字神咒經", 
//持世陀羅尼經 
//八埋茶剎羅經 

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
                set("value", 200);
                set("material", "paper");
                set("skill", ([
                        "name": "lamaism",      // name of the skill
                        "exp_required": 0,      // minimum combat experience required
                        "jing_cost":    20,     // jing cost every time study this
                        "difficulty":   10,     // the base int to learn this skill
                        "max_skill":    50      // the maximum level you can learn
                ]) );
        }
}
