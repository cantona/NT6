// This program is a part of NT MudLIB
// Written by Lonely@nitan.org
// warcraft.c
// 魔獸系統
        // 智慧型（青龍.木）     可增加主人迴避率及冥思速度
        // 攻擊型（白虎.金）     可增加主人命中率及體會上限
        // 防禦型（玄武.水）     可增加主人防禦力及內力上限
        // 靈動型（朱雀.火）     可增加主人攻擊力及潛能上限
        // 均衡型（麒麟.土）     可增加主人攻擊力及精力上限

// 金的明亮、木的深沉、水的清冷、火的炙熱、土的厚實。
/*
金  系  中級防禦（描述：你的身上金光亂舞，使對手攻擊無處着手
        。）
木  系  中級防禦（描述：眼見就要打在你的身上，卻發現象打在木
        頭上，被強大的彈力震的身形不穩，在原地打了幾個圈。）
水  系  中級防禦（描述：對手的攻擊打在身上就象石牛入海，不知
        所終。）
火  系  中級防禦（描述：熊熊的火焰使對手渾身灼熱，攻擊還未遞
        到身前就自己縮了回去。）
土  系  中級防禦（描述：對手的攻擊打在身上，卻象以卵擊石般攻
        擊到厚實的大地上軟弱無力。）
神  獸  高級防禦（有戰鬥中自動氣血恢復功能，對手無從攻擊。）
獸  王  太初、太始，太初是攻擊系，在防禦的同時有自動攻擊功能，
        太始是防禦系，可防護任何屬性的攻擊。
*/

#include <ansi.h>
#include <name.h>
#include <command.h>
#include <combat.h>

inherit NPC;
inherit F_NOCLONE;
inherit F_OBSAVE;
inherit F_SSERVER;

void remove(string euid)
{
        object env;
        
        if( is_fighting() ) remove_all_enemy(1);
        env = environment();
        if( objectp(env) && interactive(env) ) delete_temp("is_riding", env);
        save();
}

int is_warcraft() { return 1; }
int is_stay_in_room() { return 1; }

int is_owner(object me) { return query_temp("owner") == query("id", me); }
string chinese_s(mixed arg)
{
      if (arg == "白虎")  return HIY "金" NOR;
      if (arg == "青龍")  return WHT "木" NOR;
      if (arg == "玄武")  return HIG "水" NOR;
      if (arg == "朱雀")  return HIR "火" NOR;
      if (arg == "麒麟")  return YEL "土" NOR;
}

void create()
{
        seteuid(getuid());

        set_name("魔幻獸", ({ "warcraft" }));
        set("long", "玩家可以騎上它去指定的地方(rideto)。\n");
        set("race", "野獸");
        set("race_type", WHT "青龍" NOR);
        set("unit", "只");
        set("str", 30);
        set("int", 30);
        set("con", 30);
        set("dex", 30);
        set("no_sell", "這你也要賣？你忘記當初與它的血之盟約嗎？");
        set("owner", "lonely");
        set("owner_name", "高處不勝寒");
        set("limbs", ({ "頭部", "身體", "前心", "後背", "尾巴" }) );
        set("verbs", ({ "bite", "hoof" }) );

        set("qi", 300);
        set("max_qi", 300);
        set("jing", 100);
        set("max_jing", 100);
        set("neili", 100);
        set("max_neili", 100);
        set("jingli", 100);
        set("max_jingli", 100);
        set("shen_type", 0);
        set("combat_exp", 50000);
        set("attitude", "peaceful");
        set("obedience", 2);
        set("ridable", 1);

        set_skill("dodge", 100);
        set_skill("unarmed", 100);
        set_skill("parry", 100);
        set_skill("force", 100);

        set_temp("apply/attack", 100);
        set_temp("apply/unarmed_damage", 100);
        set_temp("apply/defence",100);
        set_temp("apply/armor", 200);
        set_temp("apply/dodge", 100);
        set_temp("apply/parry", 100);
        if (! check_clone()) return 0;
        restore();
        setup();

        keep_heart_beat();
}

