// This program is a part of NT MudLIB

#include <ansi.h>

inherit CLASS_D("generate") + "/chinese";

#include <slough.h>

void random_move();
int  is_stay_in_room()  { return 1; }

void create()
{
        string *long;

        ::create();
        long = query("from");
        set("gender", "男性");
        set("nickname", HIB "殺人狂魔" NOR);
        set("age", 30 + random(30));
        if (sizeof(long) < 1)
                set("long", "一個神祕的人。\n");
        else
                set("long", long[random(sizeof(long))]);
        set("attitude", "friendly");
        set("chat_chance", 30);
        set("chat_msg", ({ (: random_move :) }));
        set("chat_chance_combat", 120);
        set("scale", 150);
        set("no_get", 1);

        set_temp("apply/armor", 100);
        set_temp("apply/damage", 15);
        set_temp("born_time", time());
        set_temp("dest_time", 1500 + time());

        add_money("silver", 10 + random(20));

        if (clonep()) keep_heart_beat();
}

void set_from_me(object me)
{
        int exp;
        mapping my;

        NPC_D->init_npc_skill(this_object(), NPC_D->check_level(me) -2);
        my = query_entire_dbase();

        if (my["max_qi"] > 6000)
                my["max_qi"] = 6000;

        if (my["max_jing"] < my["max_qi"] / 2)
                my["max_jing"] = my["max_qi"] / 2;

        if (my["max_jing"] > 3000)
                my["max_jing"] = 3000;

        my["eff_jing"] = my["max_jing"];
        my["jing"] = my["max_jing"];
        my["eff_qi"] = my["max_qi"];
        my["qi"] = my["max_qi"];
        my["quest_count"]=query("quest_count", me);

        exp=query("combat_exp", me)*11/10;
        if (exp > query("combat_exp"))
                set("combat_exp", exp);


        if (my["combat_exp"] > 5000000 && random(100) < 21)
        {
                // 經驗 > 200K，21%機率出現多個敵人
                set_temp("multi-enemy", 1);
        }

        my["jiali"] = query_skill("force") / 3;
}

void init()
{
        object ob, baixing, env;
        object killer = this_object();

        ob = this_player();

        if( !query_temp("quester", this_object()) )
                return;

        if( query("id", ob) == query_temp("quester") && 
            query("slough/check", ob) )
        {
                killer->fight_ob(ob);
                ob->fight_ob(killer);
                COMBAT_D->do_attack(killer,ob,query_temp("weapon", killer),0);
                ob->remove_all_enemy(0);
                killer->remove_all_enemy(0);

                message_vision(
                        HIB "$n一看到$N, 不由分説，抄出家夥給你一記後，立馬溜之大吉！\n" NOR,
                        ob, killer);

                tell_object(ob,"你終於查清殺人狂魔原來是"+query("family/family_name", killer)+"的敗類。\n");

                place_npc(killer, ob);
                set("slough/inquiry", 1, ob);
        } else
        if( query("slough/chased", ob) && 
            !query("baixing", killer) && query("id", ob) == query_temp("quester") )
        {
                message_vision(
                        HIB "$n一看到$N，冷笑了一聲: “又一個活得不耐煩的傢伙，自尋死路！” \n" NOR,
                        ob, killer);

                this_object()->kill_ob(ob);
                ob->kill_ob(this_object());

                remove_call_out("kill_baixing");
                call_out("kill_baixing", 1, ob);
        } else
        if( query("slough/chased", ob) && 
            query("baixing", killer) && query("id", ob) == query_temp("quester") )
        {
                message_sort(
                        HIB "$n不屑地朝$N説道: “原來就是你一直在妨礙老子殺人！人我早殺完了，"
                        "你就來收屍吧，不過就不知道誰能幫你收屍了！” \n" NOR, ob, killer);
                command("heihei"+query("id", ob));

                this_object()->set_leader(ob);
                this_object()->kill_ob(ob);
                ob->kill_ob(this_object());
        }
}

void kill_ob(object ob)
{
        int lvl;

        exert_function("powerup");

        if( query("slough/id", ob) != query("id") )
        {
                ::kill_ob(ob);
                return;
        }

        if (lvl = query_temp("multi-enemy"))
        {
                // 出現多個敵人
                delete_temp("multi-enemy");
                call_out("do_help_me", 1 + random(2), ob);
        }
        ::kill_ob(ob);
}

void do_help_me(object ob)
{
        if (! objectp(ob) || environment(ob) != environment())
                return;

        switch (random(3))
        {
        case 0:
                message_vision(HIW "\n$N" HIW "大聲喝道：“好一個" +
                               ob->name(1) +
                               HIW "！各位，不要再等了，快出來幫" +
                               RANK_D->query_self(this_object()) +
                               "一把！”\n" NOR, this_object(), ob);
                break;

        case 1:
                message_vision(HIW "\n$N" HIW "忽然撮舌吹"
                               "哨，你聽了不禁微微一愣。\n" NOR,
                               this_object());
                break;

        case 2:
                message_vision(HIW "\n$N" HIW "一聲長嘯，聲音"
                               "綿泊不絕，遠遠的傳了開去。\n" NOR,
                               this_object());
                break;
        }

        call_out("do_continue_help", 1 + random(4), ob);
}

