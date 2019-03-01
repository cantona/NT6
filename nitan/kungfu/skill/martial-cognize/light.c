// light.c

#include <ansi.h>

inherit F_SSERVER;

int bbqthem(object me, object obj);
int perform(object me, object target)
{
        int lvl,i;
        object env, *inv;
        string *can_perform;

        can_perform=query("can_perform/martial-cognize", me);

        if(!can_perform || 
           !arrayp(can_perform) || 
           !sizeof(can_perform) || 
           member_array("light",can_perform) == -1)
                return notify_fail("你還沒有學會使用﹝天龍之光﹞！\n");

        if (me->is_busy())
                return notify_fail("你上一個動作還沒有完成，無法使用天龍之光。\n");

        lvl = (int)me->query_skill("martial-cognize",1);

        if (lvl < 250)
                return notify_fail("你的武學修養修為不夠。\n");

        if( query("jingli", me)<500 )
                return notify_fail("你的精力不夠！\n");

        if( query("max_jingli", me)<1000 )
                return notify_fail("你的精力還沒有達到足夠的層次！\n");

        if( query("jing", me) <= 300 )
                return notify_fail("你的精神狀況不好！\n");

        if( environment(me) && query("no_fight", environment(me)) )
                return notify_fail("這裡不能使用﹝天龍之光﹞!\n");

        addn("jingli", -400, me);
        me->receive_damage("jing", 250);

        message_vision(HIY "$N猛然爆發出一聲驚天動地的怒吼，天地隱隱回響著清澈的龍吟．．．\n" NOR, me);

        if ( lvl <= random(500) )
        {
                env = environment(me);
                inv = all_inventory(env);
                for(i=0; i<sizeof(inv); i++) 
                {
                        if( inv[i]==me ) continue;
                        if( inv[i]->is_corpse() ) continue;
                        if( !inv[i]->is_character()) continue;
                        if (userp(me) && 
                            userp(inv[i]) && 
                            !inv[i]->is_want_kill(query("id", me)) )
                                me->want_kill(inv[i]);
                        me->kill_ob(inv[i]);
                        if (living(inv[i]) && ! userp(inv[i]))
                                inv[i]->kill_ob(me);
                        else
                                inv[i]->fight_ob(me);
                }
                me->start_busy(5);
                return notify_fail("你因為武學修養修煉不夠而失敗了！\n");
        }
        message_vision(HIR "．．．$N幻化成一條模糊的龍影，全身射出千萬道熾熱的血紅光芒！！！\n" NOR, me);
        env = environment(me);
        inv = all_inventory(env);
        for(i=0; i<sizeof(inv); i++) {
                if( inv[i]==me ) continue;
                if( inv[i]->is_corpse() ) continue;
                if( !inv[i]->is_character()) continue;
                bbqthem(me, inv[i]);
        }
        me->start_busy(5);
        return 1;
}

int bbqthem(object me, object obj)
{
        int magic;
        string msg;
        magic = (int) me->query_skill("martial-cognize",1)*5;  
        message_vision(HIR "\n熾熱的紅光象利劍般射向$N，\n" NOR, obj);
        obj->receive_wound("jing", magic*2/3, me);
        if(obj->is_ghost()) 
        {
                message_vision(YEL "$N慘叫了一聲，化為了灰燼！\n" NOR, obj);
                obj->die();
                return 1;
        }
        magic = random(magic) + magic;
        if (!wizardp(obj))
        {
                if( !query("env/invisible", obj) )
                {
                        obj->receive_damage("qi",magic,me);
                        obj->receive_wound("qi",magic*2/3,me);
                }
                else
                {
                        obj->receive_wound("jing",magic/2,me);
                        obj->receive_damage("qi",magic*2,me);
                        obj->receive_wound("qi",magic*4/3,me);
                }
                msg=obj->name(query("qi", )+COMBAT_D->status_msg(obj)*100/query("max_qi", obj));
                message("vision",msg,environment(obj));
                if (userp(me) && 
                    userp(obj) && 
                    !obj->is_want_kill(query("id", me)) )
                        me->want_kill(obj);
                me->kill_ob(obj);
                if (living(obj) && ! userp(obj))
                        obj->kill_ob(me);
                else
                        obj->fight_ob(me);
                obj->start_busy(2);
        }
        return 1;
}