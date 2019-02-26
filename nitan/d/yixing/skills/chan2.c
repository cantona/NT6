// /d/yixing/skills/chan2.c  「纏」字訣
// Last Modified by winder on Jul. 12 2002

#include <ansi.h>

inherit F_SSERVER;
int perform(object me, object target)
{
        string msg, skill, spskill, spforce;
        object weapon;

        mapping forces = ([
                "sword" : "taiji-shengong",
                "stick" : "huntian-qigong",
                "whip"  : "hunyuan-yiqi",
        ]);

        mapping skills = ([
                "sword" : "taiji-jian",
                "stick" : "dagou-bang",
                "whip"  : "riyue-bian",
        ]);

        if( me->is_busy() ) {
                tell_object(me, "你上一個動作還沒有完成，不能施用外功。)\n");
                return 1;
        }

        if( query("neili", me) <= 300){
                tell_object(me, "你的內力不夠！\n");
                return 1;
        }

        if( !target ) target = offensive_target(me);

        if( !target
        ||      !target->is_character()
        ||      !me->is_fighting(target) ) {
                tell_object(me, "牽制攻擊只能對戰鬥中的對手使用。\n");
                return 1;
        }

        if( target->is_busy() ) {
                tell_object(me, target->name() + "目前正自顧不暇，放膽攻擊吧ⅵ\n");
                return 1;
        }

        if( !(weapon=query_temp("weapon", me))){
                tell_object(me, "你手中沒有武器，如何使得纏字訣？\n");
                return 1;
        }

        skill=query("skill_type", weapon);
        if( member_array(skill, keys(skills)) == -1 ) {
                tell_object(me, "你使用的武器不能使你施展纏字訣！\n");
                return 1;
        }

        spskill = skills[skill];
        if( me->query_skill_mapped(skill) != spskill ) {
                tell_object(me, "你現在不在使用" + to_chinese(spskill) + "。\n");
                return 1;
        }

        if( (int)me->query_skill(skill) < 100 ) {
                tell_object(me, "你的" + to_chinese(spskill) + "不夠嫻熟，不會使用「纏」字訣。\n");
                return 1;
        }

        spforce = forces[skill];
        if( (int)me->query_skill(spforce, 1) < 80 ) {
                tell_object(me, "你的" + to_chinese(spforce) + "修為不夠，不會使用「纏」字訣。\n");
                return 1;
        }

        if( me->query_skill_mapped("force") != spforce ) {
                tell_object(me, "你所用的內功不符。\n");
                return 1;
        }

        addn("neili", -80, me);

        switch(spskill) {
        case "taiji-jian":
                msg = CYN "$N使出太極劍法「纏」字訣，連遞數個虛招企圖擾亂$n的攻勢。\n";
                break;
        case "dagou-bang":
                msg = CYN "$N使出打狗棒法「纏」字訣，幻出連山棒影，將$n吞沒！\n";
                break;
        case "riyue-bian":
                msg = HIY "$N使出日月鞭法的天纏地繞訣，連揮數鞭，如黑龍般着地向$n的全身捲去！\n";
                break;
        }

        if( random(query("combat_exp", me))>query("combat_exp", target)/2){
                switch(spskill) {
                case "riyue-bian":
                        msg += "結果$p被$P攻了個措手不及，渾身被漫天鞭影裹在其中！\n" NOR;
                        break;
                case "taiji-jian":
                        msg += "結果$p被$P攻了個措手不及ⅵ\n" NOR;
                        break;
                case "dagou-bang":
                        msg += "結果$p被$P纏了個手忙腳亂，一時無法還招進攻！\n" NOR;
                        break;
                }
                target->start_busy(1 + random( (int)me->query_skill(spskill, 1) / 20));
        } else {
                switch(spskill) {
                case "riyue-bian":
                        msg += "可是$p看破了$P的鞭法去路，敏捷地閃了開去。\n" NOR;
                        break;
                default:
                        msg += "可是$p看破了$P的企圖，並沒有上當。\n" NOR;
                        break;
                }

                me->start_busy(1 + random(3));

        }

        message_vision(msg, me, target);
        return 1;
}