varargs string short(int raw)
{
        string str;

        str = ::short();
        str += " ≈" + query("race_type") + "≈";
        return str;
}

string get_level()
{
        string level;

        if( query("level")/10 < 9 )
                level = CHINESE_D->chinese_number(query("level")/10+1) + "級" + CHINESE_D->chinese_number(query("level")%10) + "階";
        else
        if( query("level")/10 == 9 )
                level = HIM "上古神獸" NOR;
        else
                level = HIY "遠古聖獸" NOR;

        // 太始、太初
        return level;
}

string long()
{
        string result;
        string level;

        result = query("long");

        level = get_level();

        result += "\n";
        result += HIW "幻獸等級：" + level + "\n" NOR;
        result += HIW "魔力屬性：" + chinese_s(query("race_type")) + "\n" NOR;
        result += HIW "魔力數值：" + query("magic/power")  + "\n" NOR;
        result += "\n";

        return result;
}

void init()
{
        if( query("id", this_player()) == query("owner") ) {
                add_action("do_modify", "modify");
                add_action("do_teach", "teach");
                add_action("do_shape", "shape");
        }

}

void del_hiding(object me, object target)
{

        if( !objectp(me) && !objectp(target) ) return;

        if( objectp(me) )
                delete_temp("hiding_kuihua", me);

        if( objectp(target) )
                target->clear_condition("no_perform");

        return;
}

void del_protect(object me)
{
        if( !objectp(me) ) return;

        delete_temp("protect_xuanwu", me);

        addn_temp("reduce_damage", -90, me);

        return;
}

