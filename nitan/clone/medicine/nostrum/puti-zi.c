// puti-zi.c 菩提子

#include <ansi.h>

inherit ITEM;

void setup()
{}

void init()
{
        add_action("do_eat", "eat");
        add_action("do_eat", "fu");
}

void create()
{
        set_name("菩提子", ({"puti zi", "zi"}));
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "顆");
                set("long","這是一顆晶瑩如玉的菩提子，採自靈山佛祖座前，珍稀無比，\n乃萬年菩提樹之實，功能化百劫，渡千災，與天地同壽。\n");
                set("value", 500000);
        }
        set("pour_type", "1");
        setup();
}

int do_eat(string arg)
{
        int force_limit, neili_limit, force_skill, add_skill, improve;

        object me = this_player();

        force_limit = me->query_skill("force")*10;
        neili_limit=query("max_neili", me);
        force_skill = me->query_skill("force", 1);
        
        if(!id(arg)) return notify_fail("你要吃什麼？\n");
        if(!present(this_object(), me))
                return notify_fail("你要吃什麼？\n");
        if( me->is_busy() )
                return notify_fail("別急，慢慢吃，小心別噎著了。\n");

        if ( (int)me->query_condition("putizi_drug" ) > 0 )
        {
                addn("max_neili", -100, me);
                message_vision(HIR "$N又吃下一顆菩提子，只覺得肝腸寸斷，五臟欲裂，原來服食太急太多，藥效適得其反！\n" NOR, me);
        }
        else if ( neili_limit <= force_limit  )
        {
/*                improve = force_limit - neili_limit;

                if ( improve < 100 ) { 
                        add_skill = force_skill + (100 - improve)/5 + 1;
                        me->set_skill("force", add_skill );
                }
*/        
                addn("max_neili", 100, me);
                addn("neili", 100, me);

                message_vision(HIY "$N吃下一顆菩提子，頓然間只覺一股浩盪無比的真氣直沖頂門...\n" NOR, this_player());
                me->apply_condition("putizi_drug", 1000);
        }
        me->unconcious();
        destruct(this_object());
        return 1;
}
