// 玩家任務：trace.c

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
#define PLACE1          my["place1"]
#define PLACE2          my["place2"]

string ask_1_for_2();
mixed ask_2_for_1(object npc2, object npc1, string npc1_name);

// 任務對象創建
void create()
{
        setup();
}

// 啟動一個任務。自動生成兩個人物，其中第二人打算尋
// 找第一人，只需把第二人帶到第一人處即可以領取獎勵。
void init_quest()
{
        string name;
        string place1, place2;
        object npc1, npc2;
        mapping my;

        // 產生兩個隨機地點
        place1 = NPC_D->random_place(({ "西域", place1 }));
        place2 = NPC_D->random_place(({ "西域", place2 }));

        // 產生兩個隨機人物
        npc1 = new(CLASS_D("generate") + "/questnpc");
        npc2 = new(CLASS_D("generate") + "/tracenpc");

        set_temp("quest_ob", this_object(), npc1);
        set_temp("quest_ob", this_object(), npc2);

        // 生成任務的名字
        name = "尋找" + npc1->name(1);
        set_name(name);

        // 記錄這些人物、地點和物品信息
        my = query_entire_dbase();

        NPC1 = npc1;
        NPC2 = npc2;
        PLACE1 = place1;
        PLACE2 = place2;
        NPC1_NAME = npc1->name();
        NPC2_NAME = npc2->name();
        NPC1_ID=query("id", npc1);
        NPC2_ID=query("id", npc2);

        // 人物出現
        NPC_D->place_npc(npc1, 0, ({ place1 }));
        NPC_D->place_npc(npc2, 0, ({ place2 }));

        // 設置對話信息
        set("inquiry",([
                NPC1_NAME : "那就是鄙人我了！",
                NPC1_ID   : "那就是鄙人我了！",
                NPC2_NAME : (: ask_1_for_2 :),
                NPC2_ID   : (: ask_1_for_2 :), ]), npc1);

        set("inquiry",([
                name      : (: ask_2_for_1, npc2, npc1, npc1->name() :),
                NPC1_NAME : (: ask_2_for_1, npc2, npc1, npc1->name() :),
                NPC1_NAME : (: ask_2_for_1, npc2, npc1, npc1->name() :),
                NPC2_NAME : "那就是鄙人我了！",
                NPC2_ID   : "那就是鄙人我了！", ]), npc2);

        // 設置對象
        set_temp("trace", NPC1_ID, npc2);

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
                return "天啊，我兄弟他…他怎麼了？";

        switch (random(3))
        {
        case 0:
                return "那天我們遇到仇人追殺，不小心就和他失散了，唉。";
        case 1:
                return "他是我同生共死的兄弟，可現在卻不知他生在何處。";
        default:
                return "知道他在哪裡麼？快請他過來，跟他說兄弟這裡危險。";
        }
}

// 詢問NPC2有關NPC1的事情
mixed ask_2_for_1(object npc2, object npc1, string npc1_name)
{
        object me, follow;
        string msg;

        me = this_player();

        if( query("score", me)<500 )
                return "謝謝你的好意，不過估計這事你也幫不上忙。";

        if( !query("quest/freequest", me) )
                return "唉，你也一樣有要事在身，我怎麼好麻煩你？";

        if (! query_temp("trace/" + query_temp("trace", npc2),me))
                return "你…你是從哪裡聽來的？這不幹你的事。";

        follow = npc2->query_leader();

        if (objectp(follow) && environment(follow) == environment(npc2))
        {
                // 正在跟隨另外一個人，察看當前執行的任務。

                if (follow == me)
                        // 跟隨的就是發話的人
                        return "咱們快別耽擱了，萬一我兄弟有個三長"
                               "兩短可…唉。";
                else
                        return "現在" + follow->name() + "正在幫著"
                               "尋找我兄弟，就不麻煩你了。";
        }
        message_vision(CYN "$N" CYN "一驚，緊握住$n" CYN "的雙手道"
                       "：你…你知道我兄弟在哪裡？快…快帶我去。\n"
                       NOR, npc2, me);

        npc2->set_leader(me);
        message_vision("$N決定開始跟隨$n一起行動。\n", npc2, me);

        // 四分鐘以後解除跟隨狀態
        remove_call_out("cancel_follow");
        call_out("cancel_follow", 240, npc2, me);
        return 1;
}

// 停止跟蹤
void cancel_follow(object npc2, object me)
{
        string startroom;

        if (! objectp(npc2))
                return;

        if( !stringp(startroom=query("startroom", npc2)) )
                return;

        // 不再跟隨
        npc2->set_leader(0);
        message_vision(CYN "$N" CYN "皺眉道：你到底知不知道我"
                       "兄弟的下落？算了，我還是自己找吧。\n"
                       NOR, npc2);

        message_vision(HIC "$N" HIC "嘆了口氣，頭也不回的走了。"
                       "\n" NOR, npc2);

        // 返回故地
        npc2->move(startroom);
        message_vision("$N趕了過來。\n", npc2);
}