void heart_beat()
{
        object owner, ob, target;
        object env, env1, env2;

        ob = this_object();

        // 自動回覆狀態
        if( !is_fighting() && (query("qi") < query("max_qi") ||
            query("jing") < query("max_jing") ||
            query("eff_qi") < query("max_qi") ||
            query("eff_jing") < query("max_jing")) )
                    full_self();

        // 如果主人下線則自動保存後離開
        if( !(env1=environment()) || !objectp(owner = find_player(query("owner", ob))) ) {
                save();
                message_vision("$N一閃就不見了。\n", ob);
                destruct(ob);
                return;
        }

        if( !(env2=environment(owner)) ) return;
        // 如果主人不在同一地圖則移動主人面前
        // 動作狀態；僅僅跟隨(follow)、保護(guard)
        if( living(ob) && (query_temp("comedby", owner) == ob || query("actions", ob)) &&
            env1 != env2 && env1 != owner && !query("no_magic", env2) ) {
                if( is_fighting() ) remove_all_enemy(1);
                ob->move(env2);
                message_vision("忽然一陣旋風襲過，$n" NOR "已出現在這裏。\n", owner, ob);

                // 自動跟隨
                ob->set_leader(owner);

                // 自動保護，如果是僅跟隨狀態則不保護
                if( query("actions", ob) == "guard" ) {
                        GUARD_CMD->main(ob, owner);
                }
        }

        env = environment();
        if( env != owner && env != env2 )
                ;
        else {

        // 氣血小於保護限制則隱藏
        if( query("env/wimpy") > 0 ) {
                if (query("qi") * 100 / query("max_qi") <= query("env/wimpy") ) {
                        if( env == owner ) {
                                delete_temp("is_riding", owner);
                                delete_temp("is_rided_by");
                        }
                        // 隱藏
                        save();
                        message_vision(HIR "\n$N" HIR "迅速移動到" + owner->name() + HIR "身後，躲了起來。\n" NOR, ob);
                        destruct(ob);

                        return;
                }
        }

        // 同伴技能=========
        // 療傷，擾亂，清醒，震懾，防護
        // 加生命、加殺氣、加命中閃避
        // A、護衞戰鬥B、減少傷害C、增加傷害D、傷害豁免E、虛弱狀態

        // 麒麟--治療
        if( (query("max_qi", owner) > query("qi", owner) || query("max_qi", owner) > query("eff_qi", owner))
            && query("race_type") == "麒麟" ) {
                if( random(15) < query("level")/10 ) {
                        tell_object(owner, HIY + ob->name() + HIY "全身閃出火紅般的光芒照向你，你感覺氣血有所恢復。\n" NOR);
                        addn("qi", 500 + random(query("magic/power"))*200, owner);
                        addn("eff_qi", 200 + random(query("magic/power"))*80, owner);
                        if( query("eff_qi", owner) > query("max_qi", owner) ) set("eff_qi", query("max_qi", owner), owner);
                        if( query("qi", owner) > query("max_qi", owner) ) set("qi", query("max_qi", owner), owner);
                }
        }

        // 白虎--令對手忙亂
        if( query("race_type") == "白虎" && owner->is_fighting() ) {
                int time_busy;
                target = offensive_target(owner);
                if( objectp(target) && random(15) < query("level")/10 && !target->is_busy() ) {
                        message_vision(HIG "$N" HIG "長嘶一聲，震耳欲聾，沖天而起，直撲向$n" HIG "$n" HIG
                                       "被這突如其來的變故弄得手忙腳亂。\n" NOR, ob, target);
                        time_busy = 1 + random(1 + query("level")/10);
                        if( time_busy > 5 ) time_busy = 5;
                        target->start_busy(time_busy);
                }
        }

        // 朱雀--降低主人忙亂時間
        if( query("race_type") == "朱雀" && owner->is_fighting() ) {
                int int_busy;
                if( owner->is_busy() && random(15) < query("level")/10 ) {
                        tell_object(owner, HIM + ob->name() + HIM "扇動着巨大的翅膀，狂風四起，你感覺突然見輕鬆了許多。\n" NOR);

                        int_busy = 1 + random(1 + query("level")/10);
                        owner->interrupt_me(owner, int_busy);
                }
        }

        // 青龍--震懾對手，令其暫時無法攻擊，此效果時間隨機為3-7秒
        if( query("race_type") == "青龍" && owner->is_fighting() ) {
                target = offensive_target(owner);
                if( objectp(target) && random(15) < query("level")/10 && !query_temp("hiding_kuihua", owner) ) {
                        message_vision(HIR "$N" HIR "對着$n" HIR"一聲長嘯，$n" HIR "突覺心神俱裂，難受無比。\n" NOR,
                                       ob, target);

                        set_temp("hiding_kuihua", 1, owner);
                        target->apply_condition("no_perform", 7);
                        remove_call_out("del_hiding");
                        call_out("del_hiding", 3 + random(5), owner, target);
                }
        }

        // 玄武--防護
        // 玄武--減少主人傷害
        if( query("race_type") == "玄武" && owner->is_fighting() ) {
                if( random(15) < query("level")/10 && !query_temp("protect_xuanwu", owner) ) {
                        tell_object(owner, HIM + ob->name() + HIM "發出一道耀眼的光芒，將你全身籠罩在內，你感覺到全身表面有層龜殼般保護。\n" NOR);
                        addn_temp("reduce_damage", 90, owner);
                        set_temp("protect_xuanwu", 1, owner);
                        remove_call_out("del_protect");
                        call_out("del_protect", 3 + random(5), owner);
                }
        }
        }

        ::heart_beat();
}

