// Code of ShenZhou
// puti-zi.c 菩提子

#include <ansi.h>

inherit ITEM;

void setup()
{}

int cure_ob(string);
void create()
{
        set_name("菩提子", ({"puti zi", "zi"}));
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "顆");
                set("long", "這是一顆晶瑩如玉的菩提子，採自靈山佛祖座前，珍稀無比，
乃萬年菩提樹之實，功能化百劫，渡千災，與天地同壽。\n");
                set("value", 10000);
                set("no_sell", 1);
                set("medicine", 1);
                set("no_drop","這樣東西不能離開你。\n");
                set("no_get", "這樣東西不能離開那兒。\n");
        }
        setup();
}
        
int cure_ob(object me)
{
        int force_limit, neili_limit, force_skill, add_skill, improve;


        force_limit=me->query_skill("force")*(query("con", me)*2/3);
        neili_limit=query("max_neili", me);
        force_skill = me->query_skill("force", 1);
        
        if ( (int)me->query_condition("bonze_drug" ) > 0 )
        {
                addn("max_neili", -(20+random(20)), me);
                message_vision(HIR "$N又吃下一顆菩提子，只覺得肝腸寸斷，五臟欲裂，原來服食太急太多，藥效適得其反！\n" NOR, me);
        }
        else if ( neili_limit <= force_limit  )
        {
                addn("max_neili", 20+random(20), me);
                addn("neili", 100, me);

                message_vision(HIY "$N吃下一顆菩提子，頓然間只覺一股浩盪無比的真氣直沖頂門...\n" NOR, this_player());
                me->apply_condition("bonze_drug", 100);
        }

        me->unconcious();
        destruct(this_object());
        return 1;
}
