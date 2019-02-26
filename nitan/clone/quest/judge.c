// 玩家任務：judge.c

#include <ansi.h>
#include <quest.h>

inherit QUEST_OB;

#define QOB             my["qob"]
#define NPC1            my["npc1"]
#define NPC2            my["npc2"]
#define NPC1_NAME       my["npc1_name"]
#define NPC2_NAME       my["npc2_name"]
#define NPC1_ID         my["npc1_id"]
#define NPC2_ID         my["npc2_id"]
#define PLACE           my["place"]

string ask_1_for_2();
string ask_2_for_1();

// 任務對象創建
void create()
{
        setup();
}

// 啟動一個任務
// 輸入一個物品進行尋找，自動生成兩個人物和兩個地點，其中殺
// 了第一個人即可獲得該物品，然後交給第二個人領取獎勵。
void init_quest()
{
        string name;
        string place;
        object npc1, npc2;
        mapping my;

        // 產生兩個隨機地點
        place = NPC_D->random_place(({ "西域" }));

        // 產生兩個隨機人物
        npc1 = new(CLASS_D("generate") + "/questnpc");
        npc2 = new(CLASS_D("generate") + "/questnpc");

        set_temp("quest_ob", this_object(), npc1);
        set_temp("quest_ob", this_object(), npc2);

        // 生成任務的名字
        name = npc1->name(1) + "和" + npc2->name(1) + "的事";
        set_name(name);

        // 記錄這些人物、地點和物品信息
        my = query_entire_dbase();

        NPC1 = npc1;
        NPC2 = npc2;
        PLACE = place;
        NPC1_NAME = npc1->name();
        NPC2_NAME = npc2->name();
        NPC1_ID=query("id", npc1);
        NPC2_ID=query("id", npc2);

        // 人物出現
        NPC_D->place_npc(npc1, 0, ({ place }));
        npc2->move(environment(npc1));
        delete("chat_chance", npc1);
        delete("chat_msg", npc1);
        delete("chat_chance", npc2);
        delete("chat_msg", npc2);

        // 設置對話信息
        npc1->set("inquiry",([
                NPC1_NAME : "那就是鄙人我了！",
                NPC1_ID   : "那就是鄙人我了！",
                NPC2_NAME : (: ask_1_for_2 :),
                NPC2_ID   : (: ask_1_for_2 :) ]));

        npc2->set("inquiry",([
                NPC1_NAME : (: ask_2_for_1 :),
                NPC1_ID   : (: ask_2_for_1 :),
                NPC2_NAME : "正是區區，有何貴幹？",
                NPC2_ID   : "正是區區，有何貴幹？" ]));

        // 切換到正常狀態
        change_status(QUEST_READY);

        // 設置任務最長存活時間：15分鐘
        set("live_time", 600);

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

// 詢問NPC1有關NPC2的事情
string ask_1_for_2()
{
        mapping my = query_entire_dbase();

        if (! objectp(NPC2))
                return "天啊，他...他怎麼這就...我也沒想這樣啊！";

        if (! environment(NPC2))
                return NPC2->name() + "這" + RANK_D->query_rude(NPC) +
                       "不知道溜到哪裏去了。";

        switch (random(3))
        {
        case 0:
                return "這混蛋，簡直就是不可理喻。";
        case 1:
                return "碰到他，我算是到了十八輩子的黴，不，十九輩子！";
        default:
                return "我和他沒法講理，因為他就沒理！";
        }
}

// 詢問NPC2有關NPC1的事情
string ask_2_for_1()
{
        mapping my = query_entire_dbase();

        if (! objectp(NPC1))
                return "我...我可沒有想害他...真的沒有啊！";

        if (! environment(NPC1))
                return "他奶奶的，" + NPC2->name() + "這個" +
                       RANK_D->query_rude(NPC) + "！跑了？";

        switch (random(3))
        {
        case 0:
                return "不要提他，聽到這個名字我就生氣！";
        case 1:
                return "你別添亂，這人讓我堵心。";
        default:
                return "他以為自己聲音大就佔理了？他是老天啊，靠打雷講理？";
        }
}

// 詢問NPC1的狀況
string ask_npc1(object knower, object me)
{
        mapping my = query_entire_dbase();

        if (! objectp(NPC1))
                return CYN "嘿，據説" HIY + NPC1_NAME + NOR CYN
                       "被人做掉了，你看看，火氣大就沒好處吧！" NOR;

        return CYN "哦，這人呀，我也不認識他，沒聽過他的字號。" NOR;
}

// 詢問NPC2的狀況
string ask_npc2(object knower, object me)
{
        mapping my = query_entire_dbase();

        if (! objectp(NPC2))
                return CYN "嘿，據説" HIY + NPC2_NAME + NOR CYN
                       "被人砍了，脾氣大敢情就這下場呀。" NOR;

        return CYN "這人我沒怎麼聽説過，唉！孤陋寡聞啊。" NOR;
}

// 詢問單正
string ask_shan(object knower, object me)
{
        if( query("weiwang", me)<1000 )
                call_out("do_whisper", 1, knower, me);

        return CYN "連鐵面判官你都不認識？嘖嘖，他老人家可是武林"
                   "中的\n名人呀，家住泰山，專門調節各種糾紛，處"
                   "理不平之事。\n" NOR;
}

// 通知玩家
void do_whisper(object knower, object me)
{
        if (! can_talk_with(knower, me))
                return;

        tell_object(me, WHT + knower->name() + WHT "悄悄的和你"
                    "説：“可惜你的江湖威望太低了，請不動他。”\n");
        message("vision", knower->name() + "在" + me->name() +
                "的耳邊悄悄的説了些什麼。\n", environment(me), ({ me }));
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

        return CYN "聽説" HIY + NPC1_NAME + NOR CYN "和" +
               HIY + NPC2_NAME + NOR CYN "在" + PLACE +
               CYN "發生了糾紛，不知道為什麼，要是"
               HIY "單正" NOR CYN "在就好了。" NOR;
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
        set_information(NPC1_ID, (: ask_npc1 :));
        set_information(NPC2_ID, (: ask_npc2 :));
        set_information("單正", (: ask_shan :));
        set_information("shan zheng", (: ask_shan :));
}