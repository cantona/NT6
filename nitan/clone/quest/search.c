// 玩家任務：search.c

#include <ansi.h>
#include <quest.h>

inherit QUEST_OB;

#define QOB             my["qob"]
#define NPC1            my["npc1"]
#define NPC2            my["npc2"]
#define QOB_NAME        my["qob_name"]
#define NPC1_NAME       my["npc1_name"]
#define NPC2_NAME       my["npc2_name"]
#define QOB_ID          my["qob_id"]
#define NPC1_ID         my["npc1_id"]
#define NPC2_ID         my["npc2_id"]
#define PLACE1          my["place1"]
#define PLACE2          my["place2"]

int npc_accept_object(object me, object who, object ob);
mixed ask_for_qob(object npc2, object qob, string qob_name);

// 任務對象創建
void create()
{
        setup();
}

// 啟動一個任務
// 輸入一個物品進行尋找，自動生成兩個人物和兩個地點，其中殺
// 了第一個人即可獲得該物品，然後交給第二個人領取獎勵。
void init_quest(string qob_name)
{
        string name;
        object qob;
        string place1, place2;
        object npc1, npc2;
        mapping my;

        if (objectp(qob = find_object(qob_name)))
        {
                if( objectp(query_temp("quest_ob", qob)) )
                {
                        // 該物品已經存在並用于其他任務，這個任務不能進行
                        destruct(this_object());
                        return;
                }
        } else
                // 生成任務物品
                qob = load_object(qob_name);

        // 記錄該物品的任務屬性
        set_temp("quest_ob", this_object(), qob);

        // 生成任務的名字
        name = "尋找" + filter_color(qob->name());
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
        NPC1 = npc1;
        NPC2 = npc2;
        PLACE1 = place1;
        PLACE2 = place2;
        NPC1_NAME = npc1->name();
        NPC2_NAME = npc2->name();
        QOB_ID=query("id", qob);
        NPC1_ID=query("id", npc1);
        NPC2_ID=query("id", npc2);

        // 物品承載
        qob->move(npc2);

        // 人物出現
        NPC_D->place_npc(npc1, 0, ({ place1 }));
        NPC_D->place_npc(npc2, 0, ({ place2 }));

        // 設置對話信息
        npc1->set("inquiry",([
                name      : "啊？你知道？快給我，重重有賞！",
                QOB_NAME  : "其實它並不值錢，但是對我卻很重要啊！",
                QOB_ID    : "其實它並不值錢，但是對我卻很重要啊！",
                NPC1_NAME : "那就是鄙人我了！",
                NPC1_ID   : "那就是鄙人我了！",
                NPC2_NAME : "我也曾聽說這人了，但是沒有真憑實據啊！",
                NPC2_ID   : "我也曾聽說這人了，但是沒有真憑實據啊！" ]));

        npc2->set("inquiry",([
                name      : "全是瞎鬧！哪兒的事兒啊！",
                QOB_NAME  : (: ask_for_qob, npc2, qob, qob->name() :),
                QOB_ID    : (: ask_for_qob, npc2, qob, qob->name() :),
                NPC1_NAME : "你讓他來和我對質！真是豈有此理！",
                NPC1_ID   : "你讓他來和我對質！真是豈有此理！",
                NPC2_NAME : "正是區區，有何貴幹？",
                NPC2_ID   : "正是區區，有何貴幹？" ]));

        // 設置接收物品的信息：由于NPC存在的時候該任務對象必
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

        // 任務消亡
        ::cancel_quest();
}

// user ask npc2 for quest ob
mixed ask_for_qob(object npc2, object qob, string qob_name)
{
        object me;
        string msg;

        me = this_player();
        if( query("special_skill/trick", me) )
        {
                message_vision(HIM "$N" HIM "瞥了$n" HIM "一眼，咳嗽兩聲，對著"
                               "$n" HIM "就聊了開來。\n" NOR, me, npc2);

                tell_object(me, HIC "你勸說" + npc2->name() +
                                HIC "將" + qob_name +
                                HIC "交出來，大家都了事。\n" NOR);
                if (me->query_int() > random(40))
                {
                        // 成功了！
                        if (objectp(qob) && environment(qob) == npc2)
                        {
                                message_vision(CYN "$N" CYN "嘆了一口氣，對$n"
                                               CYN "道：好了好了，你就別多說"
                                               "了！\n" NOR, npc2, me);

                                tell_object(me, HIY + npc2->name() + HIY "把" +
                                            qob_name + HIY "交給了你。\n" NOR);

                                qob->move(me, 1);
                        } else
                        {
                                message_vision(CYN "$N" CYN "嘆了口氣，對$n" CYN
                                               "說：你就別說了，那東西真的不在我"
                                               "身上！\n" NOR, npc2, me);
                        }
                } else
                        message_vision(CYN "$N" CYN "眼睛一瞪，對著$n" CYN "罵道"
                                       "：滾開！少來給我廢話！\n" NOR, npc2, me);
                return 1;
        }

        return "什麼破玩藝，我可沒有聽說過！";
}

