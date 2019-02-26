// dian.c

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

string name() { return HIR "隔" HIY "空" HIG "點" HIW "穴" NOR; }

int perform(object me, object target)
{
        string msg;
        int ap, dp, jp, lvl, xw, j, damage;

        if (! target) target = offensive_target(me);

        if( query_temp("weapon", me) )
                return notify_fail("你拿着武器怎麼能準確的點中對方的穴道呢！\n");

        if (!target || ! me->is_fighting(target))
             return notify_fail(name() + "只能對戰鬥中的對手使用。\n");

        if((int)me->query_skill("dodge",1) < 200)
                return notify_fail("你的輕功修為不夠, 不能使用隔空點穴！\n");

        if (me->query_skill_mapped("finger") != "tanzhi-shentong")
                return notify_fail("你沒有激發彈指神通，難以施展" + name() + "。\n");

        if (me->query_skill_prepared("finger") != "tanzhi-shentong")
                return notify_fail("你沒有準備彈指神通，難以施展" + name() + "。\n");

        if (! living(target))
                return notify_fail("對方都已經這樣了，用不着這麼費力吧？\n");

        if((int)me->query_skill("tanzhi-shentong",1) < 200)
                return notify_fail("你的彈指神通修為不夠， 目前不能使用隔空點穴! \n");

        if( query("neili", me)<500 )
                return notify_fail("你的真氣不夠！\n");

        if( query_temp("thd/tz", me) )
                return notify_fail("你剛點完穴道，先休息一下吧。\n");

        lvl = me->query_skill("tanzhi-shentong",1);
        jp = me->query_skill("jingluo-xue", 1);

        //隨機產生點中的穴位
        xw = (int)random(15);
        if (xw > 8)
        {
                xw = random(8);
        }

        msg = HIY "\n陡見$N" HIY "耐心的繞着$n旋走，突然只聽見$N大喊一聲:看我桃花" NOR+name()+HIY"，着 !\n" NOR;

        // 伏兔穴
        //if (xw == 1)
        {
                ap = attack_power(me, "finger") + jp + me->query_skill("dodge");
                dp = defense_power(target, "parry") + target->query_skill("dodge");

                msg += HIG "\n$N聚氣於右手食指，倏地向$n腿上伏兔穴點去！\n" NOR;

                if (ap / 2 + random(ap) < dp)
                        msg += HIW "$n趕緊縮腳，才閃過這一招。\n" NOR;
                else
                {
                        msg += HIR "$n一被點中，腿一麻，身法登時遲緩了下來。\n" NOR;
                        set_temp("thd/tz", 1, me);
                        addn("neili", -150, me);
                        addn_temp("apply/dodge", -lvl, target);
                        call_out("remove_effect_futu", 10, me, target, lvl);
                }
                message_combatd(msg, me, target);
        }

// 神門穴
        //else if (xw == 2)
        {
                ap = attack_power(me, "finger") + jp + me->query_skill("parry");
                dp = defense_power(target, "dodge") + me->query_skill("parry");
                msg += HIG "\n$N聚氣於右手食指，倏地向$n手腕神門穴點去！\n" NOR;

                if (ap / 2 + random(ap) < dp)
                        msg += HIW "$n趕緊翻轉手腕，才避開了這一招。\n" NOR;
                else
                {
                        msg += HIR "$n一被點中，手腕一麻，力道弱了許多。\n" NOR;
                        set_temp("thd/tz", 1, me);
                        addn("neili", -150, me);
                        addn_temp("apply/attack", -lvl, target);
                        call_out("remove_effect_shenmen", 10, me, target, lvl);
                }
                message_combatd(msg, me, target);
        }

// 關元穴
        //else if (xw == 3)
        {
                ap = attack_power(me, "finger") + jp + me->query_skill("force");
                dp = defense_power(target, "parry") + target->query_skill("force");
                msg += HIG "\n$N聚氣於右手食指，倏地向$n腹部關元穴點去！\n" NOR;

                if (ap / 2 + random(ap) < dp)
                        msg += HIW "$n趕緊退了一步，才閃了過去。\n" NOR;
                else
                {
                        msg += HIR "$n一被點中，一股熱氣直衝丹田，體內的真氣被打散了開去！\n" NOR;
                        set_temp("thd/tz", 1, me);
                        addn("neili", -lvl*3, target);
                        addn("neili", -150, me);
                        call_out("remove_effect_all", 10, me);
                }
                message_combatd(msg, me, target);
        }

// 玉堂穴
        //else if (xw == 4)
        {
                ap = attack_power(me, "finger") + jp + me->query_skill("bibo-shengong", 1);
                dp = defense_power(target, "dodge") + target->query_skill("force", 1);
                msg += HIG "\n$N聚氣於右手食指，倏地向$n胸口玉堂穴點去！\n" NOR;

                if (ap / 2 + random(ap) < dp)
                        msg += HIW "$n急忙抽過武器抵擋襲的指氣，一邊急忙抽身回撤，"
                                   "方躲過這一招。\n" NOR;
                else
                {
                        msg += HIR "$n一被點中，體內的真氣再也不能運轉自如，招架頓時散亂。\n" NOR;
                        set_temp("thd/tz", 1, me);
                        addn("neili", -150, me);
                        j = me->query_skill("bibo-shengong",1);
                        addn_temp("apply/parry", -j, target);
                        target->apply_condition("no_exert", j);
                        call_out("remove_effect_yutang", j, me, target);
                }
                message_combatd(msg, me, target);
        }

// 檀中穴
        //else if (xw == 5)
        {
                ap = attack_power(me, "finger") + jp + me->query_skill("dodge");
                dp = defense_power(target, "parry") + target->query_skill("dodge");
                msg += HIG "\n$N聚氣於右手食指，倏地向$n胸前檀中穴點去！\n" NOR;

                if (ap / 2 + random(ap) < dp)
                        msg += HIW "$n連退兩步，才閃過這一招。\n" NOR;
                else
                {
                        msg += HIR "$n一被點中，氣息一窒，一時難以動彈。\n" NOR;
                        set_temp("thd/tz", 1, me);
                        addn("neili", -150, me);
                        if (!target->is_busy())
                                target->start_busy(ap /100 + 2);
                        call_out("remove_effect_tanzhong", lvl/10, me, target);
                }
                message_combatd(msg, me, target);
        }

// 靈台穴
        //else if (xw == 6)
        {
                ap = attack_power(me, "finger") + jp+query("max_neili", me);
                dp = defense_power(target, "dodge")+target->query_skill("max_neili");
                msg += HIG "\n$N聚氣於右手食指，倏地向$n背後靈台穴點去！\n" NOR;

                if (ap / 2 + random(ap) < dp)
                        msg += HIW "$n急忙運氣內力，強行以內力頂住對方的指氣。\n" NOR;
                else
                {
                        damage = damage_power(me, "finger");
                        msg += HIR "$n一被點中，臉上時紅時白，看來受了內傷。\n" NOR;
                        set_temp("thd/tz", 1, me);
                        addn("neili", -150, me);
                        target->receive_wound("jing", damage / 2 );
                        call_out("remove_effect_all", 10, me);
                }
                message_combatd(msg, me, target);
        }

// 百會穴
        //else if (xw == 7)
        {
                ap = attack_power(me, "finger") + jp + me->query_skill("parry");
                dp = defense_power(target, "dodge") + me->query_skill("parry");
                msg += HIG "\n$N聚氣於右手食指，倏地向$n頭部百會穴點去！\n" NOR;

                if (ap / 2 + random(ap) < dp)
                        msg += HIW "$n一仰頭，才躲過這一招。\n" NOR;
                else
                {
                        msg += HIR "$n一被點中，登時天懸地轉，搖搖遇墜。\n" NOR;
                        set_temp("thd/tz", 1, me);
                        addn("qi", -(lvl+random(50)), target);
                        addn("neili", -150, me);
                        call_out("remove_effect_all", 10, me);
                }
                message_combatd(msg, me, target);
        }

// 風府穴
        //else if (xw == 8)
        {
                ap = attack_power(me, "finger") + jp + me->query_skill("parry");
                dp = defense_power(target, "dodge") + me->query_skill("parry");
                msg += HIG "\n$N聚氣於右手食指，倏地向$n後腦風府穴點去！\n" NOR;

                if (ap / 2 + random(ap) < dp)
                        msg += HIW "$n趕緊低頭，才閃過這一招。\n" NOR;
                else
                {
                        msg += HIR "$n一被點中，眼前陡然一黑，幾乎昏倒。\n" NOR;
                        set_temp("thd/tz", 1, me);
                        addn_temp("apply/defense", -lvl, target);
                        addn("neili", -150, me);
                        call_out("remove_effect_fengfu", ap/200 + random(2), me, target ,lvl);
                }
                message_combatd(msg, me, target);
        }
// 未對應
        //else return notify_fail("你運用彈指神通亂點一通，看樣子是毫無作用。\n");


        return 1;
}

