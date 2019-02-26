// giftd.c

#include <ansi.h>
#include <quest.h>

inherit F_DBASE;
inherit F_CLEAN_UP;

// 定義提供給外部調用的接口函數
varargs public void bonus(object who, mapping b, int flag);
varargs public void freequest_bonus(object who);
varargs public void gift_bonus(object who, mapping b);
varargs public void work_bonus(object who, mapping b);
varargs public void war_bonus(object who, mapping b);
varargs public void battle_bonus(object who, mapping b);
public void delay_bonus(object who, mapping b);
public void delay_freequest_bonus(object who);
public void delay_gift_bonus(object who, mapping b);
public void delay_work_bonus(object who, mapping b);
public void delay_war_bonus(object who, mapping b);
public void delay_battle_bonus(object who, mapping b);

void create()
{
        seteuid(getuid());
        set("channel_id", "獎勵精靈");
}

// override set function
varargs mixed set(string idx, mixed para, object who)
{
        int i, n, now_lvl, old_lvl;

        if( idx == "combat_exp" )
        {
                if( para > query("combat_exp", who) )
                {
                        old_lvl = query("level", who);
                        if( !old_lvl || old_lvl < 1 ) old_lvl = 1;

                        // 等級封印
                        if( !UPDATE_D->can_improve_level(old_lvl) &&
                            para > to_int(pow(old_lvl, 3.0)*10000) )
                        {
                                //tell_object(ob, HIR "由於你處於等級封印中，你的實戰經驗無法提升！\n" NOR);
                                return;
                        }

                        for (i = old_lvl; ;i++)
                        {
                                if( to_int(pow(i+1, 3)) > (para / 10000) )
                                {
                                        now_lvl = i;
                                        break;
                                }
                        }

                        if( now_lvl > old_lvl )
                        {
                                n = now_lvl - old_lvl;
                                efun::set("level", now_lvl, who);

                                addn("ability", 4 * n, who);
                                addn("experience", 20 * n, who);
                                addn("potential", 200 * n, who);
                                addn("magic_points", 20 * n, who);

                                tell_object(who, HIY "只見一道紅光飛進你的體內，你的人物等級提升了！\n" +
                                        "此次升級，你獲得了" + chinese_number(4 * n) +
                                        "點能力點、" + chinese_number(200 * n) +
                                        "點潛能、" + chinese_number(20 * n) +
                                        "點實戰體會、" + chinese_number(20 * n) +
                                        "點靈慧！\n" NOR);

                                UPDATE_D->improve_valid_level(who, now_lvl); 
                        }
                }
        } else
        if( idx == "xiantian_zhengqi" )
        {
        } else
        if( idx == "yuanshen_exp" )
        {
                if( para > query("yuanshen_exp", who) )
                {
                        old_lvl = query("yuanshen_level", who);
                        if( !old_lvl || old_lvl < 1 ) old_lvl = 1;

                        for (i = old_lvl; ;i++)
                        {
                                if( to_int(pow(i+1, 3)) > (para / 100000) )
                                {
                                        now_lvl = i;
                                        break;
                                }
                        }

                        if( now_lvl > old_lvl )
                        {
                                n = now_lvl - old_lvl;
                                efun::set("yuanshen_level", now_lvl, who);

                                addn("yuanshen/attack", n, who);
                                addn("yuanshen/defense", n, who);
                                addn("yuanshen/damage", n, who);
                                addn("yuanshen/armor", n, who);

                                tell_object(who, HIY "只見一道紅光飛進你的體內，你的元神等級提升了！\n" NOR);
                        }
                }
        }
        return efun::set(idx, para, who);
}

varargs mixed add(string prop, mixed data, object who)
{
        string para;
        int old;
        int level;

        if( prop == "combat_exp" )
        {
                if( !(old = query(prop, who)) )
                        return set(prop, data, who);

                if( data < 1 )
                        return efun::set(prop, old + data, who);

                level = query("level", who);
                if( !level || level < 1 ) level = 1;
                if( !UPDATE_D->can_improve_level(level) &&
                    old > to_int(pow(level, 3.0)*10000) )
                        return;

                return set(prop, old + data, who);
        } else
        if( prop == "xiantian_zhengqi" ) 
        {
        } else 
        if( prop == "yuanshen_exp" )
        {
                if( !(old = query(prop, who)) )
                        return set(prop, data, who);

                if( data < 1 )
                        return efun::set(prop, old + data, who);
        } else
                return efun::addn(prop, data, who);
}

// 延遲獎勵：因為有時給出獎勵的時候應該是在某些事件發生以後，
// 但是在該事件發生時給與獎勵更易於書寫程序，所以獎勵生成的
// 地方在事件正在發生的時候，但是要讓玩家看起來是在事件發生
// 以後。比如殺人，人死亡的時候給與獎勵是容易做的，但是我希
// 望玩家在看到NPC 的死亡信息以後才看到獎勵的信息，這時候就
// 用delay_bonus了。

public void delay_bonus(object who, mapping b)
{
        who->start_call_out((: call_other, __FILE__,
                               "bonus", who, b :), 1);
}

public void delay_work_bonus(object who, mapping b)
{
        who->start_call_out((: call_other, __FILE__,
                               "work_bonus", who, b :), 1);
}

public void delay_freequest_bonus(object who)
{
        who->start_call_out((: call_other, __FILE__,
                               "freequest_bonus", who :), 3);
}

public void delay_gift_bonus(object who, mapping b)
{
        who->start_call_out((: call_other, __FILE__,
                               "gift_bonus", who, b :), 1);
}

public void delay_war_bonus(object who, mapping b)
{
        who->start_call_out((: call_other, __FILE__,
                               "war_bonus", who, b :), 1);
}

public void delay_fuben_bonus(object who, mapping b)
{
        who->start_call_out((: call_other, __FILE__,
                               "fuben_bonus", who, b :), 1);
}

public void delay_boss_bonus(object who, mapping b)
{
        who->start_call_out((: call_other, __FILE__,
                               "boss_bonus", who, b :), 1);
}

void special_bonus(object me, object who, mixed arg)
{
        // 隨機獎勵
        string *ob_list = ({
                "/clone/gift/xiandan",
                "/clone/gift/shenliwan",
                "/clone/gift/unknowdan",
                "/clone/gift/xisuidan",
                "/d/item/obj/xuantie",
                "/d/item/obj/wujins",
                "/d/item/obj/butian",
                "/d/item/obj/tiancs",
                "/clone/gift/jinkuai",
                "/clone/tessera/metal",
                "/clone/tessera/wood",
                "/clone/tessera/water",
                "/clone/tessera/fire",
                "/clone/tessera/earth",
                "/clone/goods/forging-stone",
        });

        object ob;

        /*
        message_vision("$n對$N微微一笑，道：幹得不賴，辛苦"
                       "了，正好我這裏有點東西，你就拿去吧。\n",
                       who, me);
        */

        if (stringp(arg))
                ob = new(arg);
        else
                ob = new(ob_list[random(sizeof(ob_list))]);
        ob->move(who, 1);
        tell_object(who, HIM "你獲得了一" + query("unit", ob) + ob->name() +
                        HIM "。\n" NOR);
}

