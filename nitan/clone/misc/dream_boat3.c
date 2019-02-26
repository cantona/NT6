
#include <ansi.h>
#define MEMBER_D "/adm/daemons/memberd"

inherit ITEM;

int last_update_boss;

string *nature_message = ({
        "遠處傳來陣陣海浪聲，船身輕輕地搖晃了幾下，隨即風平浪靜。\n",
        "天空傳來數聲雷鳴，風雲突變，烏雲黑壓壓的一片籠罩着上空。\n",
        "你放眼望去，一羣海豚尾隨着船，正在跳躍嬉戲，海面波光粼粼，甚是美麗。\n",
        "幾聲驚雷過後，天空突然下起雨來，海浪滔天，船身劇烈地搖晃着。\n",
        "風雨過後，天空突然放晴，一羣海鷗從天邊飛來，映襯着遠出的彩虹，真是人間美景。\n",
        "你站在船頭，一陣海風吹過，清新撲面，閉上雙眼，感覺渾身舒泰無比。\n",
        "周圍依然是無邊的海洋，海浪拍打着帆船，海風吹過，將帆鼓得滿滿地。\n",
        });

void start_heart_beat()
{
        // 默認為心跳1
        set_heart_beat(1);
}

void create()
{
        set_name(HIW "仙境號帆船（開往未知地點）" NOR, ({ "penglai boat"}));
        set_weight(2000);
        set_max_encumbrance(10000000);
        if (clonep())
        {
                set_default_object(__FILE__);
        }
        else
        {
                set("value", 1);
                                
                if (query("running"))
                           set("long", HIR "\n船伕(chuanfu)吆喝道：我們的船正在行使中，請耐心等候。\n" NOR);
                else
                        set("long", HIC "\n船伕(chuanfu)吆喝道：我們的船正在等待中，你可以先在船上休息（enter）。\n" NOR);

                set("item_desc", ([
                        "chuanfu" : "這是一位經驗豐富船伕，正忙得不可開焦。\n",
                ]));
                set("no_flyto", 1);
                set("no_rideto", 1);
                set("no_clean_up", 1);

                set("stop_time", time()); // 靠岸的時間
                set("waiting_time", 900); // 默認等船時間
                set("running_time", 900); // 默認行使時間為十五分鐘

                set("source_place", "/d/xiakedao/haibin"); // 出發地
                set("dest_place", "/d/penglai/haitan"); // 目的地
                set("dest_place_name", "蓬萊仙島");
                set("source_place_name", "南海之濱");

                set("unit", "艘");
                set("material", "wood");
                set("no_get", "船伕(chuanfu)喝道：好傢伙，這你也想扛在肩上？\n");

        }
        setup();        
        start_heart_beat();
}

void init()
{
        add_action("do_enter", "enter");
        add_action("do_out", "out");
}

int do_enter ( string arg )
{
        object ob;
        string dir;
        object *inv;
        object horse, person;
        int i;

        ob = this_player();
        if (arg != this_object()->query("id"))
        {
                tell_object(ob , "你要 enter 哪兒？\n");
                return 1 ;
        }

        if (ob->is_busy())
                return notify_fail("你正忙。\n");
                
        // 所有騎馬的人必須下馬
        if (objectp(horse = ob->query_temp("is_riding")))
        {
                if (objectp(person = horse->query_temp("is_rided_follow")))
                        person->delete_temp("is_riding_follow");

                horse->delete_temp("is_rided_follow");
                horse->delete_temp("is_rided_by");
                ob->delete_temp("is_riding_follow");
                ob->delete_temp("is_riding"); 
                

                message_vision(HIR "\n$N的" + horse->name() + HIR " 似乎無法躍上帆船，前蹄一揚，所有人"
                               "被迫跳下馬。\n\n" NOR, ob);

                return 1;
        }

        // 把背起的用户放下來
        inv = deep_inventory(ob);
        for (i = 0; i < sizeof(inv); i++)
        {
                if (! playerp(inv[i])) continue;

                // 被人揹起的用户
                inv[i]->move(environment(this_object()));                
        }

/*
        // 暫時只對500萬EXP以下的非轉世會員開放
        if ((! MEMBER_D->is_valib_member(ob->query("id")) || 
            ob->query("scborn/ok")) && ! wizardp(ob))
                return notify_fail("船伕(chuanfu)道：公開測試期間，這船暫時只針對非轉世會員開放。\n");
*/                                
        if (environment(ob) == this_object())
                return notify_fail("船伕(chuanfu)道：你已經在船上了，怎麼，想跳下海？\n");

        if (! ob->move(this_object()))return notify_fail("這位客官，船已經坐不下了，等下班吧！\n");

        tell_object(ob, HIG "船伕(chuanfu)對你説道：要下船請輸入 out 。\n" NOR);

        return 1 ;
}

