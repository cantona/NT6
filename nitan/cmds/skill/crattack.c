// crattack.c

#include <ansi.h>

inherit F_CLEAN_UP;

void hate_attack(object me, object target);
void shout_message(string msg);

int main(object me, string arg)
{
        object target;
        int craze;
        string msg;
        int attack;
        int damage;

        if( query("no_fight", environment(me)) )
                return notify_fail("這裏不能戰鬥。\n");

        if (me->is_busy())
                return notify_fail("( 你上一個動作還沒有完成，不能施用憤怒一擊。)\n");

        if (! arg)
        {
                me->clean_up_enemy();
                target = me->select_opponent();
        } else
                target = present(arg, environment(me));

        if (! target || ! me->is_fighting(target))
                return notify_fail("憤怒一擊只能對戰鬥中的對手使用。\n");

        if (! living(target))
                return notify_fail("人家都已經這個樣子了，你"
                                   "還用得着這麼費力氣麼？\n");

        if ((craze = me->query_craze()) < 500)
                return notify_fail("你現在心平氣和，談不上什麼憤怒。\n");

        if (craze < 1000)
                return notify_fail("你現在還不夠憤怒，無法施展憤怒必殺絕技。\n");

        if( query("qi", me)*100/query("max_qi", me)<50 )
                return notify_fail("你現在體力太虛弱，無法施展憤怒必殺絕技。\n");

        if( query("qi", me)<200 )
                return notify_fail("你現在氣息不夠強，難以施展爆烈的憤怒必殺絕技。\n");

        me->receive_damage("qi",random(query("max_qi", me)/4));

        if (me->is_most_craze())
        {
                int second;

                if( me->is_hating(query("id", target)) )
                {
                        hate_attack(me, target);
                        return 1;
                }

                if( query("gender", me) == "女性" )
                        msg = HIR "$N" HIR "眼神猶如利刃，冷冷的掃過$n"
                              HIR "，讓他不禁打了個寒戰。只見$P低聲喝"
                              "道：“" + RANK_D->query_rude(target) +
                              "，你去死吧！”\n" NOR;
                else
                        msg = HIR "$N" HIR "咆哮如雷，有如瘋狂，對$n"
                              HIR "狂喝道：“" + RANK_D->query_rude(target) +
                              "，你還不快快納命來？”\n" NOR;
                message_combatd(msg, me, target);

                // first attack
                attack = craze / 50;
                damage = craze / 20;
                if (attack > me->query_skill("force") + 10)
                        attack = me->query_skill("force") + 10;
                if (damage > me->query_str() * 8)
                        damage = me->query_str() * 8;
                addn_temp("apply/attack", attack, me);
                addn_temp("apply/damage", damage, me);
                addn_temp("apply/unarmed_damage", damage, me);
                COMBAT_D->do_attack(me,target,query_temp("weapon", me),0);
                msg = HIR "\n$N" HIR "一招攻出，竟不罷休，隨即捨身撲上又是一招！\n" NOR;
                if (! me->is_fighting(target) && living(target))
                {
                        msg += HIY "$n" HIY "見$N" HIY "捨生忘死，全然"
                               "不顧自己已經認輸做罷，不由大吃一驚，慌"
                               "忙抵擋。\n" NOR;
                }
                message_combatd(msg, me, target);

                // second attack
                second=query("str", me);
                attack += second;
                damage += second;
                addn_temp("apply/attack", second, me);
                addn_temp("apply/damage", second, me);
                addn_temp("apply/unarmed_damage", second, me);
                COMBAT_D->do_attack(me,target,query_temp("weapon", me),0);
                addn_temp("apply/attack", -attack, me);
                addn_temp("apply/damage", -damage, me);
                addn_temp("apply/unarmed_damage", -damage, me);
                me->cost_craze(craze / 4 + random(craze / 2));
                me->start_busy(2);
                return 1;
        }

        if( query("gender", me) == "女性" )
                msg = HIR "$N" HIR "一聲嬌嗔，遙指$n" HIR "喝道：“" +
                      RANK_D->query_rude(target) + "，看招！”\n" NOR;
        else
                msg = HIR "$N" HIR "一聲大吼，如同晴空霹靂，對$n" HIR
                      HIR "暴喝道：“" + RANK_D->query_rude(target) +
                      "，你還不快快受死？”\n" NOR;

        message_combatd(msg, me, target);
        attack = craze / 60;
        damage = craze / 30;
        if (attack > me->query_skill("force") + 10)
                attack = me->query_skill("force") + 10;
        if (damage > me->query_str() * 8)
                damage = me->query_str() * 8;

        addn_temp("apply/attack", attack, me);
        addn_temp("apply/damage", damage, me);
        addn_temp("apply/uanrmed_damage", damage, me);
        COMBAT_D->do_attack(me,target,query_temp("weapon", me),0);
        addn_temp("apply/attack", -attack, me);
        addn_temp("apply/damage", -damage, me);
        addn_temp("apply/uanrmed_damage", -damage, me);
        me->cost_craze(craze / 4 + random(craze / 2));
        me->start_busy(1);
        return 1;
}

