// daodejing-ii.c

inherit ITEM;

void create()
{
        set_name("道德經「下卷」", ({ "jing", "daode jing" }));
        set_weight(200);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "本");
                set("long","這是一冊道德經「下卷」，由同異第四十一始至顯質第八十一止。\n");
                set("value", 500);
                set("material", "paper");
                set("skill", ([
                        "name"        : "taoism",
                        "exp_required":        1000,
                        "jing_cost"   : 20+random(20),
                        "difficulty"  : 25,
                        "min_skill"   : 49,
                        "max_skill"   : 99,
                ]) );
        }
}