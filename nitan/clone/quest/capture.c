// 玩家任務：capture.c

#include <ansi.h>
#include <quest.h>

inherit QUEST_OB;

#define NPC1            my["npc1"]
#define NPC2            my["npc2"]
#define NPC3            my["npc3"]
#define NPC1_NAME       my["npc1_name"]
#define NPC2_NAME       my["npc2_name"]
#define NPC3_NAME       my["npc3_name"]
#define NPC1_ID         my["npc1_id"]
#define NPC2_ID         my["npc2_id"]
#define NPC3_ID         my["npc3_id"]
#define PLACE1          my["place1"]
#define PLACE2          my["place2"]
#define PLACE3          my["place3"]

string ask_2_for_1();
string ask_3_for_1();
string ask_3_for_2();

// 任務對象創建
void create()
{
        setup();
}

// 啟動一個任務
// 自動生成三個追捕對象以及對象的起始地點，任務開始後
// 殺掉第一人可以獲得一些獎勵以及第二人的訊息，然後再
// 殺掉第二人獲得更多的獎勵和第三人的訊息，最後殺掉第
// 三人，任務結束。
void init_quest(string qob_name)
{
        string name;
        string place1, place2, place3;
        object npc1, npc2, npc3;
        mapping my;

        // 產生三個隨機地點
        place1 = NPC_D->random_place(({ "西域", place1 }));
        place2 = NPC_D->random_place(({ "西域", place2 }));
        place3 = NPC_D->random_place(({ "西域", place3 }));

        // 產生三個隨機人物
        npc1 = new(CLASS_D("generate") + "/capturenpc1");
        npc2 = new(CLASS_D("generate") + "/capturenpc2");
        npc3 = new(CLASS_D("generate") + "/capturenpc3");

        set_temp("quest_ob", this_object(), npc1);
        set_temp("quest_ob", this_object(), npc2);
        set_temp("quest_ob", this_object(), npc3);

        // 生成任務的名字
        name = "追殺" + npc1->name();
        set_name(name);

        // 記錄追殺對象以及地點信息
        my = query_entire_dbase();

        NPC1 = npc1;
        NPC2 = npc2;
        NPC3 = npc3;
        PLACE1 = place1;
        PLACE2 = place2;
        PLACE3 = place3;
        NPC1_NAME = npc1->name();
        NPC2_NAME = npc2->name();
        NPC3_NAME = npc3->name();
        NPC1_ID=query("id", npc1);
        NPC2_ID=query("id", npc2);
        NPC3_ID=query("id", npc3);

        // 這裏三個追殺對象是一起出現的，但是在獲得相應的訊
        // 息之前殺掉他們並無獎勵
        NPC_D->place_npc(npc1, 0, ({ place1 }));
        NPC_D->place_npc(npc2, 0, ({ place2 }));
        NPC_D->place_npc(npc3, 0, ({ place3 }));

        // 設置對話信息
        set("inquiry",([
                name      : "咦？有這回事？有意思，改天我也去瞧瞧。", // NPC1假裝不知道
                NPC1_NAME : "不認識，不認識！",
                NPC1_ID   : "不認識，不認識！",
                NPC2_NAME : "這……你還是找別人問吧，這個我可不清楚。",
                NPC2_ID   : "這……你還是找別人問吧，這個我可不清楚。",
                NPC3_NAME : "你説的是誰呀？別説見過，我連聽都沒聽説過。",
                NPC3_ID   : "你説的是誰呀？別説見過，我連聽都沒聽説過。" ]), npc1);

        set("inquiry",([
                name      : "你要追殺他就去啊，來找我幹嘛？真是莫名其妙！",
                NPC1_NAME : (: ask_2_for_1 :),
                NPC1_ID   : (: ask_2_for_1 :),
                NPC2_NAME : "正是在下，有何貴幹？",
                NPC2_ID   : "正是在下，有何貴幹？",
                NPC3_NAME : "這……你還是找別人問吧，這個我可不清楚。",
                NPC3_ID   : "這……你還是找別人問吧，這個我可不清楚。" ]), npc2);

        set("inquiry",([
                name      : "我説你這人真是不可理喻，你要追殺他卻來找我，我又不認識他。",
                NPC1_NAME : (: ask_3_for_1 :),
                NPC1_ID   : (: ask_3_for_1 :),
                NPC2_NAME : "不清楚，你到底在説誰呀？",
                NPC2_ID   : "不清楚，你到底在説誰呀？",
                NPC3_NAME : "正是在下，有何貴幹？",
                NPC3_ID   : "正是在下，有何貴幹？" ]), npc3);

        // 切換到正常狀態
        change_status(QUEST_READY);

        // 設置任務最長存活時間：50分鐘
        set("live_time", 1800);

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

        if (objectp(NPC3))
                destruct(NPC3);

        // 任務消亡
        ::cancel_quest();
}

// 詢問NPC2有關NPC1的事情
string ask_2_for_1()
{
        mapping my = query_entire_dbase();

        if (! objectp(NPC1))
                return "嗯，那傢伙不是掛了嗎，你問我作甚？";

        switch (random(3))
        {
        case 0:
                return "別説見過，我連聽都沒聽説過。";
        case 1:
                return "我不清楚，我看你還是找別人問問吧。";
        default:
                return "不認識，不認識。";
        }
}

