// This program is a part of NITAN MudLIB
// damage.c

#pragma save_binary

#include <ansi.h>
#include <login.h>
#include <move.h>
#include <action.h>
#include <condition.h>

inherit __DIR__"limb";

#define PVP_DAMAGE_SCALE        20
#define PVP_WOUND_SCALE         15

nosave mapping hatred_list;
int add_hatred(object who, int amount);
object query_max_damage_from();
varargs int receive_full(string type, int heal, object who);

int ghost = 0;
int is_ghost() { return ghost; }
int set_ghost(int f) { return ghost = f; }
int weak = 0;
int is_weak() { return weak; }
int query_weak() { return weak; }
int clear_weak()
{
        if( weak )
                tell_object(this_object(), HIG"\n你感覺身體狀態慢慢的復原了。。。\n\n" NOR);
        weak = 0;
}

nosave object last_damage_from = 0;
nosave string last_damage_name = 0;
nosave object defeated_by      = 0;
nosave string defeated_by_who  = 0;

object query_last_damage_from() { return last_damage_from; }
string query_last_damage_name() { return last_damage_name; }
object query_defeated_by()      { return defeated_by; }
string query_defeated_by_who()  { return defeated_by_who; }

varargs int set_weak(int n, int flag)
{
        int avoid;
        object me = this_object();

        avoid = query_temp("apply/avoid_weak");
        avoid+= query("ability1/avoid_weak");
        if( random(100) < avoid ) return 0;
        if( query("reborn/times") && me->query_skill_mapped("force") == "xiantian-gong" )
                if( n > 1 ) n -= random(n);
        if( intp(n) && (n >= 0) ) {
                if( !flag && weak && !n )
                        tell_object(this_object(), HIG "\n你感覺身體狀態慢慢的復原了。。。\n\n" NOR);
                else if( !flag && !weak && n )
                        tell_object(this_object(), RED "\n你感覺身體非常的虛弱，一點力氣也使不出來了。。。\n\n" NOR);

                if( !n ) {
                        weak = n;
                } else {
                        if( weak ) weak += n;
                        else weak = n;
                }
                return 1;
        }
        return 0;
}

varargs int receive_damage(string type, int damage, object who)
{
        int val, n;
        int avoid;
        function f;
        int r;

        if( damage < 0 ) error("F_DAMAGE: 傷害值為負值。\n");
        if( type!="jing" && type!="qi" )
                error("F_DAMAGE: 傷害種類錯誤( 只能是 jing, qi 其中之一 )。\n");

        if( query("master_ob", this_object()) == 5 ) return 0;
        if( objectp(who) ) {
                if( who != last_damage_from ) {
                        last_damage_name = who->name(1);
                        last_damage_from = who;
                        set_temp("last_damage_from", who);
                }
                // 裝備系統附加屬性
                if( n = (query_temp("apply/add_damage", who) + query("ability1/add_damage", who)) )
                {
                        n = n * (100 - query("reborn/times")*10)/100;
                        damage += damage * n / 100;
                }
                if( query_temp("freezing", who) )
                {
                        this_object()->affect_by("poison", 
                                ([ "level" : 8000, 
                                   "id":query("id", who), 
                                   "name" : "冰蠶寒毒", 
                                   "duration" : 200 ])); 
                        tell_object(this_object(), HIG "你中了冰蠶寒功的冰蠶寒毒。\n"); 
                }
                if( playerp(who) && playerp(this_object()) &&
                    this_object()->is_fighting(who) ) {
                        damage = damage * PVP_DAMAGE_SCALE / 100;
                        if( query("reborn/times") > query("reborn/times", who))
                                damage /= 2;
                }
        }
        if( n = (query_temp("apply/reduce_damage") + query("ability1/reduce_damage")) ) {
                if( n > 90) n = 90;
                damage -= damage * n / 100;
                if( damage < 0) damage = 0;
        }
        if( objectp(who) ) {
                /*
                if( damage > 100 &&
                    (n = query_temp("apply/add_weak", who)) ) {
                        n = n * (100 - query("reborn/times")*10)/100;
                        avoid = query_temp("apply/avoid_weak");
                        if( random(100) < n && random(100) > avoid ) set_weak(5, 0);
                }
                */
                // 仇恨系統
                if( !userp(this_object()) ) {
                        add_hatred(who, damage);
                }
        }

        if( who && damage > 150 )
                this_object()->improve_craze(damage / 5);

        f = query_temp("override/receive_damage");
        if( functionp(f) )
                r = (*f)(this_object(), type, damage, who);
        else
                r = 0;
        if( r ) return 0;
        
        // 受損的生命轉換為內力
        if( random(100) < 30 && (n = query_temp("apply/qi_vs_neili")) )
        {
                addn("neili", damage * n / 100);
                if( query("neili") > query("max_neili") )
                        set("neili", query("max_neili"));
                message_vision(HIR "\n突然間，$N全身藍光爆現，受損的氣血轉換為內力！\n", this_object());
        }
                        
        val = (int)query(type) - damage;
        if( val >= 0 ) set(type, val);
        else set( type, -1 );
        set_heart_beat(1);
        return damage;
}

