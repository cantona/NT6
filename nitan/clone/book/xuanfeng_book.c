// xuanfeng_book.c

inherit ITEM;

void create()
{
        set_name( "旋風掃葉腿法", ({ "paper" , "shu", "book" }));
        set_weight(200);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "本");
                set("long", 
"這是兩張紙片，上面寫的都是練功的口訣要旨，卻是黃藥師的
親筆，字跡遒勁挺拔，第一葉上右首寫着題目，是“旋風掃葉
腿法”六字。\n");
                set("value", 100);
                set("material", "paper");
                set("skill", ([
                        "name": "xuanfeng-leg",        // name of the skill
                        "exp_required": 1000,  // minimum combat experience required
                        "jing_cost":    40,     // jing cost every time study this
                        "difficulty":   20,     // the base int to learn this skill
                        "max_skill":    99,     // the maximum level you can learn
                        "min_skill":    30,     // the minimum level you can learn
                ]) );
        }
}