int remove_effect_futu(object me, object target, int i)
{
        string msg;

        if (!target) {
        delete_temp("thd/tz", me);
                return 1;}
        addn_temp("apply/dodge", i, target);
        if( !me ) return 1;
        delete_temp("thd/tz", me);
        msg = HIY"$n腿上的伏兔穴血脈已經行開，身法已復。\n" NOR;
        message_combatd(msg, me, target);
        return 1;
}


int remove_effect_shenmen(object me, object target, int i)
{
        string msg;

        if (!target) {
        delete_temp("thd/tz", me);
                return 1;}
        addn_temp("apply/attack", i, target);
        if( !me ) return 1;
        delete_temp("thd/tz", me);
        msg = HIY "$n手腕的神門穴血脈已經行開，力道恢復了。\n" NOR;
        message_combatd(msg, me, target);
        return 1;
}

int remove_effect_tanzhong(object me, object target)
{
        string msg;

        if (!target) {
        delete_temp("thd/tz", me);
                return 1;}
        if( !me ) return 1;
        msg = HIY "$n胸口的檀中穴血脈已經行開，行動恢復了。\n" NOR;
        delete_temp("thd/tz", me);
        message_combatd(msg, me, target);
        return 1;
}

int remove_effect_yutang(object me, object target, int i)
{
        string msg;

        if (!target) {
        if( me )
        delete_temp("thd/tz", me);
                return 1;}
        if( !me ) return 1;
        msg = HIY "$n胸口的玉堂穴血脈已經行開，內息恢復了正常。\n" NOR;
        delete_temp("thd/tz", me);
        addn_temp("apply/parry",-i, me);
        message_combatd(msg, me, target);
        return 1;
}


int remove_effect_fengfu(object me, object target, int i)
{
        string msg;

        if (!target) {
        delete_temp("thd/tz", me);
                return 1;}
        addn_temp("apply/defense", -i, target);
        if( !me ) return 1;
        delete_temp("thd/tz", me);
        msg = HIY "$n後腦的風府穴血脈已經行開，視線復原了。\n" NOR;
        message_combatd(msg, me, target);
        return 1;
}

void remove_effect_all(object me)
{
        if( !me ) return;
        delete_temp("thd/tz", me);
}
