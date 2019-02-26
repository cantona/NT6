
// jianmang.c

/*
卓不凡第二擊不中，五分驚訝之外，更增了五分懼怕，身子滴溜溜的打了半個
圈子，長劍一挺，劍尖上突然生出半尺吞吐不定的青芒。羣眾中有十餘人齊聲
驚呼：“劍芒，劍芒！”那劍芒猶似長蛇般伸縮不定，卓不凡臉露獰笑，丹田
中提一口真氣，青芒突盛，向虛竹胸口刺來。

虛竹從未見過別人的兵刃上能生出青芒，聽得羣豪呼喝，料想是一門厲害武功，
自己定然對付不了，腳步一錯，滑了開去。卓不凡這一劍出了全力，中途無法
變招，刷的一聲響，長劍刺入了大石柱中，深入尺許。這根石柱乃極堅硬的花
崗石所制，軟身的長劍居然刺入一尺有餘，可見他附在劍刃上的真力實是非同
小可，

Maco備註：
劍芒此一perform，本來出處不屬桃花島。然而Kane造出此code，長久以來也
被認定為玉簫劍法標準perform，Maco在此便將錯就錯，依着前人腳步略加拓
展code變化性，增加些許趣味。

雙重劍芒作用，在於將剩餘的劍芒有效時間一次用光，合為一劍，威力大幅提
高，然而劍芒效果立刻結束，普通劍也會立刻斷裂，這是和平常相同的。剩餘
時間越長，威力越大，可説是使盡劍芒餘力的一擊。

又，“劍意”高低，影響雙重劍芒威力至鉅。
*/

#include <ansi.h>

inherit F_SSERVER;

string name() { return "劍芒"; }

void checking(object me, object weapon,int damage);
void remove_effect1(object me, object weapon, int damage) ;

int perform(object me, object target)
{
        object weapon;
        int i, damage, sword, jianyi;

        weapon=query_temp("weapon", me);

        if( !target && me->is_fighting() ) target = offensive_target(me);

        if( !target
        ||  !target->is_character()
        ||  !me->is_fighting(target) )
                return notify_fail("劍芒只能對戰鬥中的對手使用。\n");

        // jianyi = (int)me->query("tianmo_jieti/times");
        jianyi = (int)me->query_skill("yuxiao-jianfa", 1) / 200;
        if (jianyi > 8) jianyi = 8;

        if( !objectp(weapon) || query("skill_type", weapon) != "sword" )
                return notify_fail("你手中無劍，怎能運用「劍芒」？！\n");

        if( query_temp("th_jianmang", me) )
        {
                if( jianyi < 1 )
                        return notify_fail("以你對劍意的領悟，劍芒施展至當下威力，已是極限！\n");
        }

        if( query_temp("th_wait_jianmang", me) && !query_temp("th_jianmang", me) )
                return notify_fail("你氣血翻湧，無法運用「劍芒」！\n");

        if( query_temp("th_jianzhi", me) )
                return notify_fail("你正在運用劍指相配的攻勢，不能分心運用「劍芒」！\n");

        if( me->query_skill("yuxiao-jianfa",1) < 200 )
                return notify_fail("你玉簫劍法修為還不夠，還未領悟「劍芒」！\n");

        if( me->query_skill("bibo-shengong", 1) < 150 )
                return notify_fail("你的碧波神功修為火候未到，施展劍芒只會傷及自身！\n");

        if( me->query_skill_mapped("force") != "bibo-shengong")
                return notify_fail("你所用的內功無法施展玉簫劍法的「劍芒」！\n");

        if( query("max_neili", me) <= 1200 )
                return notify_fail("你的內力修為不足，勁力不足以施展劍芒！\n");

        if( query("neili", me) <= 600 )
                return notify_fail("你的內力不夠，勁力不足以施展劍芒！\n");

        if( query("jingli", me) <= 200 )
                return notify_fail("你的精力有限，不足以施展劍芒！\n");

        sword = me->query_skill("yuxiao-jianfa",1)/10;
        damage = me->query_skill("force") + me->query_skill("qimen-wuxing",1);

        if( query_temp("th_jianmang", me)){
                addn("neili", -150, me);
                addn("jingli", -50, me);
                set_temp("final_jianmang", 1, me);
                for (i =0;i < jianyi*2;i++)
                        COMBAT_D->do_attack(me,target,query_temp("weapon", me));
                delete_temp("final_jianmang", me);
                delete_temp("th_jianmang", me);
                me->start_busy(1);
                checking(me, weapon, damage);
        }
        else {
                addn("neili", -300, me);
                addn("jingli", -100, me);
                addn_temp("th_jianmang", sword/3, me);
                set_temp("th_wait_jianmang", 1, me);
                addn_temp("apply/defense", damage, me);
                addn_temp("apply/damage", damage, me);
                addn_temp("apply/attack", damage, me);
                me->start_busy(1);

                message_combatd(HIC
                        "$N傲身長笑，手中"+NOR+weapon->name()+HIG"漸漸變成慘碧半透明色，\n"+
                        "一團青碧色豪芒從劍柄處直遊至劍尖 ......\n"+NOR+
                        weapon->name()+NOR+HIC"前端驀地伸出三尺"+HIG"劍芒"NOR+
                        HIC"，忽伸忽縮，吞吐不定，看上去詭異絕倫！！！\n"NOR,
                me);
                call_out("checking", 1, me, weapon, damage);
                call_out("remove_effect2", sword*2/3, me);
        }
        return 1;
}