int do_out()
{
        object me = this_player();

        if (environment(me) != this_object())return 0;
                
        if (query("running"))
                return notify_fail("已經開船了！\n");
                
        me->move(environment(this_object()));
                
        return 1;
}

void heart_beat()
{
                //object me = find_player("rcwiz");
                object *inv, *obs;
                object ob, ob_boss;
                string now_place_name;
                int left_time;

                //keep_heart_beat(1);

                if (! environment(this_object()))return;

                set_name(HIW "仙境號帆船（開往" + query("dest_place_name") + "）" NOR, query("id"));

                left_time = query("waiting") - (time() - query("stop_time"));
                left_time /= 60;
                if (query("running"))
                {
                        // 隨機出現描述
                        if (random(30) == 1)
                        {
                                message_vision(HIC + nature_message[random(sizeof(nature_message))] + NOR, this_object()); 
                        }
                        
                        if (time() - query("start_time") >= query("running_time") / 2 )        
                        {                
                                set("long", HIR "\n船伕(chuanfu)吆喝道：我們的船正在行使中，已行使超過路程的一半，請耐心等候。\n" NOR);                        
                                if ((time() - last_update_boss >= 1800) && random(4) == 7 )
                                {
                                        ob_boss = new("/d/penglai/npc/qingmianshou");
                                        if (ob_boss->move(this_object()))        
                                        {
                                                message_vision(HIB "突然，風起浪湧，只見天空一團黑霧飄過，船身劇烈晃動，恍惚間，一隻巨獸已經站在"
                                                               "你面前。\n" NOR, this_object()); 
                                                       CHANNEL_D->do_channel(this_object(), "rumor", "聽説" HIG "青面獸" + HIM "從蓬萊仙島逃出，上了仙境號帆船。" NOR);
                                        }
                                        last_update_boss = time();
                                }
                                
                        }
                        else
                                set("long", HIR "\n船伕(chuanfu)吆喝道：我們的船正在行使中，請耐心等候。\n" NOR);
                }
                else
                        set("long", HIC "\n船伕(chuanfu)吆喝道：我們的船正在等待中(開船剩餘" + sprintf("%d", left_time) + "分鐘)，你可以先在船上休息（enter）。\n" NOR);
                
                inv = all_inventory(this_object());
                obs = filter_array(inv, (: userp($1) :)); // 過濾掉非玩家物件

                // 正在行使中計算靠岸時間是否達到
                if (query("running"))
                {
                        // 到站了
                        if (time() - query("start_time") >= query("running_time"))
                        {
                                        set("stop_time", time()); // 設置到站時間
                                        this_object()->move(query("dest_place"));
                                        delete("running");
                                        message_vision(HIC "船伕(chuanfu)吆喝道：客官們小心喲，船靠岸了 ……\n" NOR, this_object());
/*
                                        if (ob_boss = find_living("qingmian shou"))
                                        {
                                                destruct(ob_boss);
                                        }
*/
                                        // 到岸並設置玩家startroom
                                        foreach(ob in obs)
                                        {
                                                //if (ob->query("id") == "qingmian shou")destruct(ob);
                                                ob->move(environment(this_object()));
                                                ob->set("startroom", base_name(environment(this_object())));        
                                                ob->save();
                                        }
                                        // 重新設置名稱和源，目的地點
                                        now_place_name = query("dest_place_name");
                                        set("dest_place", query("source_place"));
                                        set("dest_place_name", query("source_place_name"));

                                        set("source_place", base_name(environment(this_object())));
                                        set("source_place_name", now_place_name);

                                        
                                        // 靠岸時間
                                        set("stop_time", time());                                        
                                        
                        }
                        return;
                }
                else // ! running
                {
                        // 開船了
                        if (time() - query("stop_time") >= query("waiting_time"))
                        {
                                set("start_time", time());
                                set("running", 1);
                                message_vision(HIC "船伕(chuanfu)吆喝道：小心啦，船起航了 ……\n" NOR, this_object());
                                this_object()->move("/clone/misc/sea");
                        }
                        return;
                }
                

}
