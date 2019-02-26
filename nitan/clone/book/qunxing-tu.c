// qunxing-tu.c
inherit ITEM;

void create()
{
        set_name("羣星璀璨圖", ({ "qunxing tu" ,"tu" ,"book"}));
        set_weight(600);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "本");
                set("long", "這是一本描寫着天上羣星運動的書。\n"
                        "但似乎並沒有那麼簡單。\n");
                set("value", 1000);
                set("material", "paper");
                set("skill", ([
                        "name":  "array",               // name of the skill
                        "exp_required":  100,
                        "jing_cost":  10,
                        "difficulty":  20,                          // the base int to learn this skill
                        "max_skill":  120
                ]) );
        }
}