// 詢問NPC3有關NPC1的事情
string ask_3_for_1()
{
        mapping my = query_entire_dbase();

        if (! objectp(NPC1))
                return "嗯，那傢伙不是掛了嗎，你問我作甚？";

        switch (random(3))
        {
        case 0:
                return "別説見過，我連聽都沒聽説過。";
        case 1:
                return "我不清楚，我看你還是找別人問問吧。";
        default:
                return "不認識，不認識。";
        }
}

// 詢問NPC1 - 開始被追殺的人
string ask_npc1(object knower, object me)
{
        mapping my = query_entire_dbase();

        if (! objectp(NPC1))
                return CYN "嘿，據説" HIY + NPC1_NAME + NOR CYN "已經讓"
                       "人給做了。嘿！我早就料到他會沒命。喏，又讓我給説"
                       "中了吧。\n" + knower->name() + CYN "接着説道：現"
                       "在又傳出消息，上次擾亂六大門派的主謀竟然不是他，"
                       "原來另有其人，是一個叫什麼" HIY + NPC2_NAME + NOR
                       + CYN "的亡命徒。\n" + knower->name() + CYN "又説"
                       "道：你來説説看，人有幾個腦袋？這幾個傢伙居然敢一"
                       "次惹惱六大門派，這還有他們活得份嗎？" NOR;

        if( query("combat_exp", me)<query("combat_exp", NPC1)/2 )
        {
                remove_call_out("whisper_to1");
                call_out("whisper_to1", 0, knower, me);
        }

        set_temp("capture/"+NPC1_ID, 1, me);
        return CYN "哦，聽説最近六大門派已經上" + PLACE1 + "找他去了，我"
               "看他這次是小命不保羅。\n" + knower->name() + CYN "接着説"
               "道：唉，做人就得圖個太平，何必去惹那麼多麻煩呢？你説對不"
               "？" NOR;
}

// 詢問NPC2 - 第二個被追殺的對象
string ask_npc2(object knower, object me)
{
        mapping my = query_entire_dbase();

        if (! objectp(NPC2) && objectp(NPC1))
                return CYN "我沒聽説……咦？對了，前幾天有個家"
                       "夥掛了，倒是有點像你要找的人。" NOR;

        if (objectp(NPC1))
                return CYN "不清楚，不清楚，我從沒聽説過有那號"
                       "人！" NOR;

        if (! objectp(NPC2))
                return CYN "你剛才沒聽到謠言麼？聽説那個" HIY +
                       NPC2_NAME + NOR CYN "好像也掛了。你瞧瞧"
                       "看，這就是惹是生非的下場。\n" + knower->name()
                       + CYN "接着説道：不過現在又傳出了消息，"
                       "擾亂六大門派的主謀竟然也不是他，而是一"
                       "個叫" HIY + NPC3_NAME + NOR + CYN "的人"
                       "在幕後操縱。\n" + knower->name() + CYN
                       "伸個懶腰繼續道：嘖嘖，這些傢伙啊，一個"
                       "比一狠！" NOR;

        if( query("combat_exp", me)<query("combat_exp", NPC2)/2 )
        {
                remove_call_out("whisper_to2");
                call_out("whisper_to2", 0, knower, me);
        }

        set_temp("capture/"+NPC2_ID, 1, me);
        return CYN "唉呀呀，又來了一個打探消息的。聽説那傢伙收"
               "到風聲，已經躲了起來。\n" + knower->name() + CYN
               "接着説道：不過前兩天倒是有一夥人在店裏歇腳，不"
               "知怎麼的就談起了他，聽説好像是躲到" + PLACE2 +
               "去了。" NOR;
}

// 詢問NPC3 - 最終追殺對象
string ask_npc3(object knower, object me)
{
        mapping my = query_entire_dbase();
/*
        if (! objectp(NPC3) && objectp(NPC1))
        {
                remove_call_out("cancel_quest");
                call_out("cancel_quest", 2);
        }
                return CYN "我沒聽説……咦？對了，前幾天有個家"
                       "夥掛了，倒是有點像你要找的人。" NOR;

        if (! objectp(NPC3) && objectp(NPC2))
        {
                remove_call_out("cancel_quest");
                call_out("cancel_quest", 2);
        }
                return CYN "我沒聽説……咦？對了，前幾天有個家"
                       "夥掛了，倒是有點像你要找的人。" NOR;
*/
        if (objectp(NPC1) || objectp(NPC2))
                return CYN "不清楚，不清楚，我從沒聽説過有那號"
                       "人！" NOR;

        if (! objectp(NPC3))
                return CYN "死了，全死光了。" HIY + NPC3_NAME +
                       NOR CYN "也讓人給做了。你算算，先是" HIY
                       + NPC1_NAME + NOR + CYN "，然後是" HIY +
                       NPC2_NAME + NOR + CYN "，現在又輪到他。"
                       "\n" + knower->name() + CYN "接着説道："
                       "嘖嘖嘖，誰叫他們把該惹的和不該惹的都惹"
                       "完了啊，這下都把命出脱就高興了。" NOR;

        if( query("combat_exp", me)<query("combat_exp", NPC3)/2 )
        {
                remove_call_out("whisper_to3");
                call_out("whisper_to3", 0, knower, me);
        }

        set_temp("capture/"+NPC3_ID, 1, me);
        return CYN "我説這傢伙耐性可真好，等到他同伴全死光了他"
               "才現身，嘖嘖。\n" + knower->name() + CYN "接着"
               "説道：不過看來他好運也不長，幾大門派收到消息後"
               "已經直奔" + PLACE3 + "找他去了。\n" + knower->name()
               + CYN "輕哼一聲，接着道：我説吧，人總歸會有倒黴"
               "的一天。喏，躲得過初一躲就不過十五。" NOR;
}

