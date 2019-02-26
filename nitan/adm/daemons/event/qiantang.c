// qiantang.c 事件：錢塘江潮信

#include <ansi.h>

void create() { seteuid(getuid()); }

#define STATUS_PROMPT           1
#define STATUS_START            2
#define STATUS_END              3

// 開始創建事件
void create_event()
{
        // 明年8月份18日漲潮，提前一天提示
        EVENT_D->at_after(1, -8, -17, -12, STATUS_PROMPT);
}

// 獎勵
private void do_bonus(object room)
{
        object *obs;
        string msg;
        int r;

        obs = all_inventory(room);
        obs = filter_array(obs, (: playerp($1) && living($1) :));
        if (sizeof(obs) < 1)
                return;

        msg = HIC "只聽“隆隆”一陣雷鳴響過，潮水如湧一般的向岸邊捲來。\n"
                  "剎那間，漫江沸騰，波濤萬頃，潮高丈餘，萬馬奔騰，真有\n"
                  "“濤來勢轉雄，獵獵駕長風。雷震雲霓裏，山飛霜雪中”的\n"
                  "壯麗氣勢！正所謂“遠若素練橫江，聲如金鼓；近則亙如山\n"
                  "嶽，奮如雷霆”。一時間你不禁沉浸當中，天地萬物都已然\n"
                  "忘懷了。\n" NOR;
        message("vision", msg, obs);
        msg = "聽説八月十八" + implode(sizeof(obs) > 4 ? obs[0..3]->name(1)
                                                       : obs->name(1), "、") +
              "等人在錢塘江觀潮。";
        CHANNEL_D->do_channel(this_object(), "rumor", msg);

        obs=filter_array(obs,(:query("combat_exp", $1) >= 10000:));
        if (sizeof(obs) < 1)
                return;

        msg = HIG "你望着洶湧的潮水，若有所悟，對武功又有了新的體會。\n" NOR;
        message("vision", msg, obs);
        for( int i=0; i<sizeof(obs); i++ )
        {
                addn("combat_exp", 1000+random(500), obs[i]);
                obs[i]->improve_potential(100 + random(100));
                obs[i]->improve_skill("force", 1000 + random(1000), 1);
        }
        MAP_D->record_rumor(obs, "錢塘江潮信", this_object());
}

// 事件觸發
void trigger_event(int status)
{
        object room;

        room = find_object("/d/hangzhou/qiantang");

        // 錢塘江潮信
        switch (status)
        {
        case STATUS_PROMPT:
                CHANNEL_D->do_channel(this_object(), "rumor",
                        "八月十八又要到了，聽説不少人前往錢塘江觀潮。");
                // 明天18點鐘起潮
                EVENT_D->at_after(0, 0, 1, -18, STATUS_START);
                break;
                
        case STATUS_START:
                if (objectp(room))
                        do_bonus(room);
                // 一個小時以後落潮
                EVENT_D->at_after(0, 0, 0, 1, STATUS_END);
                break;

        case STATUS_END:
                if (objectp(room))
                        message("vision", "潮水漸漸的退了下去，你這才"
                                          "彷彿從夢中醒了過來。\n", room);
                // 繼續執行default中的內容

        default:
                create_event();
                break;
        }
}

// 描述
string query_detail(string topic)
{
        switch (topic)
        {
        case "錢塘江潮信":
                return "每年八月十八錢塘江漲潮，非常準時，故稱之為潮信。每次潮水來臨"
                       "時波濤洶湧，氣勢逼人，十分壯觀。\n";
        }
}
