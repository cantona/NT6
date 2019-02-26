#include <ansi.h>
#include <combat.h>

#define WSWD "「" HIR "無"BLU"雙"HIM"無"HIW"對" NOR "」"
#define WS "「" HIR "無"BLU"雙" NOR "」"
#define WD "「" HIM"無"HIW"對" NOR "」"

inherit F_SSERVER;

int perform(object me, object target)
{
        int skill = (int)me->query_skill("kuihua-mogong", 1), i;
        int ap, dp;
        int damage;
        int x,a;
        string msg,nextmsg;
        object weapon=query_temp("weapon", me);

        if( !target || target == me ) target = offensive_target(me);

        if( query("no_fight", environment(me)) )
                return notify_fail("這裏不準打架。\n");

        if( me->is_busy()) return notify_fail("你正忙着呢。\n");

        if( userp(me) && !query("can_perform/kuihua-mogong/ws", me) )
                return notify_fail("你所使用的外功中沒有這種功能。\n");

        if( !target || target==me || !target->is_character() )
                return notify_fail(WS"只能對對手使用。\n");

        if( !weapon
         || query("skill_type", weapon) != "sword"
        ||      me->query_skill_mapped("sword") != "kuihua-mogong" )
                return  notify_fail("你現在無法使用絕技。\n");

        if (skill < 200 || (int)me->query_skill("kuihua-mogong", 1) < 200)
                return notify_fail("以你目前的修為來看，還不足以運用"WS"\n");

        if( query("max_neili", me)<2000 )
                return notify_fail("你的內力修為不夠運用"WS"所需！\n");

        if( query("neili", me)<500 )
                return notify_fail("你的內力不夠運用"WS"所需！\n");

        if (! living(target))
                return notify_fail("對方都已經這樣了，用不着這麼費力吧？\n");

        me->start_busy(1 + random(3));
        msg = HIM "$N突然身形一轉眨眼間使用葵花魔功的終極絕招----" NOR
                WSWD HIM "之" NOR WS "\n" HIW "$N眼神瑩然有光，似乎進入了魔境之中。\n" +
                "$N手中" + weapon->name() + "化做無雙劍影攻向$n。\n";
        ap=me->query_skill("kuihua-mogong",1)*1+query("dex", me)*20+
                me->query_skill("martial-cognize", 1);
        dp=target->query_skill("parry")+query("dex", target)*10+
                target->query_skill("martial-cognize", 1);

        me->start_busy(2);
        addn("neili", -400, me);

        if (ap / 2 + random(ap) < dp)
        {
            msg += HIG "然而$n" HIG "抵擋得法，將$N" HIG
                    "的攻勢一一化解。\n" NOR;
        } else
        {
            addn("neili", -560, me);
            damage = ap * 2 + random(ap * 3 / 4) - 60 - random(40);
            msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 80,
                    HIY "$n" BLU "只覺得已經跌入了萬劫魔域之中，" HIY
                    "$N手中" + weapon->name() + WHT
                    "如同地獄中的鬼火般，從各個方位刺了過來，避無可避！\n" NOR);
        }
        message_sort(msg, me, target);

        if( query("neili", me)>2000
         && present(query("id", target),environment(me) )
        &&  me->is_fighting(target)
        &&  target->is_fighting()
        &&  living(target)
        &&  living(me)
        &&  !target->is_ghost()
        &&  !me->is_ghost()
        &&  me->query_skill_mapped("sword") == "kuihua-mogong"
         && query("skill_type", weapon) == "sword"
         && (userp(me) && query("can_perform/kuihua-mogong/wd", me )
                || !userp(me))
                )
        {
                remove_call_out("perform2");
                call_out("perform2",0, me);
        }
        else if( userp(me) && !query("can_perform/kuihua-mogong/wd", me))//沒學會無對
        {
                remove_call_out("check_wd");
                call_out("check_wd",1,me);
        }
        return 1;
}