void hate_attack(object me, object target)
{
        int craze;
        int attack;
        int damage;

        craze = me->query_craze();
        attack = craze / 40;
        damage = craze / 18;
        if (attack > me->query_skill("force") + 10)
                attack = me->query_skill("force") + 10;
        if (damage > me->query_str() * 8)
                damage = me->query_str() * 8;

        if (random(2))
                shout_message(me->name(1) + "對" + target->name() + HIR "厲聲喝道：" +
                              RANK_D->query_rude(target) + "，今日" +
                              RANK_D->query_self(me) + "要你血債血償！接招！");
        else
                shout_message(me->name(1) + "對" + target->name() + HIR "怒喝道：" +
                              RANK_D->query_rude(target) + "，自古殺人償命！" +
                              "今天我就要你的狗命！來吧！");

        me->want_kill(target);
        me->kill_ob(target);
        addn_temp("apply/attack", attack, me);
        addn_temp("apply/damage", damage, me);
        addn_temp("apply/unarmed_damage", damage, me);
        COMBAT_D->do_attack(me,target,query_temp("weapon", me),0);

        message_combatd(HIR "\n$N" HIR "叫道：" + target->name() +
                       "，你再看我上一招！\n" NOR, me);
        COMBAT_D->do_attack(me,target,query_temp("weapon", me),0);

        message_combatd(HIR "\n$N" HIR "叫道：" + RANK_D->query_rude(target) +
                      "，你再看我下一招！\n" NOR, me);
        COMBAT_D->do_attack(me,target,query_temp("weapon", me),0);

        message_combatd(HIR "\n$N" HIR "叫道：好！你再接我左一招！\n" NOR, me);
        COMBAT_D->do_attack(me,target,query_temp("weapon", me),0);

        message_combatd(HIR "\n$N" HIR "叫道：休走！你再接我右一招！\n" NOR, me);
        COMBAT_D->do_attack(me,target,query_temp("weapon", me),0);

        message_combatd(HIR "\n$N" HIR "叫道：看清楚我這當中穿心一招！\n" NOR, me);
        damage+=query("str", me);
        attack+=query("str", me);
        addn_temp("apply/attack",query("str",  me), me);
        addn_temp("apply/damage",query("str",  me), me);
        addn_temp("apply/unarmed_damage",query("str",  me), me);
        COMBAT_D->do_attack(me,target,query_temp("weapon", me),0);

        message_combatd(HIR "\n$N" HIR "叫道：還沒完，看我最後一招！！！\n" NOR, me);
        COMBAT_D->do_attack(me,target,query_temp("weapon", me),0);
        addn_temp("apply/attack", -attack, me);
        addn_temp("apply/damage", -damage, me);
        addn_temp("apply/unarmed_damage", -damage, me);

        if( query("qi", target) >= 0 && 
            query("jing", target) >= 0 )
        {
                if (random(2))
                        shout_message(target->name(1) + "呵呵大笑道：這位" +
                                      RANK_D->query_respect(me) + "，你好"
                                      "厲害啊！不過又豈能奈我何？");
                else
                        shout_message(target->name(1) + "哈哈大笑道：你的" +
                                      "來勢好凶啊，可惜本事太差，也罷，也罷，哈哈！");

                tell_object(me, HIR "你目眥俱裂，心中燃起的重重怒火，絲毫沒有減弱。\n" NOR);
        } else
        {
                if (random(2))
                        shout_message(target->name(1) + "慘叫道：我的天！");
                else
                        shout_message(target->name(1) + "慘聲呼號：天啊，報應來得好快！");

                me->cost_craze(craze);
                me->craze_defeated(query("id", target));
                tell_object(me, HIC "你長舒一口氣，心情平靜了許多。\n" NOR);
        }
        me->start_busy(2);
}

void shout_message(string msg)
{
        message("channel:chat", HIR "【報仇" HIW "雪" HIR "恨】" +
                                msg + "\n" NOR,
                                all_interactive());
}

int help (object me)
{
        write(@HELP
指令格式：crattack <對象>

如果你處於憤怒狀態，就可以利用自己的憤怒充分發揮自己的能力，
予以正在交手的對手沉重的打擊。當然你還得使用剛猛或是殺傷力高
的武功才能收到良好的效果。你的怒氣達到了頂峯的時候，威力更是
不同凡響。

如果你被人打暈或是殺死，則打暈你和殺死你的人將成為你憎恨的對
象，當你憤怒達到頂級的時候，就可以對你憎恨的對象施展出索命必
殺絕技，只能對一個憎恨的對象運用一次。

HELP );
        return 1;
}