// 詢問NPC1的狀況
string ask_npc1(object knower, object me)
{
        mapping my = query_entire_dbase();

        if( (query("score", me)<500
            || !query("quest/freequest", me) )
            && !query_temp("trace/have_ask", me) )
        {
                set_temp("trace/have_ask", 1, me);
                call_out("do_whisper", 1, knower, me);
        }

        if (! objectp(NPC1) && ! objectp(NPC2))
        {
                call_out("cancel_quest", 1);
                return CYN "嘿嘿，據說" HIY + NPC1_NAME + NOR +
                       CYN "和" HIY + NPC2_NAME + NOR + CYN "哥"
                       "倆終于見面了。嘖嘖，真不錯。" NOR;
        }

        if (! objectp(NPC1))
                return CYN "唉…據說" HIY + NPC1_NAME + NOR +
                       CYN "還是被仇家給做掉了，到死也沒見著"
                       HIY + NPC2_NAME + NOR + CYN "的面。" NOR;

        set_temp("trace/"+NPC1_ID, 1, me);

        return CYN "這人武功不高，可是極重義氣，跟他兄弟" HIY +
               NPC2_NAME + NOR + CYN "失散後，便四處躲避仇家"
               "的追殺。\n" + knower->name() + CYN "又接著道"
               "：今上午聽吃飯的幾個家伙提起" HIY + NPC1_NAME +
               NOR + CYN "，據說是躲到" + PLACE1 + NOR + CYN
               "去了。" NOR;
}

// 詢問NPC2的狀況
string ask_npc2(object knower, object me)
{
        mapping my = query_entire_dbase();

        if( (query("score", me)<500
            || !query("quest/freequest", me) )
            && !query_temp("trace/have_ask", me) )
        {
                set_temp("trace/have_ask", 1, me);
                call_out("do_whisper", 1, knower, me);
        }

        if (! objectp(NPC1) && ! objectp(NPC2))
        {
                call_out("cancel_quest", 1);
                return CYN "嘿嘿，據說" HIY + NPC1_NAME + NOR +
                       CYN "和" HIY + NPC2_NAME + NOR + CYN "哥"
                       "倆終于見面了。嘖嘖，真不錯。" NOR;
        }

        if (! objectp(NPC2))
                return CYN "唉…據說那" HIY + NPC2_NAME + NOR +
                       CYN "最後還是被仇家給做掉了，臨死前還惦"
                       "記著" HIY + NPC1_NAME + NOR + CYN "呢。" NOR;

        return "那人跟他兄弟" HIY + NPC1_NAME + NOR + CYN "失散"
               "後，擔心得不得了。喏，現在還在" + PLACE2 + NOR +
               CYN "等他兄弟呢。" NOR;
}

// 通知玩家
void do_whisper(object knower, object me)
{
        if (! can_talk_with(knower, me))
                return;

        if( query("score", me)<500 )
                tell_object(me, WHT + knower->name() + WHT "悄悄的和你"
                                "說：算了吧，憑你這兩下子，別人不會理你"
                                "的。\n" NOR);
        else
                tell_object(me, WHT + knower->name() + WHT "悄悄的和你"
                                "說：我說呢，你也有事情做，何必去幹涉別"
                                "人的私事。\n" NOR);

        delete_temp("trace/have_ask", me);
        message("vision", knower->name() + "在" + me->name() + "的耳邊"
                "悄悄的說了些什麼。\n", environment(me), ({ me }));
}

// 任務介紹
string query_introduce(object knower)
{
        mapping my = query_entire_dbase();

        if (! objectp(NPC1) && ! objectp(NPC2))
        {
                call_out("cancel_quest", 1);
                return CYN "嘿嘿，據說" HIY + NPC1_NAME + NOR +
                       CYN "和" HIY + NPC2_NAME + NOR + CYN "哥"
                       "倆終于見面了。嘖嘖，真不錯。" NOR;
        }

        return CYN "聽說" HIY + NPC2_NAME + NOR + CYN "和"
               HIY + NPC1_NAME + NOR + CYN "在" + PLACE2 +
               CYN "被仇家圍追堵殺，雙方火拼了幾個時辰，真"
               "是壯烈。\n" + knower->name() + CYN "又接著"
               "說道：唉…那幾個仇家倒是被幹掉了，可是這麼"
               "一對同生共死的兄弟也因此失散了。" NOR;
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
        set_information(NPC1_ID, (: ask_npc1 :));
        set_information(NPC2_ID, (: ask_npc2 :));
}