// 門派任務的獎勵
varargs public void bonus(object who, mapping b, int flag)
{
        int exp;                // 獎勵的經驗
        int pot;                // 獎勵的潛能
        int mar;                // 獎勵的實戰體會
        int shen;               // 獎勵的神
        int score;              // 獎勵的江湖閲歷
        int weiwang;            // 獎勵的江湖威望
        int gongxian;           // 獎勵的門派貢獻
        int gold;
        int pot_limit;          // 潛能的界限
        int mar_limit;          // 實戰體會的界限
        int percent;            // 獎勵的有效百分比
        string msg;             // 獎勵的描述信息
        int yuanshen_exp;
        int warcraft_exp;
        object ob;
        int rate;
        int quest_times = "/adm/daemons/actiond"->query_action("quest_reward");

        // 獲得獎勵的百分比
        percent = b["percent"];
        if (percent < 1 || percent > 100)
                percent = 100;
        
        if( query("reborn/times", who) ) percent /= 2;
        
        exp = b["exp"] * percent / 100;
        pot = b["pot"] * percent / 100;
        mar = b["mar"] * percent / 100;
        shen = b["shen"] * percent / 100;
        score = b["score"] * percent / 100;
        weiwang = b["weiwang"] * percent / 100;
        gongxian = b["gongxian"] * percent / 100;
        gold = b["gold"] * percent / 100;

        // 玩家經驗太高，削弱獎勵。
        /*
        if( query("combat_exp", who) >= 2160000000 )
        {
                exp /= 3;
                pot /= 3;
                mar /= 3;
        } else
        if( query("combat_exp", who) >= 1250000000 )
        {
                exp /= 2;
                pot /= 2;
                mar /= 2;
        } else
        if( query("combat_exp", who) >= 640000000 )
        {
                exp = exp*2/3;
                pot = exp*2/3;
                mar = exp*2/3;
        }
        */

#ifdef DB_SAVE
        if (MEMBER_D->is_double_reward(who))
        {
                exp *= 2;
                pot *= 2;
                mar *= 2;
        }
#endif

        if (quest_times)
        {
                exp *= quest_times;
                pot *= quest_times;
                mar *= quest_times;
        }

        if( quest_times=query_temp("apply/add_reward", who) )
        {
                if( query("reborn/times", who) ) quest_times /= 3;
                if( quest_times > 100 ) quest_times = 100;
                exp += exp*range_random(quest_times/2,quest_times)/100;
                pot += pot*range_random(quest_times/2,quest_times)/100;
                mar += mar*range_random(quest_times/2,quest_times)/100;
        }

        if( quest_times=query_temp("apply/add_exp", who) )
        {
                if( query("reborn/times", who) ) quest_times /= 3;
                if( quest_times > 200 ) quest_times = 200;
                exp += exp*random(quest_times)/100;
        }
        
        if( quest_times=query_temp("apply/add_pot", who) )
                pot += pot*random(quest_times)/100;

        if( quest_times=query_temp("apply/add_mar", who) )
                mar += mar*random(quest_times)/100;
                                                        
        // 幫派榮譽點
        if( who->query_bunch() && BUNCH_D->query_bunch_efficient(who->query_bunch(), "exp") )
                exp *= 2;        
        if( who->query_bunch() && BUNCH_D->query_bunch_efficient(who->query_bunch(), "pot") )
                pot *= 2;
        if( who->query_bunch() && BUNCH_D->query_bunch_efficient(who->query_bunch(), "mar") )
                mar *= 2;

        if( who->query_family() && FAMILY_D->query_family_efficient(who->query_family(), "exp") )
                exp *= 2;        
        if( who->query_family() && FAMILY_D->query_family_efficient(who->query_family(), "pot") )
                pot *= 2;
        if( who->query_family() && FAMILY_D->query_family_efficient(who->query_family(), "mar") )
                mar *= 2;
                              
        if (! flag)
        {
                pot_limit=who->query_potential_limit()-query("potential", who);
                if (pot > pot_limit) pot = pot_limit;
                if (pot < 1) pot = 0;

                mar_limit=who->query_experience_limit()-query("experience", who);
                if (mar > mar_limit) mar = mar_limit;
                if (mar < 1) mar = 0;
        } else
        {
                if( who->query_potential_limit()<query("potential", who) )
                        pot = 1 + random(2);

                if( who->query_experience_limit()<query("experience", who) )
                        mar = 1;
        }

        // 魔幻獸
        if( exp > 100 && intp(rate = query("env/share_exp", who)) &&
            query("warcraft/file", who) && objectp(ob=find_object(query("warcraft/file", who))) )
        {
                if( rate < 0 ) rate = 0;
                if( rate > 100 ) rate = 100;
                warcraft_exp = exp * rate/100 + 1;
                ob->add("combat_exp", warcraft_exp);
                exp -= warcraft_exp;
        }

        // 元神
        if( exp > 100 && query("yuanshen", who) )
        {
                yuanshen_exp = exp / 4 + 1;
                add("yuanshen_exp", yuanshen_exp, who);
                exp -= yuanshen_exp;
        }

        // 生成提示信息
        if (stringp(msg = b["prompt"]))
                msg = HIG + msg + HIG "，你獲得了";
        else
                msg = HIG "通過這次鍛鍊，你獲得了";

        if (exp > 0) msg += chinese_number(exp) + "點經驗、";
        if (pot > 0) msg += chinese_number(pot) + "點潛能、";
        if (mar > 0) msg += chinese_number(mar) + "點實戰體會、";
        if (shen > 0) msg += chinese_number(shen) + "點正神、";
        if (shen < 0) msg += chinese_number(-shen) + "點負神、";
        if (score > 0) msg += chinese_number(score) + "點江湖閲歷、";
        if (weiwang > 0) msg += chinese_number(weiwang) + "點威望、";
        if (gongxian > 0) msg += chinese_number(gongxian) + "點門派功績、";
        if (gold > 0) msg += chinese_number(gold) + "兩黃金、";

        if( ob )
	{
	        msg += ob->name() + "獲得經驗" + chinese_number(warcraft_exp) + "點、";
        }

        if( query("yuanshen", who) )
	{
	        msg += "元神獲得經驗" + chinese_number(yuanshen_exp) + "點、";
        }

        msg += "能力得到了提升。\n" NOR;
        tell_object(who, sort_msg(msg));

        // bonus
        add("combat_exp", exp, who);
        addn("potential", pot, who);
        addn("experience", mar, who);
        addn("shen", shen, who);
        addn("score", score, who);
        addn("weiwang", weiwang, who);
        addn("family/gongji", gongxian, who);
        addn("balance", gold*10000, who);
}

