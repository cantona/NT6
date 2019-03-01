// This program is a part of NITAN MudLIB

#include <ansi.h>
#include <combat.h>

#define JING "「" HIW "白首太玄經" NOR "」"

inherit F_SSERVER;

string final1(object me, object target, int damage, object weapon, int lvl);
string final2(object me, object target, int damage);
string final3(object me, object target, int damage, object weapon, int lvl, string msg);

int perform(object me, object target)
{
        int damage;
        string msg, sub_msg;
        int ap, dp;
        object weapon;
        int flag = 0;
        int lvl;

        if( userp(me) && !query("can_perform/taixuan-gong/jing", me) )
                return notify_fail("你所使用的外功中沒有這種功能。\n");

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(JING "只能對戰鬥中的對手使用。\n");

        if( (!objectp(weapon=query_temp("weapon", me))) || 
            (query("skill_type", weapon) != "sword"
             && query("skill_type", weapon) != "blade") )
                return notify_fail("你使用的武器不對，難以施展" JING "。\n");

        if ((int)me->query_skill("force", 1) < 340)
                return notify_fail("你內功修為不夠，難以施展" JING "。\n");

        if( query("max_neili", me)<10000 )
                return notify_fail("你內力修為不夠，難以施展" JING "。\n");

        lvl = (int)me->query_skill("taixuan-gong", 1);
        if (lvl < 340)
                return notify_fail("你太玄功火候不夠，難以施展" JING "。\n");

        if (me->query_skill_mapped("sword") != "taixuan-gong"
            && me->query_skill_mapped("blade") != "taixuan-gong")
                return notify_fail("你沒有激發太玄功為刀或劍，難以施展" JING "。\n");

        // 分別判斷激發刀劍時需要的刀、劍等級。
        if (me->query_skill_mapped("sword") == "taixuan-gong")
        {               
                if (me->query_skill("sword", 1) < 340)
                        return notify_fail("你的基本劍法火候不足，難以施展" JING "。\n");

                else 
                {
                        if( query("skill_type", weapon) == "sword" )
                                flag = 1; // 設置激發為sword標志
                        sub_msg = "劍";
                }
        }
        else // 激發為刀
        {
                if (me->query_skill("blade", 1) < 340)
                        return notify_fail("你的基本刀法火候不足，難以施展" JING "。\n");
                else 
                {
                        flag = 0; // 設置激發為blade標志
                        sub_msg = "刀";
                }
        }

        if( query("neili", me)<850 )
                return notify_fail("你現在真氣不夠，難以施展" JING "。\n");

        if (me->query_skill("martial-cognize", 1) < 260)
                return notify_fail("你武學修養不足，難以施展" JING "。\n");

        if (! living(target))
                return notify_fail("對方都已經這樣了，用不著這麼費力吧？\n");

        message_combatd(sort_msg(HIM "\n$N" HIM "情不自禁的縱聲長嘯，霎時之間，千百種招式紛至沓來，湧"
                     "向心頭。$N" HIM "隨手揮舞，已是不按次序，但覺無論何種招式皆能隨心所欲"
                     "，既不必存想內息，亦不須記憶招數，石壁上的千百種招式，自然而然的從心"
                     "中傳向手足，盡數襲向$n" HIM "。\n" NOR), me, target);


        if (flag)ap = attack_power(me, "sword") + me->query_str();
        else ap = attack_power(me, "blade") + me->query_str();

        // 第一招，判斷對方臂力
        dp = defense_power(target, "parry") + target->query_str();

        message_combatd(sort_msg(HIW "\n$N" HIW "突然間只覺得右肋下‘淵液穴’上一動，一道熱線沿著‘足少"
                     "陽膽經’，向著‘日月’、‘京門’二穴行去，一招‘十步殺一人’的" + sub_msg + 
                     "法已隨意使出，各種招式源源而出，將$n" HIW "籠罩。\n" NOR), me, target);

        if (ap / 2 + random(ap) > dp)
        {
                if (flag) damage = damage_power(me, "sword") *2/3;
                else damage = damage_power(me, "blade") *2/3;
                damage += query("jiali", me);
                msg = COMBAT_D->do_damage(me, target, REMOTE_ATTACK, damage, 60 + random(10),
                                         (: final1, me, target, damage, weapon, lvl :));
        } else
        {
                msg = HIC "$n" HIC "氣貫雙臂，凝神以對，竟將$N" HIC "之力卸去。\n" NOR;
        }
        message_combatd(sort_msg(msg), me, target);

        if( flag)ap=attack_power(me,"sword")+me->query_int();
        else ap=attack_power(me,"blade")+me->query_int();
        // 第二招，判斷對方悟性
        dp=defense_power(target,"parry")+target->query_int();

        message_combatd(sort_msg(HIW "\n$N" HIW "肌膚如欲脹裂，內息不由自主的依著‘趙客縵胡纓’那套經脈運"
                     "行圖譜轉動，同時手舞足蹈，似是大歡喜，又似大苦惱。\n" NOR), me);

        if (ap / 2 + random(ap) > dp)
        {
                if (flag) damage = damage_power(me, "sword") *2/3;
                else damage = damage_power(me, "blade") *2/3;
                damage += query("jiali", me);
                msg = COMBAT_D->do_damage(me, target, REMOTE_ATTACK, damage, 65 + random(10),
                                          HIY "$n" HIY "冷笑一聲，覺得$N" HIY "此招膚淺之極，于"
                                          "是隨意招架，猛然間，「噗嗤」！一聲，" + weapon->name() +
                                          HIY "已穿透$n" HIY "的胸膛，鮮血不斷湧出。\n" NOR, me , target);
        } else
        {
                msg = HIC "$n" HIC "會心一笑，看出$N" HIC "這招中的破綻，隨意施招竟將這招化去。\n" NOR;
        }
        message_combatd(sort_msg(msg), me, target);

        if (flag)ap = attack_power(me, "sword") + me->query_con();
        else ap = attack_power(me, "blade") + me->query_con();
        // 第三招，判斷對方根骨
        dp = defense_power(target, "force") + target->query_con();

        message_combatd(sort_msg(HIW "\n‘趙客縵胡纓’既畢，接下去便是‘吳鉤霜雪明’，$N" HIW "更"
                    "不思索，石壁上的圖譜一幅幅在腦海中自然湧出，自‘銀鞍照白馬’直到‘誰能書閣下’，"
                    "一氣呵成的使了出來。\n" NOR), me);

        if (ap / 2 + random(ap) > dp)
        {
                if (flag) damage = damage_power(me, "sword") *2/3;
                else damage = damage_power(me, "blade") *2/3;
                damage += query("jiali", me);
                msg = COMBAT_D->do_damage(me, target, REMOTE_ATTACK, damage, 70 + random(10),
                                           (: final2, me, target, damage :));
        } else
        {
                msg = HIC "$n" HIC "默運內功，內勁貫于全身，奮力抵擋住$N" HIC "這招。\n" NOR;
        }
        message_combatd(sort_msg(msg), me, target);

        // 第四招，判斷對方身法

        if (flag)ap = attack_power(me, "sword") + me->query_dex();
        else ap = attack_power(me, "blade") + me->query_dex();        
        dp = defense_power(target, "dodge") + target->query_dex();

        message_combatd(HIW "\n待得‘誰能書閣下’這套功夫演完，$N" HIW "只覺氣息逆轉"
                     "，‘不慚世上英’倒使上去。\n" NOR, me);

        if (ap / 2 + random(ap) > dp)
        {
                if (flag) damage = damage_power(me, "sword") *2/3;
                else damage = damage_power(me, "blade") *2/3;
                damage += query("jiali", me);
                msg = COMBAT_D->do_damage(me, target, REMOTE_ATTACK, damage, 75 + random(10),
                                          (: final3, me, target, damage, weapon, lvl, sub_msg :));
        } else
        {
                msg = HIC "$n" HIC "見這招來勢兇猛，身形疾退，瞬間飄出三"
                      "丈，方才躲過$N" HIC "這招。\n" NOR;
        }
        message_combatd(sort_msg(msg), me, target);

        me->start_busy(3 + random(3));
        addn("neili", -400-random(400), me);
        return 1;
}

