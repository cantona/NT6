// 玩家任務：deliver.c

#include <ansi.h>
#include <quest.h>

inherit QUEST_OB;

#define QOB             my["qob"]
#define NPC1            my["npc1"]
#define NPC2            my["npc2"]
#define QOB_NAME        my["qob_name"]
#define QOB_UNIT        my["qob_unit"]
#define NPC1_NAME       my["npc1_name"]
#define NPC2_NAME       my["npc2_name"]
#define QOB_ID          my["qob_id"]
#define NPC1_ID         my["npc1_id"]
#define NPC2_ID         my["npc2_id"]
#define PLACE1          my["place1"]
#define PLACE2          my["place2"]
#define AMOUNT          my["amount"]

int npc_accept_object(object me, object who, object ob);
mixed ask_for_qob(object npc2, object qob, string qob_name);

// 任務對象創建
void create()
{
        setup();
}

// 啟動一個任務
// 自動生成兩個人物和兩個地點，輸入一種物品進行送貨，
// 找到第一個人接到物品，然後送給第二個人領取獎勵。
void init_quest(string qob_name, int amount)
{
        string name;
        string place1, place2;
        object npc1, npc2;
        mapping my;
        object qob;

        if (objectp(qob = find_object(qob_name)))
        {
                if( objectp(query_temp("quest_ob", qob)) )
                {
                        // 該物品已經存在並用於其他任務，這個任務不能進行
                        destruct(this_object());
                        return;
                }
        } else
                // 生成任務物品
                qob = load_object(qob_name);

        // 記錄該物品的任務屬性
        set_temp("quest_ob", this_object(), qob);
        qob->set_amount(amount);

        // 生成任務的名字
        name = "運送" + filter_color(qob->name());
        set_name(name);

        // 產生兩個隨機地點
        place1 = NPC_D->random_place(({ "西域" }));
        place2 = NPC_D->random_place(({ "西域", place1 }));

        // 產生兩個隨機人物
        npc1 = new(CLASS_D("generate") + "/questnpc");
        npc2 = new(CLASS_D("generate") + "/questnpc");

        set_temp("quest_ob", this_object(), npc1);
        set_temp("quest_ob", this_object(), npc2);

        // 記錄這些人物、地點和物品信息
        my = query_entire_dbase();

        QOB = qob;
        QOB_NAME = filter_color(qob->name());
        QOB_UNIT=query("base_unit", qob);
        NPC1 = npc1;
        NPC2 = npc2;
        PLACE1 = place1;
        PLACE2 = place2;
        NPC1_NAME = npc1->name();
        NPC2_NAME = npc2->name();
        QOB_ID=query("id", qob);
        NPC1_ID=query("id", npc1);
        NPC2_ID=query("id", npc2);
        AMOUNT = amount;

        // 物品承載，保證送貨的NPC拿得動足夠的重量
        npc2->set_max_encumbrance(1000000);
        qob->move(npc2);

        // 人物出現
        NPC_D->place_npc(npc1, 0, ({ place1 }));
        NPC_D->place_npc(npc2, 0, ({ place2 }));

        // 設置對話信息
        set("inquiry",([
                name      : "啊？你是送它來的？快給我。",
                QOB_NAME  : "那些貨物呀，我這裏的生意正急需呢！",
                QOB_ID    : "那些貨物呀，我這裏的生意正急需呢！",
                NPC1_NAME : "那正是本人啊！",
                NPC1_ID   : "那正是本人啊！",
                NPC2_NAME : "是呀，就是他答應派人送來的！",
                NPC2_ID   : "是呀，就是他答應派人送來的！" ]), npc1);

        set("inquiry",([
                name      : "沒錯，你願意去幫我送這批貨！",
                QOB_NAME  : (: ask_for_qob, npc2, qob, qob->name() :),
                QOB_ID    : (: ask_for_qob, npc2, qob, qob->name() :),
                NPC1_NAME : "這批貨就是要送給他的呀！",
                NPC1_ID   : "這批貨就是要送給他的呀！",
                NPC2_NAME : "正是在下，有何貴幹？",
                NPC2_ID   : "正是在下，有何貴幹？" ]), npc2);

        // 設置接收物品的信息：由於NPC存在的時候該任務對象必
        // 定會存在（因為任務析構的時候會清除NPC），所以可以
        // 讓NPC引用本地的"npc_accept_object"函數。
        set_temp("override/accept_object", (:npc_accept_object:), npc1);

        // 切換到正常狀態
        change_status(QUEST_READY);

        // 設置任務最長存活時間：30分鐘
        set("live_time", 1200);

        // 登記謠言消息
        register_information();
}

// 任務終止
void cancel_quest()
{
        mapping my = query_entire_dbase();
        object env;

        if (! mapp(my))
                return;

        if (objectp(NPC1))
                destruct(NPC1);

        if (objectp(NPC2))
                destruct(NPC2);

        if (objectp(QOB))
                destruct(QOB);

        // 任務消亡
        ::cancel_quest();
}