varargs int receive_wound(string type, int damage, object who)
{
        int val, n;
        int avoid;

        if( damage < 0 ) error("F_DAMAGE: 傷害值為負值。\n");
        if( type!="jing" && type!="qi" )
                error("F_DAMAGE: 傷害種類錯誤( 只能是 jing, qi 其中之一 )。\n");

        if( query("master_ob", this_object()) == 5 ) return 0;
        if( objectp(who) ) {
                if( who != last_damage_from ) {
                        last_damage_name = who->name(1);
                        last_damage_from = who;
                        set_temp("last_damage_from", who);
                }
                if( n = (query_temp("apply/add_damage", who) + query("ability1/add_damage", who)) )
                {
                        n = n * (100 - query("reborn/times")*10)/100;
                        damage += damage * n / 100;
                }
                if( query_temp("freezing", who) )
                {
                        this_object()->affect_by("poison", 
                                ([ "level" : 8000, 
                                   "id":query("id", who), 
                                   "name" : "冰蠶寒毒", 
                                   "duration" : 200 ])); 
                        tell_object(this_object(), HIG "你中了冰蠶寒功的冰蠶寒毒。\n"); 
                }
                if( playerp(who) && playerp(this_object()) &&
                    this_object()->is_fighting(who) ) {
                        damage = damage * PVP_DAMAGE_SCALE / 100;
                        if( query("reborn/times") > query("reborn/times", who))
                                damage /= 2;
                }
        }
        if( n = (query_temp("apply/reduce_damage") + query("ability1/reduce_damage")) ) {
                if( n > 90) n = 90;
                damage -= damage * n / 100;
                if( damage < 0) damage = 0;
        }

        if( objectp(who) ) {
                if( damage > 100 &&
                    (n = query_temp("apply/add_weak", who)) ) {
                        n = n * (100 - query("reborn/times")*10)/100;
                        avoid = query_temp("apply/avoid_weak");
                        if( random(100) < n && random(100) > avoid ) set_weak(5, 0);
                }
                /*
                // 仇恨系統
                if( !userp(this_object()) ) {
                        add_hatred(who, damage);
                }
                */
        }

        if( who && damage > 150 )
                this_object()->improve_craze(damage / 3);

        val = (int)query("eff_" + type) - damage;
        if( val >= 0 ) set("eff_" + type, val);
        else {
                set( "eff_" + type, -1 );
                val = -1;
        }
        if( (int)query(type) > val ) set(type, val);
        set_heart_beat(1);
        return damage;
}

int receive_heal(string type, int heal)
{
        int val;

        if( heal < 0 ) error("F_DAMAGE: 恢復值為負值。\n");
        if( type!="jing" && type!="qi" )
                error("F_DAMAGE: 恢復種類錯誤( 只能是 jing, qi 其中之一 )。\n");

        val = (int)query(type) + heal;
        if( val > (int)query("eff_" + type) ) set(type, (int)query("eff_" + type));
        else set( type, val );
        return heal;
}

int receive_curing(string type, int heal)
{
        int max, val;

        if( heal < 0 ) error("F_DAMAGE: 恢復值為負值。\n");
        if( type!="jing" && type!="qi" )
                error("F_DAMAGE: 恢復種類錯誤( 只能是 jing, qi 其中之一 )。\n");

        val = (int)query("eff_" + type);
        max = (int)query("max_" + type);
        if( val + heal > max ) {
                set("eff_" + type, max);
                return max - val;
        } else {
                set( "eff_" + type, val + heal);
                return heal;
        }
}

