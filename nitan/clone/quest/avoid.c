// 玩家提示任務：avoid.c

#include <ansi.h>
#include <quest.h>
#include <command.h>

inherit QUEST_OB;

#define ZONE            my["zone"]      // 接收對象所處的區域

// 任務對象創建
void create()
{
        seteuid(getuid());
        setup();
}

// 這是提示信息任務：凡是啟動了這個任務，那麼玩家詢問的話就
// 有可能打聽到相應的消息。
//
// 其中輸入參數env 則是任務相關的場景，如果定義了這個參數，
// 那麼上只有和這個場景在同一個區域的消息靈通人士才能夠得知
// 這個任務所支持的消息。
//
// 在調用這個初始化的函數之前，調用者必須先處理好所有需要散
// 布的消息，這通過設置/rumor這個映射對象來實現。比如需要散
// 布“位置”這個消息，就需要設置“/rumor/位置”為位置消息。
void init_quest(string quest_name, object env)
{
        mapping my;
        string zone;

        my = query_entire_dbase();

        // 生成任務的名字
        set_name(quest_name);

        // 檢索場景
        if (objectp(env))
        {
                zone = base_name(env);
                if (sscanf(zone, "/d/%s/%*s", zone) == 2)
                        zone = "/d/" + zone + "/";
                else
                        zone = "/";
        } else
                zone = "/";
        ZONE = zone;

        // 切換到正常狀態
        change_status(QUEST_READY);

        // 設置任務最長存活時間：60分鐘
        set("live_time", 540);

        // 登記謠言消息
        register_information();
}

// 任務介紹
string query_introduce(object knower)
{
        return query("introduce");
}

// 登記該任務的消息
void register_information()
{
        mapping my = query_entire_dbase();
        mapping rumor;
        string  key;

        if (! clonep() || ! mapp(my))
                // 不是任務，所以不登記
                return;

        if (! mapp(rumor = query("rumor")))
                // 沒有可以散布的消息
                return;

        // 登記所有可以散布的消息
        foreach (key in keys(rumor))
        {
                if (! stringp(key))
                        continue;

                set_information(key, rumor[key]);
        }
}

// 這個任務可以被某人散布嗎？
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

// 不能被散布
int can_rumor_by()
{
        return 0;
}