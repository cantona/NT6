// book-iron.c

#include <armor.h>

//inherit ITEM;
inherit HANDS;

void create()
{
        set_name("鐵手掌", ({ "iron hand", "hand", "shu", "book" }));
        set_weight(2000);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "塊");
                set("long","易筋經攻防篇\n這是一塊鐵手掌，上面凹凹凸凸刻滿了人形搏擊的場面。\n");
                set("value", 500);
                set("material", "steel");
                set("armor_prop/armor", 3 );
                set("skill", ([
                        "name":        "parry",        // name of the skill
                        "exp_required":        0,        // minimum combat experience required
                        "jing_cost":        10,        // jing cost every time study this
                        "difficulty":        20,        // the base int to learn this skill
                        "max_skill":        29        // the maximum level you can learn
                ]) );
        }
}

void init()
{
        if( this_player() == environment() )
                add_action("do_study", "study");
}

int do_study(string arg)
{
        object me = this_player();
        int c_exp,c_skill;

        if ( arg != "iron hand" && arg != "hand" )
        return notify_fail("你要學什麼？\n");

        if ( !present(this_object(), me) )
                return 0;
        if ( me->is_fighting() &&
                (int)me->query_skill("parry", 1) >= 30 &&
                (int)me->query_skill("parry", 1) <= 100 )
                if( query("jing", me)<20 )
                {
//                        write("你現在過于疲倦，休息一會兒再讀吧！\n");
                        me->unconcious();
                        return 1;
                }                  
                else
                {                  
                        c_exp=query("combat_exp", me);
                        c_skill=me->query_skill("parry",1);
                        me->receive_damage("jing", 20);
                        if ((c_skill*c_skill*c_skill/10)< c_exp )
                                me->improve_skill("parry",query("int", me));
                        message_vision("$N一邊戰鬥，一邊抽空急急忙忙地拿出鐵手掌仔細研究。\n", me);
                        return 1;
                }

        return 0;
}