varargs int receive_full(string type, int heal, object who)
{
        int max, val, eff;
        int num, i;
        object *enemy;

        if( heal < 0 ) error("F_DAMAGE: 恢復值為負值。\n");
        if( type!="jing" && type!="qie" )
                error("F_DAMAGE: 恢復種類錯誤( 只能是 jing, qi 其中之一 )。\n");

        // 仇恨系統
        if( objectp(who) )
        {
                enemy = this_object()->query_enemy();
                if ( num = sizeof(enemy)){
                        for (i = 0; i<sizeof(enemy);i++){
                                if (userp(enemy[i])) continue;
                                enemy[i]->add_hatred(who, heal);
                        }
                }
        }

        val = (int)query(type);
        eff = (int)query("eff_" + type);
        max = (int)query("max_" + type);

        if( eff + heal > max ) {
                set("eff_" + type, max);
                if (val + heal > query("eff_"+ type) )
                        set(type, query("eff_"+ type));
                else
                        set(type, val + heal);
                return max - eff;
        } else {
                set( "eff_" + type, eff + heal);
                if (val + heal > query("eff_"+ type) )
                        set(type, query("eff_"+ type));
                else
                        set(type, val + heal);
                return heal;
        }
}

int dps_count()
{
        int i;
        object *dp;

        dp = query_temp("defeat_player");
        if( !dp ) return 0;
        for( i = 0; i < sizeof(dp); i++ )
                if( dp[i] && living(dp[i]) ) dp[i] = 0;
        dp -= ({ 0 });
        set_temp("defeat_player", dp);
        return sizeof(dp);
}

void record_dp(object ob)
{
        object *dp;

        if( !this_object()->is_want_kill(query("id", ob)) )
                // only if I want kill ob, I will record it.
                return;
        dp = query_temp("defeat_player");
        if( !dp ) dp = ({ });
        dp += ({ ob });
        set_temp("defeat_player", dp);
}

void remove_dp(object ob)
{
        object *dp;

        if( !ob ) {
                // remove all player defeated by me
                delete_temp("defeat_player");
                return;
        }
        dp = query_temp("defeat_player");
        if( !dp ) return;
        dp -= ({ ob, 0 });
        set_temp("defeat_player", dp);
}