int do_modify(string arg)
{
        string item, msg;
        object me = this_player();

        if( !arg || sscanf(arg,"%s %s", item, msg) != 2 )
                return notify_fail("SYNTAX: modify 款項 內容\n");

        if( item == "flee" ) {
                set("env/wimpy", atoi(msg));
                write("ＯＫ\n");
                save();
                return 1;
        }

        if( item == "actions" ) {
                if( msg != "follow" && msg != "guard" )
                        return notify_fail("你只可以設置為follow或者guard狀態。\n");

                set("actions", msg);
                set_temp("comedby", this_object(), me);
                write("ＯＫ\n");
                save();
                return 1;
        }

        if( CHINESE_D->check_control(msg) )
                return notify_fail("描述不可有控制符！\n");

        if( CHINESE_D->check_space(msg) )
                return notify_fail("描述必需不含空格！\n");

        if( CHINESE_D->check_return(msg) )
                return notify_fail("描述必需不含回車鍵！\n");

        msg = trans_color(msg, 3);
        switch(item)
        {
        case "desc":
                if( CHINESE_D->check_length(msg) > 100 )
                        return notify_fail("描述太長！\n");
                set("long", msg+NOR"\n");
                write("ＯＫ\n");
                save();
                return 1;
        case "nickname" :
                if( CHINESE_D->check_length(msg) > 20 )
                        return notify_fail("描述太長！\n");
                set("nickname",msg+NOR);
                write("ＯＫ\n");
                save();
                return 1;
        case "title" :
                if( CHINESE_D->check_length(msg) > 20 )
                        return notify_fail("描述太長！\n");
                set("title",msg+NOR);
                write("ＯＫ\n");
                save();
                return 1;
        case "arrive_msg" :
                if( CHINESE_D->check_length(msg) > 60 )
                        return notify_fail("描述太長！\n");
                set("arrive_msg",msg+NOR);
                write("ＯＫ\n");
                save();
                return 1;
        case "leave_msg" :
                if( CHINESE_D->check_length(msg) > 60 )
                        return notify_fail("描述太長！\n");
                set("leave_msg",msg+NOR);
                write("ＯＫ\n");
                save();
                return 1;

        }
        return notify_fail("你要修改什麼？\n");

}

int do_teach(string arg)
{
        object me;
        int gin_cost,amount;
        int myskill, itskill;

        me = this_player();

        if( !myskill = me->query_skill(arg, 1) )
                return notify_fail("這項技能你好像還不會呢！\n");

        if( arg != "unarmed" && arg != "parry" && arg != "dodge" && arg != "force" )
                return notify_fail("它學不會這項技能的！\n");

        itskill = query_skill(arg,1);
        if( myskill <= itskill )
                return notify_fail(name()+"以嘲笑的目光望着你。\n");

        if( query("potential", me) - query("learned_points", me) < 1 )
                return notify_fail("你的潛能不夠！\n");

        gin_cost = 100/ (int) query_int();
        if( (int)query("jing", me) < gin_cost )
                return notify_fail("你顯然太累了沒有辦法教！\n");

        me->receive_damage("jing", gin_cost);
        addn("potential", -1, me);
        amount = (int)me->query_int() * (int) query_int();
        message_vision(sprintf("$N不厭其煩地教$n「%s」。\n", to_chinese(arg)), me, this_object());

        if( random(100) < query("obedience") )
                command("emote 很不情願地哼了一聲。");
        else
        {
                improve_skill(arg, amount);
                message_vision(sprintf("$N似乎真的學會了一些「%s」！\n", to_chinese(arg)), this_object());
        }
        return 1;

}

string status_color(int current, int max)
{
        int percent;

        if( max>0 ) percent = current * 100 / max;
                else percent = 100;
        if( percent > 100 ) return HIC;
        if( percent >= 90 ) return HIG;
        if( percent >= 60 ) return HIY;
        if( percent >= 30 ) return YEL;
        if( percent >= 10 ) return HIR;
        return RED;
}
/*
int do_shape(string arg)
{
        mapping my;
        string shape;
        mixed at_pt, pa_pt, do_pt;

        my = query_entire_dbase();

        printf("精氣： %s%3d/ %3d %s(%3d%%)"NOR"  氣血： %s%3d/ %3d %s(%3d%%)\n"+NOR,
                status_color(my["jing"], my["eff_jing"]), my["jing"],my["eff_jing"],
                status_color(my["eff_jing"], my["max_jing"]),     my["eff_jing"] * 100 / my["max_jing"],
                status_color(my["qi"], my["eff_qi"]), my["qi"], my["eff_qi"],
                status_color(my["eff_qi"], my["max_qi"]),     my["eff_qi"] * 100 / my["max_qi"]
        );

        printf("食物： %d\t\t飲水： %d\n",
        my["food"], my["water"]);
        printf("主人： %s\t\t等級： %s\n",
        my["owner"],get_level());
        printf("經驗： %d\t\t殺氣： %d\n",
        my["combat_exp"],my["bellicosity"]
        );
        printf("智慧： %d\t\t體質： %d\n",
        query_int(), query_con()
        );
        printf("速度： %d\t\t力量： %d\n",
        query_dex(), query_str()
        );

        at_pt= COMBAT_D->skill_power(this_object(), "unarmed", SKILL_USAGE_ATTACK);
        pa_pt= COMBAT_D->skill_power(this_object(), "parry", SKILL_USAGE_DEFENSE);
        do_pt= COMBAT_D->skill_power(this_object(), "dodge", SKILL_USAGE_DEFENSE);
        printf("攻擊： %d\t\t防禦： %d\n\n",
        at_pt+1, pa_pt/2+do_pt/2+1
        );
        return 1;
}
*/