// 普通工作任務的獎勵
varargs public void work_bonus(object who, mapping b, int flag, string type/*任務類型,為活動精靈預留接口*/)
{
        int exp;                // 獎勵的經驗
        int pot;                // 獎勵的潛能
        int mar;                // 獎勵的實戰體會
        int shen;               // 獎勵的神
        int score;              // 獎勵的江湖閲歷
        int weiwang;            // 獎勵的江湖威望
        int gongxian;           // 獎勵的門派貢獻
        int gold;
        int pot_limit;          // 潛能的界限
        int mar_limit;          // 實戰體會的界限
        int percent;            // 獎勵的有效百分比
        string msg;             // 獎勵的描述信息
        int yuanshen_exp;
        int warcraft_exp;
        object ob;
        int rate;
        int quest_times = "/adm/daemons/actiond"->query_action("work_reward");

        // 獲得獎勵的百分比
        percent = b["percent"];
        if (percent < 1 || percent > 100)
                percent = 100;

        if( query("reborn/times", who) ) percent /= 2;
        
        exp = b["exp"] * percent / 100;
        pot = b["pot"] * percent / 100;
        mar = b["mar"] * percent / 100;
        shen = b["shen"] * percent / 100;
        score = b["score"] * percent / 100;
        weiwang = b["weiwang"] * percent / 100;
        gongxian = b["gongxian"] * percent / 100;
        gold = b["gold"] * percent / 100;

        // 玩家經驗太高，削弱獎勵。
        /*
        if( query("combat_exp", who) >= 2160000000 )
        {
                exp /= 3;
                pot /= 3;
                mar /= 3;
        } else
        if( query("combat_exp", who) >= 1250000000 )
        {
                exp /= 2;
                pot /= 2;
                mar /= 2;
        } else
        if( query("combat_exp", who) >= 640000000 )
        {
                exp = exp*2/3;
                pot = exp*2/3;
                mar = exp*2/3;
        }
        */

#ifdef DB_SAVE
        if (MEMBER_D->is_double_reward(who))
        {
                exp *= 2;
                pot *= 2;
                mar *= 2;
        }
#endif

        if (quest_times)
        {
                exp *= quest_times;
                pot *= quest_times;
                mar *= quest_times;
        }

        if( quest_times=query_temp("apply/add_reward", who) )
        {
                if( query("reborn/times", who) ) quest_times /= 3;
                if( quest_times > 100 ) quest_times = 100;
                exp += exp*range_random(quest_times/2,quest_times)/100;
                pot += pot*range_random(quest_times/2,quest_times)/100;
                mar += mar*range_random(quest_times/2,quest_times)/100;
        }

        if( quest_times=query_temp("apply/add_exp", who) )
        {
                if( query("reborn/times", who) ) quest_times /= 3;
                if( quest_times > 200 ) quest_times = 200;
                exp += exp*random(quest_times)/100;
        }
        
        if( quest_times=query_temp("apply/add_pot", who) )
                pot += pot*random(quest_times)/100;

        if( quest_times=query_temp("apply/add_mar", who) )
                mar += mar*random(quest_times)/100;
        
        // 幫派榮譽點
        if( who->query_bunch() && BUNCH_D->query_bunch_efficient(who->query_bunch(), "exp") )
                exp *= 2;        
        if( who->query_bunch() && BUNCH_D->query_bunch_efficient(who->query_bunch(), "pot") )
                pot *= 2;
        if( who->query_bunch() && BUNCH_D->query_bunch_efficient(who->query_bunch(), "mar") )
                mar *= 2;

        if( who->query_family() && FAMILY_D->query_family_efficient(who->query_family(), "exp") )
                exp *= 2;        
        if( who->query_family() && FAMILY_D->query_family_efficient(who->query_family(), "pot") )
                pot *= 2;
        if( who->query_family() && FAMILY_D->query_family_efficient(who->query_family(), "mar") )
                mar *= 2;                
        /*
        if (! flag)
        {
                pot_limit=who->query_potential_limit()-query("potential", who);
                if (pot > pot_limit) pot = pot_limit;
                if (pot < 1) pot = 0;

                mar_limit=who->query_experience_limit()-query("experience", who);
                if (mar > mar_limit) mar = mar_limit;
                if (mar < 1) mar = 0;
        } else
        {
                if( who->query_potential_limit()<query("potential", who) )
                        pot = 1 + random(2);

                if( who->query_experience_limit()<query("experience", who) )
                        mar = 1;
        }
        */

        // 魔幻獸
        if( exp > 100 && intp(rate = query("env/share_exp", who)) &&
            query("warcraft/file", who) && objectp(ob=find_object(query("warcraft/file", who))) )
        {
                if( rate < 0 ) rate = 0;
                if( rate > 100 ) rate = 100;
                warcraft_exp = exp * rate/100 + 1;
                ob->add("combat_exp", warcraft_exp);
                exp -= warcraft_exp;
        }

        if( exp > 10 && query("yuanshen", who) )
        {
                yuanshen_exp = exp / 4 + 1;
                add("yuanshen_exp", yuanshen_exp, who);
                exp -= yuanshen_exp;
        }

        // 生成提示信息
        if (stringp(msg = b["prompt"]))
                msg = HIC "\n" + msg + HIC "，你獲得了";
        else
                msg = HIC "\n通過這次鍛鍊，你獲得了";

        if (exp > 0) msg += chinese_number(exp) + "點經驗、";
        if (pot > 0) msg += chinese_number(pot) + "點潛能、";
        if (mar > 0) msg += chinese_number(mar) + "點實戰體會、";
        if (shen > 0) msg += chinese_number(shen) + "點正神、";
        if (shen < 0) msg += chinese_number(-shen) + "點負神、";
        if (score > 0) msg += chinese_number(score) + "點江湖閲歷、";
        if (weiwang > 0) msg += chinese_number(weiwang) + "點威望、";
        if (gongxian > 0) msg += chinese_number(gongxian) + "點門派功績、";
        if (gold > 0) msg += chinese_number(gold) + "兩黃金、";

        if( ob )
	{
	        msg += ob->name() + "獲得經驗" + chinese_number(warcraft_exp) + "點、";
        }

        if( query("yuanshen", who) )
	{
	        msg += "元神獲得經驗" + chinese_number(yuanshen_exp) + "點、";
        }

        msg += "能力得到了提升。\n\n" NOR;
        tell_object(who, sort_msg(msg));

        // bonus
        add("combat_exp", exp, who);
        addn("potential", pot, who);
        addn("experience", mar, who);
        addn("shen", shen, who);
        addn("score", score, who);
        addn("weiwang", weiwang, who);
        addn("family/gongji", gongxian, who);
        addn("balance", gold*10000, who);
}

// 中斷性質自由任務的獎勵
varargs public void freequest_bonus(object who)
{
        object gift;
        int quest;              // 當前任務數量
        int exp;                // 獎勵的經驗
        int pot;                // 獎勵的潛能
        int mar;                // 獎勵的實戰體會
        string msg;             // 獎勵的描述信息
        int yuanshen_exp;
        int warcraft_exp;
        object ob;
        int rate;
        int quest_times = "/adm/daemons/actiond"->query_action("quest_reward");

        quest=query("quest_count", who);
        quest *= 10;
        exp = quest + random(quest) + 5000;

        // 因為獲得獎勵較多且無法累及中斷任務，所以暫時不做
        // 上限的限制。
        pot = exp / 3;
        mar = random(quest / 2) + 500;

#ifdef DB_SAVE
        if (MEMBER_D->is_double_reward(who))
        {
                exp *= 2;
                pot *= 2;
                mar *= 2;
        }
#endif

        if (quest_times)
        {
                exp *= quest_times;
                pot *= quest_times;
                mar *= quest_times;
        }

        if( quest_times=query_temp("apply/add_reward", who) )
        {
                if( query("reborn/times", who) ) quest_times /= 3;
                if( quest_times > 100 ) quest_times = 100;
                exp += exp*range_random(quest_times/2,quest_times)/100;
                pot += pot*range_random(quest_times/2,quest_times)/100;
                mar += mar*range_random(quest_times/2,quest_times)/100;
        }

        if( quest_times=query_temp("apply/add_exp", who) )
        {
                if( query("reborn/times", who) ) quest_times /= 3;
                if( quest_times > 200 ) quest_times = 200;
                exp += exp*random(quest_times)/100;
        }
        
        if( quest_times=query_temp("apply/add_pot", who) )
                pot += pot*random(quest_times)/100;

        if( quest_times=query_temp("apply/add_mar", who) )
                mar += mar*random(quest_times)/100;

        // 幫派榮譽點
        if( who->query_bunch() && BUNCH_D->query_bunch_efficient(who->query_bunch(), "exp") )
                exp *= 2;        
        if( who->query_bunch() && BUNCH_D->query_bunch_efficient(who->query_bunch(), "pot") )
                pot *= 2;
        if( who->query_bunch() && BUNCH_D->query_bunch_efficient(who->query_bunch(), "mar") )
                mar *= 2;

        if( who->query_family() && FAMILY_D->query_family_efficient(who->query_family(), "exp") )
                exp *= 2;        
        if( who->query_family() && FAMILY_D->query_family_efficient(who->query_family(), "pot") )
                pot *= 2;
        if( who->query_family() && FAMILY_D->query_family_efficient(who->query_family(), "mar") )
                mar *= 2;   
                             
        // 魔幻獸
        if( exp > 100 && intp(rate = query("env/share_exp", who)) &&
            query("warcraft/file", who) && objectp(ob=find_object(query("warcraft/file", who))) )
        {
                if( rate < 0 ) rate = 0;
                if( rate > 100 ) rate = 100;
                warcraft_exp = exp * rate/100 + 1;
                ob->add("combat_exp", warcraft_exp);
                exp -= warcraft_exp;
        }
        
        if( exp > 10 && query("yuanshen", who) )
        {
                yuanshen_exp = exp / 4 + 1;
                add("yuanshen_exp", yuanshen_exp, who);
                exp -= yuanshen_exp;
        }

        msg = HIC "\n你在這次的歷練過程中，對武學似乎又"
              "有了新的突破。你獲得了" +
              chinese_number(exp) + "點經驗、" +
              chinese_number(pot) + "點潛能、" +
              chinese_number(mar) + "點實戰體會、";

        if( ob )
	{
	        msg += ob->name() + "獲得經驗" + chinese_number(warcraft_exp) + "點、";
        }

        if( query("yuanshen", who) )
	{
	        msg += "元神獲得經驗" + chinese_number(yuanshen_exp) + "點。";
        }

        msg += "能力得到了提升。\n" NOR;
        tell_object(who, sort_msg(msg));

        // bonus
        add("combat_exp", exp, who);
        addn("potential", pot, who);
        addn("experience", mar, who);
        addn("quest/freequest", -1, who);

        if (query("quest/freequest", who) < 1)
        {
                delete("quest", who);
                message_sort(HIW "\n正在這時，只見一位" +
                             query("family/family_name", who)+
                             "弟子急急忙忙趕到$N" HIW "身邊，説"
                             "道：“原來你在這裏啊，師傅正到處派"
                             "人找你呢。聽説有要緊事交給你辦，你"
                             "趕快回去吧！這個包裹是師傅讓我轉交"
                             "給你的。”\n" NOR, who);

                message_sort("\n"+query("family/family_name", who)+
                             "弟子拿出一個包裹遞給$N。\n\n" +
                             query("family/family_name", who)+
                             "弟子急急忙忙地離開了。\n" NOR, who);

                gift = new("/clone/misc/bag");
                gift->move(who, 1);
        }
}