varargs void unconcious(object defeater)
{
        object me, riding;
        object ob, env;
        string applyer;
        string owner_id;
        int avoid;
        int n;

        me = this_object();
        env = environment(me);
        if( !living(me) ) return;
        if( wizardp(me) && query("env/immortal") ) return;

        // 朱雀重生效果 50%幾率 瞬間爆發恢復氣血精力到60%
        // 如超過60%則不恢復
        if( query("special_skill/zhuque", me) && random(10) < 5)
        {
                if( query("qi", me) < query("max_qi", me) * 3 / 5)
                {
                        set("qi", query("max_qi",me) * 3 / 5, me);
                        set("eff_qi", query("max_qi", me) * 3 / 5, me);
                }
                if( query("jingli", me) < query("max_jingli", me) * 3 / 5)
                        set("jingli", query("max_jingli", me) * 3 / 5, me);

                message_vision(HIR "\n突然間，$N身後紅光爆現，猶如傳說中的鳳凰般美妙！\n" NOR, me);
                return;
        }

        if( objectp(ob = me->query_competitor()) &&
            !ob->is_killing(query("id")) ) {
                ob->win();
                me->lost();
        }
        if( me->is_busy() ) me->interrupt_me();
        if( run_override("unconcious") ) return;
        if( is_ghost() ) return;
        if( playerp(me) && env && function_exists("user_cant_die", env) ) {
                if( environment()->user_cant_die(me) )
                        return;
        }
        avoid = (int)query_temp("apply/avoid_die");
        if( avoid > 90 ) avoid = 90;
        if( query_temp("special_skill/immortal") ||
            random(100) < avoid ) {
                set("eff_qi",query("max_qi"));
                set("qi",query("max_qi"));
                set("eff_jing",query("max_jing"));
                set("jing",query("max_jing"));
                message_vision(HIY "\n突然間，$N全身散發出一陣金光，如同浴血重生一般。\n" NOR, me); 
                COMBAT_D->report_status(this_object());
                return;
        }

        if( query_temp("is_faint") ) return;
        set_temp("is_faint", 1);

        if( !last_damage_from && (applyer = query_last_applyer_id()) ) {
                last_damage_from = UPDATE_D->global_find_player(applyer);
                last_damage_name = query_last_applyer_name();
                set_temp("last_damage_from", last_damage_from);
        }
        if( objectp(defeater) ) {
                last_damage_from = defeater;
                last_damage_name = defeater->name(1);
                set_temp("last_damage_from", last_damage_from);
        } else  defeater = last_damage_from;

        defeated_by_who = last_damage_name;
        if( defeated_by = last_damage_from ) {
                object *dp;
                // 如果此人有主，則算主人打暈的
                if( objectp(query_temp("owner", defeated_by)) ) {
                        defeated_by = query_temp("owner", defeated_by);
                        defeated_by_who = defeated_by->name(1);
                } else if( stringp(owner_id = query_temp("owner_id", defeated_by)) ) {
                        defeated_by = UPDATE_D->global_find_player(owner_id);
                        if( objectp(defeated_by) )
                                defeated_by_who = defeated_by->name(1);
                }
                if( query("qi") < 0 || query("jing") < 0 )
                        COMBAT_D->winner_reward(defeated_by, me);

                // 如果對方有意殺害我，則我憤怒，並且對方累積殺氣。
                if( playerp(me) && defeated_by->is_want_kill(query("id")) ) {
                        defeated_by->record_dp(me);
                        me->craze_of_defeated(query("id", defeated_by));
                        n = 100 + random(100) + me->query_skill("force");
                        if( n > defeated_by->query_skill("force") )
                                n = defeated_by->query_skill("force") / 2 +
                                    random(defeated_by->query_skill("force") / 2);
                        addn("total_hatred", n, defeated_by);
                }
        }
        me->remove_all_enemy(0);
        me->clear_written();
        message("system", HIR "\n你的眼前一黑，接著什麼也不知道了....\n\n" NOR,
                me);
        me->disable_player(" <昏迷不醒>");
        delete_temp("sleeped");
        if( objectp(riding = query_temp("is_riding")) ) {
                object follower;
                message_vision("$N一頭從$n上面栽了下來！\n",
                              me, riding);
                delete_temp("is_riding");
                delete_temp("is_rided_by", riding);
                riding->move(env);

                if( objectp(riding) && objectp(follower = query_temp("is_rided_follow", riding)) )
                {
                        delete_temp("is_riding_follow", follower);
                        delete_temp("is_rided_follow", riding);
                        message_vision("$N從$n上飛身跳下。\n", follower, riding);
                }
        }
        set("jing", 0);
        set("qi", 0);
        if( query("eff_jing") < 0 ) set("eff_jing", 0);
        if( query("eff_qi") < 0 ) set("eff_qi", 0);
        set_temp("block_msg/all", 1);
        call_out("revive", random(60 - query("con")) + 10);
        COMBAT_D->announce(me, "unconcious");
        // remove the user if loaded by updated
        UPDATE_D->global_destruct_player(defeater, 1);
}

varargs void revive(int quiet)
{
        object me, ob;
        object env;
        string room;

        me = this_object();
        remove_call_out("revive");
        env = environment();
        if( env ) {
                // while (env->is_character() && environment(env))
                while( environment(env) ) env = environment(env);
                if( env != environment() )
                        me->move(env);
        }
        delete("disable_type");
        delete_temp("is_faint");
        set_temp("block_msg/all", 0);
        me->enable_player();
        // write the prompt
        me->write_prompt();
        if( objectp(defeated_by) )
                defeated_by->remove_dp(me);
        if( !quiet ) {
                defeated_by = 0;
                defeated_by_who = 0;
                COMBAT_D->announce(this_object(), "revive");
                message("vision", HIY "\n慢慢地你終于又有了知覺....\n\n" NOR, me);
                // 不能把 npc 搬進安全區。
                if( !userp(this_object()) && query("no_fight", env) &&
                    stringp(room = query("startroom")) && base_name(env) != room ) {
                        ob = find_object(room);
                        if( ob ) this_object()->return_home(ob);
                        else {
                                tell_object(environment(), this_object()->name()+
                                        "匆匆忙忙的走了。\n");
                                destruct(this_object());
                                return;
                        }
                }
        }
        last_damage_from = 0;
        last_damage_name = 0;
        delete_temp("last_damage_from");
}

