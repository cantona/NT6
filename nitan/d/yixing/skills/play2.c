// /d/yixing/skills/play2.c 碧海潮生曲
// Last Modified by winder on Jul. 12 2002

#include <ansi.h>

inherit F_CLEAN_UP;

int exert(object me, object target)
{
        object weapon, room, *inv;
        int i, dp, skill, damage;

        if( query("neili", me)<800){
                tell_object(me, "你的內力不夠。\n");
                return 1;
        }

        room = environment(me);
        if( query("no_fight", room)){
                tell_object(me, "在這裏不能攻擊他人。\n");
                return 1;
        }

        if( !(weapon=query_temp("weapon", me))){
               tell_object(me, "你使用的武器不對。\n");
               return 1;
        }

        if( query("id", weapon) != "yuxiao"
         && query("id", weapon) != "tiexiao"
         && query("id", weapon) != "zhuxiao"){
                tell_object(me, "你使用的武器不對。\n");
                return 1;
        }
        
        if( (string)me->query_skill_mapped("force") != "bitao-xuangong" ) {
                tell_object(me, "你所用的並非碧濤玄功，無法施展碧海潮生曲！\n");
                return 1;
        }
        
        if( (skill = (int)me->query_skill("bitao-xuangong", 1)) < 80 ) {
                tell_object(me, "你的碧濤玄功火候未到，無法施展碧海潮生曲！\n");
                return 1;
        }

   //  modified by aln to give a more reasonable damage
        addn("neili", -100, me);
        me->receive_damage("qi", 10);

   //  modified by aln to give a more reasonable busy time
        me->start_busy(1 + random(5 - skill/60));
        message_vision(
                HIG "$N抽出一支洞簫，潛運內力，放到脣邊吹奏起來，簫聲婉轉纏綿，如良宵私語，又如昆崗鳳嗚。ⅵ\n" NOR, me);

        inv = all_inventory(room);
        for(i = 0; i < sizeof(inv); i++) {
                if( !living(inv[i]) || inv[i] == me ) continue;

                dp = (int)inv[i]->query_skill("force");
                if( random(skill + dp) <= dp * 3 / 2 ) {
        // modified by aln to let enemy kill
        // if you bother them by play, they should kill you
                        inv[i]->kill_ob(me);
                        continue;
                }

        // modified by aln to give a more reasonable damage
                damage = skill * 40 / ((int)inv[i]->query_con() + 20);

                inv[i]->receive_damage("jing", damage);
                inv[i]->receive_damage("qi", damage);

                message_vision(HIM"$N覺得全身飄飄欲仙，臉上露出迷惘而滿足的神情，情不自禁的手舞足蹈起來......\n"NOR, inv[i]);
                inv[i]->start_busy(damage/100);
        }

        return 1;
}