// user ask npc2 for quest ob
mixed ask_for_qob(object npc2, object qob, string qob_name)
{
        object me;
        object ob;

        me = this_player();

        message_vision(CYN "$N" CYN "對$n" CYN "説道：這" + qob_name +
                       CYN "您就交給我幫您運送吧，咱包您準時送到！\n" NOR,
                       me, npc2);

        tell_object(me, HIC "你讓" + npc2->name() + HIC "將" + qob_name +
                        HIC "交託給你運送。\n" NOR);

        if( query("score", me)<1000 )
        {
                message_vision(CYN "$N" CYN "眯着眼睛瞥了$n" CYN "一眼，哼"
                               "了一聲道：這批貨給你？我可不放心。”\n" NOR,
                               npc2, me);
                return 1;
        }

        if (objectp(qob) && environment(qob) == npc2 && qob->query_amount())
        {
                if (me->query_encumbrance() + qob->weight() / qob->query_amount() <
                    me->query_max_encumbrance())
                {
                        message_vision(CYN "$N" CYN "打量了$n" CYN "半天，"
                                       "點點頭道：好吧，這批貨可是非常重要"
                                       "的，你一定要準時送到啊。\n" NOR, npc2, me);

                        tell_object(me, HIY + npc2->name() + HIY "把一" +
                                        query("base_unit", qob)+qob_name+
                                        HIY "交給了你託運。\n" NOR);

                        /*
                        ob = new(base_name(qob));
                        qob->add_amount(-1);
                        if (! objectp(ob))
                                tell_object(me, CYN + npc2->name() + CYN "突"
                                            "然臉色一變，大叫道：我的" + qob_name +
                                            CYN "呢？怎麼不見了？\n" NOR);
                        ob->move(me, 1);
                        */
                        qob->move(me, 1);
                } else
                {
                        message_vision(CYN "$N" CYN "眯着眼睛瞥了$n" CYN "一"
                                       "眼，歎了口氣道：" + RANK_D->query_respect(me) +
                                       CYN "，這批貨你運得了麼？\n" NOR, npc2, me);
                }
        } else
                message_vision(CYN "$N" CYN "微笑着對$n" CYN "説：不用勞煩"
                               "你了，這批" + qob_name + CYN "已經有人送去"
                               "了。\n" NOR, npc2, me);

        return 1;
}

// 詢問NPC1 - 接收貨物的人
string ask_npc1(object knower, object me)
{
        mapping my = query_entire_dbase();

        if (! objectp(NPC1))
                return CYN "唉，怎麼" HIY + NPC1_NAME + NOR CYN
                       "好端端的，" HIY + QOB_NAME + NOR CYN
                       "沒拿到，反而丟了命，真是可憐。" NOR;

        return CYN "哦，他呀，據説正在" + PLACE1 + "，等人給他送去一批" +
               HIY + QOB_NAME + NOR CYN "呢！" NOR;
}

// 詢問NPC2 - 持有物品的人
string ask_npc2(object knower, object me)
{
        mapping my = query_entire_dbase();

        if (! objectp(NPC2))
                return CYN "聽人説" HIY + NPC2_NAME + NOR CYN
                       "居然被人殺了，也不知道惹了哪門子的禍！" NOR;

        if( query("score", me)<500 )
                call_out("do_whisper", 1, knower, me);

        return CYN "哦，他呀，據説正在" + PLACE2 + "，急着等" +
               "人幫他送貨呢！" NOR;
}

// 通知玩家
void do_whisper(object knower, object me)
{
        if (! can_talk_with(knower, me))
                return;

        tell_object(me, WHT + knower->name() + WHT "悄悄的和你"
                    "説：“可惜你的江湖閲歷太低了，他不會給你運。”\n");
        message("vision", knower->name() + "在" + me->name() +
                "的耳邊悄悄的説了些什麼。\n", environment(me), ({ me }));
}

// 詢問QOB - 物品的信息
string ask_qob(object knower, object me)
{
        mapping my = query_entire_dbase();

        if (! objectp(QOB))
                return CYN "難不成已經給山賊截去了？居然沒人"
                       "知道那" HIY + QOB_NAME + NOR CYN "的下落了。" NOR;

        return CYN "這" HIY + QOB_NAME + NOR CYN + "呀，"
               "不過是很普通的一批貨物而已嘛！" NOR;
}

// 任務介紹
string query_introduce(object knower)
{
        mapping my = query_entire_dbase();

        return CYN "聽説" HIY + NPC2_NAME + NOR CYN "急需將一批" +
               HIY + QOB_NAME + NOR CYN "送到" HIY + NPC1_NAME + NOR
               CYN "哪兒，你有沒有興趣？" NOR;
}

// 任務提示
string query_prompt()
{
        switch (random(3))
        {
        case 0:
                return CYN "倒是最近聽來往的商人説起『" HIY + name() +
                       NOR CYN "』的事來。";
        case 1:
                return "也沒什麼大事，只是聽説過『" HIY + name() +
                       NOR CYN "』的事罷了。";
        default:
                return "前兩天還聽人家説起『" HIY + name() +
                       NOR CYN "』的事呢。";
        }
}

