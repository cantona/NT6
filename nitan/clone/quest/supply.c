#include <ansi.h>
#include <quest.h>

inherit QUEST_OB;

#define NPC_OB          my["npc"]       // 接收物品的NPC對象
#define NPC_NAME        my["npc_name"]  // 接收物品的NPC的名字
#define NPC_ID          my["npc_id"]    // 接收物品的NPC的ID
#define PLACE           my["place"]     // 接收物品的NPC的地點
#define SOB_FILE        my["sob_file"]  // 接收物品的文件名字
#define SOB_NAME        my["sob_name"]  // 接收物品的名字
#define COUNT           my["count"]     // 需要物品的數量
#define ZONE            my["zone"]      // 接收對象所處的區域

int  npc_accept_object(object me, object who, object ob);
void npc_destructed();

// 任務對象創建
void create()
{
        seteuid(getuid());
        setup();
}

// 啟動一個任務
// 輸入一個物品進行尋找，自動生成兩個人物和兩個地點，其中殺
// 了第一個人即可獲得該物品，然後交給第二個人領取獎勵。
void init_quest(object npc_ob, string sob_file)
{
        mapping my;

        my = query_entire_dbase();

        // 生成任務的名字
        set_name(npc_ob->name() + "的事");

        if( query_temp("quest_ob", npc_ob) )
        {
                // 這個NPC已經用於其他任務，中止任務
                destruct(this_object());
                return;
        }
        set_temp("quest_ob", this_object(), npc_ob);

        // 隨即生成需要的物品數量
        COUNT = 3 + random(6);

        // 記錄任務的數據信息
        NPC_OB = npc_ob;
        NPC_NAME = npc_ob->name();
        NPC_ID=query("id", npc_ob);
        SOB_FILE = sob_file;
        SOB_NAME = sob_file->name();
        PLACE = environment(npc_ob)->short(1);
        if (sscanf(file_name(environment(npc_ob)), "/d/%s/%*s", ZONE) == 2)
            ZONE = "/d/" + ZONE + "/";
        else
            ZONE = "/";

        // 設置NPC的對話信息
        set("inquiry/"+NPC_NAME, "正是區區在下！", npc_ob);
        set("inquiry/"+NPC_ID, "是我啊，你找對人了！", npc_ob);
        set("inquiry/"+SOB_NAME, "我現在正需要這些東西，你可帶來了？", npc_ob);

        // 設置接收物品的信息：由於NPC存在的時候該任務對象必
        // 定會存在（因為任務析構的時候會清除NPC），所以可以
        // 讓NPC引用本地的"npc_accept_object"函數。
        set_temp("override/accept_object", (:npc_accept_object:), npc_ob);

        // 設置析構信息：NPC人物析構以後將自動解除任務
        set_temp("override/destruct", (:npc_destructed:), npc_ob);

        // 切換到正常狀態
        change_status(QUEST_READY);

        // 設置任務最長存活時間：15分鐘
        set("live_time", 600);

        // 登記謠言消息
        register_information();
}

// 恢復NPC：任務結束的時候必須恢復正常的NPC
void restore_npc()
{
        mapping my = query_entire_dbase();
        object npc_ob;

        if (! objectp(npc_ob = NPC_OB))
                return;

        delete_temp("override/accept_object", npc_ob);
        delete_temp("override/destruct", npc_ob);
        delete("inquiry/"+NPC_NAME, npc_ob);
        delete("inquiry/"+NPC_ID, npc_ob);
        delete("inquiry/"+SOB_NAME, npc_ob);
        NPC_OB = 0;
}

// 結束任務
void cancel_quest()
{
        // 恢復NPC，然後結束任務
        restore_npc();

        ::cancel_quest();
}

// 任務NPC消亡
void npc_destructed()
{
        remove_call_out("cancel_quest");
        call_out("cancel_quest", 0);
}

// 詢問NPC - 需要提供物品的人
string ask_npc(object knower, object me)
{
        mapping my = query_entire_dbase();

        if (! objectp(NPC_OB))
                return CYN "哦，據説" HIY + NPC_NAME + NOR CYN
                       "不知道躲到哪兒去了，好多人正罵娘呢。" NOR;

        return "不清楚，不清楚，我又不認識人家！";
}

// 詢問SOB - 提供的物品的信息
string ask_sob(object knower, object me)
{
        mapping my = query_entire_dbase();

        return CYN "這" HIY + SOB_NAME + NOR CYN
               "可不是咱們百姓應該沾的東西呀，你説是不是？" NOR;
}

