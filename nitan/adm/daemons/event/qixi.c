// qixi.c 事件：七夕牛郎織女星相會
// couple/id 如果結婚則獎勵加倍
#include <ansi.h>

void create() { seteuid(getuid()); }

#define STATUS_PROMPT           1
#define STATUS_START            2
#define STATUS_END              3

// 開始創建事件
void create_event()
{
        // 明年7月7日牛郎織女星相會，提前一天提示
        EVENT_D->at_after(1, -7, -6, -12, STATUS_PROMPT);
}

// 獎勵
private void do_bonus(object room)
{
        object *obs;
        string msg;
        int r;
        int p = 1;
        int i;

        obs = all_inventory(room);
        obs = filter_array(obs, (: playerp($1) && living($1) :));
        if (sizeof(obs) < 1)
                return;

        msg = HIW "\n只見天際羣星光芒齊放，鵲橋隱現，牛郎織女之星光華閃耀，\n"
                  "會聚於鵲橋之上，剎那間，羣星圍繞，流光溢彩，一番盛大\n"
                  "景象。正所謂：\n" HIY
                  "　　    維天有漢，監亦有光。\n"
                  "        岐彼織女，終日七襄。\n"
                  "        雖則七襄，不成報章。\n"
                  "        睕彼牽牛，不以報箱。\n" HIW
                  "令人畢生難忘，又有古詩云：\n" HIY
                  "　　    迢迢牽牛星，皎皎河漢女。\n"
                  "        纖纖灌素手，札札弄機杼；\n"
                  "        終日不成章，泣涕零如雨。\n"
                  "        河漢清且淺，相去復幾許?\n"
                  "        盈盈一水問，脈脈不得語。\n" NOR;

        message("vision", msg, obs);
        msg = "聽説七月初七" + implode(sizeof(obs) > 4 ? obs[0..3]->name(1) : obs->name(1), "、") +
              "等人在望月台觀賞牛郎織女星相會。";

        CHANNEL_D->do_channel(this_object(), "rumor", msg);

        obs=filter_array(obs,(:query("combat_exp", $1) >= 10000:));
        if (sizeof(obs) < 1)
                return;

        msg = HIG "你望着浩瀚的天際以及牛郎星與織女星發出耀眼的光芒，似乎若有所思。\n" NOR;
        message("vision", msg, obs);

        for( i=0; i<sizeof(obs); i++ )
        {
                // 已經結婚的則獎勵加倍
                if( stringp(query("couple/id", obs[i])))
                {
                        if (query("combat_exp", obs[i]) < 1000000000)
                                addn("combat_exp", 3000 * p*2, obs[i]);
                        obs[i]->improve_potential(1000 * p*2 + random(1000 * p*2));
                        obs[i]->improve_skill("martial-cognize", 1000 * p*2 + random(1000* p*2), 1);
                        addn("magic_points", 30*p*2+random(21*p*2), obs[i]);
                }
                else
                {
                        if (query("combat_exp", obs[i]) < 1000000000)
                                addn("combat_exp", 3000 * p, obs[i]);
                        obs[i]->improve_potential(1000 * p + random(1000 * p));
                        obs[i]->improve_skill("martial-cognize", 1000 * p + random(1000* p), 1);
                        addn("magic_points", 30*p+random(21*p), obs[i]);
                }
        }
        MAP_D->record_rumor(obs, "望月台七夕盛景", this_object());
}

// 事件觸發
void trigger_event(int status)
{
        object room;

        room = find_object("/d/henshan/wangyuetai");

        // 錢塘江潮信
        switch (status)
        {
        case STATUS_PROMPT:
                CHANNEL_D->do_channel(this_object(), "rumor",
                        "七月初七又要到了，聽説不少人前往望月台觀賞牛郎織女星相會。");
                // 明天18點鐘相會
                EVENT_D->at_after(0, 0, 1, -18, STATUS_START);
                break;

        case STATUS_START:
                if (objectp(room))
                        do_bonus(room);
                // 一個小時以後完畢
                EVENT_D->at_after(0, 0, 0, 1, STATUS_END);
                break;

        case STATUS_END:
                if (objectp(room))
                        message("vision", "天際逐漸暗淡了下來，恢復了平靜，你這才"
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
        case "望月台七夕盛景":
                return "每年七月初七牛郎星與織女星在鵲橋相會，非常準時，故稱之為七夕盛景色。每次兩星相會"
                       "時羣星閃耀，光彩照人，場面甚是壯觀。\n";
        }
}

