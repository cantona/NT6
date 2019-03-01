// snowman
#include <ansi.h>

int check_fight(object me);
int remove_effect(object me);

int perform(object me)
{
        object weapon;

        if( !me->is_fighting() || !living(me))
                return notify_fail("「紅蓮火」只能在戰鬥中的使用。\n");

      if( !objectp(weapon=query_temp("weapon", me)) || 
          query("skill_type", weapon) != "blade" )
                return notify_fail("你先找把刀再說吧！\n");

        if( query_temp("honglian", me) )
                return notify_fail("你正在使用「紅蓮火」。\n");  

        if( query_temp("mz_lx", me) )
                return notify_fail("你正在使用「降妖伏魔咒」。\n");  

        if((int)me->query_skill("jiechen-dao", 1) < 180 )
                return notify_fail("你的戒塵刀不夠嫻熟，還不能領會「紅蓮火」之訣竅。\n");

        if (me->query_skill_mapped("blade") != "jiechen-dao")
                return notify_fail("你必須使用戒塵刀來施展「紅蓮火」。\n");   

        if( query("max_neili", me)<3500 )
                return notify_fail("你的內力修為太弱，使不出「紅蓮火」。\n");                

        if( query("neili", me)<800 )
                return notify_fail("你現在真氣不夠，使不出「紅蓮火」。\n");


        if(userp(me) && (int)me->query_skill("buddhism", 1) < 180 )
                return notify_fail("你對禪宗心法的領悟不夠，無法使用「紅蓮火」。\n");

        if(userp(me) && me->query_skill_mapped("force") != "hunyuan-yiqi")
                return notify_fail("你的內功不對，根本不能使出「紅蓮火」。\n");
                                                                                     
        if( !query("jiali", me) )
                return notify_fail("「紅蓮火」全以內力為本。你不加力，是無法發揮出它的威力的。\n");

        message_vision(RED "\n$N祭起戒塵刀之「紅蓮火」絕技，精純的內力呈紅色緩緩湧出，\n"
                           "于身前三尺之處，便即停住不動，將這飄盪無定的真氣定在半空，\n"
                           "它雖是虛無縹緲，不可捉摸，卻能殺人于無形，實是厲害不過！\n" NOR, me);
        me->start_busy(1);
        set_temp("honglian", 1, me);
        addn("neili", -300, me);
        addn("jingli", -100, me);
        addn_temp("apply/parry", me->query_skill("jiechen-dao",1)/3, me);
        addn_temp("apply/arrmor", me->query_skill("jiechen-dao",1)/3, me);
        check_fight(me);
        return 1;
}

int check_fight(object me)
{
        object *enemy, target;
        int sz;        

        if (!me) return 0;

        if( me->is_ghost() || !living(me) || query("no_fight", environment(me)) || query_temp("weapon", me)){
           addn_temp("apply/parry", -me->query_skill("jiechen-dao",1)/3, me);
           addn_temp("apply/arrmor", -me->query_skill("jiechen-dao",1)/3, me);
           delete_temp("honglian", me);
           return 0;
           }        

        addn("neili", -5, me);
        enemy = me->query_enemy();

        if( !enemy || !arrayp(enemy) ) remove_effect(me);
        sz = sizeof(enemy);
        if( sz > 4 ) sz = 4;
        if( sz > 0 ) target = enemy[random(sz)];
        else remove_effect(me);
        if( !query_temp("honglian", me))return 1;

        else if(!me->is_fighting())
        {
                if( !query_temp("stopped", me) )
                {
                    set_temp("stopped", 1, me);
                    call_out("check_fight", 2, me);
                }
                else remove_effect(me);
        }
        else if (userp(me))
        {
                  message_vision(HIY"$N一刀劈出，突然變招，竟然是完全不同的招數來！\n"NOR,me);
                  me->start_busy(1);
                  addn_temp("apply/parry", -me->query_skill("jiechen-dao",1)/3, me);
                  addn_temp("apply/arrmor", -me->query_skill("jiechen-dao",1)/3, me);
                  delete_temp("honglian", me);
                  return 1;
        }   
       else if( query("neili", me) <= 10 || !target)remove_effect(me);
       else call_out("check_fight", 1, me);
       return 1;
}       

int remove_effect(object me)
{
   string msg;
   message_vision(HIY "\n$N回手一招紅蓮火使完，雙手合十立于當地，示慈悲為懷。\n\n"NOR, me);
   addn_temp("apply/parry", -me->query_skill("jiechen-dao",1)/3, me);
   addn_temp("apply/armor", -me->query_skill("jiechen-dao",1)/3, me);
   delete_temp("honglian", me);
   delete_temp("stopped", me);
   remove_call_out("check_fight"); 
   return 0;
}