// 顯示同伴狀態
int do_shape(string arg)
{
        object ob;
        string line = HIC "=-------------------------------------=\n" NOR;
        string str;
        mixed at_pt, pa_pt, do_pt;
        string actions;

        ob = this_object();


        actions = query("actions", ob);
        if( !stringp(actions) )

                actions = "自由";
        else
                actions == "follow" ? "僅跟隨" : "保護";

	str = HIY + ob->name() + HIY "狀態屬性如下(" + HIR + actions + HIY + ")：\n" NOR;
        str += line;

        str += HIR "等級：" + sprintf("%s",get_level()) + "\n" NOR;
        str += HIR "屬性：" + sprintf("%s",chinese_s(query("race_type"))) + "\n" NOR;
        str += HIR "魔值：" + sprintf("%d",query("magic/power")) + "\n" NOR;

        str += HIW "經驗：" + sprintf("%d", query("combat_exp")) + "\n" + NOR;
        str += HIW "悟性：" + sprintf("%-22d速度：%d", query("int"), query("dex")) + "\n" + NOR;
        str += HIW "臂力：" + sprintf("%-22d根骨：%d", query("str"), query("con")) + "\n" + NOR;

        str += HIC "生命：" + sprintf("%d", query("qi")) + "/" + sprintf("%d", query("eff_qi")) + "\n" NOR;
        str += HIC "內力：" + sprintf("%d", query("neili")) + "/" + sprintf("%d", query("max_neili")) + "\n" NOR;
        str += HIC "精氣：" + sprintf("%d", query("jing")) + "/" + sprintf("%d", query("eff_jing")) + "\n" NOR;
        str += HIC "精力：" + sprintf("%d", query("jingli")) + "/" + sprintf("%d", query("max_jingli")) + "\n" NOR;

        at_pt= COMBAT_D->skill_power(this_object(), "unarmed", SKILL_USAGE_ATTACK);
        pa_pt= COMBAT_D->skill_power(this_object(), "parry", SKILL_USAGE_DEFENSE);
        do_pt= COMBAT_D->skill_power(this_object(), "dodge", SKILL_USAGE_DEFENSE);

        str += HIM "攻擊：" + sprintf("%d", at_pt+1) + "\n" NOR;
        str += HIM "防禦：" + sprintf("%d", pa_pt/2+do_pt/2+1) + "\n" NOR;

        str+= line;

        write(str);
        return 1;
}