// 特殊事件的獎勵
varargs public void gift_bonus(object who, mapping b)
{
        int exp;                // 獎勵的經驗
        int pot;                // 獎勵的潛能
        int mar;                // 獎勵的實戰體會
        int score;              // 獎勵的江湖閲歷
        int weiwang;            // 獎勵的江湖威望
        int gongxian;           // 獎勵的門派貢獻
        int percent;            // 獎勵的有效百分比
        string msg;             // 獎勵的描述信息
        string temp;            // 進程記錄信息
        int quest_times;
        int yuanshen_exp;
        int warcraft_exp;
        object ob;
        int rate;

        // 獲得獎勵的百分比
        percent = b["percent"];

        if (percent < 1 || percent > 100)
                percent = 100;
        
        if( query("reborn/times", who) ) percent /= 2;
        
        // 進程記錄，針對第一次完成有獎勵的情節
        temp = b["temp"];

        exp = b["exp"] * percent / 100;
        pot = b["pot"] * percent / 100;
        mar = b["mar"] * percent / 100;
        score = b["score"] * percent / 100;
        weiwang = b["weiwang"] * percent / 100;
        gongxian = b["gongxian"] * percent / 100;

#ifdef DB_SAVE
        if (MEMBER_D->is_double_reward(who))
        {
                exp *= 2;
                pot *= 2;
                mar *= 2;
        }
#endif

        if( quest_times=query_temp("apply/add_reward", who) )
        {
                if( query("reborn/times", who) ) quest_times /= 3;
                if( quest_times > 100 ) quest_times = 100;
                exp += exp*range_random(quest_times/2,quest_times)/100;
                pot += pot*range_random(quest_times/2,quest_times)/100;
                mar += mar*range_random(quest_times/2,quest_times)/100;
        }

        if( quest_times=query_temp("apply/add_exp", who) )
        {
                if( query("reborn/times", who) ) quest_times /= 3;
                if( quest_times > 200 ) quest_times = 200;
                exp += exp*random(quest_times)/100;
        }
        
        if( quest_times=query_temp("apply/add_pot", who) )
                pot += pot*random(quest_times)/100;

        if( quest_times=query_temp("apply/add_mar", who) )
                mar += mar*random(quest_times)/100;

        // 幫派榮譽點
        if( who->query_bunch() && BUNCH_D->query_bunch_efficient(who->query_bunch(), "exp") )
                exp *= 2;        
        if( who->query_bunch() && BUNCH_D->query_bunch_efficient(who->query_bunch(), "pot") )
                pot *= 2;
        if( who->query_bunch() && BUNCH_D->query_bunch_efficient(who->query_bunch(), "mar") )
                mar *= 2;

        if( who->query_family() && FAMILY_D->query_family_efficient(who->query_family(), "exp") )
                exp *= 2;        
        if( who->query_family() && FAMILY_D->query_family_efficient(who->query_family(), "pot") )
                pot *= 2;
        if( who->query_family() && FAMILY_D->query_family_efficient(who->query_family(), "mar") )
                mar *= 2;                
       // 魔幻獸
        if( exp > 100 && intp(rate = query("env/share_exp", who)) &&
            query("warcraft/file", who) && objectp(ob=find_object(query("warcraft/file", who))) )
        {
                if( rate < 0 ) rate = 0;
                if( rate > 100 ) rate = 100;
                warcraft_exp = exp * rate/100 + 1;
                ob->add("combat_exp", warcraft_exp);
                exp -= warcraft_exp;
        }

        if( exp > 10 && query("yuanshen", who) )
        {
                yuanshen_exp = exp / 4 + 1;
                add("yuanshen_exp", yuanshen_exp, who);
                exp -= yuanshen_exp;
        }

        // 生成謠言信息
        if (stringp(msg = b["rumor"]))
        {
                shout(HIR "【武林傳聞】" NOR + WHT "聽説" +
                      who->name()+WHT"["+query("id", who)+
                      WHT "]" + msg + WHT "。\n" NOR);
        }

        if( !stringp(temp) || !query(temp, who) )
        {
                // 生成提示信息
                if (stringp(msg = b["prompt"]))
                        msg = HIW "\n" + msg + HIW "，你獲得了";
                else
                        msg = HIW "\n通過此次經歷，你獲得了";

                // 記錄下進程
                if (stringp(temp))
                        addn(temp, 1, who);

                if (exp > 0) msg += chinese_number(exp) + "點經驗、";
                if (pot > 0) msg += chinese_number(pot) + "點潛能、";
                if (mar > 0) msg += chinese_number(mar) + "點實戰體會、";
                if (score > 0) msg += chinese_number(score) + "點江湖閲歷、";
                if (weiwang > 0) msg += chinese_number(weiwang) + "點江湖威望、";
                if (gongxian > 0) msg += chinese_number(gongxian) + "點門派功績、";

                if( ob )
	        {
	                msg += ob->name() + "獲得經驗" + chinese_number(warcraft_exp) + "點、";
                }

                if( query("yuanshen", who) )
	        {
	                msg += "元神獲得經驗" + chinese_number(yuanshen_exp) + "點、";
                }
                msg += "能力得到了提升。\n" NOR;
                tell_object(who, sort_msg(msg));

                // bonus
                add("combat_exp", exp, who);
                addn("potential", pot, who);
                addn("experience", mar, who);
                addn("score", score, who);
                addn("weiwang", weiwang, who);
                addn("family/gongji", gongxian, who);
        }
}