// 詢問NPC1 - 丟物品的人
string ask_npc1(object knower, object me)
{
        mapping my = query_entire_dbase();

        if (! objectp(NPC1))
                return CYN "嘿，據說" HIY + NPC1_NAME + NOR CYN
                       "倒了大霉，先丟" HIY + QOB_NAME + NOR CYN
                       "再丟命，你說人要這麼多東西幹什麼呢？" NOR;

        return CYN "哦，他呀，據說正在" + PLACE1 + "，找他的" +
               HIY + QOB_NAME + NOR CYN "呢！" NOR;
}

// 詢問NPC2 - 持有物品的人
string ask_npc2(object knower, object me)
{
        mapping my = query_entire_dbase();

        if (! objectp(NPC2))
                return CYN "聽人說" HIY + NPC2_NAME + NOR CYN
                       "已經被人殺了，嘖嘖，你看看，惹禍上身吧！" NOR;

        if( query("combat_exp", me)<query("combat_exp", NPC2)/2 )
        {
                remove_call_out("whisper_to");
                call_out("whisper_to", 0, knower, me);
        }

        return CYN "哦，他呀，據說正在" + PLACE2 + "，大家" +
               "都奔他去了，看來他不妙噢！" NOR;
}

// 詢問QOB - 物品的信息
string ask_qob(object knower, object me)
{
        mapping my = query_entire_dbase();

        if (! objectp(QOB))
                return CYN "不就是你爭我奪鬧的？現在已經沒人"
                       "知道那" HIY + QOB_NAME + NOR CYN "的下落了。" NOR;

        return CYN "你說這" HIY + QOB_NAME + NOR CYN
               "究竟是啥？還能比命值錢？真是的！" NOR;
}

void whisper_to(object knower, object me)
{
        mapping my = query_entire_dbase();

        if (! can_talk_with(me, knower))
                return;

        message("vision", knower->name() + "悄悄的在" +
                me->name() + "耳邊說了些什麼。\n",
                environment(me), ({ me }));
        tell_object(me, WHT + knower->name() + WHT "悄悄的和你說：" +
                    RANK_D->query_respect(me) + "，我看你就別淌"
                    "這渾水了，" + NPC2_NAME + WHT "厲害著呢！\n" NOR);
}

// 任務介紹
string query_introduce(object knower)
{
        mapping my = query_entire_dbase();

        if (! objectp(NPC2))
        {
                remove_call_out("do_say");
                call_out("do_say", 1, knower);
        }

        return CYN "聽說" HIY + NPC1_NAME + NOR CYN "丟了" +
               HIY + QOB_NAME + NOR CYN "，有人說不知怎麼的就落到了"
               HIY + NPC2_NAME + NOR CYN "手中了。" NOR;
}

void do_say(object knower)
{
        if (! objectp(knower) || ! living(knower))
                return 0;

        message_vision(CYN "$N" CYN "又自言自語道：結果你爭我奪的，"
                       "這不，果然就沒什麼好下場！\n" NOR, knower);
}

int npc_accept_object(object me, object who, object ob)
{
        mapping my = query_entire_dbase();
        object reward;
        int percent;
        string msg;

        if (ob != QOB)
        {
                message_vision(CYN "$N" CYN "瞪著$n" CYN "，看了半天"
                               "才道：這是什麼？\n" NOR, me, who);
                return 0;
        }

        message_vision(HIY "$N" HIY "大喜過望，對$n" HIY "說道：這位"
                       + RANK_D->query_respect(who) + "，太感謝了，"
                       + RANK_D->query_self(me) + "實在不知道該怎麼"
                       "報答你！\n" NOR, me, who);

        reward = new("/clone/money/gold");
        reward->set_amount(1);

        message_vision(HIC "$N" HIC "掏出了一些" NOR + YEL "黃金" HIC
                       "雙手奉上，感激道：一點薄禮，不成敬意，不成敬"
                       "意！\n" NOR, me, who);

        reward->move(who, 1);

        // 獎勵
        percent=10000*100/(random(query("score", who)+1)+10000);

        GIFT_D->bonus(who, ([ "exp" : 200 + random(100),
                              "pot" : 150 + random(100),
                              "score" : 30 + random(20),
                              "percent" : percent ]));

/*
        CHANNEL_D->do_channel(find_object(QUEST_D), "rumor",
                              "聽說" + who->name(1) + "(" +
                              query("id", who)+")替"+
                              me->name() + HIM "找到了" + ob->name() +
                              HIM "，平息了一場武林風波。" NOR);
*/

        // 被列為門派中斷的自由任務
        if( query("quest/freequest", who)>0 )
                GIFT_D->delay_freequest_bonus(who);

        // 結束任務
        destruct(ob);
        call_out("cancel_quest", 2);
        return -1;
}

// 這個消息能夠被散布嗎？
int can_rumor_by(object knower)
{
        // 20%的幾率被散布
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
