// fengjiang.c 玉蜂漿
// By Lgg,1998.9

#include <ansi.h>
inherit ITEM;

int decayed = 0;
void create()
{
        set_name("玉蜂漿", ({"jiang", "feng jiang"}));
        set_weight(100);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", "一瓶用玉蜂巢搗成的漿。\n");
                set("unit", "瓶");
                set("value", 30);
                set("only_do_effect", 1); 
                set("can_fulan",1);
        }
}

int do_effect(object me)
{
        set("jing",query("max_jing",  me), me);
        message_vision(HIY"$N服下了一瓶玉蜂漿，那玉蜂漿非常的甘甜，實在是好吃。\n"NOR,me);
        if (me->query_condition("yufengdu") > 0)
        {
                me->clear_condition("yufengdu");
                tell_object(me,HIY "你感覺體內的蜂毒已慢慢消去。\n" NOR, me);
        }
        destruct(this_object());
        return 1;
}
 void decay(int phase) 
{
        string msg;
        object env;
        env = environment();
        decayed = phase;
        set("on_fulan",1);
        set("value",0);
        set("food_remaining",0);
        switch(phase)
        {
                case 1:
                        msg =  name(1) + "開始變質了，發出一股難聞的餿味。\n";
                        set("old_name",name(1));
                        set_name("變質的" + query("old_name"),({ query("id") }));
                        call_out("decay", 120, phase + 1);
                        break;
                case 2:
                        msg = name(1) + "開始腐爛了，上面長出許多綠毛，發出難聞的臭味。\n";
                        set_name("腐爛的" + query("old_name"),({ query("id") }));
                        call_out("decay", 60, phase + 1);
                        break;
                case 3:
                        msg = "一陣風吹過，把" + name(1) + "化成灰吹散了。\n";
                        if( env )
                                all_inventory(this_object())->move(env);
                        tell_room(env, msg);
                        destruct(this_object());
                        return;
        }
        while (env && env->is_character())
                env = environment(env);
        if (env) tell_room(env, msg); 
}