varargs public void war_bonus(object who, mapping b)
{
        int exp;                // 獎勵的經驗
        int pot;                // 獎勵的潛能
        int mar;                // 獎勵的實戰體會
        int shen;               // 獎勵的神
        int score;              // 獎勵的江湖閲歷
        int weiwang;            // 獎勵的江湖威望
        int gongxian;           // 獎勵的門派貢獻
        int gold;
        int pot_limit;          // 潛能的界限
        int mar_limit;          // 實戰體會的界限
        int percent;            // 獎勵的有效百分比
        string msg;             // 獎勵的描述信息
        int yuanshen_exp;
        int warcraft_exp;
        object ob;
        int rate;
        int quest_times = ACTION_D->query_action("battle_reward");

        // 獲得獎勵的百分比
        percent = b["percent"];
        if (percent < 1 || percent > 100)
                percent = 100;
        
        // 轉世後獎勵大幅度降低，轉世獎勵高是為了新人適應這裏
        if( query("reborn/times", who) ) percent /= 4; 
        
        exp = b["exp"] * percent / 100;
        pot = b["pot"] * percent / 100;
        mar = b["mar"] * percent / 100;
        shen = b["shen"] * percent / 100;
        score = b["score"] * percent / 100;
        weiwang = b["weiwang"] * percent / 100;
        gongxian = b["gongxian"] * percent / 100;
        gold = b["gold"] * percent / 100;

        // 玩家經驗太高，削弱獎勵。
        /*
        if( query("combat_exp", who) >= 2160000000 )
        {
                exp /= 3;
                pot /= 3;
                mar /= 3;
        } else
        if( query("combat_exp", who) >= 1250000000 )
        {
                exp /= 2;
                pot /= 2;
                mar /= 2;
        } else
        if( query("combat_exp", who) >= 640000000 )
        {
                exp = exp*2/3;
                pot = exp*2/3;
                mar = exp*2/3;
        }
        */

#ifdef DB_SAVE
        if (MEMBER_D->is_double_reward(who))
        {
                exp *= 2;
                pot *= 2;
                mar *= 2;
        }
#endif

        if (quest_times)
        {
                exp *= quest_times;
                pot *= quest_times;
                mar *= quest_times;
        }

        if( quest_times=query_temp("apply/add_reward", who) )
        {
                if( query("reborn/times", who) ) quest_times /= 3;
                if( quest_times > 100 ) quest_times = 100;
                exp += exp*range_random(quest_times/2,quest_times)/100;
                pot += pot*range_random(quest_times/2,quest_times)/100;
                mar += mar*range_random(quest_times/2,quest_times)/100;
        }

        if( quest_times=query_temp("apply/add_exp", who) )
        {
                if( query("reborn/times", who) ) quest_times /= 3;
                if( quest_times > 200 ) quest_times = 200;
                exp += exp*random(quest_times)/100;
        }
        
        if( quest_times=query_temp("apply/add_pot", who) )
                pot += pot*random(quest_times)/100;

        if( quest_times=query_temp("apply/add_mar", who) )
                mar += mar*random(quest_times)/100;

        // 幫派榮譽點
        if( who->query_bunch() && BUNCH_D->query_bunch_efficient(who->query_bunch(), "exp") )
                exp *= 2;        
        if( who->query_bunch() && BUNCH_D->query_bunch_efficient(who->query_bunch(), "pot") )
                pot *= 2;
        if( who->query_bunch() && BUNCH_D->query_bunch_efficient(who->query_bunch(), "mar") )
                mar *= 2;

        if( who->query_family() && FAMILY_D->query_family_efficient(who->query_family(), "exp") )
                exp *= 2;        
        if( who->query_family() && FAMILY_D->query_family_efficient(who->query_family(), "pot") )
                pot *= 2;
        if( who->query_family() && FAMILY_D->query_family_efficient(who->query_family(), "mar") )
                mar *= 2;
                                
        // 魔幻獸
        if( exp > 100 && intp(rate = query("env/share_exp", who)) &&
            query("warcraft/file", who) && objectp(ob=find_object(query("warcraft/file", who))) )
        {
                if( rate < 0 ) rate = 0;
                if( rate > 100 ) rate = 100;
                warcraft_exp = exp * rate/100 + 1;
                ob->add("combat_exp", warcraft_exp);
                exp -= warcraft_exp;
        }

        if( exp > 10 && query("yuanshen", who) )
        {
                yuanshen_exp = exp / 4 + 1;
                add("yuanshen_exp", yuanshen_exp, who);
                exp -= yuanshen_exp;
        }

        // 生成提示信息
        if (stringp(msg = b["prompt"]))
                msg = HIG + msg + HIG "，你獲得了";
        else
                msg = HIG "通過這次鍛鍊，你獲得了";

        if (exp > 0) msg += chinese_number(exp) + "點經驗、";
        if (pot > 0) msg += chinese_number(pot) + "點潛能、";
        if (mar > 0) msg += chinese_number(mar) + "點實戰體會、";
        if (shen > 0) msg += chinese_number(shen) + "點正神、";
        if (shen < 0) msg += chinese_number(-shen) + "點負神、";
        if (score > 0) msg += chinese_number(score) + "點江湖閲歷、";
        if (weiwang > 0) msg += chinese_number(weiwang) + "點威望、";
        if (gongxian > 0) msg += chinese_number(gongxian) + "點門派功績、";
        if (gold > 0) msg += chinese_number(gold) + "兩黃金、";

        if( ob )
	{
	        msg += ob->name() + "獲得經驗" + chinese_number(warcraft_exp) + "點、";
        }

        if( query("yuanshen", who) )
        {
	        msg += "元神獲得經驗" + chinese_number(yuanshen_exp) + "點、";
        }

        msg += "能力得到了提升。\n" NOR;
        tell_object(who, sort_msg(msg));

        // bonus
        add("combat_exp", exp, who);
        addn("potential", pot, who);
        addn("experience", mar, who);
        addn("shen", shen, who);
        addn("score", score, who);
        addn("weiwang", weiwang, who);
        addn("family/gongji", gongxian, who);
        addn("balance", gold*10000, who);
}

