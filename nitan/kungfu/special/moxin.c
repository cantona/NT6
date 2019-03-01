
#include <ansi.h>

inherit F_CLEAN_UP;

int is_scborn() { return 1; }

string name() { return HIW "魔由心生" NOR; }

int perform(object me, string skill, string arg)
{
        int joblv, damage_up;
      
        joblv = me->query_joblv();

        if (me->query_temp("special2/moxin"))
                return notify_fail("你已經在運功中了。\n");

        if (me->query("yhjob/job") != "魔師")
                return notify_fail("你的職業錯誤，無法施展。\n");
                
        if (me->query("neili") < 800)
                return notify_fail("你的內力不足，無法施展。\n");

        if (joblv < 20)
                return notify_fail("你的職業等級不足，無法施展。\n");                

        if (me->is_busy())return notify_fail("等你忙完再說吧！\n");

        message_vision(HIM "$N" HIM "施展出魔由心生，心中頓時一陣凄苦！\n" NOR, me);
 
        me->add("neili", -800);
        me->start_busy(1);

        joblv = joblv + me->query("lhpoint/special/moxin") * 8;

        me->set_temp("special2/moxin", joblv);
        me->add_temp("apply/damage", joblv * 100);
        me->add_temp("apply/unarmed_damage", joblv * 100);
        // 傷害額外提升15%
        damage_up = me->query_temp("apply/damage") * 3 / 20;
        me->add_temp("apply/damage", damage_up);
        
        me->start_call_out( (: call_other, __FILE__, "remove_effect", me, joblv, damage_up :), joblv * 10);
        return 1;
}

void remove_effect(object me, int joblv, int damage_up)
{
        if ((int)me->query_temp("special2/moxin"))
        {
                me->add_temp("apply/damage", -1 * joblv * 100);
                me->add_temp("apply/unarmed_damage", -1 * joblv * 100);
                me->add_temp("apply/damage", -1 * damage_up);
                me->delete_temp("special2/moxin");
                tell_object(me, "你魔由心生運功完畢。\n");
        }
}