varargs void die(object killer)
{
        object me, env;
        object corpse, room, obj, *inv;
        mixed  riding;
        object dob;
        object ob;
        string dob_name;
        string killer_name;
        string applyer;
        object tmp_load;
        int direct_die;
        int avoid;
        int i;
        int duration;
        string follow_msg = 0;

        me = this_object();
        env = environment(me);
        delete_temp("sleeped");
        delete("last_sleep");

        // 朱雀重生效果 50%幾率 瞬間爆發恢復氣血精力到60%
        // 如超過60%則不恢復
        if( query("special_skill/zhuque", me) && random(10) < 5)
        {
                if( query("qi", me) < query("max_qi", me) * 3 / 5)
                {
                        set("qi", query("max_qi",me) * 3 / 5, me);
                        set("eff_qi", query("max_qi", me) * 3 / 5, me);
                }
                if( query("jingli", me) < query("max_jingli", me) * 3 / 5)
                        set("jingli", query("max_jingli", me) * 3 / 5, me);

                message_vision(HIR "\n突然間，$N身後紅光爆現，猶如傳說中的鳳凰般美妙！\n" NOR, me);
                return;
        }
        
        // I am lost if in competition with others
        if( ob = me->query_competitor() ) {
                ob->win();
                me->lost();
        }
        if( wizardp(me) && query("env/immortal") ) {
                delete_temp("die_reason");
                return;
        }
        if( me->is_busy() ) me->interrupt_me();
        if( run_override("die") ) return;
        if( is_ghost() ) return;
        if( playerp(me) && env && function_exists("user_cant_die", env) ) {
                if( environment()->user_cant_die(me) )
                        return;
        }
        avoid = (int)query_temp("apply/avoid_die");
        if( avoid > 90 ) avoid = 90;
        if( query_temp("special_skill/immortal") ||
            random(100) < avoid ) {
                set("eff_qi",query("max_qi"));
                set("qi",query("max_qi"));
                set("eff_jing",query("max_jing"));
                set("jing",query("max_jing"));
                message_vision(HIY "\n突然間，$N全身散發出一陣金光，如同浴血重生一般。\n" NOR, me); 
                COMBAT_D->report_status(this_object());
                return;
        }

        if( playerp(me) && env && query("no_death", env) ) {
                remove_call_out("revive");
                unconcious();
                return;
        }

        if( env && sscanf(base_name(env), "/d/newbie/%*s") ) 
        {
                set("eff_qi", query("max_qi", me) / 2, me); 
                set("qi", query("max_qi", me) / 2, me); 
                set("eff_jing", query("max_jing", me) / 2, me); 
                set("jing", query("max_jing", me) / 2, me); 
                remove_call_out("revive");
                unconcious();
                me->move("/d/newbie/luanfengang"); 
                return; 
        }


        if( !last_damage_from && (applyer = query_last_applyer_id()) ) {
                tmp_load = UPDATE_D->global_find_player(applyer);
                last_damage_from = tmp_load;
                last_damage_name = query_last_applyer_name();
                set_temp("last_damage_from", last_damage_from);
        }
        if( !killer ) {
                killer = last_damage_from;
                killer_name = last_damage_name;
        } else {
                last_damage_from = killer;
                last_damage_name = killer->name(1);
                killer_name = killer->name(1);
                set_temp("last_damage_from", last_damage_from);
        }
        // record defeater first, because revive will clear it
        if( !living(me) ) {
                direct_die = 0;
                if( userp(me) || playerp(me) )
                        revive(1);
                else
                        delete("disable_type");
        } else  direct_die = 1;

        if( direct_die && killer )
                COMBAT_D->winner_reward(killer, me);
        if( objectp(riding = query_temp("is_riding")) ) {
                object follower;
                message_vision("$N一頭從$n上面栽了下來！\n",
                               me, riding);
                delete_temp("is_riding");
                delete_temp("is_rided_by", riding);
                riding->move(env);
                if( objectp(follower = query_temp("is_rided_follow", riding)) )
                {
                        delete_temp("is_riding_follow", follower);
                        delete_temp("is_rided_follow", riding);
                        message_vision("$N從$n上飛身跳下。\n", follower, riding);
                }
        }
        // Check how am I to die
        dob = defeated_by;
        dob_name = defeated_by_who;
        if( !query_temp("die_reason") ) {
                if( playerp(me) && dob_name && killer_name &&
                    (dob_name != killer_name || dob != killer) ) {
                        if( dob && playerp(dob) && dob->is_want_kill(query("id")) ) {
                                if( !dob->query_condition("killer") ) {
                                        follow_msg = "聽說官府發下海捕文書，緝拿殺人肇事兇手" +
                                                     dob->name(1) + "。";
                                        dob->apply_condition("killer", 500);
                                } else {
                                        follow_msg = "聽說官府加緊捉拿累犯重案的肇事暴徒" +
                                                     dob->name(1) + "。";
                                        dob->apply_condition("killer", 800 +
                                                     (int)dob->query_condition("killer"));
                                }
                                set("combat/pktime", time(), dob);
                        }
                        // set the die reason
                        set_temp("die_reason", "被" +
                                 dob_name + "打暈以後，被" +
                                 (dob_name == killer_name ? "另一個" : "") +
                                 killer_name + "趁機殺掉了");
                } else if( playerp(me) && killer_name && !killer ) {
                        set_temp("die_reason", "被" + killer_name +
                                               HIM "殺害了");
                }
        }
        if( COMBAT_D->player_escape(killer, this_object()) ) {
                UPDATE_D->global_destruct_player(tmp_load, 1);
                return;
        }
        COMBAT_D->announce(me, "dead");
        if( objectp(killer) )
                set_temp("my_killer", query("id", killer));

        COMBAT_D->killer_reward(killer, me);

        UPDATE_D->global_destruct_player(tmp_load, 1);
        addn("combat/dietimes", 1);
        if( objectp(corpse = CHAR_D->make_corpse(me, killer)) )
                corpse->move(env);
        defeated_by = 0;
        defeated_by_who = 0;
        me->remove_all_killer();
        all_inventory(env)->remove_killer(me);
        set_weak(0, 1);
        if( me->in_team() )
                me->dismiss_team();
        if( userp(me) || playerp(me) ) {
                if( me->is_busy() )
                        me->interrupt_me();
                set("jing", 1); set("eff_jing", 1);
                set("qi", 1);   set("eff_qi", 1);
                ghost = 1;
                me->move(DEATH_ROOM);
                DEATH_ROOM->start_death(me);
                delete_temp("die_reason");
                delete_temp("is_faint");
                me->craze_of_die(killer ? query("id", killer) : 0);

                if( (killer && playerp(killer)) || (dob && playerp(dob)) ) {
                        set("die_protect/last_dead", time());
                        duration = (int)query("die_protect/duration");

                        if( query("combat_exp") > 20000000 && duration > 0 )
                                duration = duration * 2;
                        else    duration = 2 * 3600;
                        if( duration > 3 * 86400 )
                                duration = 3 * 86400;
                        set("die_protect/duration", duration);
                }
        } else
                destruct(me);

        if( follow_msg )
                CHANNEL_D->do_channel(find_object(COMBAT_D), "rumor",
                                      follow_msg);
}