void do_continue_help(object ob)
{
        int n;
        object *obs;

        if (! objectp(ob) || environment(ob) != environment())
                return;

        n = random(3) + 1;
        set_temp("slough/help_count", n, ob);
        message("vision", HIR "説時遲，那時快！突然轉出" +
                          chinese_number(n) +
                          "個人，一起衝上前來，看來是早"
                          "有防備！\n" NOR, environment());

        // 生成幫手
        obs = allocate(n);
        while (n--)
        {
                obs[n] = new(CLASS_D("generate") + "/slough_killed.c");
                NPC_D->set_from_me(obs[n], ob, 100);
                delete_temp("multi-enemy", obs[n]);
                set_temp("help_who", this_object(), obs[n]);
                set_temp("is_helper", 1, obs[n]);
        }

        // 參與戰鬥
        set_temp("help_ob", obs);
        set_temp("help_count", sizeof(obs));
        obs->move(environment());
        obs->set_leader(this_object());
        obs->kill_ob(ob);
}

void start_kill(object ob)
{
        int t;
        if(! objectp(ob))
        {
                destruct(this_object());
                return;
        }
        t=query("combat_exp", ob)/10000000;
        if (t < 1) t = 1;
        if (t > 5) t = 5;

        remove_call_out("kill_baixing");
        call_out("kill_baixing", (t * 90 + 30), ob);
}

int kill_baixing(object ob)
{
        object baixing;

        if( !query("baixing", this_object()) )
        {
                baixing = new("/quest/quest3/baixing");
                set("waiting",query("id",  ob), baixing);
                baixing->move(environment(this_object()));

                this_object()->set_leader(baixing);
                baixing->set_leader(this_object());
                kill_ob(baixing);
                set("baixing",query("id", baixing));
        }
        return 1;
}

int filter_to_bonus(object ob, object aob)
{
        if (! playerp(ob) || ! living(ob) ||
            ! ob->is_killing(query("id")))
                // 必須是玩家並且參與屠殺我(NPC)
                return 0;

        // 協助的對象一致
        return (aob == query_temp("quest/assist", ob));
}

