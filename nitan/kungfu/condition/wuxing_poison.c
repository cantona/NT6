// wuxing_poison.c 無形之毒

inherit F_CLEAN_UP;

int update_condition(object me, int duration)
{
        int limit,limit1,limit2,limit3,limit4,damage;
  if (me->is_ghost()) return 1;
        damage=query("max_qi", me)/30;
        if(damage < 20) damage = 20;
        limit=query("con", me)+me->query_skill("force",1)/10;
        if( query_temp("nopoison", me))return 0;
        if(limit >50) limit =49;
        limit1=50 - limit + 2;
        limit2=50 - limit*2/3;
        limit3=50 - limit/2;
        limit4=50 - limit/4;
        if( duration<limit1 && living(me) && !query_temp("noliving", me) )
        {
                tell_object(me,"你毒氣攻心，心如刀絞，不由得大叫一聲，一口鮮血狂噴而出。\n");
                message("vision", me->name() + "忽然大叫一聲，口中鮮血狂噴不止，一頭栽倒在地上。\n", environment(me), me);
                me->unconcious();
                me->die();
                return 0;
        }
        if( duration > limit4 )
        {
                tell_object(me,"你忽然覺得腹痛如絞，眼前一陣發黑，一定是吃了什麼有毒的東西。\n");
                message("vision", me->name() + "忽然臉色蒼白，豆大的汗珠從額頭滲出。\n", environment(me), me);
        }
        if( duration > limit3 && duration < limit4)
        {
                tell_object(me,"你覺得肝腸寸斷，全身痛苦得縮成一團，毒氣似乎已經開始擴散了。\n");
                message("vision", me->name() + "嘴脣發青，牙關咬的咯咯直響，身子已經蜷縮成了一團。\n", environment(me), me);
        }
        if( duration > limit2 && duration < limit3)
        {
                tell_object(me,"你覺得四肢已經麻木，毒氣已經升至小腹，快找解藥吧，否則會死的。\n");
                message("vision", me->name() + "面上現出一股黑氣，雙目突出，眼中全是通紅的血絲。\n", environment(me), me);
        }
        if( duration > limit1 && duration < limit2)
        {
                tell_object(me,"你覺得一陣天旋地轉，毒氣已升至胸口，快找解藥吧，否則會死的。\n");
                message("vision", me->name() + "面上黑氣越來越濃了，全身大汗淋漓，嘴角滲出了一縷黑血。\n", environment(me), me);
        }
        me->receive_wound("qi", damage,"無形之毒發作");
        me->receive_damage("jing", damage,"無形之毒發作");
        if( query("eff_jing", me)<0 || query("eff_qi", me)<0)return 0;
        me->apply_condition("wuxing_poison", duration - 1);
        if( !duration ) return 0;
        return 1;
}

string query_type(object me)
{
        return "poison";
}