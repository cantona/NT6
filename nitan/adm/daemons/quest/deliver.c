// 玩家任務守護進程：deliver.c

#include <ansi.h>

string *ob_list = ({
        "/clone/questob/rice",
        "/clone/questob/cloth",
        "/clone/questob/spice",
        "/clone/questob/bait",
        "/clone/questob/wood",
        "/clone/questob/metal",
        "/clone/questob/farm",
        "/clone/questob/silver",
        "/clone/questob/gold",
});

void startup();

// 任務對象創建
void create()
{
        seteuid(getuid());
        if (! clonep() && find_object(QUEST_D)) startup();
}

void start_quest()
{
        object qob;     // 任務物件
        string name;    // 要送的貨物
        int amount;     // 送貨的數量

        if (sizeof(children("/clone/quest/deliver")) > 30)
                // 系統中最68個送貨的任務
                return;

        name = ob_list[random(sizeof(ob_list))];
        amount = 5 + random(6);

        qob = new("/clone/quest/deliver");
        qob->init_quest(name, amount);

/*
        CHANNEL_D->do_channel(find_object(QUEST_D),
                              "debug", "進程(DELIVER)利用" +
                              get_object(name)->name() +
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
                                      "sys", "進程(DELIVER)啟動了。");

        // 平均每四分鐘產生一個任務
        set_heart_beat(2 + random(2));
}

// 停止這個任務進程
void stop()
{
        set_heart_beat(0);
}