// BOSS任務的獎勵
varargs public void boss_bonus(object who, mapping b, int flag)
{
        int exp;                // 獎勵的經驗
        int pot;                // 獎勵的潛能
        int mar;                // 獎勵的實戰體會
        int shen;               // 獎勵的神
        int score;              // 獎勵的江湖閲歷
        int weiwang;            // 獎勵的江湖威望
        int gongxian;           // 獎勵的門派貢獻
        int gold;
        int pot_limit;          // 潛能的界限
        int mar_limit;          // 實戰體會的界限
        int percent;            // 獎勵的有效百分比
        string msg;             // 獎勵的描述信息
        int yuanshen_exp;
        int warcraft_exp;
        object ob;
        int rate;
        int quest_times = "/adm/daemons/actiond"->query_action("boss_reward");

        // 獲得獎勵的百分比
        percent = b["percent"];
        if (percent < 1 || percent > 100)
                percent = 100;
        
        if( query("reborn/times", who) ) percent /= 2;
        
        exp = b["exp"] * percent / 100;
        pot = b["pot"] * percent / 100;
        mar = b["mar"] * percent / 100;
        shen = b["shen"] * percent / 100;
        score = b["score"] * percent / 100;
        weiwang = b["weiwang"] * percent / 100;
        gongxian = b["gongxian"] * percent / 100;
        gold = b["gold"] * percent / 100;

        // 玩家經驗太高，削弱獎勵。
        /*
        if( query("combat_exp", who) >= 2160000000 )
        {
                exp /= 3;
                pot /= 3;
                mar /= 3;
        } else
        if( query("combat_exp", who) >= 1250000000 )
        {
                exp /= 2;
                pot /= 2;
                mar /= 2;
        } else
        if( query("combat_exp", who) >= 640000000 )
        {
                exp = exp*2/3;
                pot = exp*2/3;
                mar = exp*2/3;
        }
        */

#ifdef DB_SAVE
        if (MEMBER_D->is_double_reward(who))
        {
                exp *= 2;
                pot *= 2;
                mar *= 2;
        }
#endif

        if (quest_times)
        {
                exp *= quest_times;
                pot *= quest_times;
                mar *= quest_times;
        }

        if( quest_times=query_temp("apply/add_reward", who) )
        {
                if( query("reborn/times", who) ) quest_times /= 3;
                if( quest_times > 100 ) quest_times = 100;
                exp += exp*range_random(quest_times/2,quest_times)/100;
                pot += pot*range_random(quest_times/2,quest_times)/100;
                mar += mar*range_random(quest_times/2,quest_times)/100;
        }

        if( quest_times=query_temp("apply/add_exp", who) )
        {
                if( query("reborn/times", who) ) quest_times /= 3;
                if( quest_times > 200 ) quest_times = 200;
                exp += exp*random(quest_times)/100;
        }
        
        if( quest_times=query_temp("apply/add_pot", who) )
                pot += pot*random(quest_times)/100;

        if( quest_times=query_temp("apply/add_mar", who) )
                mar += mar*random(quest_times)/100;
        
        // 幫派榮譽點
        if( who->query_bunch() && BUNCH_D->query_bunch_efficient(who->query_bunch(), "exp") )
                exp *= 2;        
        if( who->query_bunch() && BUNCH_D->query_bunch_efficient(who->query_bunch(), "pot") )
                pot *= 2;
        if( who->query_bunch() && BUNCH_D->query_bunch_efficient(who->query_bunch(), "mar") )
                mar *= 2;

        if( who->query_family() && FAMILY_D->query_family_efficient(who->query_family(), "exp") )
                exp *= 2;        
        if( who->query_family() && FAMILY_D->query_family_efficient(who->query_family(), "pot") )
                pot *= 2;
        if( who->query_family() && FAMILY_D->query_family_efficient(who->query_family(), "mar") )
                mar *= 2;
                                
        if (! flag)
        {
                pot_limit=who->query_potential_limit()-query("potential", who);
                if (pot > pot_limit) pot = pot_limit;
                if (pot < 1) pot = 0;

                mar_limit=who->query_experience_limit()-query("experience", who);
                if (mar > mar_limit) mar = mar_limit;
                if (mar < 1) mar = 0;
        } else
        {
                if( who->query_potential_limit()<query("potential", who) )
                        pot = 1 + random(2);

                if( who->query_experience_limit()<query("experience", who) )
                        mar = 1;
        }

        // 魔幻獸
        if( exp > 100 && intp(rate = query("env/share_exp", who)) &&
            query("warcraft/file", who) && objectp(ob=find_object(query("warcraft/file", who))) )
        {
                if( rate < 0 ) rate = 0;
                if( rate > 100 ) rate = 100;
                warcraft_exp = exp * rate/100 + 1;
                ob->add("combat_exp", warcraft_exp);
                exp -= warcraft_exp;
        }

        if( exp > 10 && query("yuanshen", who) )
        {
                yuanshen_exp = exp / 4 + 1;
                add("yuanshen_exp", yuanshen_exp, who);
                exp -= yuanshen_exp;
        }

        // 生成提示信息
        if (stringp(msg = b["prompt"]))
                msg = HIG + msg + HIG "，你獲得了";
        else
                msg = HIG "通過這次鍛鍊，你獲得了";

        if (exp > 0) msg += chinese_number(exp) + "點經驗、";
        if (pot > 0) msg += chinese_number(pot) + "點潛能、";
        if (mar > 0) msg += chinese_number(mar) + "點實戰體會、";
        if (shen > 0) msg += chinese_number(shen) + "點正神、";
        if (shen < 0) msg += chinese_number(-shen) + "點負神、";
        if (score > 0) msg += chinese_number(score) + "點江湖閲歷、";
        if (weiwang > 0) msg += chinese_number(weiwang) + "點威望、";
        if (gongxian > 0) msg += chinese_number(gongxian) + "點門派功績、";
        if (gold > 0) msg += chinese_number(gold) + "兩黃金、";

        if( ob )
	{
	        msg += ob->name() + "獲得經驗" + chinese_number(warcraft_exp) + "點、";
        }

        if( query("yuanshen", who) )
        {
	        msg += "元神獲得經驗" + chinese_number(yuanshen_exp) + "點、";
        }

        msg += "能力得到了提升。\n" NOR;
        tell_object(who, sort_msg(msg));

        // bonus
        add("combat_exp", exp, who);
        addn("potential", pot, who);
        addn("experience", mar, who);
        addn("shen", shen, who);
        addn("score", score, who);
        addn("weiwang", weiwang, who);
        addn("family/gongji", gongxian, who);
        addn("balance", gold*10000, who);
}

// 副本任務的獎勵
varargs public void fuben_bonus(object who, mapping b, int flag)
{
        int exp;                // 獎勵的經驗
        int pot;                // 獎勵的潛能
        int mar;                // 獎勵的實戰體會
        int shen;               // 獎勵的神
        int score;              // 獎勵的江湖閲歷
        int weiwang;            // 獎勵的江湖威望
        int gongxian;           // 獎勵的門派貢獻
        int gold;
        int pot_limit;          // 潛能的界限
        int mar_limit;          // 實戰體會的界限
        int percent;            // 獎勵的有效百分比
        string msg;             // 獎勵的描述信息
        int yuanshen_exp;
        int warcraft_exp;
        object ob;
        int rate;
        int quest_times = "/adm/daemons/actiond"->query_action("fuben_reward");

        // 獲得獎勵的百分比
        percent = b["percent"];
        if (percent < 1 || percent > 100)
                percent = 100;
        
        if( query("reborn/times", who) ) percent /= 2;
        
        exp = b["exp"] * percent / 100;
        pot = b["pot"] * percent / 100;
        mar = b["mar"] * percent / 100;
        shen = b["shen"] * percent / 100;
        score = b["score"] * percent / 100;
        weiwang = b["weiwang"] * percent / 100;
        gongxian = b["gongxian"] * percent / 100;
        gold = b["gold"] * percent / 100;

        // 玩家經驗太高，削弱獎勵。
        /*
        if( query("combat_exp", who) >= 2160000000 )
        {
                exp /= 3;
                pot /= 3;
                mar /= 3;
        } else
        if( query("combat_exp", who) >= 1250000000 )
        {
                exp /= 2;
                pot /= 2;
                mar /= 2;
        } else
        if( query("combat_exp", who) >= 640000000 )
        {
                exp = exp*2/3;
                pot = exp*2/3;
                mar = exp*2/3;
        }
        */

#ifdef DB_SAVE
        if (MEMBER_D->is_double_reward(who))
        {
                exp *= 2;
                pot *= 2;
                mar *= 2;
        }
#endif

        if (quest_times)
        {
                exp *= quest_times;
                pot *= quest_times;
                mar *= quest_times;
        }

        if( quest_times=query_temp("apply/add_reward", who) )
        {
                if( query("reborn/times", who) ) quest_times /= 3;
                if( quest_times > 100 ) quest_times = 100;
                exp += exp*range_random(quest_times/2,quest_times)/100;
                pot += pot*range_random(quest_times/2,quest_times)/100;
                mar += mar*range_random(quest_times/2,quest_times)/100;
        }

        if( quest_times=query_temp("apply/add_exp", who) )
        {
                if( query("reborn/times", who) ) quest_times /= 3;
                if( quest_times > 200 ) quest_times = 200;
                exp += exp*random(quest_times)/100;
        }
        
        if( quest_times=query_temp("apply/add_pot", who) )
                pot += pot*random(quest_times)/100;

        if( quest_times=query_temp("apply/add_mar", who) )
                mar += mar*random(quest_times)/100;

        // 幫派榮譽點
        if( who->query_bunch() && BUNCH_D->query_bunch_efficient(who->query_bunch(), "exp") )
                exp *= 2;        
        if( who->query_bunch() && BUNCH_D->query_bunch_efficient(who->query_bunch(), "pot") )
                pot *= 2;
        if( who->query_bunch() && BUNCH_D->query_bunch_efficient(who->query_bunch(), "mar") )
                mar *= 2;

        if( who->query_family() && FAMILY_D->query_family_efficient(who->query_family(), "exp") )
                exp *= 2;        
        if( who->query_family() && FAMILY_D->query_family_efficient(who->query_family(), "pot") )
                pot *= 2;
        if( who->query_family() && FAMILY_D->query_family_efficient(who->query_family(), "mar") )
                mar *= 2;
                                
        if (! flag)
        {
                pot_limit=who->query_potential_limit()-query("potential", who);
                if (pot > pot_limit) pot = pot_limit;
                if (pot < 1) pot = 0;

                mar_limit=who->query_experience_limit()-query("experience", who);
                if (mar > mar_limit) mar = mar_limit;
                if (mar < 1) mar = 0;
        } else
        {
                if( who->query_potential_limit()<query("potential", who) )
                        pot = 1 + random(2);

                if( who->query_experience_limit()<query("experience", who) )
                        mar = 1;
        }

        // 魔幻獸
        if( exp > 100 && intp(rate = query("env/share_exp", who)) &&
            query("warcraft/file", who) && objectp(ob=find_object(query("warcraft/file", who))) )
        {
                if( rate < 0 ) rate = 0;
                if( rate > 100 ) rate = 100;
                warcraft_exp = exp * rate/100 + 1;
                ob->add("combat_exp", warcraft_exp);
                exp -= warcraft_exp;
        }

        if( exp > 10 && query("yuanshen", who) )
        {
                yuanshen_exp = exp / 4 + 1;
                add("yuanshen_exp", yuanshen_exp, who);
                exp -= yuanshen_exp;
        }

        // 生成提示信息
        if (stringp(msg = b["prompt"]))
                msg = HIG + msg + HIG "，你獲得了";
        else
                msg = HIG "通過這次鍛鍊，你獲得了";

        if (exp > 0) msg += chinese_number(exp) + "點經驗、";
        if (pot > 0) msg += chinese_number(pot) + "點潛能、";
        if (mar > 0) msg += chinese_number(mar) + "點實戰體會、";
        if (shen > 0) msg += chinese_number(shen) + "點正神、";
        if (shen < 0) msg += chinese_number(-shen) + "點負神、";
        if (score > 0) msg += chinese_number(score) + "點江湖閲歷、";
        if (weiwang > 0) msg += chinese_number(weiwang) + "點威望、";
        if (gongxian > 0) msg += chinese_number(gongxian) + "點門派功績、";
        if (gold > 0) msg += chinese_number(gold) + "兩黃金、";

        if( ob )
	{
	        msg += ob->name() + "獲得經驗" + chinese_number(warcraft_exp) + "點、";
        }

        if( query("yuanshen", who) )
        {
	        msg += "元神獲得經驗" + chinese_number(yuanshen_exp) + "點、";
        }

        msg += "能力得到了提升。\n" NOR;
        tell_object(who, sort_msg(msg));

        // bonus
        add("combat_exp", exp, who);
        addn("potential", pot, who);
        addn("experience", mar, who);
        addn("shen", shen, who);
        addn("score", score, who);
        addn("weiwang", weiwang, who);
        addn("family/gongji", gongxian, who);
        addn("balance", gold*10000, who);
}

