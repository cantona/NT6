// This program is a part of NT MudLIB
// person used in quest
// update by Lonely

#include <ansi.h>

inherit CLASS_D("generate") + "/chinese";

#define GIFT_DIR        "/clone/gift/"
string  *GF_LIST = ({
        "xiandan", "shenliwan", "unknowdan", "xisuidan",
});

int  accept_object(object who, object ob);
int do_nod(string arg);
void random_move();
int  leave();
int  is_stay_in_room()  { return 1; }

void create()
{
        ::create();
        set("gender", "男性");
        set("age", 30 + random(30));
        set("long", "");
        set("attitude", "friendly");
        set("chat_chance", 30);
        set("chat_msg", ({ (: random_move :) }));
        set("chat_chance_combat", 120);
        set("scale", 150);
        set("no_get", 1);
        set("auto_perform", 2);

        set_temp("apply/armor", 100);
        set_temp("apply/damage", 15);
        set_temp("born_time", time());
        set_temp("dest_time", 1200 + time());

        add_money("silver", 10 + random(20));

        if (clonep()) keep_heart_beat();
}

void init()
{
        add_action("do_nod", "nod");
}

void set_from_me(object me, int scale)
{
        int exp;
        mapping my;

        NPC_D->init_npc_skill(this_object(), NPC_D->check_level(me) - 2);
        my = query_entire_dbase();

        if (my["max_qi"] > 60000)
                my["max_qi"] = 60000;

        if (my["max_jing"] < my["max_qi"] / 2)
                my["max_jing"] = my["max_qi"] / 2;

        if (my["max_jing"] > 30000)
                my["max_jing"] = 30000;

        my["eff_jing"] = my["max_jing"];
        my["jing"] = my["max_jing"];
        my["eff_qi"] = my["max_qi"];
        my["qi"] = my["max_qi"];

        my["quest_count"]=query("quest_count", me);

        // 這裡修改
        exp=query("combat_exp", me)*12/10;
        if (exp > query("combat_exp"))
                set("combat_exp", exp);


        if (my["combat_exp"] > 200000 && random(100) < 5)
        {
                // 經驗 > 200K，5%幾率出現多個敵人
                set_temp("multi-enemy", 1);
        }


        my["jiali"] = query_skill("force") / 3;
        if (query("place") == "西域")
                set_temp("dest_time", 900 + time());
        else
                set_temp("dest_time", 600 + time());
}

int do_nod(string arg)
{
        object obj;
        object me = this_player();
        object ob = this_object();
        int amount;

        if( !arg || arg != query("id", ob) || 
            !query_temp("family_quest/waiting", me) )
                return 0;

        me->command("nod");

        if( query_temp("family_quest/ob", me) )
        {
                message_sort(HIW "只見$N" HIW "長笑三聲：“哈哈哈，識時務者為俊傑，" +
                        RANK_D->query_respect(me) + "果然是明白人，嘿嘿，這區區仙丹" +
                        "就歸你了，哈哈。”\n\n" NOR,
                        ob, me);
                obj = new(GIFT_DIR + GF_LIST[random(sizeof(GF_LIST))]);

                tell_object(me, HIR + ob->name() + "遞給了你" + obj->name() +
                        HIR "以後，吐出一口鮮血，揚長而去。\n" NOR);
                if (! obj->move(me))
                        obj->move(environment(me));
                delete_temp("family_quest", me);
                destruct(ob);
                return 1;
        }
        amount=query_temp("family_quest/waiting", me);

        message_sort(HIW "只見$N" HIW "長笑三聲：“哈哈哈，識時務者為俊傑，" +
                RANK_D->query_respect(me) + "果然是明白人，嘿嘿，這區區" +
                chinese_number(amount) + "兩黃金就歸你了，哈哈。”\n\n" NOR,
                ob, me);
        MONEY_D->pay_player(me, amount * 10000);
        tell_object(me, HIR + ob->name() + "遞給了你" + chinese_number(amount) +
                "兩黃金以後，吐出一口鮮血，揚長而去。\n" NOR );
        delete_temp("family_quest", me);
        destruct(ob);
        return 1;
}

