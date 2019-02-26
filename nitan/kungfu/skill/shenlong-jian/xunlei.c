//xunlei.c 迅雷劍

#include <ansi.h>

inherit F_SSERVER;

string name() { return "迅雷劍"; }

int perform(object me, object target)
{
        object weapon, ob;
        string msg, string1;
        int speed, attack, lv, damage;

        lv = (int)me->query_skill("shenlong-jian", 1);
        damage = lv + random(lv/2) + (int)me->query_skill("sword",1);
        attack = lv + random(lv/2);
        speed = me->query_skill("sword")/80;

        if( !target ) target = offensive_target(me);

        if( !target || !target->is_character() || !me->is_fighting(target) )
             return notify_fail("「迅雷劍」只能對戰鬥中的對手使用。\n");

        if( query_temp("xunlei_yushi", me) || query_temp("xunlei", me) )
             return notify_fail("你劍勢未盡，不能再施展「迅雷劍」！\n");

        if( !objectp(weapon=query_temp("weapon", me) )
         || query("skill_type", weapon) != "sword" )
             return notify_fail("你使用的武器不對。\n");

        if( query("neili", me)<300 )
             return notify_fail("你的內力不夠！\n");

        if( me->query_skill("shenlong-jian", 1) < 100 )
             return notify_fail("你的「神龍劍法」未臻高妙境界，無法使用「迅雷劍」！\n");

        msg=HIR"\n$N手中"+query("name", weapon)+HIR"劍尖指向自己胸口，劍柄斜斜向外，怪異之極，竟似回劍自戕一般！\n\n"NOR;
        message_combatd(msg, me,target);
        me->start_busy(1);
        ob = me->select_opponent();
        set_temp("xunlei", 4, me);
            addn("neili", -5, me);
        me->set_temp("xunlei_yushi");
        call_out("checking", 1, me, target);
        return 1;
}


  void checking(object me, object target, int speed, int damage, int attack)
{

        object weapon;
        if ( !objectp( me ) ) return;
        weapon=query_temp("weapon", me);

        if( !objectp(weapon=query_temp("weapon", me) )
         || query("skill_type", weapon) != "sword"){
                tell_object(me, "\n你手中無劍，當下停止了迅雷劍的架勢。\n" NOR);
                delete_temp("xunlei", me);
                return;
        }
        else if( query("weapon_prop", weapon) == 0){
                tell_object(me, "\n你的"+weapon->name()+"已毀，無法持續迅雷劍的攻勢！\n\n" NOR);
                    call_out("xunlei_end", 6, me);
                delete_temp("xunlei", me);
                return;
        }
          else if( query("neili", me)<300){
                  message_combatd(HIR"$N的內勁後繼無力，不得不停止迅雷劍的攻勢！\n" NOR, me,target);
                    call_out("xunlei_end", 6, me);
                delete_temp("xunlei", me);
                return;
        }
        else if ( me->query_skill_mapped("sword") != "shenlong-jian" ) {
                tell_object(me, HIR "\n你轉而施展其他劍法，無法再以迅雷劍攻敵！\n\n" NOR);
                    call_out("xunlei_end", 6, me);
                delete_temp("xunlei", me);
                return;
        }
        else if ( me->is_busy() ) {
                tell_object(me, HIR "\n你現在動作不夠靈活，無法繼續維持迅雷劍攻勢！\n\n" NOR);
                    call_out("xunlei_end", 6, me);
                delete_temp("xunlei", me);
                return;
        }
        else if (!me->is_fighting() || !objectp(target)) {
                tell_object(me,  "\n你現在沒有和人過招，當下收回了迅雷劍的攻勢。\n" NOR);
                    call_out("xunlei_end", 6, me);
                delete_temp("xunlei", me);
                return;
        }
        if( environment(target) != environment(me) ) {
                tell_object(me, "你見對方已經不在這裏，當下停止了迅雷劍的攻勢。\n");
                    call_out("xunlei_end", 6, me);
                delete_temp("xunlei", me);
                return;
        }
        else{
                addn_temp("apply/damage", damage*2, me);
                addn_temp("apply/attack", attack*2, me);

                if( query_temp("xunlei", me) == 4)message_combatd(HIY"\n$N縱身近前，"+weapon->name()+HIY"陡然彎彎彈出，劍尖直刺$n，出招之快真乃為任何劍法所不及！\n"NOR,me,target);
                if( query_temp("xunlei", me) == 3)message_combatd(HIW"\n$N伸指在"+weapon->name()+HIW"上一彈，劍聲嗡嗡，有若龍吟，"+weapon->name()+HIW"顫處，劍鋒來勢神妙無方！\n"NOR,me,target);
                if( query_temp("xunlei", me) == 2)message_combatd(HIG"\n$N陡然間大喝一聲，"+weapon->name()+HIG"上寒光閃動，喝道：「"+target->name()+HIG"，可小心了！」\n"NOR,me,target);
                if( query_temp("xunlei", me) == 1)message_combatd(HIR"\n見$N隨手揮劍，"+weapon->name()+HIR"顫處，前後左右，瞬息之間已攻出了四四一十六招！\n"NOR,me,target);
                addn("neili", -30, me);

                COMBAT_D->do_attack(me,target,query_temp("weapon", me));
                COMBAT_D->do_attack(me,target,query_temp("weapon", me));
                COMBAT_D->do_attack(me,target,query_temp("weapon", me));
                COMBAT_D->do_attack(me,target,query_temp("weapon", me));

                addn_temp("apply/damage", -damage*2, me);
                addn_temp("apply/attack", -attack*2, me);
                if( query_temp("xunlei", me) == 1){
                        message_combatd(HIY "\n$N順勢圈轉手中"+weapon->name()+HIY"，一十六手「迅雷劍」已然盡數使出！\n" NOR, me, weapon);
                        call_out("xunlei_end", 12, me);
                        me->start_busy(2);
                }
                else {
                        me->set_temp("xunlei_attack");
                        set_temp("xunlei",query_temp("xunlei",  me)-1, me);
                        call_out("checking", 1, me, target);
                }
        }
}

void xunlei_end(object me)
{
        object weapon;
        if ( !objectp( me ) )
                return;
        weapon=query_temp("weapon", me);

        tell_object(me, HIR "\n你暗自調息，漸漸平復騰湧的真氣。\n\n" NOR);

        delete_temp("xunlei", me);
        delete_temp("xunlei_yushi", me);

}
