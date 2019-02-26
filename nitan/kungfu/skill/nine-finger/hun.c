// hun.c 無名

#include <ansi.h>

inherit F_SSERVER;

int perform(object me, object target)
{
        string msg,str,mapforce;
        object weapon,weapon2;
        int n;
        int skill, ap, dp, damage;

        me->clean_up_enemy();
        if (! target) target = me->select_opponent();

        skill = me->query_skill("nine-finger", 1);

        if (! me->is_fighting(target))
                return notify_fail("無名只能對戰鬥中的對手使用。\n");

        if(me->query_skill_mapped("finger") != "nine-finger") 
                return notify_fail("你沒有用九字真言手印，無法使用「無名」絕招！\n");

        if (me->query_skill_prepared("finger") != "nine-finger")
                return notify_fail("你沒有準備使用九字真言手印，無法施展「無名」絕招。\n");

        if (skill < 100)
                return notify_fail("你的九字真言手印等級不夠，練好了再來！\n");

        if( objectp(weapon=query_temp("weapon", me)) || 
            objectp(weapon=query_temp("handing", me)) )
                return notify_fail("你必須空着雙手才能使用指法絕招。\n");

        if( query("neili", me)<500 )
                return notify_fail("你的內力不夠。\n");
        
        ap = me->query_skill("finger") + me->query_skill("force");
        ap+=query("jiali", me);
        ap+=query("jianu", me);

        damage = ap + random(ap);
                
        dp = target->query_skill("parry",1) + target->query_skill("dodge",1);
        dp = dp*3/2;

        weapon2=query_temp("weapon", target);
        
        if (me->query_skill_mapped("force"))
                mapforce = to_chinese(me->query_skill_mapped("force"));
        else
                mapforce = "內力";
                
        msg = MAG "\n$N" NOR MAG "口中默誦九字真言，雙手攤開，九式手印不住變幻。\n" +
               "一時之間，漫天手印混雜着強烈的" HIW + mapforce + NOR + 
               MAG "，無堅不摧地殺向$n" NOR MAG "！\n" NOR;
                
        message_combatd(msg, me, target);

        n=query("tianmo_jieti/times", me);
        
        while (n-- && me->is_fighting(target))
        {
                if (! target->is_busy() && random(3))
                        target->start_busy(1);
                COMBAT_D->do_attack(me, target, 0, 0);
        }

        msg = "\n忽聞一聲大喝" HIW " 臨 兵 鬥 者 皆 陣 列 在 前 !\n" NOR +  
              "只見$N身形凌空而起，雙手合什，寶瓶氣從四面八方湧來，充塞天地，即使協生雙翼，還是避無可避！ \n" + 
              "正是" HIW "九字真言手印" NOR "終極式： " HIY "九印合一" NOR "！\n" NOR; 

        if (ap / 2 + random(ap) > dp || !living(target))
        {
                if (weapon2)
                        msg += MAG "$n" NOR MAG "見$N" MAG "來勢兇猛，不敢正面抵擋，手中" + weapon2->name() + 
                               NOR MAG "滿天幻影，防得水泄不通\n" + 
                               "$N" NOR MAG "竟是置若罔聞，" HIW "螺旋勁氣" NOR MAG "仍舊綿綿不絕，$n" NOR MAG "無可奈何之下，被擊個正着！\n" NOR; 
                else
                        msg += MAG "$n" NOR MAG "見$N" MAG "來勢兇猛，不敢正面抵擋，側身進步雙掌奮力側擊$N\n" + 
                               NOR MAG "$N" NOR MAG "竟是置若罔聞，" HIW "螺旋勁氣" NOR MAG "仍舊綿綿不絕，$n" + 
                               NOR MAG "無可奈何之下，被擊個正着！\n" NOR;
               
                target->receive_damage("qi", damage, me);
                target->receive_wound("qi", damage/2, me);
                str=COMBAT_D->status_msg(query("qi", target)*100/query("max_qi", target));
                msg += "($n"+str+")\n";
                target->start_busy(1);
        } else
        {
                if (weapon)
                        msg += MAG "$n" NOR MAG "見$N" NOR MAG "來勢兇猛，不敢正面抵擋，手中" + weapon2->name() +
                               NOR MAG "滿天幻影，防得水泄不通\n" +
                               "$N" NOR MAG "被緩得一緩，" HIW "螺旋勁氣" NOR MAG"已然落空！\n" NOR;

                else
                        msg += MAG "$n" NOR MAG "見$N" NOR MAG "來勢兇猛，不敢正面抵擋，側身進步雙掌奮力側擊$N\n" + 
                               NOR MAG "$N" NOR MAG "被緩得一緩，" HIW "螺旋勁氣" NOR MAG "已然落空，但$n" NOR MAG "也被$N" NOR MAG "震得氣血翻湧！\n" NOR;
        }

        me->start_busy(2 + random(2));
        message_vision(msg, me, target);
        if(!userp(target) && !target->is_killing(query("id",me)) ) target->kill_ob(me); 
        addn("neili", -damage/3, me);
        return 1;
}
