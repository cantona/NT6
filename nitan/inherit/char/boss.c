// Written by Lonely@chinamud.cn
// boss.c
#include <ansi.h>

inherit NPC;

int is_boss() { return 1; }
int is_stay_in_room() { return 1; }

void fight_ob(object ob)
{
        if( is_fighting() || !query("end_time") )
                return ::fight_ob(ob);

        set_temp("end_time", time() + query("end_time"));
        return ::fight_ob(ob);
}

varargs void die(object killer)
{
        object *obs, *obn, env;
        object me, ob;
        mapping drops, rewards;
        string *ks;
        string line, key;
        int exp, pot;
        int i, n, times, value, rand;
        string fbname, owner;
        mapping fuben_data;
        int fuben_level, percent;
        mixed death_msg;

        me = this_object();

        //if( query("end_boss", me) || query("fight_boss", me) )
        if( objectp(ob = previous_object(0)) && sscanf(base_name(ob), "/kungfu/skill/%*s") ) {
                full_self();
                return;
        }

        if( time() < query_temp("end_time", me) ) // 時間沒有到，死亡不了
        {
                addn("jing", query("max_jing") / 10);
                if( query("jing") > query("max_jing") ) set("jing", query("max_jing"));
                addn("eff_jing", query("max_jing") / 10);
                if( query("eff_jing") > query("max_jing") ) set("eff_jing", query("max_jing"));
                addn("qi", query("max_qi") / 10);
                if( query("qi") > query("max_qi") ) set("qi", query("max_qi"));
                addn("eff_qi", query("max_qi") / 10);
                if( query("eff_qi") > query("max_qi") ) set("eff_qi", query("max_qi"));
                message_vision(HIR "\n$N" HIR "大喝一聲，運用秘法，氣血有所回升！\n\n" NOR, me);
                return;
        }

        if( !killer ) killer = me->query_last_damage_from();
        if( !killer ) killer = query_temp("last_damage_from");
        if( !killer ) return;

        if( death_msg = query("death_msg", me) ) {
                if( functionp(death_msg) )
                        evaluate(death_msg, me);
                else
                        message_vision(death_msg, me);
        }
        else
                message_vision(NOR "\n$N撲在地上掙紮了幾下，腿一伸，口中噴出幾口" 
                               HIR "鮮血" NOR "，死了！\n\n" NOR, me); 

        // 以下部分轉移到equipmentd.c中處理,因涉及到動態物品
        if( mapp(drops = query("drops")) ) {
                EQUIPMENT_D->killer_reward(killer,this_object(),drops);
                /*
                times = ACTION_D->query_action("fuben_drop");
                if( !times ) times = 1;

                ks = keys(drops);
                for( i=0; i<sizeof(ks); i++ ) {
                        key = ks[i];
                        value = drops[ks[i]];
                        for( n=0;n<times;n++ ) {
                                rand = random(value);
                                if( !rand ) {
                                        if( ob = new(key) ) {
                                                ob->move(me, 1);
                                        }
                                }
                        }
                }
                */
        }

        fbname = FUBEN_D->query_fuben_name(me);
        owner = FUBEN_D->query_fuben_owner(me);
        if( fbname && owner ) {
                fuben_data = FUBEN_D->query_fuben_data();
                if( !undefinedp(fuben_data[fbname]) ) {
                if( fuben_data[fbname]["level"] )
                        fuben_level = to_int(fuben_data[fbname]["level"]);
                }
                if( query("clear_fuben", me) )
                        FUBEN_D->delay_clear_fuben(fbname, owner);
        }
        if( !fuben_level )
                fuben_level = query("level", me);

        if( !(rewards = query("rewards")) ) {
                ::die(killer);
                return;
        }

        if( objectp(killer) ) {
                env = environment(me);
                obs = pointerp(killer->query_team()) ?
                                killer->query_team() : ({ killer });
                obs = filter_array(obs, (: environment($1) == $(env) :));
                // 如果隊長不在，則這個隊成員無任何獎勵
                if( killer->query_team() && (!objectp(killer->query_team_leader()) || environment(killer->query_team_leader()) != env) )
                        obs = ({ });

                if( arrayp(obn = keys(this_object()->query_hatred_list())) && sizeof(obn) > 0 )
                {
                        obn -= ({ 0 });
                        obn = filter_array(obn, (: environment($1) == $(env) :));
                        obn -= obs;
                        obs += obn;
                }
                foreach( object user in obs ) {
                        if( !objectp(user) ) continue;
                        if( fuben_level ) {
                                if( query("level", user) <= fuben_level )    percent = 100;
                                /*
                                else if( query("level", user) <= fuben_level+20 ) percent = 80;
                                else if( query("level", user) <= fuben_level+30 ) percent = 50;
                                */
                                else {
                                        tell_object(user, ((killer == user)?"您":killer->name())+"殺死"+query("name")+"，但您經驗與BOSS的水平相差過大，沒有獎勵。\n");
                                        continue;
                                }
                                rewards["percent"] = percent;
                        }
                        /*
                        else
                        {
                                if( query("combat_exp", user) > query("combat_exp")*2 ) {
                                        tell_object(user, ((killer == user)?"您":killer->name())+"殺死"+query("name")+"，但您經驗與BOSS的水平相差過大，沒有獎勵。\n");
                                        continue;
                                }
                        }
                        */
                        if( query("doing", user) ) rewards["percent"] = 50;
                        GIFT_D->bonus(user, rewards);
                }
        }

        destruct(this_object());
        return;
}

varargs void unconcious(object defeater)
{
        object ob;

        //if( query("end_boss") || query("fight_boss") )
        if( objectp(ob = previous_object(0)) && sscanf(base_name(ob), "/kungfu/skill/%*s") ) {
                full_self();
                return;
        }
        die(defeater);
        return;
}