// 任務介紹
string query_introduce(object knower)
{
        mapping my = query_entire_dbase();

        if (! objectp(NPC))
        {
                remove_call_out("do_say");
                call_out("do_say", 1);
        }

        return CYN "據説" + PLACE + "的" + HIY + NPC_NAME + NOR CYN "急需一批" +
               HIY + SOB_NAME + NOR CYN "。嘿！你説他想幹什麼？" NOR;
}

// 任務提示
string query_prompt()
{
        switch (random(3))
        {
        case 0:
                return CYN "倒是最近聽有些客人説起『" HIY + name() +
                       NOR CYN "』來。";
        case 1:
                return "也沒什麼大事，只是聽説過『" HIY + name() +
                       NOR CYN "』罷了。";
        default:
                return "前兩天還聽人家説過『" HIY + name() +
                       NOR CYN "』呢。";
        }
}

void do_say(object knower)
{
        if (! objectp(knower) || ! living(knower))
                return 0;

        message_vision(CYN "$N" CYN "嘟囔道：我跟你都説了，要這些東西沒好"
                       "事，這不？出事了吧？\n" NOR, knower);
}

int npc_accept_object(object me, object who, object ob)
{
        mapping my = query_entire_dbase();
        mapping b;

        int exp;
        int pot;
        int score;

        if (ob->is_character() || ob->is_item_make())
                // 不接受人物和自造的兵器
                return 0;

        if (ob->name() != SOB_FILE->name())
                return 0;

        if (me->is_fighting())
                return 0;

        if( base_name(environment(me)) != query("startroom", me) )
        {
                message_vision(CYN "$N" CYN "一臉茫然的望着$n" CYN "。\n" NOR,
                               me, who);
                return -1;
        }

        message_vision(HIY "$N" HIY "大喜，接過" + ob->name() + "看了看，對$n"
                       HIY "道：這位" + RANK_D->query_respect(who) + "，很好，"
                       "很好！\n" NOR, me, who);
        COUNT--;

        message_vision(HIC "$N" HIC "交給了$n" HIC "一些錢作為報酬。\n" NOR,
                       me, who);

        MONEY_D->pay_player(this_player(),query("value", SOB_FILE)*3/2);

        remove_call_out("do_notice");
        if (COUNT < 1)
        {
                // 所有的物品全部接收完了，準備結束任務
                message_vision(HIY "$N" HIY "抹了抹頭上的汗，道：總算全備齊了"
                               "，這事可真夠羅嗦的。\n" NOR, me);

/*
                CHANNEL_D->do_channel(this_object(), "rumor",
                                      "聽説" + who->name(1) +
                                      "("+query("id", who)+")替"+
                                      me->name() + HIM + "備齊了" + SOB_NAME + "。");
*/
                // 被列為門派中斷的自由任務
                if( query("quest/freequest", who)>0 )
                        GIFT_D->delay_freequest_bonus(who);

                call_out("do_finish", 4);
                restore_npc();
                change_status("stopping");
        } else
                call_out("do_notice", 1 + random(3), me, who);

        // 獎勵
        exp = 50 + random(50);
        pot = 20 + random(20);
        score = 8 + random(8);

        if( query("combat_exp", who)>400000 )
        {
                // 經驗太高，削弱獎勵
                exp = exp / 2 + 1;
                pot = pot / 2 + 1;
                score = score / 2 + 1;

                if( query("combat_exp", who)>500000 )
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
                                  "準備" + ob->name() + "的事情" ]);
                set("bonus/"+query("id", who),b);
                call_out("do_bonus",2+random(2),query("id", who),who);
        }

        destruct(ob);
        return -1;
}

protected void do_notice(object me, object who)
{
        mapping my = query_entire_dbase();

        if (! can_talk_with(me, who))
                return;

        message_vision(CYN "$N" CYN "點了點貨，又對$n" CYN "道：我還需"
                       "要"+chinese_number(COUNT)+query("unit", SOB_FILE)+
                       SOB_NAME + NOR + CYN  "才夠。\n" NOR, me, who);
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

// 登記該任務的消息
void register_information()
{
        mapping my = query_entire_dbase();

        if (! clonep() || ! mapp(my))
                // 不是任務，所以不登記
                return;

        set_information(NPC_NAME, (: ask_npc :));
        set_information(NPC_ID,   (: ask_npc :));
        set_information(SOB_NAME, (: ask_sob :));
}

// 這個任務可以被某人知曉嗎？
int can_know_by(object knower)
{
        mapping my = query_entire_dbase();
        string fname;

        fname = file_name(environment(knower));
        if (! stringp(ZONE) || strlen(ZONE) < 1 ||
            ZONE == fname[0..strlen(ZONE) - 1])
                // 和小二在同一個區域
                return 1;

        return 0;
}
