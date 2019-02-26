// dream_npc.c

#include <ansi.h>

#define MAX_POINT     180000

inherit NPC;

int accept_fight(object ob)
{
        kill_ob(ob);
        return -1;
}

int accept_kill(object ob)
{
        return 1;
}

int accept_hit(object ob)
{
        return 1;
}

void fight_ob(object ob)
{
        if( is_fighting() || !query("end_time") )
                return ::fight_ob(ob);

        set_temp("end_time", time() + query("end_time"));
        return ::fight_ob(ob);
}

varargs void unconcious(object defeater)
{
        object ob;

/*
        //if( query("end_boss") || query("fight_boss") )
        if( objectp(ob = previous_object(0)) && sscanf(base_name(ob), "/kungfu/skill/%*s") ) {
                full_self();
                return;
        }
*/
        die(defeater);
        return;
}

void init()
{
        // 隨機攻擊玩家
        if( userp(this_player()) && random(4) == 1 && !query_temp("apply/invisible", this_player()) )
        {
                kill_ob(this_player());
        }

        set("env/combatd", 4, this_player());
}

void die(object killer)
{
        object dob;             // 打暈這個NPC的人
        int n;                  // 可以獎勵的人的數目
        int exp;                // 需要瓜分的經驗
        int pot;                // 需要瓜分的潛能
        int exp2, pot2;
        object *t;              // 殺死我的人的隊伍列表
        object tob;
        int i, mar;
        object *inv, objenv;

        object gift_ob;
        string s_gift, *key_s_gift;
        int gift_point;

        // 定義獎勵物品列表
        mixed oblist;

        object env;
        object ob;

/*
        //if( query("end_boss") || query("fight_boss") )
        if( objectp(ob = previous_object(0)) && sscanf(base_name(ob), "/kungfu/skill/%*s") ) {
                full_self();
                return;
        }
*/

        if( time() < query_temp("end_time", this_object()) ) // 時間沒有到，死亡不了
        {
                addn("jing", query("max_jing") / 10);
                if( query("jing") > query("max_jing") ) set("jing", query("max_jing"));
                addn("eff_jing", query("max_jing") / 10);
                if( query("eff_jing") > query("max_jing") ) set("eff_jing", query("max_jing"));
                addn("qi", query("max_qi") / 10);
                if( query("qi") > query("max_qi") ) set("qi", query("max_qi"));
                addn("eff_qi", query("max_qi") / 10);
                if( query("eff_qi") > query("max_qi") ) set("eff_qi", query("max_qi"));
                message_vision(HIR "\n$N" HIR "全身泛起一道紅光，奇蹟般的活了下來！\n\n" NOR, this_object());
                return;
        }
        
        oblist = query("oblist");

        // 通知當前房間，以便計算刷新
        env = environment(this_object());
        env->npc_die(this_object());

        // 找到殺了我(NPC)或是打暈我的人
        if (! objectp(dob = killer))
                dob = query_last_damage_from();

        if (! dob)
        {
                destruct(this_object());
                return;
        }

        // 帝王符圖
        // 編號22-30
        if( query("quest_tuteng/start", dob) )
        {
                int n_tt;
                object ob_tt;

                if (random(10000) == 1)
                {
                        n_tt = 22 + random(14);
                        if (n_tt == 28 && random(10) > 1)n_tt = 25;
                        ob_tt = new("/clone/tuteng/diwang-suipian" + sprintf("%d", n_tt));
                        if (ob_tt)
                        {
                                write(HIG "你獲得了一張帝王符圖碎片。\n" NOR);
                                ob_tt->move(dob, 1);
                        }
                }
        }

        t = dob->query_team();

        if (objectp(dob) && environment(dob) == environment(this_object()))
        {
                exp = query("gift/exp");
                pot = query("gift/pot");

                n = 0;
                n = sizeof(t);


                if (n > 1)
                {
                        exp /= n;
                        pot /= n;
                }

                if (n)
                {
                        foreach(tob in t)
                        {
                                if (! objectp(tob))continue;

                                exp2 = exp;
                                pot2 = pot;

                                // 佩帶斬妖勛章增加10%
                                if( query_temp("apply/zhanyao", tob) )
                                {
                                        exp2 = exp2 + exp2 / 10;
                                        pot2 = pot2 + pot2 / 10;
                                }
                                // 佩帶十週年紀念勛章增加5%
                                if( query_temp("apply/year10", tob) )
                                {
                                        exp2 = exp2 + exp2 / 20;
                                        pot2 = pot2 + pot2 / 20;
                                }

                                if (objectp(tob) && living(tob))
                                {
                                        if (environment(tob) == environment(dob))
                                                GIFT_D->event_bonus(tob,
                                                        ([ "exp"      : exp2 + ((tob == dob) ? exp2 / 10 : 0),
                                                           "pot"      : pot2 + ((tob == dob) ? pot2 / 10 : 0),
                                                           "prompt"   : "你的隊伍殺死" + name() + "之後"]));
                                }
                        }
                }
                else
                {
                        // 佩帶斬妖勛章增加10%
                        if( query_temp("apply/zhanyao", dob) )
                        {
                                exp = exp + exp / 10;
                                pot = pot + pot / 10;
                        }
                        // 佩帶十週年紀念勛章增加5%
                        if( query_temp("apply/year10", dob) )
                        {
                                exp = exp + exp / 20;
                                pot = pot + pot / 20;
                        }

                        GIFT_D->event_bonus(dob,
                                ([ "exp"      : exp,
                                   "pot"      : pot,
                                   "prompt"   : "你在殺死" + name() + "之後"]));
                }
        }

        // 一定機率掉物品在殺我的人身上dob
        if (objectp(dob) && environment(dob) == environment(this_object()))
        {
                key_s_gift = keys(oblist);
                s_gift = key_s_gift[random(sizeof(key_s_gift))];
                gift_point = oblist[s_gift];

                // 判斷機率
                if( random(10) == 1
                        && random(MAX_POINT / ITEM_D->gift_point()) < gift_point )
                {
                        // 獲得物品--爆出物品
                        gift_ob = new(s_gift);
                        if (objectp(gift_ob))
                        {
                                message_vision(HIR "叮~~一聲，從$N" HIR "身上掉出一樣東西。\n" NOR, this_object(), dob);
                                set("who_get/id", query("id", dob), gift_ob);
                                set("who_get/time", time()+60, gift_ob);//一分鐘內只能自己撿取
                                gift_ob->move(environment(this_object()));
                        }
                }
        }

        // 掉出金錢及其他物品
        if (random(5) == 1)
        {
                inv = all_inventory(this_object());
                inv -= ({ 0 });
                i = sizeof(inv);
                while (i--)
                {
                        if (objectp(dob))
                        {
                                set("who_get/id", query("id", dob), inv[i]);
                                set("who_get/time", time()+60, inv[i]);
                        }
                        inv[i]->move(environment(this_object()));
                }
        }

        // 1/550000機率掉出無名銅人
        if (random(550000) == 1 && objectp(dob))
        {
                object ob_tongren;

                if( random(2) )
                        ob_tongren = new("/clone/tongren/tongren1");
                else
                        ob_tongren = new("/clone/tongren/tongren2");
                ob_tongren->move(dob, 1);
                write(HIR "你得到一個" + ob_tongren->name() + HIR "。\n");
        }

        //1/5000機率掉出蓬萊仙果
        if (random(5000) == 1 && objectp(dob))
        {
                object ob_xianguo;

                ob_xianguo = new("/clone/fam/item/penglai-xianguo");
                ob_xianguo->move(dob, 1);
                write(HIR "你得到一顆" + ob_xianguo->name() + HIR "。\n");
        }

        // 在九頭蛇領地殺死九頭蛇可獲取少量體會
        objenv = environment(this_object());
        if( objectp(objenv) && query("short", objenv) == "九頭蛇領地" )
        {
                mar = 25;
                if( query("experience", dob) >= 2000000000) mar=0;
                if( query("experience", dob)-query("learned_experience", dob) >= 10000000) mar=0;
                addn("experience", mar, dob);
        }

        destruct(this_object());

        return;
}
