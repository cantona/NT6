// freezing.c

#include <ansi.h>
#include <condition.h>

inherit F_CLEAN_UP;
inherit POISON;

string name() { return "freezing"; }

string chinese_name() { return "寒冰真氣"; }

string update_msg_others()
{
        return HIW "$N" HIW "臉色鐵青，四肢僵硬，全身上下竟籠"
               "罩了一層寒霜。\n" NOR;
}

string update_msg_self()
{
        return HIW "你只覺全身冰冷無比，四肢百骸難受之極，如墮"
               "冰獄。\n" NOR;
}

string die_msg_others()
{
        return HIW "$N" HIW "僵硬的身子在地上撲騰了幾下，就再"
               "沒半點動靜了。\n" NOR;
}

int jing_damage(object me, mapping cnd)
{
        return cnd["level"] / 8;
}

int qi_damage(object me, mapping cnd)
{
        return cnd["level"] / 6;
}

string die_reason()
{
        return "被寒冰真氣活活凍死了";
}


int dispel(object me, object ob, mapping cnd)
{
        if ((me->query_skill("jiuyang-shengong", 1) > 180 && 
             me->query_skill_mapped("force") == "jiuyang-shengong") ||
             (me->query_skill("hanbing-zhenqi", 1) > 180 &&
              me->query_skill_mapped("force") == "hanbing-zhenqi") || 
             (me->query_skill("zixia-shengong", 1) > 180 &&
              me->query_skill_mapped("force") == "zixia-shengong"))
        {
               me->add_temp("apply/dispel-poison", 1000);
               me->set_temp("add_dispel", 1); 
               call_out("clear_dispel", 2, me);
        }

        return ::dispel(me, ob, cnd);

}


void clear_dispel(object me)
{
       if (me->query_temp("apply/dispel-poison") && 
           me->query_temp("add_dispel"))
       {
                me->delete_temp("add_dispel");
                me->add_temp("apply/dispel-poison", -1000);
                return;
       }
               
}