varargs public void battle_bonus(object who, mapping b)
{
        int exp;                // 獎勵的經驗
        int pot;                // 獎勵的潛能
        int mar;                // 獎勵的實戰體會
        int shen;               // 獎勵的神
        int score;              // 獎勵的江湖閲歷
        int weiwang;            // 獎勵的江湖威望
        int gongxian;           // 獎勵的門派貢獻
        int gold;
        int pot_limit;          // 潛能的界限
        int mar_limit;          // 實戰體會的界限
        int percent;            // 獎勵的有效百分比
        string msg;             // 獎勵的描述信息
        int yuanshen_exp;
        int warcraft_exp;
        object ob;
        int rate;
        int quest_times = ACTION_D->query_action("battle_reward");

        // 獲得獎勵的百分比
        percent = b["percent"];
        if (percent < 1 || percent > 100)
                percent = 100;
        
        if( query("reborn/times", who) ) percent /= 2;
        
        exp = b["exp"] * percent / 100;
        pot = b["pot"] * percent / 100;
        mar = b["mar"] * percent / 100;
        shen = b["shen"] * percent / 100;
        score = b["score"] * percent / 100;
        weiwang = b["weiwang"] * percent / 100;
        gongxian = b["gongxian"] * percent / 100;
        gold = b["gold"] * percent / 100;

        // 玩家經驗太高，削弱獎勵。
        /*
        if( query("combat_exp", who) >= 2160000000 )
        {
                exp /= 3;
                pot /= 3;
                mar /= 3;
        } else
        if( query("combat_exp", who) >= 1250000000 )
        {
                exp /= 2;
                pot /= 2;
                mar /= 2;
        } else
        if( query("combat_exp", who) >= 640000000 )
        {
                exp = exp*2/3;
                pot = exp*2/3;
                mar = exp*2/3;
        }
        */

#ifdef DB_SAVE
        if (MEMBER_D->is_double_reward(who))
        {
                exp *= 2;
                pot *= 2;
                mar *= 2;
        }
#endif

        if (quest_times)
        {
                exp *= quest_times;
                pot *= quest_times;
                mar *= quest_times;
        }

        if( quest_times=query_temp("apply/add_reward", who) )
        {
                if( query("reborn/times", who) ) quest_times /= 3;
                if( quest_times > 100 ) quest_times = 100;
                exp += exp*range_random(quest_times/2,quest_times)/100;
                pot += pot*range_random(quest_times/2,quest_times)/100;
                mar += mar*range_random(quest_times/2,quest_times)/100;
        }

        if( quest_times=query_temp("apply/add_exp", who) )
        {
                if( query("reborn/times", who) ) quest_times /= 3;
                if( quest_times > 200 ) quest_times = 200;
                exp += exp*random(quest_times)/100;
        }
        
        if( quest_times=query_temp("apply/add_pot", who) )
                pot += pot*random(quest_times)/100;

        if( quest_times=query_temp("apply/add_mar", who) )
                mar += mar*random(quest_times)/100;

        // 幫派榮譽點
        if( who->query_bunch() && BUNCH_D->query_bunch_efficient(who->query_bunch(), "exp") )
                exp *= 2;        
        if( who->query_bunch() && BUNCH_D->query_bunch_efficient(who->query_bunch(), "pot") )
                pot *= 2;
        if( who->query_bunch() && BUNCH_D->query_bunch_efficient(who->query_bunch(), "mar") )
                mar *= 2;

        if( who->query_family() && FAMILY_D->query_family_efficient(who->query_family(), "exp") )
                exp *= 2;        
        if( who->query_family() && FAMILY_D->query_family_efficient(who->query_family(), "pot") )
                pot *= 2;
        if( who->query_family() && FAMILY_D->query_family_efficient(who->query_family(), "mar") )
                mar *= 2;                
        // 魔幻獸
        if( exp > 100 && intp(rate = query("env/share_exp", who)) &&
            query("warcraft/file", who) && objectp(ob=find_object(query("warcraft/file", who))) )
        {
                if( rate < 0 ) rate = 0;
                if( rate > 100 ) rate = 100;
                warcraft_exp = exp * rate/100 + 1;
                ob->add("combat_exp", warcraft_exp);
                exp -= warcraft_exp;
        }

        if( exp > 10 && query("yuanshen", who) )
        {
                yuanshen_exp = exp / 4 + 1;
                add("yuanshen_exp", yuanshen_exp, who);
                exp -= yuanshen_exp;
        }

        // 生成提示信息
        if (stringp(msg = b["prompt"]))
                msg = HIG + msg + HIG "，你獲得了";
        else
                msg = HIG "通過這次鍛鍊，你獲得了";

        if (exp > 0) msg += chinese_number(exp) + "點經驗、";
        if (pot > 0) msg += chinese_number(pot) + "點潛能、";
        if (mar > 0) msg += chinese_number(mar) + "點實戰體會、";
        if (shen > 0) msg += chinese_number(shen) + "點正神、";
        if (shen < 0) msg += chinese_number(-shen) + "點負神、";
        if (score > 0) msg += chinese_number(score) + "點江湖閲歷、";
        if (weiwang > 0) msg += chinese_number(weiwang) + "點威望、";
        if (gongxian > 0) msg += chinese_number(gongxian) + "點門派功績、";
        if (gold > 0) msg += chinese_number(gold) + "兩黃金、";

        if( ob )
	{
	        msg += ob->name() + "獲得經驗" + chinese_number(warcraft_exp) + "點、";
        }

        if( query("yuanshen", who) )
        {
	        msg += "元神獲得經驗" + chinese_number(yuanshen_exp) + "點、";
        }

        msg += "能力得到了提升。\n" NOR;
        tell_object(who, sort_msg(msg));

        // bonus
        add("combat_exp", exp, who);
        addn("potential", pot, who);
        addn("experience", mar, who);
        addn("shen", shen, who);
        addn("score", score, who);
        addn("weiwang", weiwang, who);
        addn("family/gongji", gongxian, who);
        addn("balance", gold*10000, who);
}