int npc_accept_object(object me, object who, object ob)
{
        mapping my = query_entire_dbase();
        mapping b;
        object reward;
        int exp;
        int pot;
        int score;

        if (ob->is_character() || ob->is_item_make())
        {
                message_vision(CYN "$N" CYN "瞪着$n" CYN "，使勁的搖着頭"
                               "道：我要這幹什麼？\n" NOR, me, who);
                return 0;
        }

        if( query("id", ob) != QOB_ID )
        {
                message_vision(CYN "$N" CYN "瞪着$n" CYN "，使勁的搖着頭"
                               "道：我要這幹什麼？\n" NOR, me, who);
                return 0;
        }

        if (me->is_fighting())
                return 0;

        AMOUNT -= ob->query_amount();

        message_vision(CYN "$N" CYN "看了看" + ob->name() + CYN "，對$n"
                       CYN "道：還不錯，辛苦你了。這點銀子你收下吧。\n" NOR,
                       me, who);

        reward = new("/clone/money/silver");
        reward->set_amount(ob->query_amount() / 1 + random(3));
        reward->move(who, 1);

        remove_call_out("do_notice");
        if (AMOUNT < 1)
        {
                // 所有的物品全部接收完了，準備結束任務
                message_vision(CYN "$N" CYN "抹了抹頭上的汗，道：總算"
                               "全運到了，這事可真夠羅嗦的。\n" NOR, me);

/*
                CHANNEL_D->do_channel(find_object(QUEST_D), "rumor",
                                      "聽説" + who->name(1) + "(" +
                                      query("id", who)+")替"+
                                      me->name() + HIM "安全送到了" + 
                                      "一批" + ob->name() + HIM "。" NOR);
*/

                // 被列為門派中斷的自由任務
                if( query("quest/freequest", who)>0 )
                        GIFT_D->delay_freequest_bonus(who);

                call_out("do_finish", 4);
                change_status("stopping");
        } else
                call_out("do_notice", 1 + random(3), me, who, ob);

        // 獎勵
        exp = 50 + random(50);
        exp *= ob->query_amount();
        pot = 20 + random(20);
        pot *= ob->query_amount();
        score = 4 + random(4);
        score *= ob->query_amount();

        if( query("combat_exp", who)>200000 )
        {
                // 經驗太高，削弱獎勵
                exp = exp / 2 + 1;
                pot = pot / 2 + 1;
                score = score / 2 + 1;

                if( query("combat_exp", who)>400000 )
                {
                        // 再次削弱獎勵
                        exp = exp / 2 + 1;
                        pot = pot / 2 + 1;
                        score = score / 2 + 1;
                }
        }

        if( mapp(b=query("bonus/"+query("id", who))) )
        {
                // 正在獎勵該人中
                b["exp"] += exp;
                b["pot"] += pot;
                b["score"] += score;
        } else
        {
                b = ([ "exp" : exp,
                       "pot" : pot,
                       "score" : score,
                       "prompt": "經過這次幫助" + me->name() +
                                 "運送" + ob->name() + "的事情" ]);
                set("bonus/"+query("id", who),b);
                call_out("do_bonus",1+random(2),query("id", who),who);
        }

        destruct(ob);
        return -1;
}

protected void do_notice(object me, object who, object ob)
{
        mapping my = query_entire_dbase();

        if (! can_talk_with(me, who))
                return;

        message_vision(CYN "$N" CYN "點了點貨，又對$n" CYN "道：我還需"
                       "要" + chinese_number(AMOUNT) + QOB_UNIT + QOB_NAME +
                       CYN "才夠。\n" NOR, me, who);
}

// 準備完成任務
protected void do_finish()
{
        if (sizeof(query("bonus")) > 0)
        {
                call_out("do_finish", 4);
                return;
        }

        // 該任務已經完成
        cancel_quest();
}

// 給某人獎勵
protected void do_bonus(string who_id, object who)
{
        mapping b;

        b = query("bonus/" + who_id);
        delete("bonus/" + who_id);

        if (! mapp(b) || ! objectp(who) || ! living(who))
                return;

        GIFT_D->bonus(who, b);
}

// 這個消息能夠被散佈嗎？
int can_rumor_by(object knower)
{
        // 20%的機率被散佈
        return (random(10) < 2);
}

// 登記該任務的消息
void register_information()
{
        mapping my = query_entire_dbase();

        if (! clonep() || ! mapp(my))
                // 不是任務，所以不登記
                return;

        set_information(NPC1_NAME, (: ask_npc1 :));
        set_information(NPC2_NAME, (: ask_npc2 :));
        set_information(QOB_NAME, (: ask_qob :));
        set_information(NPC1_ID, (: ask_npc1 :));
        set_information(NPC2_ID, (: ask_npc2 :));
        set_information(QOB_ID, (: ask_qob :));
}
