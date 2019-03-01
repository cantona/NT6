// 真武劍陣 zhenwu-array.c
// Modified by haiyan

#include <ansi.h>

#define MAX_ZHEN 8 
#define MIN_ZHEN 5 

inherit F_CLEAN_UP;
inherit F_SSERVER;

int valid_enable(string usage) { return usage=="array"; }

string *style = ({ 
HIM "$N手持$w，前進中一陣急驟，手中$w猛然刺向$n！\n"NOR,
HIM "$N著地一滾，手中$w上挑，已刺向$n小腹！\n"NOR, 
HIM "$N反手握住$w，化出一道白弧，劍尖直指$n眉心！\n"NOR,
HIM "$N向前一縱，略退半步，突然一個急進，手中$w向$n猛撲過去！\n"NOR,
HIM "$N與$w合而為一，飛身而起，挺身刺向$n的兩處要害！\n"NOR, 
HIM "$N左手捻一個劍訣，手中$w忽而向下，刺向$n下盤！\n"NOR, 
HIM "$N縱身一躍，手中$w叮叮作響，已向$n連刺三劍！\n"NOR, 
HIM "$N手中$w疾揮，劃出道道劍光，身形一轉，迅速刺向$n！\n"NOR
});

string *zhen = ({ 
HIC"\n真武劍陣緩緩轉動，將$n圍在核心，一股強大的綿力壓向$n。\n\n"NOR, 
HIC"\n真武劍陣忽進忽退，$n凝神觀陣，看不出絲毫破綻，只得緊守門戶，不敢妄自出招。\n\n"NOR, 
HIC"\n$N一聲長嘯，真武劍陣迅速移位，眾人步法精妙，緊隨$n進退。\n\n"NOR, 
HIC"\n真武劍陣越縮越小，攻勢連綿不絕，無形劍氣象浪潮一般圈向$n。\n\n"NOR 
});

int valid_learn(object me) 
{ 
        if ((int)me->query_skill("wudang-xinfa", 1) < 100)
                return notify_fail("你的武當心法火候不夠，難以領會「真武劍陣」。\n"); 

        if ((int)me->query_skill("taoism", 1) < 150) 
                return notify_fail("你的道學心法修為不夠，無法領悟高深的「真武劍陣」。\n"); 

        if ((int)me->query_skill("sword", 1) < 100) 
                return notify_fail("你的基本劍法火候太淺，對「真武劍陣」的變化不能領會。\n"); 

        if ((int)me->query_skill("array", 1) < (int)me->query_skill("zhenwu-array", 1)) 
                return notify_fail("你的基本陣法水平有限，無法領會更高深的「真武劍陣」。\n"); 

        return 1;
} 

void remove_effect(object me);
void checking(int del_time,object me);

int practice_skill(object me) 
{
      return notify_fail("真武劍陣只能用學(learn)或操演來增加熟練度。\n"); 
}

int form_array(object me)
{
        int i; 
        object *member, weapon; 
        member = me->query_team();

        if( !pointerp(member=me->query_team()) || !me->is_team_leader())
                return notify_fail("只有隊伍領袖才可以指揮組陣！\n");

        if( me->query_skill_mapped("array") != "zhenwu-array") 
                return notify_fail("你還沒有準備好真武劍陣！\n");

        if( sizeof(member) > MAX_ZHEN )
                return notify_fail("真武劍陣最多只能由八名武當弟子組成。\n");

        if( sizeof(member) < MIN_ZHEN )
                return notify_fail("真武劍陣至少要由五名武當弟子組成。\n");

        if( me->query_skill("zhenwu-array",1) < sizeof(member)*20 ) 
                return notify_fail("你對真武劍陣的精要變化還未完全領悟！\n"); 

        for( i = 0; i < sizeof(member); i++ ) 
        { 
           if (!member[i]) 
                return notify_fail("你的隊伍中有人離開，需要重新組合隊伍。\n");

           if (environment(member[i]) != environment(me)) 
                return notify_fail("你隊伍中的"+member[i]->name()+"不在你身邊。\n");

           if( query("family/family_name", member[i]) != "武當派" )
                return notify_fail("你隊伍中的"+member[i]->name()+"不是武當派弟子。\n"); 

           if (member[i]->query_skill("zhenwu-array",1) < 80 ) 
                return notify_fail("你隊伍中的"+member[i]->name()+"真武劍陣陣法還未入門。\n");

           if( !objectp(weapon=query_temp("weapon", member[i])) || 
                query("skill_type", weapon) != "sword" )
                return notify_fail("你隊伍中的"+member[i]->name()+"沒有裝備劍。\n"); 

           if (member[i]->query_skill("sword",1) < 120 ) 
                return notify_fail("你隊伍中"+member[i]->name()+"的基本劍法造詣太低。\n");

           if (member[i]->query_skill_mapped("array") != "zhenwu-array") 
                return notify_fail("你隊伍中的"+member[i]->name()+"未準備好真武劍陣陣法！\n");
        } 

        if( me->is_busy())
               return notify_fail("你現在忙不過來指揮眾人組陣! \n");

        if( query_temp("alreading", me) )
               return notify_fail("你的隊伍已經組成了「真武劍陣」！\n");

        message_vision( HIY "$N" HIY "一聲長嘯，手中" + weapon->name() + 
                        HIY "一盪，身形移動，率領眾人分四象八卦站定方位，擺出了"
                        HIY "「真武劍陣」陣法！\n\n"
                        HIW "眾人揮劍齊呼：真武劍陣 ── 天下第一！\n\n" NOR, me);

        set_temp("alreading", me->query_skill("zhenwu-array",1)/10+10, me);
        call_out("checking", 1, 1, me); 
        return 1;
}