void reincarnate()
{
        ghost = 0;
        this_object()->start_busy(0);
        set("eff_jing", query("max_jing"));
        set("eff_qi", query("max_qi"));
}

int max_food_capacity()
{
        int f;

        f = query("str") * 10 + 100;
        if( query("jingmai/finish") ) f += ZHOUTIAN_D->query_jingmai_effect("food");
        f += query("jingmai/food");
        return f;
}
int max_water_capacity()
{
        int w;

        w = query("str") * 10 + 100;
        if( query("jingmai/finish") ) w += ZHOUTIAN_D->query_jingmai_effect("water");
        w += query("jingmai/water");
        return w;
}

int heal_up()
{
        int update_flag, i;
        int scale, t, q;
        int is_user;
        int is_bigu = 0;
        mapping my;
        object me;
        mixed guard;
        int count;
        int flag = 0;
        int n;

        // Update the affect of nopoison
        if( query_temp("nopoison") )
                delete_temp("nopoison");

        me = this_object();

        if( !playerp(me) ) {
                object env;

                if( !me->open_heart_beat() ) {
                        set_heart_beat(0);
                        return 0;
                }

                if( me->is_time_ctl_ob()
                &&      !me->query_is_valid_time() ) {
                        if( objectp(env = environment()) ) {
                                env->set_check_dtime(me->query_lasting_time());
                                tell_object(env, me->query_disappear_msg());
                        }
                        destruct(me);
                        return 0;
                }
        }

        // For Business.
        if( playerp(me) )
        {
                // 戰神附體
                n = query_temp("apply/full_self", me) + query("ability1/full_self", me);
                if( n > 90 ) n = 90;
                if( !me->is_busy() && n > random(100) && random(10) < 5 )
                {
                        if( query("qi", me) < query("max_qi", me) )
                        {
                                flag = 1;
                                set("qi", query("max_qi",me), me);
                        }
                        if( query("eff_qi", me) < query("max_qi", me) )
                        {
                                flag = 1;
                                set("eff_qi", query("max_qi", me), me);                               
                        }
                        if( query("neili", me) < query("max_neili", me) )
                        {
                                flag = 1;
                                set("neili", query("max_neili", me), me);
                        }

                        if( flag )
                        tell_object(me, HIR "你全身紅光爆現，猶如戰神附體般恢復了氣血和內力！\n" NOR);
                }
                
                if( query("reborn/times") && me->query_skill_mapped("force") == "xiantian-gong" )
                {
                        if( query("neili") < query("max_neili") * 70 / 100 )
                        {
                                set("neili", query("max_neili"));
                                tell_object(me, HIC "你先天功運轉，頓時真氣流動生生不息，用之不歇。\n" NOR);
                        }
                }
                if( query("reborn/times") && (me->query_skill_mapped("force") == "taiji-shengong"
                ||  me->query_skill_mapped("cuff") == "taiji-quan" || me->query_skill_mapped("sword") == "taiji-jian"
                ||  me->query_skill_mapped("blade") == "taiji-dao") )
                {
                        if( query("eff_qi") < query("max_qi") )
                        {
                                count = (me->query_skill("taiji-shengong",1)+me->query_skill("taoism",1))*10;
                                addn("eff_qi", count, me);
                                if( query("eff_qi") > query("max_qi") ) set("eff_qi",query("max_qi", me), me);
                                addn("qi", count, me);
                                if( query("qi") > query("max_qi") ) set("qi",query("max_qi", me), me);
                                tell_object(me, HIC "你體內陰陽太極運轉，頓時化陰陽魚之力治癒自身受傷血氣。\n" NOR);
                        }
                }
                me->update_all_wares();
        }

        // Am I in prison ?
        if( me->is_in_prison() ) {
                me->update_in_prison();
                return 1;
        }

        is_user = playerp(me);
        is_bigu = objectp(present("bigu fu", me)) || query("reborn/times", me) >= 3;
        scale = living(me) ? 1 : (is_user ? 4 : 8);
        update_flag = 0;
        my = this_object()->query_entire_dbase();

        if( !is_user ||
            environment() &&
            !environment()->is_chat_room() &&
            (!stringp(my["doing"]) && interactive(me) || my["doing"] == "scheme") ) {
                if( my["water"] > 0 && !is_bigu ) { my["water"] -= 1; update_flag++; }
                if( my["food"] > 0 && !is_bigu ) { my["food"] -= 1; update_flag++; }

                if( my["water"] < 1 && is_user && !is_bigu )
                        return update_flag;

                if( (guard = query_temp("guardfor")) &&
                    (!objectp(guard) || ! guard->is_character()) ) {
                        if( my["jing"] * 100 / my["max_jing"] < 50 ) {
                                tell_object(me, "你覺得太累了，需要放鬆放鬆了。\n");
                                command("guard cancel");
                                return update_flag;
                        }

                        my["jing"] -= 30 + random(20);
                        switch (random(8))
                        {
                        case 0: message_vision("$N緊張的盯著四周來往的行人。\n", me);
                                break;

                        case 1: message_vision("$N打了個哈欠，隨即振作精神繼續觀察附近情況。\n", me);
                                break;

                        case 2: message_vision("$N左瞅瞅，右看看，不放過一個可疑的人物。\n", me);
                                break;

                        case 3: message_vision("$N打起精神細細的觀察周圍。\n", me);
                                break;
                        }
                        update_flag++;
                        return update_flag;
                }

                t = (my["con"] + my["max_jingli"] / 10) / scale;
                my["jing"] += t;

                if( my["jing"] >= my["eff_jing"] ) {
                        my["jing"] = my["eff_jing"];
                        if( my["eff_jing"] < my["max_jing"] ) {
                                my["eff_jing"] ++;
                                // 裝備系統附加屬性
                                if( q = (query_temp("apply/ref_jing") + query("ability1/ref_jing")) ) {
                                        my["eff_jing"] += q;
                                }
                                update_flag++;
                        }
                } else update_flag++;

                if( !me->is_busy() ) {
                        t = (my["con"] * 2 + my["max_neili"] / 20) / scale;
                        my["qi"] += t;
                }
                if( my["qi"] >= my["eff_qi"] ) {
                        my["qi"] = my["eff_qi"];
                        if( my["eff_qi"] < my["max_qi"] ) {
                                my["eff_qi"] ++;
                                // 裝備系統
                                if( q = (query_temp("apply/ref_qi") + query("ability1/ref_qi")) ) {
                                        my["eff_qi"] += q;
                                }
                                update_flag++;
                        }
                } else update_flag++;

                if( my["food"] < 1 && is_user && !is_bigu )
                        return update_flag;

                if( my["max_jingli"] && my["jingli"] < my["max_jingli"] ) {
                        t = my["con"] + (int)me->query_skill("force") / 6;
                        my["jingli"] += t;
                        if (my["jingli"] > my["max_jingli"])
                                my["jingli"] = my["max_jingli"];
                        update_flag++;
                }

                if( my["max_neili"] && my["neili"] < my["max_neili"] ) {
                        t = my["con"] * 2 + (int)me->query_skill("force") / 3;
                        my["neili"] += t;
                        if( my["neili"] > my["max_neili"] )
                                my["neili"] = my["max_neili"];
                        update_flag++;
                }

        }
        return update_flag;
}