// 當任務的NPC死亡的時候，檢查是否可以進行獎勵某些玩家。獎勵
// 的對象：幫助任務者完成這個任務的所有人， 當然首先要求殺的
// 這個人是任務的完成對象，其次就是在這個場景中對該NPC下了殺
// 命令，並且協助了任務的完成者的玩家。
void die(object killer)
{
        object *obs;            // 場景中所有可以獎勵的
        object dob;             // 打暈這個NPC的人
        object hob;             // 協助者
        object aob;             // 被協助者
        int qlevel;             // 本次任務的等級
        int lvl;                // NPC的等級
        int scale;              // NPC呼叫的幫手和逃跑的次數
        int n;                  // 可以獎勵的人的數目
        int exp;                // 需要瓜分的經驗
        int pot;                // 需要瓜分的潛能
        int weiwang;            // 需要瓜分的威望
        int score;              // 需要瓜分的閲歷
        int extra_exp;          // 打暈的人的額外經驗
        int extra_pot;          // 打暈的人的額外潛能
        string quester;         // 需要完成這個任務的玩家ID
        object qob;             // 需要完成這個任務的玩家對象
        object baixing;

        // 找到殺了我(NPC)或是打暈我的人
        if (! objectp(dob = killer))
                dob = query_defeated_by();

        if( objectp(dob) && query_temp("owner", dob) )
                dob=query_temp("owner", dob);

        while (1)
        {
                // 記錄：此任務已經終止
                if (stringp(quester = query_temp("quester")))
                {
                        qob = UPDATE_D->global_find_player(quester);
                        if( query("slough/id", qob) == query("id") )
                                set("slough/notice", "die", qob);
                        UPDATE_D->global_destruct_player(qob, 1);
                }

                if( dob && query("slough/id", dob) == query("id") )
                        // 我自己打死的
                        break;

                if( dob)aob=query_temp("quest/assist", dob);
                if( aob && query("slough/id", aob) == query("id") )
                        // 我協助別人殺死的
                        break;

                // 非任務所有者或是任務所有者協助的人殺死，則記錄之。
                CHANNEL_D->do_channel(this_object(), "info",
                                      sprintf("聽説%s被人殺死了。", name()));

                break;
        }

        if (! aob) aob = dob;

        if (! aob)
        {
                remove_call_out("kill_baixing");
                // 沒有找到 QUEST 的屬主
                ::die();
                return;
        }

        if (query("baixing") &&
             objectp(baixing = present(query("baixing", environment(this_object())))))
        {
                message_vision(CYN "$N對$n表示衷心的感謝！\n" NOR, baixing, dob);
                baixing->command("bye"+query("id", dob));
                destruct(baixing);
        }

        if (! query_temp("baixing_killed"))
        {
                set("slough/succeed", 1, dob);
                tell_object(dob,
                        HIY "由於你的卓越表現，成功的解救了當地的百姓！\n" NOR);
        }

        if( query("id", dob) == query_temp("quester") && 
            query("slough/succeed", dob) != 1 )
        {
                tell_object(dob,
                        HIW "由於你的失誤，未能成功解救受害百姓！\n" NOR);
        }

        // 察看目前正在殺我的人，是否也有值得獎勵的
        obs = all_inventory(environment());
        obs = filter_array(obs, (: filter_to_bonus :), aob);

        if ((n = sizeof(obs)) > 0)
        {
                // 查找打暈我的人：不是殺死我的人
                dob = query_defeated_by();

                // 獎勵多少呢？總共獎勵供所有的人分，最後每
                // 人加上一點隨機量，其中打暈這個人的玩家獲
                // 得額外的一些獎勵。
                lvl = NPC_D->check_level(this_object());
                exp = 15 + random(10) + lvl;
                pot = 9 + random(5) + lvl;
                weiwang = 8 + random(6) + lvl / 2;
                score = 9 + random(6) + lvl / 2;

                // 根據這個任務的等級進行獎勵調整
                switch(query("slough/level", aob) )
                {
                case 1:
                        break;
                case 2:
                        exp += exp / 2;
                        pot += pot / 2;
                        weiwang += weiwang / 2;
                        score += score / 2;
                        break;
                case 3:
                        exp += exp;
                        pot += pot;
                        weiwang += weiwang;
                        score += score;
                        break;
                default:
                        exp = exp / 2 + 1;
                        pot = pot / 2 + 1;
                        weiwang = weiwang / 2 + 1;
                        score = score / 2 + 1;
                        break;
                }
                // 如果NPC呼叫了幫手，則可以獲得額外經驗
                if (scale = sizeof(query_temp("help_count")) > 0)
                {
                        exp += exp * scale;
                        pot += pot * scale;
                }
                // 所有人均分經驗：為什麼除以n + 2？這是因為
                // 打暈我的人分兩份經驗，所以是n + 1，再加上
                // 領任務的這個人算1，那麼就是n + 2。
                exp = exp / (n + 2) + 1;
                pot = pot / (n + 2) + 1;
                weiwang = weiwang / (n + 2) + 1;
                score = score / (n + 2) + 1;

                // 計算打暈我的額外獎勵
                if (objectp(dob) && member_array(dob, obs) != -1)
                {
                        extra_exp = 1 + random(exp);
                        extra_pot = 1 + random(pot);
                        if( query("combat_exp", dob)<query("combat_exp")/2 )
                        {
                                // 出手的人武功比較低，獲得的額外獎勵多
                                extra_exp *= 2;
                                extra_pot *= 2;
                        } else
                        if( query("combat_exp", dob)>query("combat_exp")*2 )
                        {
                                // 出手的人武功太高，獲得的額外獎勵少
                                extra_exp /= 2;
                                extra_pot /= 2;
                        }
                }

                // 進行獎勵
                foreach (hob in obs)
                {
                        // 調用延遲獎勵，為什麼這麼調用？很簡單，
                        // 因為我希望玩家在看到NPC死了以後才能夠
                        // 看到獎勵。
                        GIFT_D->delay_bonus(hob, ([ "exp"     : exp + random(4) +
                                                    ((hob == dob) ? extra_exp : 0),
                                                    "pot"     : pot + random(3) +
                                                    ((hob == dob) ? extra_pot : 0),
                                                    "weiwang" : weiwang + random(3),
                                                    "score"   : score + random(3),
                                                    "prompt"  : "擊斃" + name() + "之後" ]));
                }
        }

        remove_call_out("kill_baixing");
        // 正常死亡
        ::die();

        return ;
}

int accept_fight(object ob)
{
        command("say 好！咱們就比劃比劃！");
        kill_ob(ob);
        return 1;
}

int accept_hit(object ob)
{
        command("say 你死去吧！");
        kill_ob(ob);
        return 1;
}

int accept_kill(object ob)
{
        command("say 哼！找死！");
        return 1;
}

void random_move()
{
        if (query_temp("is_helper"))
        {
                // is a helper
                if (! environment())
                {
                        // not in environment? unavaliable npc.
                        destruct(this_object());
                        return;
                }

                if (! query_temp("help_who"))
                {
                        // owner is killed. destruct this helper
                        if (! living(this_object()))
                                message_vision("$N緩緩的醒了過來。\n",
                                               this_object());

                        message_vision("$N看看四周，急匆匆的逃走了。\n",
                                       this_object());
                        destruct(this_object());
                        return;
                }

                // move with owner
                return;
        }

        if (time() > query_temp("dest_time"))
        {
                message_vision("$N急急忙忙的走了。\n", this_object());
                CHANNEL_D->do_channel(this_object(), "info",
                                      sprintf("聽説%s隱居到了深山老澤，從此不再出沒在世間。", name()));
                log_file("static/killed_die", sprintf("%s %s(%s) vanished because timeout(%d:%d).\n",
                                                      log_time(), name(), query("id"),
                                                      time() - query_temp("born_time"),
                                                      query_temp("dest_time") - query_temp("born_time")));
                destruct(this_object());
                return;
        }
        NPC_D->random_move(this_object());
}