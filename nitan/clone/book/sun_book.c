// sun-book.c
#include <ansi.h>
inherit ITEM;

void create()
{
        set_name( HIR"一陽指訣"NOR,({ "sunfinger book","book"}));
        set_weight(200);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "本");
                set("long","這是一本一陽指密訣。封面上有一位中年秀士右手中指指向天空的背影。\n");
                set("value", 500);
                set("material", "paper");
                set("skill", ([
                        "name":         "sun-finger", // name of the skill
					    "family_name" : "段氏皇族",
                        "exp_required": 1000, // minimum experience required
                        "jing_cost":  30, // jing cost every time study this
                        "difficulty": 20, // the base int to learn this skill
                        "min_skill":   0, // the minimum level you can learn
                        "max_skill":  99  // the maximum level you can learn
                ]) );
        }
}