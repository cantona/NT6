// 玩家任務守護進程：search.c

#include <ansi.h>

string *lost_objs = ({
        "/clone/questob/baijinhe",
        "/clone/questob/baiyubi",
        "/clone/questob/jingua",
        "/clone/questob/jinhulu",
        "/clone/questob/jlhua",
        "/clone/questob/jxshi",
        "/clone/questob/qkmao",
        "/clone/questob/qtding",
        "/clone/questob/sjping",
        "/clone/questob/tiegy",
        "/clone/questob/tieruyi",
        "/clone/questob/tongxq",
        "/clone/questob/ygbei",
        "/clone/questob/ylhua",
        "/clone/questob/yudai",
        "/clone/questob/yuhulu",
        "/clone/questob/yuping",
        "/clone/questob/zijinchui",
        "/clone/questob/zysha",
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
        object qob;
        string qob_name;
        string *ob_names;

        // 派生其它的任務對象：必須有可用物品，當前任務 < 5
        ob_names=filter_array(lost_objs,(:!find_object($1) || !query_temp("quest_ob", get_object($1)):));
        if (sizeof(ob_names) < 1)
                return;

        if (sizeof(children("/clone/quest/search")) > 20)
                // 系統中最多10個尋找物品的任務
                return;

        qob_name = ob_names[random(sizeof(ob_names))];
        qob = new("/clone/quest/search");
        qob->init_quest(qob_name);
        CHANNEL_D->do_channel(find_object(QUEST_D),
                              "debug", "進程(SEARCH)"
                              NOR HIW "利用" + qob_name->name() +
                              NOR HIW "創建了一個任務。");
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
                                      "sys", "進程(SEARCH)啟動了。");

        // 平均每四分鐘產生一個任務
        //set_heart_beat(110 + random(20));
        set_heart_beat(2 + random(2));
}

// 停止這個任務進程
void stop()
{
        set_heart_beat(0);
}