varargs mixed set(string idx, mixed para, object ob)
{
        int i, j, lvl, level;

        if( !ob )
                ob = this_object();

        if( idx == "combat_exp" && para ) {
                if( para > query("combat_exp") ) {
                        level = query("level");
                        if( !level || level < 1 ) level = 1;

                        for (i = level; ;i++) {
                                if( (i + 1) * (i + 1) * (i + 1) > (para / 10000) ) {
                                        lvl = i;
                                        break;
                                }
                        }

                        if( lvl > level ) {
                                j = lvl - level;
                                set("level", lvl);

                                addn("max_jingli", 1000*j);
                                addn("max_neili", 2000*j);
                                addn("max_jing", 500*j);
                                addn("max_qi", 300*j);
                                addn("int", j);
                                addn("str", j);
                                addn("con", j);
                                addn("dex", j);
                                set("magic/power", 100*lvl);

                                add_skill("dodge", 50*j);
                                add_skill("parry", 50*j);
                                add_skill("unarmed", 50*j);
                                add_skill("force", 50*j);

                                message_vision(HIY "$N" HIY "身忽的泛起紅光，無數道紫光隱入$N" HIY "的身體，不見了！\n" NOR, ob);
                                if( lvl%10 == 0 )
                                        message_vision(HIY "突然天空出現一道玄光與$N" HIY "身泛起的紅光相接，$N" HIY "全體通紅！\n" NOR, ob);
                        }
                }
                return efun::set(idx, para);
        } else
                return efun::set(idx, para);
}

mixed add(string prop, mixed data)
{
        string para;
        mixed old;
        int level;

        if( prop == "combat_exp" ) {
                if( !(old = query(prop)) )
                        return set(prop, data);

                if( data < 1 )
                        return efun::set(prop, old + data);

                level = query("level");
                if( !level || level < 1 ) level = 1;

                return set(prop, old + data);
        } else
                return efun::addn(prop, data);
}

// 召喚接口
int receive_whistle(object me)
{
        object env, follower;
        int    period;

        if( (env = environment()) && env == me )
        {
                write(name() + "你不是正騎着嗎？你召喚個什麼勁？\n");
                return 1;
        }

        if( env == environment(me) )
        {
                if( is_fighting() )
                        remove_all_enemy(1);
                message_vision(name() + "一閃就不見了。\n", me);
                period = time() - ((int) query("last_save"));
                if( period < 0 || period > 900 )
                {
                        set("last_save", time());
                        save();
                }
                destruct(this_object());
                return 1;
        }
        else
        {
                if( env )
                {
                        if( env->is_character() && environment(env) )
                                env = environment(env);

                        message("vision", HIG "突然" + name() + HIG "化作一道光芒，"
                                HIG "瞬間消失了！\n\n" NOR, env);

                        if( interactive(env = environment()) )
                        {
                                delete_temp("is_riding", env);
                                delete_temp("is_rided_by");
                                tell_object(env, HIM + name() +
                                        HIM "忽然離你而去了！\n" NOR);
                                // 讓所有的人也下馬
                                if (objectp(follower = query_temp("is_rided_follow", this_object())))
                                {
                                        delete_temp("is_riding_follow", follower);
                                        delete_temp("is_rided_follow");
                                        tell_object(follower, HIM + name() + HIM "忽然離你而去了！\n" NOR);
                                }
                        }
                }
                message_vision(HIG "$n" HIG "不知從哪裏竄到$N" HIG "面前！\n\n" NOR,
                        me, this_object());
        }

        move(environment(me));

        if( environment() != environment(me) )
                return 0;

        return 1;
}

varargs void die(object killer)
{
        object owner;
        int exp;


        owner = UPDATE_D->global_find_player(query("owner"));

        if( !objectp(owner) )
                return ::die(killer);

        message_vision(HIR "$N" HIR "哀傷地説道：對不起，主人，我不能再保護你了，珍重！\n" NOR, this_object());
        tell_object(owner, HIG "你的魔獸死亡了，請到張天師處［ask zhang about 魔獸復活］來複活你的魔獸！\n" NOR);
        set("warcraft/status", "died", owner);

        UPDATE_D->global_destruct_player(owner, 1);

        // 死亡掉經驗2%
        exp = query("combat_exp");
        add("combat_exp", -exp*2/100);

        // 狀態復原
        full_self();

        save();
        destruct(this_object());

        return;
}

varargs void unconcious(object defeater)
{
        die(defeater);
}

mixed valid_damage(object ob, object me, int damage, object weapon)
{
        mixed result;

        result = ([ "damage": -query("magic/power") ]);

        result += (["msg" :   HIC "$N" HIC "的攻擊打在$n"
                              HIC "厚實的護甲上。\n" NOR ]);

        return result;
}