void checking(int del_time,object me)
{
        string msg;
        int num, atac;
        int i, fighting;
        object *member, target, weapon;

        if( !query_temp("alreading", me))return ;

        target=query_temp("offensive_target", me);
        num=query_temp("alreading", me);
        member = me->query_team(); 

        set_temp("alreading",query_temp("alreading",  me)-del_time, me);
        if( wizardp(me) )  tell_object(me,sprintf("<持續時間還剩%d秒>\n",num));
        if( num <= 1 ) 
        {
             message_vision(HIW "$N" HIW "已將自己所掌握的真武劍陣全部變化"
                            HIW "操演完畢，解散了劍陣。\n\n"NOR, me);
             delete_temp("alreading", me);
             return;
        }

        if( !target ) target = offensive_target(me);
        if( !target || !target->is_character())
        {
            call_out("checking", 1, 1, me); 
            return;
        }

        for (i = 0; i < sizeof(member); i++ ) 
        {
            if (!member[i]) 
            {
                message_vision(HIW "由于$n" HIW "已離開劍陣，真武劍陣需要重新組合。\n\n" NOR, me, member[i]); 
                remove_effect(me);
                return;
            }

            if(member[i]->is_corpse())
            {
                if ( sizeof(member) < MIN_ZHEN )
                {
                    message_vision(HIW "由于$N" HIW "沒能抵擋住$n"
                                   HIW "的致命一擊，真武劍陣人數不足，頓出破綻，被$n攻破。\n\n"NOR, member[i], target);
                    remove_effect(me);
                    return;
                }
                else
                    message_vision(HIW "眾人看到$N" HIW "慘遭$n"
                                   HIW "毒手，怒從心起，士氣大增，當下改變陣形，將$n"
                                   HIW "團團圍住。\n\n"NOR, member[i], target);
            }

            if (environment(member[i]) != environment(me)) 
            {
                message_vision(HIW "$n" HIW "見$N" HIW "癒戰癒勇，私心頓起，為求自保，悄然逃離現場！\n"
                               HIC "由于$n離開現場，真武劍陣被$N攻破了！\n\n" NOR, target, member[i]); 
                remove_effect(me);
                return;
            }

            weapon=query_temp("weapon", member[i]);
            if( !objectp(weapon) || query("skill_type", weapon) != "sword" )
            {
                message_vision(HIW "$N" HIW "見$n" HIW "劍已離手，精神大振，疾向$n連攻數招。\n"
                               HIW "$n" HIW "無奈之下，步步後退，終于偏離了真武劍陣方位！\n"
                               HIC "真武劍陣被$N" HIC "攻破了！！\n\n" NOR, target, member[i]); 
                remove_effect(me);
                return;
            }
            atac += (member[i]->query_skill("force",1) +
                     member[i]->query_skill("sword",1)) / 2;
            member[i]->kill_ob(target); 
        }

        atac = atac / sizeof(member);
        if( wizardp(me) )  tell_object(me,sprintf("<增加攻擊力%d點>\n",atac));
        fighting = random(sizeof(member)); 
        if (living(member[fighting]))
        {
           if (random(10) > 6)
           {
              msg = zhen[random(sizeof(zhen))]; 
              message_vision(msg, me, target);
           }

           if (random(8) > 5)
           {
               if( query("family/family_name", target) != "武當派" )
                   message_vision(HIY "$N" HIY "大聲對$n"
                                  HIY "喝道：“大膽狂徒，我武當派今日替天行道，還不快快受死！”\n"
                                  NOR, member[fighting], target);
           else
                   message_vision(HIY "$N" HIY "對$n"
                                  HIY "喝道：“今日我武當派要清理門戶，還不快快受死？”\n"
                                  NOR, member[fighting], target);
           }

           weapon=query_temp("weapon", member[fighting]);
           msg = style[random(sizeof(style))]; 
           msg = replace_string(msg,"$w",weapon->name()); 
           if( objectp(weapon) && query("skill_type", weapon) == "sword" )
           {
               if (!member[fighting]->is_busy())
               {
                   message_combatd(msg, member[fighting], target); 
                   addn_temp("apply/attack", atac, member[fighting]);
                   addn_temp("apply/damage", atac, member[fighting]);
                   COMBAT_D->do_attack(member[fighting], target, weapon, 0);
                   addn_temp("apply/attack", -atac, member[fighting]);
                   addn_temp("apply/damage", -atac, member[fighting]);
                   member[fighting]->start_busy(2);
               }
           }
        }
        call_out("checking", 1, 1, me);
        return;
}

void remove_effect(object me)
{
        if (!me) return;
        delete_temp("alreading", me);
        me->start_busy(1);
}
