// This program is a part of NT MudLIB

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

string name() { return HIY"八荒獨尊掌"NOR; }

int perform(object me, object target)
{
        string msg;
        int ap, dp;
        int damage;
        int lvl;

        if( !query("reborn/times", me) )
                return notify_fail("你還沒有轉世重生，還不能領悟到"+name()+"的精髓。\n");

        if( me->is_busy() )
                return notify_fail("你正忙著呢。\n");

        if( !target )
        {
                me->clean_up_enemy();
                target = me->select_opponent();
        }

        if( objectp(query_temp("weapon", me)) )
                return notify_fail(name()+"只能空手才能施展。\n");

        if( !me->is_fighting(target) )
                return notify_fail(name()+"只能對戰鬥中的對手使用。\n");

        if( !target || !target->is_character() )
                return notify_fail("你要對誰施展"+name()+"？\n");

        if( !living(target) )
                return notify_fail("對方都已經這樣了，用不著這麼費力吧？\n");

        if( me->query_skill_prepared("strike") != "liuyang-zhang" )
                return notify_fail("你還沒有將天山六陽掌與逍遙折梅手互備，無法施展"+name()+"。\n");

        if( (int)me->query_skill("force") < 1000 )
                return notify_fail("你內功修為不夠，難以施展" + name() + "。\n");

        if( lvl = me->query_skill("liuyang-zhang", 1) < 1000 )
                return notify_fail("你的天山六陽掌火候不夠，無法施展"+name()+"。\n");

        if( query("neili", me) < 2500 )
                return notify_fail("你的真氣不夠，現在無法施展"+name()+"。\n");

        msg = HIY "但見$N" HIY "衣袂飄飄翩躚起舞，閉目凝神默運玄功，手中生死符由內勁霧化蒸騰，\n"
              HIY "如雲霞般隨著雙掌的翻飛繚繞周身，忽然$N" HIY "傾步前移，雙掌破空擊出，挾著絲絲寒意，直向$n" HIY "雙肩貫去。\n" NOR;

        msg += HIR "$n" HIR "只覺胸口一悶，一絲涼意直入肺腑，腦中一片空白茫然不知所措！\n" NOR;

        target->affect_by("ss_poison",
                          ([ "level" : lvl * 2,
                             "id"    : query("id", me),
                             // "remain"   : -1,
                             "duration" : lvl / 100 + random(lvl / 10) ,
                          ]));
        // 第一掌
        ap = attack_power(me, "strike") + me->query_str()*20;
        dp = defense_power(target, "dodge") + target->query_str()*20;
        damage = damage_power(me, "strike");
        damage+= query("jiali", me);
        damage *= 2;

        addn_temp("apply/add_damage", 50, me);
        if (ap / 2 + random(ap) > dp)
        {
                msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 300,
                                           HIR "$n" HIR "恍然驚醒，心下大駭，慌亂中抬手相抗，怎料得$N"
                                           HIR "那凝脂如雪的雙掌竟然蘊含千鈞力道，\n"
                                           HIR "一觸之下頓讓自己雙臂氣勁潰散，毫無抵擋之力，結結實實地受下此招。\n" NOR);

        } else
        {
                msg += CYN "$p" CYN "眼見$P" CYN "來勢洶湧，情急之下力貫雙臂，奮起抵抗，居然未佔下風。\n" NOR;
        }
        addn_temp("apply/add_damage", -50, me);
        message_combatd(msg, me, target);

        msg = HIY "$N" HIY "一招未老，瞬即抽身回翔，接著反手推出一掌，看似漫無目的，那匯聚著白虹掌力的內勁確如浪湧一般奔至$n"HIY"胸前。\n" NOR;
        // 第二掌
        ap = attack_power(me, "strike") + me->query_con()*20;
        dp = defense_power(target, "parry") + target->query_con()*20;

        if (ap / 2 + random(ap) > dp)
        {
                target->set_weak(5);

                msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 150,
                                           HIR "那掌勁不疾不徐，卻又避無可避，從$n" HIR "胸口透體而過,直震得$n筋骨寸裂。\n"
                                           HIR "$n" HIR "只覺心脈如千道銀針紮入，氣海一陣翻湧，一團血霧從口中噴激而出。\n" NOR);

        } else
        {
                msg += CYN "只見$p" CYN "早有準備，猛一提氣，內力從丹田源源不斷灌入胸腔護住心脈，硬吃下這掌，倒也無甚大礙。\n" NOR;
        }

        message_combatd(msg, me, target);

        // 第三掌
        msg = HIY "$N" HIY "縱身一躍，驀然騰空數丈，隨著一聲嬌叱，已俯身飄搖而下，重重掌影層疊成一朵巨大的雪蓮，朝$n" HIY "頭頂壓下。\n" NOR;

        ap = attack_power(me, "strike") + me->query_dex()*20;
        dp = defense_power(target, "force") + target->query_dex()*20;

        if (ap / 2 + random(ap) > dp)
        {
                if( !target->is_busy() )
                        target->start_busy(5);

                msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 200,
                                           HIR "只聽的一聲悶響，一道雄渾的掌勁已在$n" HIR "天靈炸開，順勢泄入$n" HIR "周身，\n"
                                           HIR "$n" HIR "顱內一陣裂痛，全身經脈如浸寒冰，一下子癱倒在地，動彈不得。\n" NOR);

        } else
        {
                msg += CYN "$p" CYN "見此招來勢洶湧，豈敢貿然招架。俯腰移步，一個靈動，居然在千鈞一發之際抽身而出。\n" NOR;
        }


        addn("neili", -1500, me);
        me->start_busy(2+random(2));
        message_combatd(msg, me, target);

        return 1;
}