void checking(object me, object weapon, int damage)
{
        if (!me) return;
        addn_temp("th_jianmang", -1, me);

        if( !living(me) || me->is_ghost() )
        {
                remove_effect1(me, weapon, damage);
                return ;
        }
        if( !me->is_fighting() )
        {
                message_combatd("\n$N見戰局已畢，便即收起了催動劍芒的內力。\n", me);
                remove_effect1(me, weapon, damage);
                return ;
        }
        else if( !weapon || environment(weapon) != me || weapon != query_temp("weapon", me) )
        {
                message_combatd("\n$N手中兵器已失，劍芒真力隨之瓦解。\n"NOR, me);
                remove_effect1(me, weapon, damage);
                return ;
        }
        else if( me->query_skill_mapped("sword") != "yuxiao-jianfa"
         || me->query_skill_mapped("force") != "bibo-shengong" )
        {
                remove_effect1(me, weapon, damage);
                message_combatd(HIG"\n$N武功路數陡變，"+
                        weapon->name()+HIG"上青芒消逝。\n"NOR, me);
                return ;
        }
        else if( query_temp("th_jianmang", me) <= 0 )
        {
                tell_object(me,HIG"\n劍芒威力已到極限！\n"NOR);
                remove_effect1(me, weapon, damage);
                return;
        }
        else call_out("checking", 1, me, weapon,damage);

        if (random(2))
                message_combatd(HIG"$N的"NOR+"$n"+NOR+HIG"頂端青色劍芒忽長忽短，閃爍不定....\n"NOR,me,query_temp("weapon", me));
        return;
}

void remove_effect1(object me, object weapon, int damage)
{
        if (!me) return;
        addn_temp("apply/defense", -damage, me);
        addn_temp("apply/damage", -damage, me);
        addn_temp("apply/attack", -damage, me);
        delete_temp("th_jianmang", me);

        if (!weapon) return;

        if( environment(weapon) != me || weapon != query_temp("weapon", me) )
                return;
        else if( query("weapon_prop/damage", weapon)<40){
                message_combatd(HIW"\n只聽得一聲清響，$N手中"+weapon->name()+
                        HIW"經不住內力衝擊，已裂成碎片！！\n"NOR,me);
                destruct(weapon);
        }
        else {
                message_combatd(HIY"\n$N手中"+weapon->name()+HIY+
                        "“咯”的一聲輕響，附在劍上的青芒已消失得無影無蹤。\n"NOR, me);
        }
}

void remove_effect2(object me)
{
        if (!me) return;
        delete_temp("th_jianmang", me);
        delete_temp("th_wait_jianmang", me);
        tell_object(me, HIG"\n你經過一段時間調氣養息，經脈氣血已運轉如常。\n"NOR);
}