int perform2(object me)
{
        int ap, dp;
        string nextmsg;
        int damage;
        object target;
        object weapon=query_temp("weapon", me);

        if( !target ) target = offensive_target(me);
        if( !target || living(target) )     return 1;
        if(!objectp(weapon)) return 1;

        nextmsg = HIM "説是遲那時快，$N身形逆轉使出了" NOR WSWD "之" WD HIM
                "式，剎那間天空陰雲密佈，\n" NOR HIM "$n的心臟幾乎停止了跳動，呆呆的望着$N\n" NOR;
        ap=me->query_skill("kuihua-mogong",1)*1+query("dex", me)*20+
        me->query_skill("martial-cognize", 1);
        dp=target->query_skill("parry")+query("dex", target)*8+
        target->query_skill("martial-cognize", 1);

        me->start_busy(2);
        addn("neili", -400, me);

        if ( ap / 2 + random(ap) < dp && !(target->is_busy()) )
        {
                nextmsg += HIG "這時$n屏住呼吸" HIG "抵擋得法，將$N" HIG
                        "的攻勢一一化解。\n" NOR;
        } else
        {
                addn("neili", -260, me);
                damage = ap * 1 + random(ap * 1 / 5) - 60 - random(40);
                nextmsg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 80,
                        HIY "$n" BLU "只覺身上如同萬劍穿心一般，" HIY "$N"
                        WHT "如同死神一般，勢必要取$n性命！\n" NOR
                        HIM "此時此刻$N揮舞着手中" + weapon->name() + HIM
                        "，瞬間變化了幾個劍招，可是$n就是無法找出破解之法，\n" +
                        "説時遲那時快" + weapon->name() + HIM
                        "已經刺進了$n的胸膛，鮮血濺了一地！！\n" NOR);
        }
        message_vision(nextmsg, me, target);
        return 1;
}

int check_wd(object me)
{
        int x,a;
        object target;

        x=query("kar", me);
        a = x + random(70);

        if( !target ) target = offensive_target(me);
        if(living(target))  return 1;
        if (me->is_fighting())  return 1;

        if(a>=80){
                tell_object(me,
                        HIW "\n你突然若有所悟，對剛才使用過的魔功之" WS
                        HIW "式反覆琢磨，\n對了，這樣也可以耶！你學會了" WSWD
                        HIW "之" WD HIW "式！\n" NOR);
                set("can_perform/kuihua-mogong/wd", 1, me);
        }
        return 1;
}
/*
    } else {
        msg += "$n邪邪的看着$N，不知不覺中$n表現出萬分的恐懼。\n"NOR;
        msg += HIM"\n$N猛然想到了什麼，$n立刻開始無限痛苦的呻吟起來！\n\n"NOR;

        ap=me->query_skill("kuihua-mogong",1)*1+query("dex", me)*10+
        me->query_skill("martial-cognize", 1);
        dp=target->query_skill("parry")+query("dex", target)*20+
        target->query_skill("martial-cognize", 1);

        me->start_busy(2);
        addn("neili", -400, me);

        if (ap / 2 + random(ap) < dp)
        {
            msg += HIG "然而$n" HIG "抵擋得法，將$N" HIG
            "的攻勢一一化解。\n" NOR;
        } else
        {
            addn("neili", -260, me);
            damage = ap * 1 + random(ap * 1 / 5) - 60 - random(40);
            msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 70,
              HIY "$n" BLU "只覺得已經跌入了萬劫魔域之中，"HIY"$N"
              WHT "如同地獄幽靈一樣手舞足蹈，從九九八十一個方位殺了過去！\n" NOR);
        }

        message_combatd(msg, me, target);

    }
    if(!me->is_fighting(target)) me->fight_ob(target);
    if(!target->is_fighting(me)) target->fight_ob(me);
    remove_call_out("checking");
    call_out("checking", 1, me);
    return 1;
}
*/
