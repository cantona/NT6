
#include <ansi.h>

inherit ITEM;

void start_heart_beat()
{
        // 默認為心跳1
                set_heart_beat(1);
}

void create()
{
        set_name(HIW "巨型帆船（開往未知地點）" NOR, ({ "large boat"}));
        set_weight(200000);
        set_max_encumbrance(1000000);
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
                                set("no_clean_up", 1);

                                set("stop_time", time()); // 靠岸的時間
                                set("waiting_time", 600); // 默認等船時間
                                set("running_time", 600); // 默認行使時間為十分鐘

                                set("source_place", "/d/shenlong/haitan"); // 出發地
                                set("dest_place", "/b/tulong/haigang"); // 目的地
                                set("dest_place_name", "東海之濱");
                                set("source_place_name", "神龍島");

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

        ob = this_player();
        if (arg != this_object()->query("id"))
        {
                tell_object(ob , "你要 enter 哪兒？\n");
                return 1 ;
        }

                if (environment(ob) == this_object())
                        return notify_fail("船伕(chuanfu)道：你已經在船上了。\n");
                
        ob ->move(this_object());

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
                object ob;
                string now_place_name;
                int left_time;

                if (! environment(this_object()))return;

                set_name(HIW "巨型帆船（開往" + query("dest_place_name") + "）" NOR, query("id"));

                left_time = query("waiting") - (time() - query("stop_time"));
                left_time /= 60;
                if (query("running"))
                {
                        if (time() - query("start_time") >= query("running_time") / 2 )                        
                                set("long", HIR "\n船伕(chuanfu)吆喝道：我們的船正在行使中，已行使超過路程的一半，請耐心等候。\n" NOR);                        
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
                                        foreach(ob in obs)
                                        {
                                                ob->move(environment(this_object()));                                                
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
