// emei.c 事件：峨嵋金頂日出

#include <ansi.h>

void create() { seteuid(getuid()); }

// 開始創建事件
void create_event()
{
        // 明天5點鐘日出
        EVENT_D->at_after(0, 0, 1, -5);
}

// 獎勵
private void do_bonus(object room)
{
        object *obs;
        object ob;
        string msg;
        int lvl;
        int r;

        obs = all_inventory(room);
        obs = filter_array(obs, (: playerp($1) && living($1) :));
        if (sizeof(obs) < 1)
                return;

        r = random(365);
        if (r == 0)
        {
                msg = HIR "只見太陽一點一點的升了起來，倏的眼前一亮，只見一道光暈出現在雲際，\n"
                          "朦朦朧朧似乎有一個人影立在當中，令人嘆羨不已。\n" NOR;
                msg += HIG "你冥冥中仿佛得到了佛主的指示，登時有茅塞頓開的感覺。\n" NOR;

                for( int i=0; i<sizeof(obs); i++ )
                        addn("potential", 1000, obs[i]);

                // 佛門弟子增加佛學技能
                foreach (ob in obs)
                {
                        if( query("class", ob) != "bonze" )
                                continue;

                        if ((lvl = ob->query_skill("buddhism", 1)) >= 50)
                                ob->set_skill("buddhism", lvl + 1);

                        if ((lvl = ob->query_skill("mahayana", 1)) >= 50)
                                ob->set_skill("mahayana", lvl + 1);

                        if ((lvl = ob->query_skill("lamaism", 1)) >= 50)
                                ob->set_skill("lamaism", lvl + 1);
                }

                message("vision", msg, obs);

                // 記錄事件
                MAP_D->record_rumor(obs, "峨嵋佛光", this_object());

                CHANNEL_D->do_channel(this_object(), "rumor",
                                      "聽說峨嵋金頂佛光出現，令人嘆為觀止，讚嘆不已。");
        } else
        if (r < 250)
        {
                switch (random(3))
                {
                case 0:
                        msg = HIY "一輪紅日躍出天際，映射得層巒疊翠分外妖嬈，茫茫雲海，盡披紅妝。\n" NOR;
                        break;
                case 1:
                        msg = HIY "忽然間一輪紅日躍了上來，天地之間登時輝煌無比，只射得你眼睛都無法睜開。\n" NOR;
                        break;
                default:
                        msg = HIY "驀然眼前金光四射，一輪紅日冉冉升起。\n" NOR;
                        break;
                }
                msg += HIG "你心頭閃過一道靈光，似乎受到了某種啟迪。\n" NOR;
                obs->improve_potential(10 + random(10));

                message("vision", msg, obs);

                // 記錄事件
                MAP_D->record_rumor(obs, "峨嵋日出", this_object());
        } else
        {
                switch (random(3))
                {
                case 0:
                        msg = WHT "眼見太陽朦朦朧朧的就要升上來，卻見一片烏雲飄過，遮了個嚴嚴實實。\n" NOR;
                        break;
                case 1:
                        msg = WHT "你眼前越來越亮，但是霧氣好重，讓你什麼都看不清楚。\n" NOR;
                        break;
                default:
                        msg = WHT "天邊漸漸的發白，但是一層一層的雲氣將日頭壓得光芒一絲都看不見。\n" NOR;
                        break;
                }
                msg += HIG "你心中連嘆：“太可惜了！”\n" NOR;

                message("vision", msg, obs);
        }
}

// 事件觸發
void trigger_event()
{
        object room;

        // 峨嵋金頂日出
        if (objectp(room = find_object("/d/emei/jinding")))
                do_bonus(room);

        create_event();
}

// 描述
string query_detail(string topic)
{
        switch (topic)
        {
        case "峨嵋佛光":
                return "峨嵋佛光是峨嵋山獨特的景觀，你能在遠處天邊的光暈中"
                       "看到你自己的身影，非常的奇妙。\n";

        case "峨嵋日出":
                return "在峨嵋山上欣賞日出令人心曠神怡，格外領略峨嵋山的雋"
                       "秀險奇。\n";
        }
}
