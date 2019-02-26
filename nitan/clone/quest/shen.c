// 玩家任務：shen.c

#include <ansi.h>
#include <quest.h>

inherit QUEST_OB;

#define QOB             my["qob"]
#define NPC_OB          my["npc_ob"]
#define NPC_ID          my["npc_id"]
#define NPC_NAME        my["npc_name"]
#define PLACE           my["place"]
#define TYPE            my["type"]
#define ZONE            my["zone"]

void npc_destructed();

// 任務對象創建
void create()
{
        setup();
}

// 啟動一個任務
// 殺一個人即可獲得神的獎勵。
void init_quest()
{
        string name;
        object qob;
        string place;
        object npc;
        mapping my;
        int type;

        // 產生兩個隨機地點
        place = NPC_D->random_place(({ "西域" }));

        // 產生兩個隨機人物
        npc = new(CLASS_D("generate") + "/shennpc");
        set_temp("quest_ob", this_object(), npc);

        // 設置析構信息：NPC人物析構以後將自動解除任務
        set_temp("override/destruct", (:npc_destructed:), npc);

        // 生成任務的名字
        if (type = random(2))
        {
                name = "飛賊" + npc->name();
                set("shen_type", -1, npc);
        } else
        {
                name = "反賊" + npc->name();
                set("shen_type", 1, npc);
        }
        set_name(name);

        // 記錄這些人物、地點和物品信息
        my = query_entire_dbase();

        TYPE = type;
        NPC_OB = npc;
        PLACE = place;
        NPC_NAME = npc->name();
        NPC_ID=query("id", npc);

        // 人物出現
        NPC_D->place_npc(npc, 0, ({ place }));

        if (sscanf(file_name(environment(npc)), "/d/%s/%*s", ZONE) == 2)
            ZONE = "/d/" + ZONE + "/";
        else
            ZONE = "/";

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

        if (objectp(NPC_OB))
        {
                delete_temp("override/destruct", NPC_OB);
                destruct(NPC_OB);
        }

        // 任務消亡
        ::cancel_quest();
}

// 任務NPC消亡
void npc_destructed()
{
        call_out("cancel_quest", 0);
}

// 詢問NPC
string ask_npc(object knower, object me)
{
        mapping my = query_entire_dbase();

        if (! objectp(NPC_OB))
                return CYN "哎，這年頭，出頭就沒有好事，小命都要送掉了。" NOR;

        return CYN "哎，都説他在" + PLACE + "，找他的人好像可多了。" NOR;
}

// 任務介紹
string query_introduce(object knower)
{
        mapping my = query_entire_dbase();

        switch (TYPE)
        {
        case 0:
                return "聽説朝廷正在通緝反賊" + NPC_NAME +
                       "，嘖嘖，膽子大了，敢造反。";
        case 1:
                return "據説官府正在捉拿飛賊" + NPC_NAME +
                       "，這傢伙，可不是好人啊。";
        }
}

void do_say(object knower)
{
        mapping my = query_entire_dbase();

        message_vision("$N又自言自語道：凡是被官府捉拿的都沒好下場，你看，" +
                       NPC_NAME + "這麼狠，不也把小命送掉了？\n", knower);
}

// 這個消息能夠被散佈嗎？
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

// 登記該任務的消息
void register_information()
{
        mapping my = query_entire_dbase();

        if (! clonep() || ! mapp(my))
                // 不是任務，所以不登記
                return;

        set_information(NPC_NAME, (: ask_npc :));
        set_information(NPC_ID, (: ask_npc :));
}