string final1(object me, object target, int damage, object weapon, int lvl)
{
        addn("neili", -(lvl+random(lvl)), target);

        return  HIY "$n" HIY "卻覺$N" HIY "這招氣勢恢弘，于是運力奮力抵擋。但是無奈這"
                "招威力驚人，$n" HIY "悶哼一聲，倒退幾步，頓覺內息渙散，" + weapon->name() + HIY 
                "上早已染滿鮮血！\n" NOR;
}

string final2(object me, object target, int damage)
{
        target->receive_damage("jing", damage / 2, me);
        target->receive_wound("jing", damage / 4, me);
        return  HIY "$n" HIY "心中一驚，但見$N" HIY "這幾招奇異無比，招式變化莫測，"
                "但威力卻依然不減，正猶豫間，$n" HIY "卻已中招，頓感精力不濟，渾"
                "身無力。\n" NOR;
}

string final3(object me, object target, int damage, object weapon, int lvl, string msg)
{
   
        target->start_busy(4 + random(3));
  
        return  HIY "$N" HIY + msg + "法奇妙無比，手中" + weapon->name() + HIY "時而宛若遊龍，時而"
                "宛若驚鴻，霎那間$n" HIY "已遍體鱗傷，$N" HIY "猛然將手中" + weapon->name() + HIY "一"
                "轉，劍勢陡然加快，將$n" HIY "團團圍住，竟無一絲空隙！\n" NOR;

}