// 活動的獎勵
varargs public void event_bonus(object who, mapping b, int flag)
{
        int exp;                // 獎勵的經驗
        int pot;                // 獎勵的潛能
        int mar;                // 獎勵的實戰體會
        int shen;               // 獎勵的神
        int score;              // 獎勵的江湖閲歷
        int weiwang;            // 獎勵的江湖威望
        int gongxian;           // 獎勵的門派貢獻
        int gold;
        int pot_limit;          // 潛能的界限
        int mar_limit;          // 實戰體會的界限
        int percent;            // 獎勵的有效百分比
        string msg;             // 獎勵的描述信息
        int yuanshen_exp;
        int warcraft_exp;
        object ob;
        int rate;
        int quest_times;
        int event;

        // 獲得獎勵的百分比
        percent = b["percent"];
        if (percent < 1 || percent > 100)
                percent = 100;
        
        if( query("reborn/times", who) ) percent /= 2;
        
        exp = b["exp"] * percent / 100;
        pot = b["pot"] * percent / 100;
        mar = b["mar"] * percent / 100;
        shen = b["shen"] * percent / 100;
        score = b["score"] * percent / 100;
        weiwang = b["weiwang"] * percent / 100;
        gongxian = b["gongxian"] * percent / 100;
        gold = b["gold"] * percent / 100;

        // 玩家經驗太高，削弱獎勵。
        /*
        if( query("combat_exp", who) >= 2160000000 )
        {
                exp /= 3;
                pot /= 3;
                mar /= 3;
        } else
        if( query("combat_exp", who) >= 1250000000 )
        {
                exp /= 2;
                pot /= 2;
                mar /= 2;
        } else
        if( query("combat_exp", who) >= 640000000 )
        {
                exp = exp*2/3;
                pot = exp*2/3;
                mar = exp*2/3;
        }
        */

#ifdef DB_SAVE
        if (MEMBER_D->is_double_reward(who))
        {
                exp *= 2;
                pot *= 2;
                mar *= 2;
        }
#endif
        event = ACTION_D->query_action("event_reward");
        if (event)
        {
                exp *= event;
                pot *= event;
                mar *= event;
        }

        if( quest_times=query_temp("apply/add_reward", who) )
        {
                if( query("reborn/times", who) && !event ) quest_times /= 3;
                if( quest_times > 100 ) quest_times = 100;
                exp += exp*range_random(quest_times/2,quest_times)/100;
                pot += pot*range_random(quest_times/2,quest_times)/100;
                mar += mar*range_random(quest_times/2,quest_times)/100;
        }

        if( quest_times=query_temp("apply/add_exp", who) )
        {
                if( query("reborn/times", who) && !event ) quest_times /= 3;
                if( quest_times > 200 ) quest_times = 200;
                exp += exp*random(quest_times)/100;
        }
        
        if( quest_times=query_temp("apply/add_pot", who) )
                pot += pot*random(quest_times)/100;

        if( quest_times=query_temp("apply/add_mar", who) )
                mar += mar*random(quest_times)/100;
                                                        
        // 幫派榮譽點
        if( who->query_bunch() && BUNCH_D->query_bunch_efficient(who->query_bunch(), "exp") )
                exp *= 2;        
        if( who->query_bunch() && BUNCH_D->query_bunch_efficient(who->query_bunch(), "pot") )
                pot *= 2;
        if( who->query_bunch() && BUNCH_D->query_bunch_efficient(who->query_bunch(), "mar") )
                mar *= 2;

        if( who->query_family() && FAMILY_D->query_family_efficient(who->query_family(), "exp") )
                exp *= 2;        
        if( who->query_family() && FAMILY_D->query_family_efficient(who->query_family(), "pot") )
                pot *= 2;
        if( who->query_family() && FAMILY_D->query_family_efficient(who->query_family(), "mar") )
                mar *= 2;
                              
        if (! flag)
        {
                pot_limit=who->query_potential_limit()-query("potential", who);
                if (pot > pot_limit) pot = pot_limit;
                if (pot < 1) pot = 0;

                mar_limit=who->query_experience_limit()-query("experience", who);
                if (mar > mar_limit) mar = mar_limit;
                if (mar < 1) mar = 0;
        } else
        {
                if( who->query_potential_limit()<query("potential", who) )
                        pot = 1 + random(2);

                if( who->query_experience_limit()<query("experience", who) )
                        mar = 1;
        }

        // 魔幻獸
        if( exp > 100 && intp(rate = query("env/share_exp", who)) &&
            query("warcraft/file", who) && objectp(ob=find_object(query("warcraft/file", who))) )
        {
                if( rate < 0 ) rate = 0;
                if( rate > 100 ) rate = 100;
                warcraft_exp = exp * rate/100 + 1;
                ob->add("combat_exp", warcraft_exp);
                exp -= warcraft_exp;
        }

        // 元神
        if( exp > 100 && query("yuanshen", who) )
        {
                yuanshen_exp = exp / 4 + 1;
                add("yuanshen_exp", yuanshen_exp, who);
                exp -= yuanshen_exp;
        }

        // 生成提示信息
        if (stringp(msg = b["prompt"]))
                msg = HIG + msg + HIG "，你獲得了";
        else
                msg = HIG "通過這次鍛鍊，你獲得了";

        if (exp > 0) msg += chinese_number(exp) + "點經驗、";
        if (pot > 0) msg += chinese_number(pot) + "點潛能、";
        if (mar > 0) msg += chinese_number(mar) + "點實戰體會、";
        if (shen > 0) msg += chinese_number(shen) + "點正神、";
        if (shen < 0) msg += chinese_number(-shen) + "點負神、";
        if (score > 0) msg += chinese_number(score) + "點江湖閲歷、";
        if (weiwang > 0) msg += chinese_number(weiwang) + "點威望、";
        if (gongxian > 0) msg += chinese_number(gongxian) + "點門派功績、";
        if (gold > 0) msg += chinese_number(gold) + "兩黃金、";

        if( ob )
	{
	        msg += ob->name() + "獲得經驗" + chinese_number(warcraft_exp) + "點、";
        }

        if( query("yuanshen", who) )
	{
	        msg += "元神獲得經驗" + chinese_number(yuanshen_exp) + "點、";
        }

        msg += "能力得到了提升。\n" NOR;
        tell_object(who, sort_msg(msg));

        // bonus
        add("combat_exp", exp, who);
        addn("potential", pot, who);
        addn("experience", mar, who);
        addn("shen", shen, who);
        addn("score", score, who);
        addn("weiwang", weiwang, who);
        addn("family/gongji", gongxian, who);
        addn("balance", gold*10000, who);
}