mixed hit_ob(object me, object ob, int damage_bouns)
{

        ob->receive_wound("qi", 200 + query("magic/power"), me);

        return sort_msg(HIR "$N" HIR "張嘴朝着$n，" HIR "喉嚨深處微"
               "微閃出光芒，一團約十公分大小的火球，自$N"
               HIR "嘴中射出，飛快的擊中$n" HIR "的胸口，"
               "$n" HIR "蹬蹬蹬的倒退了幾步，跪了下來。\n" NOR);
}

/*
int do_look(string target)
{
        object ob, me;

        string msg;

        ob = this_object();


        if (! id(target))
                return notify_fail("你要看什麼？");

        if (! stringp(msg = query("look_msg", ob)) ) return 1;

        message_sort(HIC + "\n" + msg + "\n" NOR, this_object());

        return 1;
}

int accept_ask(object who, string topic)
{
        // 設置的回答列表
        object ob;

        mapping ans;
        string *key_ans;
        string msg;

        if (! sizeof(topic))return 0;

        ob = this_object();
        ans = query("answer", ob);

        if (! sizeof(ans))return 0;

        key_ans = keys(ans);

        if (! sizeof(key_ans))return 0;

        if (member_array(topic, key_ans) == -1)return 0;

        return ans[topic];

}

// whichask 指令返回的列表
mixed whichask()
{
        object ob;

        mapping ans;
        string *key_ans;
        string msg;
        int i;

        ob = this_object();
        ans = query("answer", ob);

        if (! sizeof(ans))return 0;

        key_ans = keys(ans);

        if (! sizeof(key_ans))return 0;

        msg = "";
        for (i = 0; i < sizeof(key_ans); i ++)
        {
                if (i < 10)
                        msg = msg + sprintf(" %d", i + 1) + ". " + key_ans[i] + "\n";
                else
                        msg = msg + sprintf("%d", i + 1) + ". " + key_ans[i] + "\n";
        }


        return msg;
}

// 查詢設置的對話列表
mixed answer_list()
{
        object ob;

        mapping ans;
        string *key_ans;
        string msg;
        int i;

        ob = this_object();
        ans = query("answer", ob);

        if (! sizeof(ans))return 0;

        key_ans = keys(ans);

        if (! sizeof(key_ans))return 0;

        msg = "";
        for (i = 0; i < sizeof(key_ans); i ++)
        {
                if (i < 10)
                {
                        msg += HIG + sprintf(" %d", i + 1) + ". " + "ask    : " + key_ans[i] + "。\n" NOR;
                        msg += HIR "    answer : " + ans[key_ans[i]] + "\n\n" NOR;
                }
                else
                {
                        msg += HIG + sprintf("%d", i + 1) + ". " + "ask    : " + key_ans[i] + "。\n" NOR;
                        msg += HIR "   answer : " + ans[key_ans[i]] + "\n\n" NOR;
                }
        }


        return msg;
}

int delete_answer(int n)
{
        object ob;

        mapping ans;
        string *key_ans;
        int i;

        ob = this_object();

        ans = query("answer", ob);

        if (! sizeof(ans)) return notify_fail("（A）無法刪除該信息。\n");

        key_ans = keys(ans);

        if (! sizeof(key_ans)) return notify_fail("（B）無法刪除該信息。\n");

        if (n > sizeof(key_ans) + 1)
                return notify_fail("（C）無法刪除該信息。\n");

        if (n < 1)
                return notify_fail("（D）無法刪除該信息。\n");

        // 開始刪除
        map_delete(ans, key_ans[n - 1]);
        set("answer", ans, ob);
        write("刪除完畢！\n");
        return 1;
}
*/

// 接受存盤數據的接口函數
int receive_dbase_data(mixed data)
{
        if( !mapp(data) )
                return 0;

        this_object()->set_dbase(data);

        return 1;
}

// 進行保存數據的接口函數
mixed save_dbase_data()
{
        mapping data;

        data = this_object()->query_entire_dbase();

        return data;
}