void kill_ob(object ob)
{
        int lvl;

        if (! is_busy())
                exert_function("powerup");

        if( query("quest/id", ob) != query("id") )
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
        set_temp("quest/help_count", n, ob);
        message("vision", HIR "說時遲，那時快！突然轉出" +
                          chinese_number(n) +
                          "個人，一起沖上前來，看來是早"
                          "有防備！\n" NOR, environment());

        // 生成幫手
        obs = allocate(n);
        while (n--)
        {
                obs[n] = new(CLASS_D("generate") + "/killed.c");
                NPC_D->set_from_me(obs[n], ob, 200);
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

int filter_to_bonus(object ob, object aob)
{
        object *obs;

        if (! playerp(ob) || ! living(ob) ||
            ! ob->is_killing(query("id")))
                // 必須是玩家並且參與屠殺我(NPC)
                return 0;

        // 協助的對象一致
        if( aob == query_temp("quest/assist", ob) )
                return 1;

        // 都在一個陣法中
        obs = ob->query_array_member();
        if (sizeof(obs) > 0 && member_array(aob, obs) != -1)
                return 1;

        // 都在一個隊伍中
        obs = ob->query_team_member();
        if (sizeof(obs) > 0 && member_array(aob, obs) != -1)
                return 1;
}

// remove
void remove()
{
        object qob;

        if (objectp(qob = query_temp("quest_ob")))
        {
                // 這個人已經消失了，取消相關聯的任務
                destruct(qob);
        }

        ::remove();
}

// 隨即重新放置
void random_place(string msg)
{
        object old_env;
        object qob;
        string *not_place;
        string new_place;
        int limit;
        int qcount;

        // 如果原先創建了任務，就直接修改信息
        if (objectp(qob = query_temp("quest_ob")))
                set("introduce", msg, qob);
        else
                qob = new("/clone/quest/avoid");

        // 隨即選擇另外一個地方放置NPC
        old_env = environment();
        not_place = ({ query("place") });

        if (query("combat_exp") < 500000)
                not_place += ({ "大理一帶" });

        if (query("combat_exp") < 800000)
                not_place += ({ "西域" });

        NPC_D->place_npc(this_object(), not_place);

        // 根據格式化消息生成結果
        msg = replace_string(msg, "$N", name(1));

        qcount = query("quest_count");
        if ((qcount < 100 || qcount >= 900) && random(10) ||
            (qcount >= 100 && qcount < 900) && random(50))
        {
                new_place = query("place");
                if (new_place == "西域")
                        limit = 1800;
                else
                        limit = 1200;
        } else
        {
                new_place = "很遠的地方";
                limit = 1800;

                // 減少打聽的價格
                set("ask_cheap", 3);
        }
        set_temp("dest_time", limit + time());
        msg = replace_string(msg, "PLACE",  new_place);

        // 初始化並記錄這個任務
        set("introduce", msg, qob);
        qob->init_quest(name(1), old_env);
        set_temp("quest_ob", qob);

        return;
}

// 暈倒的時候有機會逃走
void unconcious()
{
        object *obs;
        object ob;
        object me;
        int amount = 10 + random(10);
        mapping my;
        string msg;
        string quester;
        string *condition = ({
                "氣喘吁吁，就要不支", "頭重腳輕，馬上就倒",
                "嘔血成升，眼冒金星", "傷痕累累，無力招架",
        });

        if (! query_temp("is_helper") && ! query_temp("help_ob"))
        {
                if (random(100) < 8)
                {
                        // 10%幾率逃走
                        switch (random(8))
                        {
                        case 0:
                                msg = HIC "$N" HIC "狂叫一聲，狂吐幾"
                                      "口鮮血，眼看就已不支，忽然一"
                                      "道黑影竄出，接連攻出數招，逼"
                                      "退$n" HIC "，只在這麼一瞬間，"
                                      "此人已經扶起$N" HIC "，遁逃而"
                                      "走，竟然未留半點痕跡。\n" NOR;
                                break;
                        case 1:
                                msg = HIC "$N" HIC "搖搖欲墜，眼看就"
                                      "要跌倒，忽然口中噴出一口鮮血"
                                      "，$n" HIC "連忙側身一避，就在"
                                      "此時，$N" HIC "奮然振作精神，"
                                      "提氣一縱，竟然飄出十數丈之遠"
                                      "，令人目瞪口呆！只見$N" HIC
                                      "剎間變做一個黑影，漸漸消失。"
                                      "\n" NOR;
                                break;
                        case 2:
                                msg = HIC "在$n" HIC "一陣狂攻之下，"
                                      "$N" HIC "只有招架之功，哪裡還"
                                      "有還手之力？眼看就要命喪$n" HIC
                                      "之手，$N" HIC "忽然招式一變，"
                                      "精妙無方，竟是世上罕見！$n" HIC
                                      "略一疏神，已被$N" HIC "連環數"
                                      "招逼退，只見$N" HIC "邁開大步"
                                      "，逃遁而走。\n" NOR;
                                break;
                        case 3:
                                msg = HIC "只見$N" HIC "深吸一口氣"
                                      "，神色略微好了一些，陡然迸發"
                                      "出驚天動地的一聲大吼，直震得"
                                      "$n" HIC "發耳欲聵！僅這一霎"
                                      "，$N" HIC "身形一轉，飄然退"
                                      "去，竟讓$n" HIC "措手不及，"
                                      "追趕不上！\n" NOR;
                                break;
                        case 4:
                                msg = HIC "$n" HIC "連連進擊，眼看"
                                      "便要得手，接連數招，讓$N" HIC
                                      "已是避無可避，退無可退！$N"
                                      HIC "神色神色倉皇，急切間猛地"
                                      "咬中舌尖，“噗”的吐出！$n"
                                      HIC "只見眼前一陣紅霧，待得霧"
                                      "散去，哪裡還有$N" HIC "的影"
                                      "子？\n" NOR;
                                break;
                        case 5:
                                msg = HIC "$N" HIC "再退一步，卻慢"
                                      "了小許，腿上早中招！一聲慘"
                                      "呼，人已跌倒。$n" HIC "見狀"
                                      "趕上前去，忽然眼前星光閃閃"
                                      "，倉皇下急退，只聽有人哈哈"
                                      "大笑道：“$N" HIC "莫慌，我"
                                      "來也！”說罷又是一撒手，數"
                                      "十根銀針飛出，待得$n" HIC
                                      "抵擋兩下，那人早扶起$N" HIC
                                      "遁去了。\n" NOR;
                                break;
                        case 6:
                                msg = HIC "$N" HIC "晃了兩下，忽然"
                                      "跌倒。$n" HIC "收住招式，笑道"
                                      "：“$N" HIC "，你……”話音未"
                                      "落，忽見$N" HIC "驀的竄起，一"
                                      "招直奔$n" HIC "的要害，$n" HIC
                                      "大吃一驚！慌忙招架，只覺得內"
                                      "息紊亂，幾欲嘔吐！$N" HIC "也"
                                      "不追擊，只是急奔而走，$n" HIC
                                      "連運幾口氣，去了胸前煩悶，卻"
                                      "已不見$N" HIC "的蹤影。\n" NOR;
                                break;
                        default:
                                msg = HIC "$N身負重傷，已然不敵，悲"
                                      "憤間只放聲疾呼，一時震得$n"
                                      HIC "耳鼓欲破，攻勢少緩。$N"
                                      HIC "猛然見到有機可乘，哪裡肯"
                                      "放過，連出數招，殺出一條血路"
                                      "，就此不見。\n" NOR;
                                break;
                        }

                        clean_up_enemy();
                        obs = query_enemy();
                        if (sizeof(obs) > 0) ob = obs[0]; else ob = 0;
                        if (! objectp(ob))
                                msg = replace_string(msg, "$n", "眾人");
                        message_sort("\n" + msg, this_object(), ob);

                        // 解除NPC的中毒狀態
                        clear_condition(0);

                        // 恢復NPC的力氣
                        my = query_entire_dbase();
                        my["eff_jing"] = my["max_jing"];
                        my["jing"]     = my["max_jing"];
                        my["eff_qi"]   = my["max_qi"] * 2 / 3;
                        my["qi"]       = my["eff_qi"];
                        my["neili"]    = my["max_neili"] * 2;
                        if (! intp(query_temp("escape_times")))
                                set_temp("escape_times", 1);
                        else
                                addn_temp("escape_times", 1);

                        // 登記一個任務，以便玩家可以追蹤他的行跡
                        switch (random(9))
                        {
                        case 0:
                                msg = "聽說$N被人打傷逃走，據說是躲到PLACE去了。";
                                break;
                        case 1:
                                msg = "聽說$N和人動手，差點被打死，不過最"
                                      "後還是僥幸逃走了，好像去了PLACE。";
                                break;
                        case 2:
                                msg = "聽說那$N和人一場血戰，最後還是全身"
                                      "而退，好像是去了PLACE吧。";
                                break;
                        case 3:
                                msg = "$N聽說是在PLACE啊，不過前一陣好像來過這裡的。";
                                break;
                        case 4:
                                msg = "聽說$N被人打死了吧？咦？不過聽人說"
                                      "在PLACE也見過他呀！";
                                break;
                        case 5:
                                msg = "這事我也不太清楚，不過聽說他好像在PLACE。";
                                break;
                        case 6:
                                msg = "你找他幹啥？他不是在PLACE麼？";
                                break;
                        case 7:
                                msg = "前兩天他還來過我們這兒呢，現在應該"
                                      "是去了PLACE吧。";
                        default:
                                msg = "$N呀，有人說在PLACE看到過他，好像還受傷了。";
                                break;
                        }

                        random_place(msg);
                        remove_all_enemy(1);
                        return;
                } else
                if (objectp(me = query_last_damage_from()) &&
                    environment() == environment(me) &&
                    !query_temp("family_quest/waiting", me) )
                {
                        switch (random(20))
                        {
                        case 1:
                                message_sort(HIR "\n眼見$N" HIR + condition[random(sizeof(condition))] +
                                        "，突然$N大喝一聲，急退幾步，\n“撲通”給$n跪了下來。"
                                        "\n" NOR, this_object(), me);
                                tell_object(me, HIW + this_object()->name() + "突然從懷裡掏出一堆白花花的銀子，小聲"
                                        "對你道：“這位" + RANK_D->query_respect(me) + "，\n你"
                                        "就網開一面（nod）如何，這" + chinese_number(amount) +
                                        "兩黃金就歸你了！”\n" NOR);
                                clean_up_enemy();
                                remove_all_enemy(1);
                                clear_condition(0);
                                set("qi", 1, this_object());
                                set("jing", 1, this_object());
                                set_temp("family_quest/waiting", amount, me);
                                return;
                        case 2:
                                message_sort(HIR "眼見$N" HIR + condition[random(sizeof(condition))] +
                                        "，突然$N大喝一聲，急退幾步，\n“撲通”給$n跪了下來。"
                                        "\n" NOR, this_object(), me);
                                tell_object(me, HIW + this_object()->name() + "突然從懷裡掏出一粒仙丹，小聲"
                                        "對你道：“這位" + RANK_D->query_respect(me) + "，\n你"
                                        "就網開一面（nod）如何，這仙丹就歸你了！”\n" NOR);
                                clean_up_enemy();
                                remove_all_enemy(1);
                                clear_condition(0);
                                set("qi", 1, this_object());
                                set("jing", 1, this_object());

                                set_temp("family_quest/waiting", amount, me);
                                set_temp("family_quest/ob", 1, me);
                                return;
                        default:
                                break;
                        }
                }
        }

        if (stringp(quester = query_temp("quester")))
        {
                // 如果找到領取該quest的人
                if (objectp(ob = find_player(quester)))
                        set_temp("quest/escape_times", query_temp("escape_times"), ob);
        }
        ::unconcious();
}



// 當任務的NPC死亡的時候，檢查是否可以進行獎勵某些玩家。獎勵
// 的對象：幫助任務者完成這個任務的所有人， 當然首先要求殺的
// 這個人是任務的完成對象，其次就是在這個場景中對該NPC下了殺
// 命令，並且協助了任務的完成者的玩家。
void die(object killer)
{
        mapping quest;          // 任務
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
        int score;              // 需要瓜分的閱歷
        int extra_exp;          // 打暈的人的額外經驗
        int extra_pot;          // 打暈的人的額外潛能
        string quester;         // 需要完成這個任務的玩家ID
        object qob;             // 需要完成這個任務的玩家對象
        object ob;              // NPC暴出的物品
        string *ob_list = ({    // 任務賦予NPC身上的暴出隨機物品
                "/clone/gift/puti-zi",
                "/clone/gift/jiuzhuan",
                "/clone/gift/tianxiang",
                "/clone/gift/xuanhuang",
                "/clone/fam/gift/int3",
                "/clone/fam/gift/con3",
                "/clone/fam/gift/dex3",
                "/clone/fam/gift/str3",
                "/clone/fam/item/stone1",
                "/clone/fam/item/stone2",
                "/clone/fam/item/stone3",
                "/clone/fam/item/stone4",
                "/clone/fam/etc/lv5f",
                "/clone/fam/etc/lv5d",
                "/clone/fam/etc/lv7c",
                "/clone/fam/etc/lv7d",
                "/clone/fam/etc/lv7b",
                "/clone/fam/etc/lv7a",
                "/clone/fam/etc/prize5",
                "/clone/fam/item/baxian",
                "/clone/fam/item/kunlun",
                "/clone/fam/item/leihuo",
                "/clone/fam/item/lihuo",
                "/clone/fam/item/zhenlong",
                "/clone/tessera/rune16", 
                "/clone/tessera/rune17", 
                "/clone/tessera/rune18", 
                "/clone/tessera/rune19", 
                "/clone/tessera/rune20", 
        });

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
                        if( query("quest/id", qob) == query("id") )
                                set("quest/notice", "die", qob);
                        UPDATE_D->global_destruct_player(qob, 1);
                }

                if( dob && query("quest/id", dob) == query("id") )
                        // 我自己打死的
                        break;

                if( dob)aob=query_temp("quest/assist", dob);
                if( aob && query("quest/id", aob) == query("id") )
                        // 我協助別人殺死的
                        break;

                if (dob && dob->in_array() && dob->query_array_status())
                        // 我組陣殺死的
                        break;

                if (dob && dob->in_team())
                        // 我組隊殺死的
                        break;

                // 非任務所有者或是任務所有者協助的人殺死，則記錄之。
                /*
                CHANNEL_D->do_channel(this_object(), "rumor",
                                      sprintf("聽說%s被人殺死了。", name()));
                log_file("static/killed_die", sprintf("%s %s(%s) died at %s because %s.\n",
                                                      log_time(), name(), query("id"),
                                                      environment()->short(),
                                                      dob?sprintf("%s(%s)",dob->name(1),query("id", dob)):"none"));
                */

                break;
        }

        if (! aob) aob = dob;

        if (! aob)
        {
                // 沒有找到 QUEST 的屬主
                ::die(killer);
                return;
        }

        // 察看目前正在殺我的人，是否也有值得獎勵的
        obs = all_inventory(environment(this_object()));
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
                switch(query("quest/level", aob) )
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
                if ((scale = sizeof(query_temp("help_count") +
                     query_temp("escape_times") * 2)) > 0)
                {
                        exp += exp * scale / 2;
                        pot += pot * scale / 2;
                }
                // 所有人均分經驗：為什麼除以n + 2？這是因為
                // 打暈我的人分兩份經驗，所以是n + 1，再加上
                // 領任務的這個人算1，那麼就是n + 2。
                if (n > 1)
                {
                        exp *= 1.2;
                        pot *= 1.2;
                        weiwang *= 1.2;
                        score *= 1.2;
                }
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

        // 根據玩家連續完成的任務數量來隨機暴出物品
        if ((query_temp("is_helper") || query_temp("help_ob") ||
            query_temp("escape_times")))
        {
                // 有幫手、幫手、或者逃跑過的NPC有九成的機率物品被暴下來
                ob = new(ob_list[random(sizeof(ob_list))]);
                message_vision(HIY"$N"HIY"身子一退，掉下一"+query("unit", ob)+
                        ob->name() + HIY "。\n\n" NOR, this_object());
                ob->move(environment());
        }

        /*
        // 無需要完成這個任務的玩家？或者無法生成遠程任務，
        // 那麼就正常死亡
        // 如果不是自己殺死的，不允許發送遠程任務
        if (! qob || random(20) ||
            quester != query("id", dob) || 
            ! mapp(quest = QUEST_D->prepare_quest(qob)))
        {
                ::die(killer);
                return;
        }

        // 人物正常完成
        set("quest/finished", 1, qob);

        // 使用書信分配任務
        QUEST_D->remote_assign_quest(qob, quest);
        */

        // 正常死亡
        ::die(killer);

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

                /*
                CHANNEL_D->do_channel(this_object(), "rumor",
                                      sprintf("聽說%s隱居到了深山老澤，從此不再出沒在世間。", name()));
                log_file("static/killed_die", sprintf("%s %s(%s) vanished because timeout(%d:%d).\n",
                                                      log_time(), name(), query("id"),
                                                      time() - query_temp("born_time"),
                                                      query_temp("dest_time") - query_temp("born_time")));
                */
                destruct(this_object());
                return;
        }
        NPC_D->random_move(this_object());
}