mapping query_hatred_list()
{
        return hatred_list;
}

object query_max_hatred() 
{
        object *list;
        int i,num,max,flag;
        
        max = 0;
        if( mapp(hatred_list) ) 
        {
                list = keys(hatred_list);
                if( i = sizeof(hatred_list) ) 
                {
                        while (i--) 
                        {
                                if( !objectp(list[i]) ) 
                                {
                                        list[i] = 0;
                                        continue;
                                }
                                
                                if( hatred_list[list[i]] < 0 )
                                        hatred_list[list[i]] = 0;
                                        
                                if( !this_object()->is_fighting(list[i])
                                        || environment() != environment(list[i]))
                                        continue;
                                        
                                if( hatred_list[list[i]] > max ) 
                                {
                                        max = hatred_list[list[i]];
                                        num = i;
                                        flag = 1;
                                }
                        }
                        if( flag )
                                return list[num];
                        else
                                return 0;
                }
        }
}

// 查詢某一對手的仇恨
int query_hatred(object enemy)
{
        if (mapp(hatred_list))
        {
                return  hatred_list[enemy];
        }
        return 0;

}

// 增加仇恨
int add_hatred(object who, int amount)
{

        if( !mapp(hatred_list) )
                hatred_list = ([ who : amount ]);
        else
                hatred_list[who] = (hatred_list[who] + amount)>0
                                        ? hatred_list[who] + amount:0;

        return 1;
}

