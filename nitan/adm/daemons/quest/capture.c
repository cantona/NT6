#include <ansi.h>

void startup();

// 任務對象創建
void create()
{
        seteuid(getuid());
        if (! clonep() && find_object(QUEST_D)) startup();
}

void start_quest()
{
        object qob;
        string qob_name;
        string *ob_names;

        if (sizeof(children("/clone/quest/capture")) > 300)
                // 系統中最7個追殺的任務
                return;

        qob = new("/clone/quest/capture");
        qob->init_quest();
/*
        CHANNEL_D->do_channel(find_object(QUEST_D),
                              "debug", "進程(CAPTURE)"
                              NOR HIW "創建了一個任務。");
*/
}

private void heart_beat()
{
        if (! find_object(QUEST_D))
                return;

        // 如果可以，每次心跳產生一個QUEST
        start_quest();
}

// 任務守護進程喚醒這個進程
void startup()
{
        // 啟動
        if (! find_object(QUEST_D))
                return;

        if (! query_heart_beat())
                CHANNEL_D->do_channel(find_object(QUEST_D),
                                      "sys", "進程(CAPTURE)啟動了。");

        // 平均每四分鐘產生一個任務
        set_heart_beat(2 + random(2));
}

// 停止這個任務進程
void stop()
{
        set_heart_beat(0);
}