void whisper_to1(object knower, object me)
{
        mapping my = query_entire_dbase();

        if (! can_talk_with(me, knower))
                return;

        message("vision", knower->name() + "悄悄的在" + me->name()
                + "耳邊説了些什麼。\n", environment(me), ({ me }));

        tell_object(me, WHT + knower->name() + WHT "悄悄的對你説："
                     + RANK_D->query_respect(me) + "，我看你就別淌"
                    "這渾水了，" + NPC1_NAME + WHT "厲害着呢！\n" NOR);
}

void whisper_to2(object knower, object me)
{
        mapping my = query_entire_dbase();

        if (! can_talk_with(me, knower))
                return;

        message("vision", knower->name() + "悄悄的在" + me->name()
                + "耳邊説了些什麼。\n", environment(me), ({ me }));

        tell_object(me, WHT + knower->name() + WHT "悄悄的對你説："
                     + RANK_D->query_respect(me) + "，我看你就別淌"
                    "這渾水了，" + NPC2_NAME + WHT "厲害着呢！\n" NOR);
}

void whisper_to3(object knower, object me)
{
        mapping my = query_entire_dbase();

        if (! can_talk_with(me, knower))
                return;

        message("vision", knower->name() + "悄悄的在" + me->name()
                + "耳邊説了些什麼。\n", environment(me), ({ me }));

        tell_object(me, WHT + knower->name() + WHT "悄悄的對你説："
                     + RANK_D->query_respect(me) + "，我看你就別淌"
                    "這渾水了，" + NPC3_NAME + WHT "厲害着呢！\n" NOR);
}

// 任務介紹
string query_introduce(object knower)
{
        mapping my = query_entire_dbase();

        if (objectp(NPC1))
                return CYN "唉呀呀，聽説" HIY + NPC1_NAME + NOR +
                       CYN "那傢伙不知怎麼搞的，居然把江湖上六大門"
                       "派全都給惹了，真是有種！\n" + knower->name()
                       + CYN "接着説道：這下一來，六大門派便放出口"
                       "信，只要有人見到他，馬上格殺勿論。" NOR;

        if (objectp(NPC2) && ! objectp(NPC1))
                return CYN "你收到消息了嗎？上次擾亂六大門派那件事"
                       "，主謀竟然不是" HIY + NPC1_NAME + NOR + CYN
                       "，而是一個叫作" HIY + NPC2_NAME + NOR + CYN
                       "的在背後指使。\n" + knower->name() + CYN
                       "接着説道：提起" HIY + NPC1_NAME + NOR + CYN
                       "的下場也真慘，明明只是個幫兇，結果卻先一步"
                       "讓人家給做了。" NOR;

        if (objectp(NPC3) && ! objectp(NPC2) && ! objectp(NPC1))
                return CYN "想不到啊想不到！你給猜猜看，上次擾亂六"
                       "大門派的主謀是誰？\n" + knower->name() + CYN
                       "嘿嘿一笑，道：結果啊，既不是" HIY + NPC1_NAME
                       + NOR + CYN "，也不是" HIY + NPC2_NAME + NOR +
                       CYN "，而是一個叫" HIY + NPC3_NAME + NOR + CYN
                       "的人在幕後全權操縱！\n" + knower->name() +
                       CYN "接着説道：現在六大門派已經收到了消息，準"
                       "備全面追擊他去了。" NOR;

        if (! objectp(NPC3))
                return CYN "嘿嘿，這下人死光了，也算是太平了。\n" +
                       knower->name() + CYN "白眼一翻道：你算算，先"
                       "是" HIY + NPC1_NAME + NOR + CYN "，然後是"
                       HIY + NPC2_NAME + NOR + CYN "，最後又是" HIY
                       + NPC3_NAME + NOR + CYN "。\n" + knower->name()
                       + CYN "又接着道：嘖嘖嘖，誰叫他們把該惹的和不"
                       "該惹的都惹完了啊，這下都把命出脱就高興了。" NOR;
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
        set_information(NPC3_NAME, (: ask_npc3 :));
        set_information(NPC1_ID, (: ask_npc1 :));
        set_information(NPC2_ID, (: ask_npc2 :));
        set_information(NPC3_ID, (: ask_npc3 :));
}