// 移除仇恨
void remove_hatred()
{
        hatred_list = ([]);
}

mapping query_combine_damage_list()
{
        int i,j,n;
        mapping list;
        object *a, *team;
        int *b;

        n = sizeof(hatred_list);
        if( n < 1 ) return 0;

        a = keys(hatred_list);
        b = allocate(n);
        list = allocate_mapping(n);

        for( i=0;i<n;i++ ) 
        {
                if( !objectp(a[i]) ) continue;
                if( b[i] ) continue; // 隊伍中成員統計過

                list[a[i]] = hatred_list[a[i]];

                team = a[i]->query_team();
                if( !team || !sizeof(team) )  
                        continue;

                for( j=i+1;j<n;j++ ) 
                {
                        if( !objectp(a[j]) ) continue;
                        if( a[i]->is_team_member(a[j]) ) 
                        {
                                list[a[i]] += hatred_list[a[j]];
                                b[j] = 1;
                                continue;
                        }
                }
        }

        return list;
}

object query_max_damage_from()
{
        mapping list;
        int i,n,max;
        object *a;

        max = 0;

        if( sizeof(hatred_list)<1 ) return 0;

        list = query_combine_damage_list();
        if( sizeof(list) < 1 ) return 0;

        a = keys(list);
        n = 0;

        for( i=0;i<sizeof(list);i++ )
        {
                if( !a[i] || !objectp(a[i])) 
                        continue;
                if( list[a[i]]> max )
                {
                        n = i;
                        max = list[a[i]];
                }
        }
        return a[n];
}

