// freezing.c

#include <ansi.h>
#include <condition.h>

inherit F_CLEAN_UP;
inherit POISON;

string name() { return "yinyang12"; }

string chinese_name() { return "亂氣之陰陽"; }

string update_msg_others()
{
        return HIW "$N" HIW "臉上呈現出痛苦的表情，四肢變得僵硬，全身癱軟了下來。\n" NOR;
}

string update_msg_self()
{
        return HIW "你只覺全身痠軟無比，竟使不出絲毫氣力。\n" NOR;
}

string die_msg_others()
{
        return HIW "$N" HIW "倒在地上，抽搐了一陣，再也沒有半點生氣了。\n" NOR;
}

int jing_damage(object me, mapping cnd)
{
        return cnd["level"] / 6;
}

int qi_damage(object me, mapping cnd)
{
        return cnd["level"] / 5;
}

string die_reason()
{
        return "亂氣之陰陽發作，力乏而盡";
}


int dispel(object me, object ob, mapping cnd)
{
        if ((me->query_skill("jiuyang-shengong", 1) > 180 && 
             me->query_skill_mapped("force") == "jiuyang-shengong") ||
             (me->query_skill("jiuyin-shengong", 1) > 180 &&
              me->query_skill_mapped("force") == "jiuyin-shengong") || 
             (me->query_skill("yinyang-shiertian", 1) > 180 &&
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