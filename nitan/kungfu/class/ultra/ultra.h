// ultra.h 宗師評價玩家的公共代碼

int calc_level(object me, string skill);
void check_ultra(object me);

// check level
// level is calculate as:
// level = (skill effect level) + (action["force"] - 200) / 5
mapping opinions_rank = ([
        520 : "宗師",
        490 : "登峯造極",
        460 : "超凡脱俗",
        430 : "臻至化境",
        400 : "爐火純青",
        360 : "已有大成",
        320 : "非同凡響",
        280 : "出類拔萃",
        240 : "身手不凡",
        200 : "已有小成",
]);

// generate opinion
void check_opinion(object me)
{
        string msg;
        string rank;
        int *ks;
        int lvl;
        int next_lvl;
        int opinion;
        int i;

        delete_temp("opinion");
        if (! me || environment(me) != environment())
        {
                command("sigh");
                return;
        }

        // rank: 原有的評價稱號
        // ks:   不同評價需要的等級按照升序排列
        // lvl:  原有評價所在的等級
        // next_lvl: 在原有的評價下下一等級需要的lvl
        // opinion : 此次的評價等級，如果為-1就沒有變化
        rank=query("opinion/"MY_OPINION, me);
        ks  = sort_array(keys(opinions_rank), 1);
        if (! stringp(rank))
        {
                // 以前沒有評價，設置最小評價需要的等級
                next_lvl = ks[0];
        } else
        {
                // 以前有評價，看這一次如果提升的話需要
                // 到多少級
                for (i = 0; i < sizeof(ks) - 1; i++)
                        if (opinions_rank[ks[i]] == rank)
                        {
                                next_lvl = ks[i + 1];
                                break;
                        }
                if (i >= sizeof(ks))
                {
                        // 無法找到原先的等級，設置最小評價
                        next_lvl = ks[0];
                }
        }
        opinion = -1;
        for (i = 0; i < sizeof(my_opinions); i++)
        {
                lvl = calc_level(me, my_opinions[i]);
                if (lvl >= next_lvl && lvl > opinion)
                        // 記錄：第i項武學有更好的評價
                        opinion = lvl;
        }

        if (opinion == -1)
        {
                if (next_lvl == ks[0])
                {
                        message_vision(CYN "\n$N" CYN "淡淡一笑，對$n"
                                       CYN "道：“你的" OPINION_TYPE
                                       + NOR + CYN "不行啊！好好努力"
                                       "吧！”\n" NOR, this_object(),
                                       me);
                        return;
                }
                message_vision(CYN "\n$N" CYN "對$n" CYN "搖搖頭道："
                               "“不怎麼樣，我發現你的" OPINION_TYPE
                               + NOR + CYN "比上次沒什麼太大的進步。"
                               "”\n" NOR, this_object(), me);
                return;
        }

        for (i = sizeof(ks) - 1; i > 0; i--)
                if (opinion >= ks[i]) break;

        set("opinion/"MY_OPINION, opinions_rank[ks[i]], me);
        if (i == sizeof(ks) -1)
        {
                // 到了終極
                message_vision(CYN "\n$N" CYN "對$n" CYN "笑道：“恭"
                               "喜！" + RANK_D->query_respect(me) +
                               "的" OPINION_TYPE + NOR + CYN "已然到"
                               "了宗師境界！武道無窮，閣下自重！”\n"
                               NOR, this_object(), me);
                set("opinions/master", 1, me);
                check_ultra(me);
                return;
        }

        message_vision(CYN "\n$N" CYN "沉思片刻，對$n" CYN "道：“就"
                       "目前來看，你的" OPINION_TYPE + NOR + CYN "已"
                       "經可以算得上是" + opinions_rank[ks[i]] + NOR
                       + CYN "了。”\n" NOR, this_object(), me);
}

void check_ultra(object me)
{
        object *ultra;

        if( query("opinion/unarmed", me) != "宗師" || 
            query("opinion/weapon", me) != "宗師" || 
            query("opinion/force", me) != "宗師" || 
            query("opinion/dodge", me) != "宗師" )
                return;

        set("opinion/ultra", 1, me);
        ultra = NPC_D->query_ultra_master();
        ultra -= ({ this_object() });
        command("chat真是長江後浪推前浪，想不到今日又有"+query("name", me)+
                "躋身武林大宗師的行列！");
        ultra->do_congration(me);
        CHANNEL_D->do_channel(find_object(MASTER_OB), "rumor",
                              "聽説"+query("name", me)+"成為武學大宗師。");
}
