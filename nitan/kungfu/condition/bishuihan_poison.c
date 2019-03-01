#include <ansi.h>
#include <condition.h>

inherit F_CLEAN_UP;
inherit POISON;

string name() { return "bishuihan_poison"; }

string chinese_name() { return "碧水寒毒"; }

string update_msg_others()
{
       return HIW "$N" HIW "臉色蒼白，突然由白轉為綠色，接著又由綠色轉為紫色，全身不住的顫抖，似乎非常痛苦。\n" NOR;
}

string update_msg_self()
{
        return HIW "你只感到一股從未有過的奇寒之氣從體內猶然而升，沁入全身各處大穴，看來是碧水寒毒發作了！\n" NOR;
}

int jing_damage(object me, mapping cnd)
{
                me->add("neili", -1 * cnd["level"] / 6);
                if (random(3) == 1)me->start_busy(2 + random(3));
                else me->start_busy(1);

        return 1;
}

int qi_damage(object me, mapping cnd)
{
        return cnd["level"] / 6;
}

int dispel(object me, object ob, mapping cnd)
{

        if ((me->query_skill("jiuyang-shengong", 1) > 380 && 
             me->query_skill_mapped("force") == "jiuyang-shengong") ||
             (me->query_skill("yinyang-shiertian", 1) > 380 &&
              me->query_skill_mapped("force") == "yinyang-shiertian"))
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