// xuxiake.c 徐霞客

#include <ansi.h>

inherit NPC;

mixed ask_map();

void create()
{
        set_name("徐霞客", ({ "xu xiake", "xu" }));

        set("gender", "男性");
        set("age", 45);
        set("long",
                "他早年走遍天下，見識了無數的美景奇觀，對山川地理莫不了如指掌。\n");

        set("attitude", "friendly");
        set("inquiry", ([
                "地圖" : (: ask_map :),
                "map"  : (: ask_map :),
        ]));

        setup();
        carry_object("/clone/misc/cloth")->wear();
}

mixed ask_map()
{
        object me, ob;
        mapping map;
        string *ks;
        string msg;
        string str;
        int n;
        object obn;

        ob = this_object();
        me = this_player();
        if( !query("out_family", me) )
        {
                message_vision("$N微微一笑，對$n道：“你身上帶了地圖冊麼？”\n",
                               ob, me);
                return 1;
        }

        if( query("map_all", me) )
        {
                message_vision("$N笑道：“" + RANK_D->query_respect(ob) +
                               "，你的地圖冊已經收錄了全集了，不如到處多走走吧。”\n",
                               ob, me);
                return 1;
        }

        if( !mapp(map=query("map", me)) )
                return "哦？你這本地圖冊還全是白紙呢！";

        // 查看那些地方沒有繪制
        ks = (string *) MAP_D->query_all_map_zone() - keys(map);
        if (sizeof(ks) < 1)
        {
                n = 0;
                foreach (str in keys(map))
                        n += sizeof(map[str]);
                if (n < 200)
                {
                        message_sort("$N接過$n的地圖冊，仔細翻了一會兒，嘆道：“"
                                     "我看過你繪制的地圖冊了，收錄的地點倒是滿全"
                                     "的，可惜很多地方記載不祥，你自己好好再看看"
                                     "吧。”\n", ob, me);
                        return 1;
                }

                message_sort("$N接過$n的地圖冊，仔細翻了一會兒，凝思良久，又翻閱"
                             "了一陣，不由得喜上眉梢，對$n讚道：“實在不曾想到這"
                             "世上還有人能像我一樣走遍名山大川，難得，難得！嗯，"
                             "我看你的地圖冊中還有少許缺漏，這就給你補全吧，日後"
                             "你或許還用得上。”說完，$N隨手拿起筆，在$n的地圖冊"
                             "上補了幾筆，還給了$n。\n", ob, me);
                delete("map", me);
                set("map_all", 1, me);
                CHANNEL_D->do_channel(this_object(), "rumor",
                                      "聽說"+me->name(1)+"("+query("id", me)+
                                      ")向徐霞客討教地理山川知識，獲得了地圖全集。");
                addn("potential", 30000, me);
                addn("score", 20000, me);
                addn("weiwang", 20, me);
                obn = new("/clone/gift/xuanhuang");
                obn->move(me, 1);
                if (! query("zhufu_mod/cloth", me)) 
                {
                        message_vision("$n對$N微微一笑，道：幹得不賴，有點" 
                                       "意思，這個神之祝福戰衣就算是我送給你的禮物吧。\n",
                                       me, this_object());
                        obn = new("/clone/goods/zhufu_cloth"); 
                        obn->move(me, 1);
                        tell_object(me, HIM "\n你獲得了一個" + obn->name() + HIM "！\n" NOR);
                        set("zhufu_mod/cloth", 1, me); 
                }
                tell_object(me, HIG "你仔細翻閱了地圖全集，思索許久，收獲良多，獲"
                                "得了三萬點潛能、兩萬點江湖閱歷和一個練功仙丹。\n" NOR);
                return 1;
        }

        if (sizeof(ks) > 3) ks = ks[0..2];
        ks = map_array(ks, (: MAP_D->query_map_short($1) :));
        msg = "$N接過$n的地圖冊，仔細翻了一會兒，皺眉道：“以我看來，"
              "你這裡面繪制的地圖還相當不全呢，至少" +
              implode(ks, "、") + "就沒有收錄在內。”\n";
        message_sort(msg, ob, me);
        return 1;
}
