int dispel() { return 0; }

int update_condition(object me, int duration)
{
        if (duration < 1)
        {
                tell_object(me, "官府不再通緝你了！\n");
                CHANNEL_D->do_channel(this_object(), "rumor",
                        "因為" + me->name(1) + "一直沒能被" +
                        "緝拿歸案，聽説官府已經取消了通緝令。");
                return 0;
        }

        if( query("no_fight", environment(me)) || 
            query("room_owner_id", environment(me)) )
        {
                int i = random(30);
                
                me->receive_damage("jing",query("max_jing", me)/5);
                me->receive_damage("qi",query("max_qi", me)/5);
                me->receive_wound("jing",query("max_jing", me)/10);
                me->receive_wound("qi",query("max_qi", me)/10);
                if ( i > 20) 
                        tell_object(me, "一道閃電劃過長空，你想起以前為非作歹的事蹟，不由得心發虛！\n"  );
                else 
                if (i > 10)  
                        tell_object(me, "天空中響起了滾滾雷聲，你怔怔地望着天喃喃自語：我做了這麼多壞事，該不會被天遣吧！\n");
                else 
                        tell_object(me, "你覺得背脊一涼，打心底湧起了一股寒意：鬼！！\n");

                set_temp("die_reason", "遭天遣而死", me);
        }

        me->apply_condition("killer", duration - 1);
        return 1;
}
