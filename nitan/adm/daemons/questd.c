// questd.c 處理任務的守護進程
// 包括師門任務函數載體和系統註冊任務(SYSREG_QUEST)

// 更新的內容：
// mapping mlist           - 發放任務者列表
// int     remote_bonus()  - 遠程獎勵玩家
// mapping prepare_quest() - 準備遠程任務
// int     start_quest()   - 正式開始遠程任務

#include <ansi.h>
#include <quest.h>

#pragma optimize
#pragma save_binary

inherit F_DBASE;

// 定義提供給外部調用的接口函數
varargs public void bonus(object who, mapping b, int flag);
public void   delay_bonus(object who, mapping b);
public mixed  accept_ask(object me, object who, string topic);
public void   set_information(object qob, string key, mixed info);
public mixed  query_information(object qob, string key);
public void   remove_information(object qob, string key);
public void   remove_all_information(object qob);
public string generate_information(object knower, object who, string topic);
public void   start_all_quest();

// 發放任務者列表
mapping mlist = ([
        "丐幫"     : CLASS_D("gaibang")   + "/hong.c",
        "明教"     : CLASS_D("mingjiao")  + "/zhangwuji.c",
        "魔教"     : CLASS_D("mojiao")    + "/tieyan.c",
        "五毒教"   : CLASS_D("wudu")      + "/hetieshou.c",
        "全真教"   : CLASS_D("quanzhen")  + "/ma.c",
        "峨嵋派"   : CLASS_D("emei")      + "/miejue.c",
        "古墓派"   : CLASS_D("gumu")      + "/longnv.c",
        "華山派"   : CLASS_D("huashan")   + "/yue-buqun.c",
        "靈鷲宮"   : CLASS_D("lingjiu")   + "/xuzhu.c",
        "少林派"   : CLASS_D("shaolin")   + "/xuan-ci.c",
        "神龍教"   : CLASS_D("shenlong")  + "/hong.c",
        "桃花島"   : CLASS_D("taohua")    + "/huang.c",
        "武當派"   : CLASS_D("wudang")    + "/zhang.c",
        "逍遙派"   : CLASS_D("xiaoyao")   + "/suxingh.c",
        "星宿派"   : CLASS_D("xingxiu")   + "/ding.c",
        "凌霄城"   : CLASS_D("lingxiao")  + "/baizizai.c",
        "鐵掌幫"   : CLASS_D("tiezhang")  + "/qiuqianren.c",
        "崑崙派"   : CLASS_D("kunlun")    + "/hetaichong.c",
        "青城派"   : CLASS_D("qingcheng") + "/yu.c",
        "嵩山派"   : CLASS_D("songshan")  + "/zuo.c",
        "泰山派"   : CLASS_D("taishan")   + "/tianmen.c",
        "衡山派"   : CLASS_D("henshan")   + "/mo.c",
        "恆山派"   : CLASS_D("hengshan")  + "/xian.c",
        "血刀門"   : CLASS_D("xuedao")    + "/laozu.c",
        "雪山寺"   : CLASS_D("xueshan")   + "/jiumozhi.c",
        "天地會"   : CLASS_D("yunlong")   + "/chen.c",
        "紅花會"   : CLASS_D("honghua")   + "/chen-jialuo.c",
        "段氏皇族" : CLASS_D("duan")      + "/duanzc.c",
        "慕容世家" : CLASS_D("murong")    + "/murongbo.c",
        "歐陽世家" : CLASS_D("ouyang")    + "/ouyangfeng.c",
        "關外胡家" : CLASS_D("hu")        + "/hufei.c",
        "華山劍宗" : CLASS_D("huashan")   + "/feng-buping.c",
        "唐門世家" : CLASS_D("tangmen")   + "/tangltt.c",
        "日月神教" : CLASS_D("riyue")     + "/dongfang.c",
]);

void create()
{
        seteuid(getuid());
        set("channel_id", "任務精靈");
        set_heart_beat(900);
        call_out("collect_all_quest_information", 1);
}

#define ONE_DAY                 (86400 / 365)
#define MAX_QUEST_LEVEL         3

private void skill_bonus(object me, object who)
{
        int gongxian;
        string *sk_list = ({
                "wuming-jianfa",
                "wuming-jianfa",
                "wuming-jianfa",
                "wuming-jianfa",
                "wuming-jianfa",
/*
                "qishang-quan",
                "qishang-quan",
                "qishang-quan",
                "qishang-quan",
                "zhuihun-jian",
                "zhuihun-jian",
                "zhuihun-jian",
                "zhuihun-jian",
                "baihua-quan",
                "baihua-quan",
                "baihua-quan",
                "baihua-quan",
                "sougu-yingzhua",
                "sougu-yingzhua",
                "sougu-yingzhua",
                "zhuangzi-wu",
                "shenxing-baibian",
                "hanbing-mianzhang",
                "hanbing-mianzhang",
                "hanbing-mianzhang",
                "xuanming-zhang",
                "xuanming-zhang",
                "xuanming-zhang",
                "shenzhaojing",
                "shenzhaojing",
                "shenzhaojing",
                "mingyu-gong",
                "mingyu-gong",
                "mingyu-gong",
                "shexing-lifan",
                "shexing-lifan",
                "shexing-lifan",
                "baihua-cuoquan",
                "baihua-cuoquan",
*/
        });
        string sk;

        sk = sk_list[random(sizeof(sk_list))];
        if (who->query_skill(sk, 1) > 0)
                return;

        gongxian = 100000;
        if( query("family/gongji", who)<gongxian
        ||  !SKILL_D(sk)->valid_learn(who))
        {
                message_vision("$n讚許的對$N笑了笑，道：“你真是我們" +
                               query("family/family_name", me)+
                               "的佼佼者，我最近研究過" +
                               HIY + to_chinese(sk) + NOR
                               "，\n頗有心得，只可惜你現在尚不足以"
                               "領悟其中奧妙，罷了，罷了。”\n",
                               who, me);
                return;
        }

        message_vision("$n讚許的對$N笑了笑，道：“你真是我們" +
                       query("family/family_name", me)+
                       "的佼佼者，正好我最近研究過" +
                       HIY + to_chinese(sk) + NOR
                       "，\n頗有心得，如果你想學，就傳授一些與你吧！”\n",
                       who, me);

        tell_object(who, HIW "\n學習" + to_chinese(sk) + HIW "需要消耗"
                         "你" + chinese_number(gongxian) + "點門派"
                         "貢獻，你是否願意(" HIY "answer Y|N" HIW
                         ")接受？\n\n" NOR);

        // 記錄可以領取任務獎勵的NPC
        set_temp("quest_gift/npc",query("id",  me), who);

        // 記錄任務獎勵武功
        set_temp("quest_gift/skill", sk, who);

        // 記錄領取該武功所需的門牌貢獻
        set_temp("quest_gift/gongxian", gongxian, who);

        return;
}

void special_bonus(object me, object who, mixed arg)
{
        int gongxian;
        // 隨機獎勵
        string *ob_list = ({
                "/clone/gift/xiandan",
                "/clone/gift/shenliwan",
                "/clone/gift/unknowdan",
                "/clone/gift/xisuidan",
                "/d/item/obj/xuantie",
                "/d/item/obj/wujins",
                "/d/item/obj/butian",
                "/d/item/obj/tiancs",
                "/clone/gift/jinkuai",
                "/clone/fam/pill/neili2",
                "/clone/fam/item/bixue",
                "/clone/quarry/item/zhenzhu",
                "/clone/tessera/gem",
                "/clone/goods/forging-stone",
                "/clone/tessera/rune11",
                "/clone/tessera/rune12",
                "/clone/tessera/rune13",
                "/clone/tessera/rune14",
                "/clone/tessera/rune15",
        });

        string un, gift;
        object ob;

        /*
        message_vision("$n對$N微微一笑，道：幹得不賴，辛苦"
                       "了，正好我這裏有點東西，你就拿去吧。\n",
                       who, me);
        */

        if (stringp(arg))
                gift = arg;
        else

        if( query("quest_count", who) == 1000 )
        {
                gift = ob_list[random(sizeof(ob_list))];
                gongxian = 500;
        } else

        if( query("quest_count", who) == 900 )
        {
                gift = ob_list[random(sizeof(ob_list))];
                gongxian = 300;
        } else

        if( query("quest_count", who) == 800 )
        {
                gift = ob_list[random(sizeof(ob_list))];
                gongxian = 400;
        } else

        if( query("quest_count", who) == 700 )
        {
                gift = ob_list[random(sizeof(ob_list))];
                gongxian = 400;
        } else

        if( query("quest_count", who) == 600 )
        {
                gift = ob_list[random(sizeof(ob_list))];
                gongxian = 500;
        } else

        if( query("quest_count", who) == 500 )
        {
                gift = ob_list[random(sizeof(ob_list))];
                gongxian = 300;
        } else

        if( query("quest_count", who) == 400 )
        {
                gift = ob_list[random(sizeof(ob_list))];
                gongxian = 300;
        } else

        if( query("quest_count", who) == 300 )
        {
                gift = ob_list[random(sizeof(ob_list))];
                gongxian = 200;
        } else

        if( query("quest_count", who) == 200 )
        {
                gift = ob_list[random(sizeof(ob_list))];
                gongxian = 150;
        } else

        if( query("quest_count", who) == 100 )
        {
                gift = ob_list[random(sizeof(ob_list))];
                gongxian = 80;
        } else

        if( query("quest_count", who) == 50 )
        {
                gift = ob_list[random(sizeof(ob_list))];
                gongxian = 30;
        } else

        if( query("quest_count", who) == 30 )
        {
                gift = ob_list[random(sizeof(ob_list))];
                gongxian = 10;
        } else
        {
                gift = ob_list[random(sizeof(ob_list))];
                gongxian = 1;
        }

        ob = new(gift);
        if( query("base_unit", ob) )
                un=query("base_unit", ob);
        else
                un=query("unit", ob);

        if( query("family/gongji", who) >= gongxian )
        {
                message_vision(CYN "$n" CYN "對$N" CYN "微笑道：我這裏有一"
                               + un + ob->name() + CYN "，如果你用得着就拿"
                               "去吧。\n" NOR, who, me);

                tell_object(who, HIW "\n獲得" + ob->name() + HIW "需要消耗"
                                 "你" + chinese_number(gongxian) + "點門派"
                                 "貢獻，你是否願意(" HIY "answer Y|N" HIW
                                 ")接受？\n\n" NOR);

                // 記錄可以領取任務獎勵的NPC
                set_temp("quest_gift/npc",query("id",  me), who);

                // 記錄任務獎勵物品的路徑
                set_temp("quest_gift/obj", gift, who);

                // 記錄領取該物品所需的門牌貢獻
                set_temp("quest_gift/gongxian", gongxian, who);
        } else
                message_vision(CYN "$n" CYN "對$N" CYN "道：正好我這"
                               "裏有…嗯…還是算了，相信你也用不到。"
                               "\n" NOR, who, me);
        destruct(ob);

        return ;
}

void money_bonus(object me, object who, mixed arg)
{
        string *ob_list = ({
                "/clone/gift/jinkuai",
                "/clone/gift/jintiao",
                "/clone/gift/xiaoyuanbao",
                "/clone/gift/dayuanbao",
                "/clone/gift/jinding",
        });
        object ob;

        /*
        message_vision("$n對$N微微一笑，道：幹得不賴，辛苦"
                       "了，行走江湖，總有各類開支應酬，這裏有些金子，你就拿去吧。\n",
                       who, me);
        */

        if (stringp(arg))
                ob = new(arg);
        else
                ob = new(ob_list[random(sizeof(ob_list))]);

        ob->move(who,1);

        tell_object(who, HIM "你獲得了一" + query("unit", ob) + ob->name() +
                        HIM "。\n" NOR);
}

varargs public void bonus(object who, mapping b, int flag)
{
        int exp;                // 獎勵的經驗
        mixed pot;              // 獎勵的潛能
        mixed mar;              // 獎勵的實戰體會
        int shen;               // 獎勵的神
        int score;              // 獎勵的江湖閲歷
        int weiwang;            // 獎勵的江湖威望
        int gongxian;           // 獎勵的門派貢獻
        mixed pot_limit;        // 潛能的界限
        mixed mar_limit;        // 實戰體會的界限
        int percent;            // 獎勵的有效百分比
        string msg;             // 獎勵的描述信息
        int quest_times;

        quest_times = "/adm/daemons/actiond"->query_action("quest_reward");
        // 獲得獎勵的百分比
        percent = b["percent"];
        if (percent < 1 || percent > 100)
                percent = 100;

        exp = b["exp"] * percent / 100;
        pot = b["pot"] * percent / 100;
        mar = b["mar"] * percent / 100;
        shen = b["shen"] * percent / 100;
        score = b["score"] * percent / 100;
        weiwang = b["weiwang"] * percent / 100;
        gongxian = b["gongxian"] * percent / 100;

        if( query("special_skill/intellect", who) && random(2) )
        {
                exp += exp / 5;
                pot += pot / 5;
        }

        // 八面玲瓏增和門派功績
        if( query("special_skill/cunning", who) && random(2) )
                gongxian += gongxian;

        if (quest_times)
        {
                exp = exp*quest_times;
                pot = pot*quest_times;
                mar = mar*quest_times;
        }

#ifdef DB_SAVE
        if (MEMBER_D->is_double_reward(who))
        {
                exp *= 2;
                pot *= 2;
                mar *= 2;
        }
#endif

        if (! flag)
        {
                pot_limit = who->query_potential_limit() - query("potential", who);
                if (pot > pot_limit) pot = pot_limit;
                if (pot < 1) pot = 0;

                mar_limit = who->query_experience_limit() - query("experience", who);
                if (mar > mar_limit) mar = mar_limit;
                if (mar < 1) mar = 0;
        } else
        {
                if (who->query_potential_limit() < query("potential", who))
                        pot = 1 + random(2);

                if (who->query_experience_limit() < query("experience", who))
                        mar = 1;
        }

        // 生成提示信息
        if (stringp(msg = b["prompt"]))
                msg = HIC + msg + HIG "，你獲得了";
        else
                msg = HIC "通過這次鍛鍊，你獲得了";

        if (exp > 0) msg += chinese_number(exp) + "點經驗、";
        if (pot > 0) msg += chinese_number(pot) + "點潛能、";
        if (mar > 0) msg += chinese_number(mar) + "點實戰體會、";
        if (shen > 0) msg += chinese_number(shen) + "點正神、";
        if (shen < 0) msg += chinese_number(-shen) + "點負神、";
        if (score > 0) msg += chinese_number(score) + "點江湖閲歷、";
        if (weiwang > 0) msg += chinese_number(weiwang) + "點威望、";
        if (gongxian > 0) msg += chinese_number(gongxian) + "點門派功績、";

        msg += "能力得到了提升。\n" NOR;
        tell_object(who, sort_msg(msg));

        // bonus
        addn("combat_exp", exp, who);
        addn("potential", pot, who);
        addn("experience", mar, who);
        addn("shen", shen, who);
        addn("score", score, who);
        addn("weiwang", weiwang, who);
        addn("family/gongji", gongxian, who);
}

// 延遲獎勵：有時候給出獎勵的時候應該是在某些事件發生以後，
// 但是在該事件發生時給與獎勵更易於書寫程序，所以獎勵生成的
// 地方在事件正在發生的時候，但是要讓玩家看起來是在事件發生
// 以後。比如殺人，人死亡的時候給與獎勵是容易做的，但是我希
// 望玩家在看到NPC 的死亡信息以後才看到獎勵的信息，這時候就
// 用delay_bonus了。
public void delay_bonus(object who, mapping b)
{
        who->start_call_out((: call_other, __FILE__,
                               "bonus", who, b :), 1);
}

public mixed accept_ask(object me, object who, string topic)
{
        string my_fam;

        my_fam=query("family/family_name", me);

        if (topic == "歷練" || topic == "歷煉" ||
            topic == "鍛鍊")
        {
                if( my_fam != query("family/family_name", who) )
                        return "你是誰？找我有什麼事情麼？";

                if( query("out_family", who) )
                        return "去吧！" + who->name(1) + "，好自為之！";

                if( query("combat_exp", who)<50000 )
                {
                        message_sort(CYN "$N" CYN "歎了一口氣，看了看$n"
                                     CYN "道：“你的武功基礎還不太好，還是再"
                                     "好好鍛鍊吧！”\n", me, who);
                        return 1;
                }

                if( query("score", who)<100 )
                {
                        message_sort(CYN "$N" CYN "擺擺手道：“你的江湖"
                                     "閲歷太少，現在不可外出獨自行走江湖。”\n",
                                     me, who);
                        return 1;
                }

                set("out_family", 1, who);
                if (me->is_good())
                {
                        message_sort(HIY "$N" HIY "對$n" HIY "欣慰的點了"
                                     "點頭，道：“看來我們" + my_fam +
                                     "又出了一位人才啊！你記住了！我輩武"
                                     "人，切忌不可好勇爭鬥，要多做行俠仗"
                                     "義之事！”\n" NOR, me, who);
                } else
                if (me->is_bad())
                {
                        message_sort(HIR "$N" HIR "對$n" HIR "哈哈大笑道"
                                     "：“好！好！你可以出去走走看看了，"
                                     "對那些自認所謂大俠之輩可不要手軟，"
                                     "去吧！”\n" NOR, me, who);
                } else
                {
                        message_sort(HIY "$N" HIY "對$n" HIY "叮囑道：“"
                                     "以後你行走江湖常常是孤身一人，記得"
                                     "要敬重前輩，不可狂妄自大，切記了，"
                                     "去吧！”\n" NOR, me, who);
                }

                message_sort("$N翻出一本小冊子來，對$n道：“今後你行走江"
                             "湖，許多山川地理，世間風情你都可以記錄在這"
                             "本地圖冊上，以諮參考，對你多少也會有些幫助"
                             "。”\n", me, who);

                tell_object(me, HIY"你獲得了師傅贈給你的地圖冊，請參見幫"
                            "助(HELP QUEST)以\n獲得更詳細的信息。\n" NOR);

                CHANNEL_D->do_channel(this_object(), "rumor",
                        "聽説" + who->name(1) + "已經開始闖蕩江湖。");
                return 1;
        }
}

// 領取任務
// 如果目前正在協助別人，不能領取任務
public int ask_quest(object me, object who)
{
        string fam;             // ME的門派信息
        object ob;              // 任務重的某些物件或人物
        mapping q;              // WHO的人物
        object aob;             // WHO目前正在協助的對象
        mixed exp;              // WHO的經驗
        int t;                  // 用來計算時間的變量
        int level;              // QUEST的等級
        string place;

        message_vision("$n向$N打聽有關任務的情況。\n", me, who);

        fam=query("family/family_name", me);
        if( query("family/family_name", who) != fam )
        {
                message_vision("$N瞪大眼睛看着$n，道：“你又不是我們" + fam +
                               "的，來搗什麼亂？”\n", me, who);
                return 1;
        }

        if( query_temp("quest_gift", who) )
        {
                if( query_temp("quest_gift/skill", who) )
                        message_vision(CYN "$N" CYN "對$n" CYN "皺眉道：我問你"
                                       "話呢，那武功你到底學(" HIY "answer Y|N"
                                        NOR + CYN ")還是不學？\n" NOR, me, who);
                else
                        message_vision(CYN "$N" CYN "對$n" CYN "皺眉道：我問你"
                                       "話呢，那東西你到底要(" HIY "answer Y|N"
                                        NOR + CYN ")還是不要？\n" NOR, me, who);
                return 1;
        }

        q=query("quest", who);
        if (mapp(q))
        {
                if (q["freequest"] > 0)
                {
                        message_vision(CYN "$N" CYN "對$n" CYN "説道：我這裏暫"
                                       "時也沒什麼事情，你還是自己鍛鍊一段時間"
                                       "吧。\n" NOR, me, who);
                        tell_object(who, HIY "你突然想到：現在江湖正值動亂，何"
                                         "不四處走訪，也許可提高自己的經驗閲歷"
                                         "。\n" NOR);
                        return 1;
                }

                if( q["master_id"] && q["master_id"] != query("id", me) )
                {
                        message_vision(CYN "$N" CYN "看了看$n" CYN "，"
                                       "哼了一聲，沒有理會$n" CYN "。\n"
                                       NOR, me, who);
                        return 1;
                }

                switch (q["type"])
                {
                case "kill":
                        message_vision(CYN "$N" CYN "一臉怒容對$n" CYN "道：我不是讓"
                                       "你" + CHINESE_D->chinese_monthday(q["limit"]) +
                                       "之前殺了" NOR + HIR + q["name"] + "(" + q["id"] +
                                       ")" + NOR + CYN "的嗎？現在是" +
                                       CHINESE_D->chinese_monthday(time()) +
                                       "，他的人頭呢？\n" NOR, me, who);
                        break;

                case "letter":
                        message_vision(CYN "$N" CYN "一臉怒容對$n" CYN "道：我不是讓"
                                       "你" + CHINESE_D->chinese_monthday(q["limit"]) +
                                       "之前把信送到" NOR + HIC + q["name"] + "(" + q["id"] +
                                       ")" + NOR + CYN "那裏的嗎？現在是" +
                                       CHINESE_D->chinese_monthday(time()) +
                                       "，他的回執呢？\n" NOR, me, who);
                        break;

                }
                return 1;
        }

        if (query("eff_qi", me) * 2 < query("max_qi", me) ||
            query("qi", me) * 2 < query("max_qi", me))
        {
                message_vision(HIC "$N" HIC "捂着胸口，一副非常痛苦的樣子，對你的"
                               "話顯然沒有聽進去。\n" NOR, me);
                return 1;
        }

        exp=query("combat_exp", who);
        if (exp < 30000)
        {
                message_vision(CYN "$N" CYN "歎了一口氣，對$n" CYN "道：就你那點水平，"
                               "我實在沒法給你派任務。\n" NOR, me, who);
                return 1;
        }

        if( objectp(aob=query_temp("quest/assist", who)) )
        {
                message_vision(CYN "$N" CYN "看了看$n" CYN "，道：我聽説你不是幫" NOR +
                               HIY + aob->name(1) + NOR + CYN "去了麼？先辦妥了"
                               "再説吧！\n" NOR, me, who);
                return 1;
        }

        if (exp < 100000)
        {
                object letter;

                if( query("score", who)<20 )
                {
                        message_vision(CYN "$N" CYN "搖搖頭，對$n" CYN "道：可惜你"
                                       "的江湖閲歷太差，不然我還可以讓你幫我送封信"
                                       "。\n" NOR, me, who);
                        return 1;
                }

                ob = new(CLASS_D("generate") + "/receiver.c");
                NPC_D->place_npc(ob, ({ "大理一帶", "關外", "星宿海", "天山",
                                        "終南山", "西域" }));
                NPC_D->set_from_me(ob, me, 100);

                NPC_D->random_move(ob);
                NPC_D->random_move(ob);
                NPC_D->random_move(ob);

                place=query("place", ob);

                letter = new("/clone/misc/letter");
                letter->set("long","這是一封"+me->name()+"寫給"+ob->name()+
                                    "的親筆信函。\n");
                set("send_from",query("id",  me), letter);
                set("send_to",query("id",  ob), letter);
                set("send_from_name", me->name(), letter);
                letter->move(me);

                message_vision(CYN "$N" CYN "對$n" CYN "道：這封信你幫我交到" NOR +
                               HIC + ob->name() + "(" + query("id", ob) + ")" + NOR +
                               CYN "手中，他現在應該在" + place + "，然後把回執帶回來給我！\n" NOR,
                               me, who);

                me->force_me("give letter to " + query("id", who));
                set("quest/info",query("id",  letter), who);
                set("quest/type", "letter", who);
        } else
        if (exp < 200000)
        {
                message_vision("$N盯着$n看了半天，道：“讓你送信委屈了你，"
                               "叫你闖蕩江湖我又不放心，你還是好好練練功夫"
                               "吧！”\n", me, who);
                return 1;
        } else
        {
                if( !query("out_family", who) )
                {
                        message_sort(CYN "$N" CYN "擺擺手，對$n" CYN "道：我現在"
                                      "這裏倒是有一些事情，不過待你外出歷練段時間"
                                      "後再説吧！\n" NOR, me, who);
                        return 1;
                }

                if( query("score", who)<2000 )
                {
                        message_sort(CYN "$N" CYN "歎了一口氣，對$n" CYN "道：“你還"
                                     "是在江湖上多歷練歷練，增進一些閲歷再説吧！現在"
                                     "我對你還不夠放心！”\n" NOR, me, who);
                        return 1;
                }

                if( query("weiwang", who)<20 )
                {
                        message_sort(CYN "$N" CYN "看了看$n" CYN "，歎氣道：你在"
                                     "江湖上一點名頭都沒有，我沒法放心把任務交給"
                                     "你。\n" NOR, me, who);
                        tell_object(who, HIY "看來還是的加強自己的江湖威望才行。\n" NOR);
                        return 1;
                }

                if (who->is_bad() && me->is_good())
                {
                        message_sort(CYN "$N" CYN "大怒道：豈有此理！你居然已經誤"
                                     "入歧途，還敢來見我！\n" NOR, me, who);
                        return 1;
                }

                if (who->is_good() && me->is_bad())
                {
                        message_sort(CYN "$N" CYN "大怒道：豈有此理！才幾天不見，"
                                     "你居然也學起假仁假義來了，快給我滾！\n"
                                     NOR, me, who);
                        return 1;
                }

                level=query_temp("quest/next_level", who);
                if (level < 0 || level > MAX_QUEST_LEVEL)
                        level = 0;

                ob = new(CLASS_D("generate") + "/killed.c");
                NPC_D->place_npc(ob,query("combat_exp", who)<500000?({"大理一帶","終南山","關外","西域"}):
                                     query("combat_exp", who)<800000?({"大理一帶","終南山","西域"}):0);
                NPC_D->set_from_me(ob, who, 100);

                ob->add_temp("apply/attack",ob->query_skill("force")*
                                             (level - 1) / 15);
                ob->add_temp("apply/dodge",ob->query_skill("force")*
                                            (level - 1) / 15);
                ob->add_temp("apply/parry",ob->query_skill("force")*
                                            (level - 1) / 15);
                addn_temp("apply/damage", 5+level*7, ob);
                addn_temp("apply/unarmed_damage", 5+level*7, ob);
                addn_temp("apply/armor", 10+level*15, ob);
                set_temp("quester",query("id",  who), ob);

                NPC_D->random_move(ob);
                NPC_D->random_move(ob);
                NPC_D->random_move(ob);

                place=query("place", ob);

                message("vision", WHT + me->name() + WHT "小聲的對" + who->name() +
                        WHT "吩咐着什麼，" + who->name() +
                        WHT "一邊聽，一邊不住的點頭。\n" NOR,
                        environment(who), ({ who }));

                if (me->is_good())
                {
                        set("shen", -20000, ob);
                        if( query("family/family_name", me) == "少林派" )
                                tell_object(who, CYN + me->name() + CYN "對你道：雖"
                                                 "然我們出家人以慈悲為懷，但是對於大"
                                                 "兇大惡之徒也不能放過。\n最近" NOR +
                                                 HIR + ob->name() + "(" + query("id", ob) +
                                                 ")" + NOR + CYN "在" + place + "作惡多端，"
                                                 "你去把他除了，提頭來見。\n" NOR);
                        else
                                tell_object(who, CYN + me->name() + CYN"對你道：" NOR
                                                 + HIR + ob->name() + "(" + query("id", ob) +
                                                 ")" + NOR + CYN "這個"
                                                 "敗類打家劫舍，無惡不作，聽説他最近"
                                                 "在" + place + "，你去除掉他，提頭來"
                                                 "見我！\n" NOR);
                } else
                if (me->is_bad())
                {
                        set("shen", 20000, ob);
                        tell_object(who, CYN + me->name() + CYN "對你道：" NOR + HIR
                                         + ob->name() + "(" + query("id", ob) + ")" +
                                         NOR + CYN "這個所謂大俠屢次"
                                         "和我派作對，聽説他最近在" + place + "，你"
                                         "去宰了他，提頭來見！\n" NOR);
                } else
                {
                        set("shen_type", 0, ob);
                        set("shen", 0, ob);
                        tell_object(who, CYN + me->name() + CYN "對你説道：我早就看"
                                         NOR + HIR + ob->name() + "(" + query("id", ob) +
                                         ")" + NOR + CYN "不順眼"
                                         "，聽説他最近在" + place + "，你去做了他，"
                                         "帶他的人頭來交差！\n" NOR);
                }
                set("quest/type", "kill", who);
                switch (level)
                {
                case 0:
                        message_vision(CYN "$N" CYN "頓了頓，又對$n" CYN "道：這個"
                                       "事情容易辦得很，你要是還辦不成那可不象話。"
                                       "\n" NOR, me, who);
                        break;
                case 1:
                        break;
                case 2:
                        message_vision(CYN "$N" CYN "看了看$n" CYN "又道：這個事情"
                                       "很是有些難辦，你要是不行我就另找人吧。\n"
                                       NOR, me, who);
                        break;
                case 3:
                        message_vision(CYN "$N" CYN "歎了口氣，鄭重的對$n" CYN "道"
                                       "：這次任務兇險得緊，你不要勉強自己，不行就"
                                       "算了。\n" NOR, me, who);
                        break;
                }

                if (level > 0 && random(10) == 1)
                {
                        string flee_msg;

                        // 隨機重新放置NPC的位置
                        message_sort(CYN "$N" CYN "話音剛落，突然一人"
                                     "急急忙忙的趕了過來，喊道：“不"
                                     "好了，不好了，" HIR + ob->name() +
                                     NOR CYN "在" + place +
                                     "失蹤了！現在不知道去了哪裏！”"
                                     "$N" CYN "呆了半晌，這才對$n" CYN
                                     "道：“這事麻煩了，看來只有靠你自"
                                     "己努力了！”\n" NOR, me, who);
                        switch (random(3))
                        {
                        case 0:
                                flee_msg = "聽説$N聽到了江湖上追殺他的風"
                                           "聲，已經躲到PLACE去了。";
                                break;
                        case 1:
                                flee_msg = "有人説$N就在咱們這地界呢，"
                                           "但是也有人説他在PLACE，不知道是真是假。";
                                break;
                        default:
                                flee_msg = "不知道...不知道...哦？好像"
                                           "聽人説過是在PLACE。";
                                break;
                        }
                        ob->random_place(flee_msg);
                }
        }

        set("quest/family", fam, who);
        set("quest/master_name", me->name(), who);
        set("quest/master_id",query("id",  me), who);
        set("quest/name", ob->name(), who);
        set("quest/id",query("id",  ob), who);
        set("quest/level", level, who);
        set("quest/place", place, who);
        t = time();
        set("quest/time", t, who);
        t = time() / ONE_DAY;
        if( query("place", ob) == "西域" )
                t += 8;
        else
                t += 4;
        t = t * ONE_DAY - 1;
        set("quest/limit", t, who);
        message("vision", WHT + me->name() + WHT "在你耳邊悄聲説道：你務必要在"
                          NOR + HIY + CHINESE_D->chinese_monthday(t) + NOR + WHT
                         "之前完成！\n" NOR, who);
        who->start_busy(1);
        return 1;
}

public int ask_defend(object me, object who)
{
        function f;
        int r;

        f=query_temp("override/ask_defend", me);
        if (functionp(f))
                r = (*f)(me, who);
        else
                r = 0;
        return r;
}

public int ask_finish(object me, object who)
{
        function f;
        int r;

        f=query_temp("override/ask_finish", me);
        if (functionp(f))
                r = (*f)(me, who);
        else
                r = 0;
        return r;
}

int accept_object(object me, object who, object ob)
{
        mapping q;              // WHO的任務
        string msg;             // 掌門説的消息
        object dob;             // 打暈敵人的人
        int bonus;              // 獎勵(正整數，1是正常)
        int t;                  // 用來計算時間的變量
        int exp;                // 獲得的經驗
        int pot;                // 獲得的潛能
        int mar;                // 獲得的實戰體會
        int weiwang;            // 獲得的威望
        int score;              // 獲得的江湖閲歷
        int gongxian;           // 獲得的門派貢獻
        int lvl;                // 人物的等級
        int quest_level;        // QUEST的等級
        int quest_count;        // 連續QUEST的數目
        int total_count;        // ......
        int timeover;           // 標誌：超時了？
        int added;              // 做任務的時候額外出現的敵人或敵人逃走
        mixed special = 0;      // 是否有特殊獎勵

        if( query("family/family_name", me) != query("family/family_name", who) )
                return 0;

        q=query("quest", who);

        if( query("money_id", ob) )
        {
               if( !mapp(q) || q["master_id"] != query("id", me) )
               {
                       tell_object(who,me->name() + "奇怪的看着你説：我沒給你什麼任務啊？\n");
                       return 0;
               }

               if (ob->value() < 1000000)
               {
                       tell_object(who,me->name() + "不屑一顧的説：這麼一點點錢，能用來幹什麼？你自己留着買雞腿用吧！\n");
                       tell_object(who,me->name() + "頓了一下又説：如果你給我100兩黃金，或許我可以考慮消除了你的任務。\n");
                       return 0;
               }

               delete("quest", who);
               tell_object(who,me->name() + "微微笑了笑，點頭道：那你這個任務不做就算了吧。\n");
               destruct(ob);
               return 1;
        }

        if (ob->is_letter())
        {
                if( query("send_from", ob) != query("id", me) )
                {
                        message_vision(CYN "$N" CYN "道：你要幹什麼？\n" NOR, me);
                        return -1;
                }

                if (! q || q["type"] != "letter" || query("send_to", ob) != q["id"])
                {
                        message_vision(CYN "$N" CYN "深深的歎了一口氣，沒説什麼？\n" NOR, me);
                        destruct(ob);
                        return 1;
                }

                message_vision(CYN "$N" CYN "瞪着$n" CYN "道：幹什麼？交給你"
                               "的活你不打算幹了？\n" NOR, me, who);
                return -1;
        }

        if (ob->is_receipt())
        {
                if( query("reply_to", ob) != query("id", me) )
                {
                        message_vision("$N皺眉道：“給我這玩藝幹什麼？”\n", me);
                        return 0;
                }

                if( !q || q["type"] != "letter" || q["id"] != query("reply_by", ob) )
                {
                        message_vision("$N點點頭道：“多謝了。”\n", me);
                        destruct(ob);
                        return 1;
                }

                message_vision(CYN "$N" CYN "接過" + ob->name() + NOR + CYN"，仔細看了"
                              "看，滿意的説：很好。\n" NOR, me, who);

                msg = "";
                t = time();
                if (t > q["limit"])
                {
                        msg += CYN + me->name() + CYN "歎了口氣，又道：可惜，不是讓你" +
                               CHINESE_D->chinese_monthday(t) + "前做完嗎？算"
                               "了，將功補過，你先退下吧。\n" NOR;
                        timeover = 1;
                } else
                {
                        if (t - q["time"] < ONE_DAY)
                        {
                                msg += CYN + me->name() + CYN "點點頭道：你很不錯，這麼"
                                       "快就完成了，好好幹！\n" NOR;
                        } else
                                msg += CYN + me->name() + CYN "點點頭道：這次不錯，辛苦"
                                       "了。\n" NOR;
                        timeover = 0;
                }
                bonus=(query("receive_from", ob) == query("id", who));
                exp = 15 + random(10);
                pot = 5 + random(8);
                mar = 1;
                score = 6 + random(5);
                weiwang = 1;
                gongxian = 1;
                destruct(ob);
        } else
        {
                if (! mapp(q) || ! ob->is_corpse() && ! ob->is_head())
                        return 0;

                if (! stringp(query("owner_id", ob)))
                {
                        message_vision(CYN "$N" CYN "捂着鼻子看了看" + ob->name()
                                       + NOR + CYN "，道：什麼臭烘烘的？快給我"
                                       "拿走。\n" NOR, me);
                        return 0;
                }

                if( query("owner_id", ob) != q["id"] )
                        return 0;

                msg = CYN + me->name() + CYN "接過" + ob->name() + NOR + CYN "，呵呵大笑"
                      "，對你道：";

                if (me->is_good())
                        msg += CYN "又除了一害，很好！";
                else
                if (me->is_bad())
                        msg += CYN "好極了！什麼大俠，不堪一擊！";
                else
                        msg += CYN "幹得好，漂亮！";

                msg += "\n" NOR;
                t = time();
                if( query_temp("quest/escape_times", who) )
                {
                        msg += CYN + me->name() + CYN "讚許道：這次沒想到敵人這麼強悍，實"
                               "在未曾料到，辛苦，辛苦！\n" NOR;
                        timeover = 0;
                } else
                if (t > q["limit"])
                {
                        msg += CYN + me->name() + CYN "搖搖頭，又道：可惜，不是讓你" +
                               CHINESE_D->chinese_monthday(t) + "前做完嗎？算"
                               "了，將功補過，你先退下吧。\n" NOR;
                        timeover = 1;
                } else
                {
                        if (t - q["time"] < ONE_DAY)
                        {
                                msg += CYN + me->name() + CYN "點點頭道：幹得不錯，這麼"
                                       "快就完成了，好好幹！\n" NOR ;
                        } else
                                msg += CYN + me->name() + CYN "點點頭道：這次不錯，辛苦"
                                       "了。\n" NOR;
                        timeover = 0;
                }

                // bonus為1表示正常獎勵，為2表示扣除一半。
                bonus=(query("killed_by", ob) == query("id", who)) /*&&
                        (query("defeated_by", ob) == who ||
                         !query("defeated_by", ob) &&
                           query("defeated_by_who", ob) == who->name(1))*/;

                if( query("assist", ob) == who )
                {
                        dob=query("defeated_by", ob);
                        msg += CYN + me->name() + CYN "欣慰的對你道：這次你能夠"
                               "得到" + (dob ? dob->name(1) : "同門師兄弟") +
                               NOR + CYN "的幫忙，也屬不易！以後彼此要多加照"
                               "應！\n" NOR;
                        bonus = 2;
                } else
                if (bonus)
                        bonus = 1;

                destruct(ob);
                lvl = NPC_D->check_level(who);
                exp = 10 + random(5) + lvl;
                pot = 5 + random(3) + lvl;
                mar = 1 + random(2);
                weiwang = 2 + random(3) + lvl / 2;
                score = 2 + random(3) + lvl / 2;
                gongxian = 2;
                quest_count=query("quest_count", who)+1;

                // add temped for keep compactible with old version
                if( query_temp("quest/total_count", who) )
                {
                        quest_count=query_temp("quest/total_count", who)+1;
                        delete_temp("quest/total_count", who);
                }

                // 根據任務完成的次數修正獎勵
                if (quest_count >= 1000)
                {
                        exp += 80 + random(50);
                        pot += 45 + random(40);
                        mar = 50 + random(20);
                        weiwang += 8 + random(20);
                        score += 4 + random(15);
                        gongxian += 4 + random(15);
                } else
                if (quest_count >= 500)
                {
                        // 連續完成了超過500次的任務
                        exp += 80 + random(quest_count / 20 + 1);
                        pot += 45 + random(quest_count / 25 + 1);
                        mar = 50 + random(20);
                        weiwang += 8 + random(20);
                        score += 4 + random(15);
                        gongxian += 4 + random(15);
                } else
                if (quest_count >= 200)
                {
                        // 連續完成了超過200次的任務
                        exp += 70 + random(quest_count / 20 + 1);
                        pot += 40 + random(quest_count / 25 + 1);
                        mar = 20 + random(10);
                        weiwang += 5 + random(15);
                        score += 3 + random(10);
                } else
                if (quest_count >= 100)
                {
                        // 連續完成了超過100次的任務
                        exp += 50 + random(quest_count / 20 + 1);
                        pot += 30 + random(quest_count / 25 + 1);
                        weiwang += 3 + random(10);
                        score += 2 + random(10);
                } else
                if (quest_count >= 10)
                {
                        // 連續完成了超過10次的任務
                        exp += 45 + random(quest_count / 20 + 1);
                        pot += 25 + random(quest_count / 25 + 1);
                        weiwang += 1 + random(5);
                        score += 1 + random(5);
                }

                switch (quest_level = q["level"])
                {
                case 0:
                        exp = exp / 2 + 1;
                        pot = pot / 2 + 1;
                        gongxian = gongxian / 2 + 1;
                        weiwang = weiwang / 3 + 1;
                        score = score / 4 + 1;
                        msg += CYN + me->name() + CYN "看着你接着説道：還行吧，下"
                               "次我給你個難點的任務。\n" NOR;
                        break;
                case 1:
                        msg += CYN + me->name() + CYN "對你又道：不錯，看來我可以"
                               "託付些重任給你了。\n" NOR;
                        break;
                case 2:
                        exp += exp / 4;
                        pot += pot / 4;
                        mar += mar / 4;
                        weiwang += weiwang / 4;
                        score += score / 4;
                        msg += CYN + me->name() + CYN "對你笑道：真是不錯，不愧是"
                               "我們"+query("family/family_name", who)+"的"
                               "矯矯者。\n" NOR;
                        break;
                case 3:
                        exp += exp / 2;
                        pot += pot / 2;
                        mar += mar / 2;
                        gongxian += gongxian / 2;
                        weiwang += weiwang / 2;
                        score += score / 2;
                        msg += CYN + me->name() + CYN "讚許道：非常不錯，這次可給我們" +
                               query("family/family_name", who)+"爭臉了。\n"
                               NOR;
                        break;
                }
                total_count = quest_count % 1000;
                if (total_count == 100)
                {
                        msg += CYN + me->name() + CYN "哈哈大笑兩聲道：“真有你的，連着" + chinese_number(quest_count) +
                               "次任務都完成的漂漂亮亮，很好，很好。”\n" NOR;
                        special = 1;
                } else
                if (total_count == 200)
                {

                        msg += CYN + me->name() + CYN "大喜道：“不錯不錯，真實不錯，連着" + chinese_number(quest_count) +
                               "次任務乾得很好。”\n NOR";
                        special = "/clone/gift/puti-zi";
                } else
                if (total_count == 300)
                {
                        msg += CYN + me->name() + CYN "歎道：“真是長江後浪推前浪，想不到你接連着" + chinese_number(quest_count) +
                               "次任務都無一疏漏，不易，不易！”\n" NOR;
                        special = "/clone/gift/tianxiang";
                } else
                if (total_count == 500)
                {
                        msg += CYN + me->name() + CYN "深深歎了口氣，道：“想不到你連着" + chinese_number(quest_count) +
                               "次任務無一失手，看來我們"+query("family/family_name", me)+
                               "真是後繼有人啊！”\n";
                        special = "/clone/gift/jiuzhuan";
                } else
                if (total_count == 0)
                {
                        msg += CYN + me->name() + CYN "深深歎了口氣，道：“想不到你連着" + chinese_number(quest_count) +
                               "次任務無一失手，看來我們"+query("family/family_name", me)+
                               "將有宗師出世拉！”\n" NOR;
                        special = "/clone/gift/xuanhuang";
#ifdef DB_SAVE
                        if (MEMBER_D->is_valid_member(query("id", who)))
                        {
                                if( query("special_skill/sophistry", who) )
                                {
                                       if (quest_count >= 5000)
                                                quest_count = 0;
                                } else
                                {
                                       if (quest_count >= 3000)
                                                quest_count = 0;
                                }
                        }
                        else
                        {
#endif
                                if (quest_count >= 1000)
                                        quest_count = 0;
#ifdef DB_SAVE
                        }
#endif
                } else
                if ((total_count % 10) == 0)
                {
                        msg += CYN + me->name() + CYN "喜道：“真是不賴，居然連着" + chinese_number(quest_count) +
                               "次都沒有失手，乾的好！”\n" NOR ;
                }

                quest_level = q["level"];
                quest_level++;
                if (quest_level > MAX_QUEST_LEVEL)
                        quest_level = 1;

                set("quest_count", quest_count, who);
                addn("all_quest", 1, who);
                set_temp("quest/next_level", quest_level, who);
        }

        if( (added=query_temp("quest/help_count", who))>0 )
        {
                msg += HIY + me->name() + HIY "又道：這次敵人伏下幫手，而你能隨機應變，"
                       "完成任務，可喜，可賀！\n" NOR;
                delete_temp("quest/help_count", who);
        }
        added+=query_temp("quest/escape_times", who)*2;
        delete_temp("quest/escape_times", who);
        // 根據NPC的幫手和逃走的次數調整經驗
        if (added)
        {
                exp += exp * added / 2;
                pot += pot * added / 2;
        }

        // message_vision(msg, me, who);
        tell_object(who, msg);

        delete("quest", who);
        if (! bonus) return 1;

        exp /= bonus;
        pot /= bonus;
        mar /= bonus;
        weiwang /= bonus;
        score /= bonus;
        gongxian /= bonus;

        // bouns
        if (timeover)
        {
                exp /= 2;
                pot /= 3;
                mar /= 2;
                weiwang /= 4;
                score /= 4;
                gongxian /= 2;
        } else
        {
                // 百分之一的機率直接贈送物品獎勵
                if ((quest_count >= 100 && random(2000) == 1) || special)
                        special_bonus(me, who, special);
                else
                if (random(10000) == 1)
                        skill_bonus(me, who);
        }

       if( query("quest_tuteng/start", who) )
        {
                int n_tt;
                object ob_tt;

                if (random(3000) == 1)
                {
                        n_tt = 1 + random(10);
                        if (n_tt == 6 && random(10) > 1) n_tt = 4;
                        ob_tt = new("/clone/tuteng/diwang-suipian" + sprintf("%d", n_tt));
                        if (ob_tt)
                        {
                                write(HIG "你獲得了一張帝王符圖碎片。\n" NOR);
                                ob_tt->move(who, 1);
                        }
                }
        }

	// 擁有真龍天神則獎勵提高10%
	if( query("special_skill/tianshen", me) )
	{
	         exp = exp + exp / 10;
		 pot = pot + pot / 10;
		 mar = mar + mar / 10;
		 weiwang = weiwang + weiwang / 10;
		 gongxian = gongxian + gongxian / 10;		
	}

        GIFT_D->bonus(who, ([ "exp" : exp * 3, "pot" : pot * 2, "mar" : mar * 2,
                              "weiwang" : weiwang, "score" : score, "gongxian" : gongxian*2 ]), 1);

        // 隨機停止發送任務，必須等完成一定數量的freequest才能繼續。
        if (random(60) == 1 && quest_count >= 50)
                addn("quest/freequest", 1+random(3), who);

        return 1;
}

// 遠程獎勵
int remote_bonus(object me)
{
        mapping q;              // WHO的任務
        string msg;             // 掌門説的消息
        object dob;             // 打暈敵人的人
        int bonus;              // 獎勵(正整數，1是正常)
        int t;                  // 用來計算時間的變量
        int exp;                // 獲得的經驗
        int pot;                // 獲得的潛能
        int mar;                // 獲得的實戰體會
        int weiwang;            // 獲得的威望
        int score;              // 獲得的江湖閲歷
        int lvl;                // 人物的等級
        int quest_level;        // QUEST的等級
        int quest_count;        // 連續QUEST的數目
        int timeover;           // 標誌：超時了？
        int added;              // 做任務的時候額外出現的敵人或敵人逃走

        if( !mapp(q=query("quest", me)) )
                return 0;

        msg = "你翻開信箋反面，發現師傅另有話説：\n\n又及：為師"
              "得知";
        if (me->is_good())
                msg += "你又除了" HIR + q["name"] + NOR "這一害，很好。";
        else
        if (me->is_bad())
                msg += "你已除掉" HIR + q["name"] + NOR "那不堪一擊的所謂"
                       "大俠。";
        else
                msg += "你已完成除掉" HIR + q["name"] + NOR "的任務，不錯"
                       "。";
        t = time();
        if( query_temp("quest/escape_times", me) )
        {
                msg += "且不料此次敵人甚為強悍，屢次逃竄，追擊可"
                       "謂辛苦，";
                timeover = 0;
        } else
        if (t > q["limit"])
        {
                msg += "但可惜，為師是讓你於" +
                       CHINESE_D->chinese_monthday(t) + "前完成，"
                       "將功補過，此次就記下不算。";
                timeover = 1;
        } else
        {
                if (t - q["time"] < ONE_DAY)
                {
                        msg += "你完成的速度如此之快，實在出乎我"
                               "的預料。";
                } else
                        msg += "你這次事情辦的不錯，辛苦了。";

                timeover = 0;
        }


        // bonus 為 1 表示正常獎勵，為 2 表示扣除一半。
        bonus = 1;

        lvl = NPC_D->check_level(me);
        exp = 10 + random(5) + lvl;
        pot = 5 + random(3) + lvl;
        weiwang = 2 + random(3) + lvl / 2;
        score = 2 + random(3) + lvl / 2;
        quest_count=query("quest_count", me)+1;

        // add temped for keep compactible with old version
        if( query_temp("quest/total_count", me) )
        {
                quest_count=query_temp("quest/total_count", me)+1;
                delete_temp("quest/total_count", me);
        }

        // 根據任務完成的次數修正獎勵
        if (quest_count >= 500)
        {
                // 連續完成了超過500次的任務
                exp += 80 + random(quest_count / 20 + 1);
                pot += 45 + random(quest_count / 25 + 1);
                mar = 50 + random(20);
                weiwang += 8 + random(20);
                score += 4 + random(15);
        } else
        if (quest_count >= 200)
        {
                // 連續完成了超過200次的任務
                exp += 70 + random(quest_count / 20 + 1);
                pot += 40 + random(quest_count / 25 + 1);
                mar = 20 + random(10);
                weiwang += 5 + random(15);
                score += 3 + random(10);
        } else
        if (quest_count >= 100)
        {
                // 連續完成了超過100次的任務
                exp += 50 + random(quest_count / 20 + 1);
                pot += 30 + random(quest_count / 25 + 1);
                weiwang += 3 + random(10);
                score += 2 + random(10);
        } else
        if (quest_count >= 10)
        {
                // 連續完成了超過10次的任務
                exp += 45 + random(quest_count / 20 + 1);
                pot += 25 + random(quest_count / 25 + 1);
                weiwang += 1 + random(5);
                score += 1 + random(5);
        }

        switch (quest_level = q["level"])
        {
        case 0:
                exp = exp / 2 + 1;
                pot = pot / 2 + 1;
                weiwang = weiwang / 3 + 1;
                score = score / 4 + 1;
                msg += "下次再給你一個較難的任務吧。";
                break;
        case 1:
                msg += "不錯，看來我可以託付些重任給你了。";
                break;
        case 2:
                exp += exp / 4;
                pot += pot / 4;
                weiwang += weiwang / 4;
                score += score / 4;
                msg += "真是不錯，不愧是我們" +
                       query("family/family_name", me)+
                       "的矯矯者。";
                break;
        case 3:
                exp += exp / 2;
                pot += pot / 2;
                weiwang += weiwang / 2;
                score += score / 2;
                msg += "非常不錯，這次可給我們" +
                       query("family/family_name", me)+
                       "爭臉了。";
                break;
        }

        if (quest_count == 100)
        {
                msg += "而且連着上百次任務都完成的漂漂亮亮，"
                       "很好。";
        } else
        if (quest_count == 200)
        {
                msg += "而且竟一連兩百次任務都乾得很好。";
        } else
        if (quest_count == 500)
        {
                msg += "真是長江後浪推前浪，不想你接連五百"
                       "次任務都無一疏漏，不易，不易！";
        } else
        if (quest_count >= 1000)
        {
                msg += "想不到你連着上千次任務無一失手，看"
                       "來我們"+query("family/family_name", me)+
                       "後繼有人矣。";

#ifdef DB_SAVE
                if (MEMBER_D->is_valid_member(query("id", me)))
                {
                        if( query("special_skill/sophistry", me) )
                        {
                                if (quest_count >= 20000)
                                        quest_count = 0;
                        } else
                        {
                                if (quest_count >= 10000)
                                        quest_count = 0;
                        }
                }
                else
                {
#endif
                        if (quest_count >= 5000)
                                quest_count = 0;
#ifdef DB_SAVE
                }
#endif
        } else
        if ((quest_count % 10) == 0)
        {
                msg += "嗯，況且居然連着" +
                       chinese_number(quest_count) +
                       "次都沒有失手。";
        }

        quest_level = q["level"];
        quest_level++;
        if (quest_level > MAX_QUEST_LEVEL)
                quest_level = 1;

        set("quest_count", quest_count, me);
        addn("all_quest", 1, me);
        set_temp("quest/next_level", quest_level, me);

        if( (added=query_temp("quest/help_count", me))>0 )
        {
                msg += HIY "另及：這次敵人伏下幫手，而你能隨"
                       "機應變，完成任務，可喜，可賀。\n" NOR;
                delete_temp("quest/help_count", me);
        }
        added+=query_temp("quest/escape_times", me)*2;
        delete_temp("quest/escape_times", me);
        // 根據 NPC 的幫手和逃走的次數調整經驗
        if (added)
        {
                exp += exp * added / 2;
                pot += pot * added / 2;
        }
        msg = sort_msg(msg);
        msg += "\n\n";
        tell_object(me, msg);
        delete("quest", me);
        if (! bonus) return 1;

        exp /= bonus;
        pot /= bonus;
        mar /= bonus;
        weiwang /= bonus;
        score /= bonus;
        // bonus
        if (timeover)
        {
                exp /= 2;
                pot /= 3;
                mar /= 2;
                weiwang /= 4;
                score /= 4;
        }

        GIFT_D->bonus(me, ([ "exp" : exp, "pot" : pot, "mar" : mar,
                      "weiwang" : weiwang, "score" : score ]), 1);
        return 1;
}

int cancel_quest(object me, object who)
{
        mapping dbase;
        mapping q;
        object ob;
        string msg;
        int n;
        int c;

        dbase = who->query_entire_dbase();
        if (! mapp(q = dbase["quest"]) ||
                q["master_id"] != query("id", me) )
                return notify_fail("我沒給你什麼任務啊？\n");

        switch (q["type"])
        {
        case "kill":
                if (q["notice"] == "die")
                {
                        message_vision(CYN "$N" CYN "點點頭，對$n" CYN "道：算了，聽説這人"
                                       "已經被殺了，你不用再辛苦了。\n" NOR, me, who);
                } else
                {
                        message_vision(CYN "$N" CYN "擺擺手，對$n" CYN "道：你幹不了就算了"
                                       "，讓別人做吧！\n" NOR, me, who);

                        if( !query("special_skill/sophistry", who) )
                                delete("quest_count", who);
                }

                delete_temp("quest/next_level", who);
                if( query("special_skill/sophistry", who) )
                        break;

                n = (40 + random(40) + NPC_D->check_level(who) * 5);
                c = (10 + random(10) + NPC_D->check_level(who));
                // add temped for keep compactible with old version
                switch (q["level"])
                {
                case 0:
                        n *= 2;
                        break;
                case 1:
                        break;
                case 2:
                        n = 0;
                        break;
                case 3:
                        n = 0;
                        break;
                }
                if (! n) break;

                // adjust weiwang
                dbase["weiwang"] -= n;
                if (dbase["weiwang"] < 0)
                        dbase["weiwang"] = 0;
                msg = HIR "你的江湖威望受到了損失";

                // adjust gongxian
                addn("family/gongji", -c, who);
                if( query("family/gongji", who)<0 )
                        set("family/gongji", 0, who);
                msg += HIR "，師門對你的信任降低了";

                // adjust experience
                if (dbase["experience"] > dbase["learned_experience"])
                {
                        dbase["experience"] += (dbase["learned_experience"] - dbase["experience"]) * 2 / 3;
                        msg += "，由於疲於奔命，你的實戰體會難以及時消化吸收";
                }

                // notice place
                message("vision", msg + "。\n" NOR, who);
                break;

        case "letter":
                message_vision(CYN "$N" CYN "歎口氣，看了看$n" CYN "道：連這點小事都幹不了？算了吧。\n" NOR,
                               me, who);

                addn("score", -(15+random(10)), who);
                if( query("score", who)<0 )
                        set("score", 0, who);
                message("vision", HIR "你的江湖閲歷受到了損失。\n" NOR, who);
                break;
        }
        who->start_busy(2);

        ob = find_living(q["id"]);
        map_delete(dbase, "quest");
        if( query_temp("quest/help_count", who) )
                delete_temp("quest/help_count", who);
        if( !ob || query_temp("quester", ob) != query("id", who) )
                return 1;

        if (environment(ob))
                message_vision(HIC "$N" HIC "看了看四周，急急忙忙的走掉了。\n" NOR, ob);

        destruct(ob);
        return 1;
}

// 傳書分配新任務
void remote_assign_quest(object who, mapping new_quest)
{
        call_out("assign_quest_by_letter", 1,
                 who,query("quest/id", who),new_quest);
}

protected void assign_quest_by_letter(object who, string killed_id, mapping new_quest)
{
        mapping q;
        string  msg;
        string  refuse, accept;
        object  letter;             // 師傅手諭

        if (! objectp(who) || ! living(who))
                return;

        if( !mapp(q=query("quest", who)) )
                return;

        if (! q["finished"])
                return;

        if (q["id"] != killed_id)
                // 任務已經變化了
                return;

        // 師傅發下新的任務，詢問是否接受
        switch (random(7))
        {
        case 0:
                // 出現新任務提示
                msg = "只聽撲倏撲倏幾聲，一隻白鴿飛了過來，落在"
                      "$N肩頭，$N只見白鴿足上紅繩繫着些什麼，連"
                      "忙解下一看，原來竟是師傅手諭。\n";
                // 拒絕信息
                refuse = "$N搖了搖頭，將信函隨手一撕。\n";
                // 接受信息
                accept = "$N點了點頭，將在信函後面寫了幾個字，綁"
                         "在白鴿足上放走。\n";
                break;
        case 1:
                msg = "$N轉身一看，竟見到一隻灰點信鴿飛至身旁，"
                      "$N趕緊收住身形，取下信鴿腳上縛着的捲起信"
                      "箋，展看便讀。\n";
                refuse = "$N搖了搖頭，將信函隨手一撕。\n";
                accept = "$N點了點頭，將在信函後面寫了幾個字，綁"
                         "在灰鴿足上放走。\n";
                break;
        case 2:
                msg = "$N一回頭，只見一位同門裝束的弟子滿頭大汗"
                      "地跑了過來，邊喘氣邊道：“可叫我好找，這"
                      "是師傅派我送給你的手諭。”\n";
                refuse = "$N皺了皺眉，道：“我還是不去了，你讓師"
                         "傅找別的同門去吧。”那位弟子歎了口氣，"
                         "轉身離開。\n";
                accept = "$N喜道：“請你稟報師傅，我一定準時完成"
                         "。”那位弟子揮了揮手，風塵僕僕的離開了"
                         "。\n";
                break;
        case 3:
                msg = "突然一位" + query("family/family_name", who) +
                      "弟子急急忙忙地跑了上來，拍拍$N的肩膀，把"
                      "一封信遞上。\n";
                refuse = "$N皺了皺眉，道：“我還是不去了，你讓師"
                         "傅找別的同門去吧。”那位弟子歎了口氣，"
                         "轉身離開。\n";
                accept = "$N喜道：“請你稟報師傅，我一定準時完成"
                         "。”那位弟子揮了揮手，風塵僕僕的離開了"
                         "。\n";
                break;
        case 4:
                msg = "只見$N剛想離開，一位同門裝束的弟子追了上"
                      "來，抹了抹頭上的汗珠，説道：“原來你在這"
                      "裏啊，快看看師傅派我送來的信。”\n";
                refuse = "$N皺了皺眉，道：“我還是不去了，你讓師"
                         "傅找別的同門去吧。”那位弟子歎了口氣，"
                         "轉身離開。\n";
                accept = "$N喜道：“請你稟報師傅，我一定準時完成"
                         "。”那位弟子揮了揮手，風塵僕僕的離開了"
                         "。\n";
                break;
        case 5:
                msg = "$N正欲離開，忽然發現不遠處的地上一塊石頭"
                      "上刻着些什麼，走進一看，正是本門專用的記"
                      "認，原來石頭下壓着一封書信。\n";
                refuse = "$N搖了搖頭，將信函隨手一撕。\n";
                accept = "$N點了點頭，將在信函後面寫了幾個字，重"
                         "新壓在石頭下面。\n";
                break;
        default:
                msg = "忽聽“嗖”的一聲，一件暗器從$N背後飛來，"
                      "$N不敢疏忽，趕緊接下一看，竟是同門送來的"
                      "一封師傅手諭。\n";
                refuse = "$N搖了搖頭，將信函隨手一撕。\n";
                accept = "$N點了點頭，在信函後面寫了幾個字，一甩"
                         "手將信函向背後平平送出，那信不知給誰接"
                         "住，竟即刻便消失了。\n";
                break;
        }

        message_sort(HIY + "\n" + msg + NOR, who);

        letter = new("/clone/questob/letter");

        // 這封信是給誰的？
        set("killed_id", killed_id, letter);
        set("quester",query("id",  who), letter);
        set("quest", new_quest, letter);
        set("msg/accept", accept, letter);
        set("msg/refuse", refuse, letter);

        // 要在什麼時候之前回答？
        set("dest_time", time()+30, letter);
        letter->move(who);

        // 若 30 秒內不輸入 accept 即作拒絕論
        letter->start_auto_cancel(who, 30);
}

// 準備給玩家發送遠程任務
mapping prepare_quest(object me)
{
        mapping q;      // 任務數據
        string place;   // npc 放置的地點
        mapping name;   // npc 的姓名
        int exp;        // 完成任務玩家的經驗值
        int t;          // 時間
        string family;  // 玩家門派
        object master;  // 師傅

        exp=query("combat_exp", me);
        t = time();
        name = NPC_D->get_cn_name();
        family=query("family/family_name", me);

        // 師傅一般是複製出來的，載入非複製的對象也可
        if (! objectp(master = find_object(mlist[family])))
        {
                master = load_object(mlist[family]);
                if (! objectp(master))
                    log_file("log", sprintf("Can not load master \"%s\".\n",
                                            mlist[family]));
                return 0;
        }

        q = ([ ]);
        q["place"] = NPC_D->random_place(exp < 500000  ? ({ "大理一帶", "終南山", "關外", "西域" }) :
                                         exp < 800000 ? ({ "大理一帶", "終南山", "西域" }) : 0);
        q["name"] = name["name"];
        q["id"] = name["id"][0];
        q["full_id"] = name["id"];
        q["level"]=query_temp("quest/next_level", me);
        q["time"] = t;
        q["count"]=query("quest_count", me)+1;
        q["family"] = family;
        q["master_name"] = master->name();
        q["master_id"]=query("id", master);
        q["type"] = "kill";

        t = time() / ONE_DAY;
        if (place == "西域")
                t += 8;
        else
                t += 4;
        t = t * ONE_DAY - 1;
        q["limit"] = t;

        return q;
}

// 正式開始遠程 quest
int start_quest(object me, mapping quest)
{
        object ob;
        int level;
        string place;

        level = quest["level"];
        ob = new(CLASS_D("generate") + "/killed.c");

        // 換上預置的姓名
        ob->set_name(quest["name"], quest["full_id"]);
        // 更換了姓名，需要重新 set_living_name，否則
        // 無法 find_living()
        ob->enable_player();

        // 到預先生成的指定地方去
        NPC_D->place_npc(ob, 0, ({ quest["place"] }));
        NPC_D->set_from_me(ob, me, 100);

        ob->add_temp("apply/attack",ob->query_skill("force")*
                                     (level - 1) / 15);
        ob->add_temp("apply/dodge",ob->query_skill("force")*
                                    (level - 1) / 15);
        ob->add_temp("apply/parry",ob->query_skill("force")*
                                    (level - 1) / 15);
        addn_temp("apply/damage", 5+level*7, ob);
        addn_temp("apply/unarmed_damage", 5+level*7, ob);
        addn_temp("apply/armor", 10+level*15, ob);
        set_temp("quester",query("id",  me), ob);
        NPC_D->random_move(ob);
        NPC_D->random_move(ob);
        NPC_D->random_move(ob);
        place=query("place", ob);

        if (me->is_good())
        {
                ob->set("shen", -query("combat_exp", ob) / 2000);
        } else
        if (me->is_bad())
        {
                set("shen",query("combat_exp",  ob)/2000, ob);
        } else
        {
                set("shen_type", 0, ob);
                set("shen", 0, ob);
        }

        // 1 級以上的任務有 10% 機會重新分佈
        if (level > 0 && random(10) == 1)
        {
                string flee_msg;

                // 隨機重新放置NPC的位置
                message_sort(CYN "$N" CYN  "剛想離開，突然一個"
                             "同門裝束的弟子急急忙忙的趕了過來"
                             "，喊道：“不好了，不好了，" HIR +
                             ob->name() + NOR CYN "在" + place +
                             "失蹤了！現在不知道去了哪裏！”弟"
                             "子歎了口氣，續道：“這事麻煩了，"
                             "看來只有靠你自己努力了。”\n" NOR, me);
                switch (random(3))
                {
                case 0:
                        flee_msg = "聽説$N聽到了江湖上追殺他的風"
                                   "聲，已經躲到PLACE去了。";
                        break;
                case 1:
                        flee_msg = "有人説$N就在咱們這地界呢，"
                                   "但是也有人説他在PLACE，不知道是真是假。";
                        break;
                default:
                        flee_msg = "不知道...不知道...哦？好像"
                                   "聽人説過是在PLACE。";
                        break;
                }
                ob->random_place(flee_msg);
        }

        set("quest", quest, me);
        return 1;
}

/***********************************************************
  系統註冊任務概念

    HELL採用任務對象來管理眾多各式各樣的任務，而任務守護進程
就是他們的管理者。為什麼需要任務對象？這是因為大部分任務都具
有類似的處理過程：收集情報，根據線索完成某些要求，實現最終任
務，獲得獎勵。為了能夠快速的編寫和實現多種任務，共享重複的實
現代碼，系統規定了任務對象的格式，只要遵循任務對象的格式，就
可以快速的生成玩家任務。

    讓我們首先看一下任務的結構：一個任務實際上就是一個自動機，
然後由玩家不斷的觸發這個自動機最後達到一個穩定狀態，一般來説
就是任務成功或是終止。系統可以為任務對象制定一些標準事件，然
後由任務的設計者自己制定一些事件，這就組合成了一個任務的輸入
事件，然後系統為任務維護一個狀態，這樣就構成了一個完整的自動
機。

    看一個簡單的“殺人”任務。

    殺一個人主要需要三個要素：時間、地點、人物。在某一個時間，
某個地點出現一個人物，殺掉它就算完成，可以獲得獎勵。那麼我們
設計的流程預期是這樣的：一個人打聽到了這個任務，就去相應的地
點，殺人，殺掉以後獲得獎勵。

    任務對象的自動機器：

                                      消息收集完全
            <原生態> -> 人物生成態 -----------+
                           /                  |
                 <Timeout>/    <Timeout>      |
                   -------<---------------\   |
                 /                         \  v
            <結束態>   <--------------- 人物出現態
                            殺死該人

<原生態>和<結束態>是系統規定的狀態，<Timeout> 是系統原先保留
的事件。而人物生成態和人物出現態是該任務特有的狀態，另外消息
收集完全和殺死該人則是該任務對象特有的事件。

<原生態>階段系統初始化任務對象，完成一些必要的操作，並將控制
權傳遞給任務對象以進行後續的操作。這時該任務就自動生成一個人
物，制定它的等級，正邪，預期出現的地點，打聽的難度等等。然後
就進入到人物生成態，同時表明自己需要接受超時事件。

此時，玩家如果打聽消息，有可能打聽到這個任務，並經過反覆打聽，
獲得了該人出現的地點信息，則該人物對象認為消息收集完全，就真
正的生成這個人物，等候玩家將它消滅。

如果該人物被消滅，則通知任務對象，人物對象轉移到<結束態>。另
外一個進入結束態的可能是超時了。

進入<結束態>，系統自動清除該任務對象。

任務產生：這可以是遊戲中的機關產生，故事產生，和系統隨機產生
等等。只要調入一個對象，就可以產生任務。

任務消息：除了通常的消息，有一種消息即通過電腦控制的人物產生，
包括店小二和特殊的傳遞消息的人物，這些消息可以反映出當前任務
的一些信息，這些功能已經由系統封裝。任務產生以後，系統調用接
口函數：register_information()來登記和任務相關的消息 -- 為什
麼不在任務產生的同時由任務自己登記？這是因為任務守護進程有可
能析構後重新創建，這樣將遺失所有登記的數據，此時任務守護進程
就會遍歷系統中所有的任務，調用register_information()接口來重
新組織這些消息。

消息數據結構：

---+-- scheme(1) -*
   |
   +-- scheme(2) -*
   |
   +-- scheme(3) --+-- 關鍵字：消息1
                   |
                   +-- 關鍵字：消息2
                   |
                   .........

打聽需要一定的江湖閲歷，當random(江湖閲歷) > 消息的時候， 就
有可能打聽到這個消息。消息可能是一個函數，如果是這樣的話，在
打聽消息的時候系統把打聽的對象和打聽消息的人，關鍵字傳遞給該
函數，取它的返回結果。

QUEST_D提供的消息API：

QUEST_D->add_quest(QUEST_OBJECT);
QUEST_D->set_information(QUEST_OBJECT, key, information);
QUEST_D->query_information(QUEST_OBJECT, key);
QUEST_D->remove_information(QUEST_OBJECT, key);
QUEST_D->remove_all_information(QUEST_OBJECT);

QUEST_OB必須提供的消息接口：

QUEST_OB->register_information();
QUEST_OB->name();
QUEST_OB->can_know_by(object knower);
QUEST_OB->can_rumor_by(object knower);
QUEST_OB->query_introduce(object knower, object who);

***********************************************************/

// 系統增加一個任務
public void add_quest(object qob)
{
        mapping total;

        if (! mapp(total = query("information")))
        {
                // 原先沒有任何任務
                total = ([ qob : 1 ]);
                set("information", total);
        } else
        {
                // 查看這個任務是否已經有定義
                if (undefinedp(total[qob]))
                        // 增加一個任務，因為這時候剛剛將任
                        // 務加入，還沒有任何相關的具體信息，
                        // 所以這個條目對應的就只是一個簡單
                        // 整數標識。
                        total[qob] = 1;
        }
}

// 設置消息
public void set_information(object qob, string key, mixed info)
{
        mixed total;
        mixed all_info;

        if (! stringp(key) || (! stringp(info) && ! functionp(info)))
        {
                log_file("static/quest",
                         sprintf("%s Quest:%O(%s) set illegal info:%s:%O.\n",
                                 log_time(), qob, qob->name(), key, info));
                return;
        }

        if (! mapp(total = query("information")))
                total = ([ ]);

        if (! mapp(all_info = total[qob]))
        {
                // 原先沒有該任務對象的消息信息
                all_info = ([ ]);
                total += ([ qob : all_info ]);
        }

        all_info[key] = info;
        set("information", total);
}

// 查詢消息
public mixed query_information(object qob, string key)
{
        mapping total;
        mapping all_info;

        if (! mapp(total = query("information")))
                return 0;

        if (! mapp(all_info = total[qob]))
                return 0;

        return all_info[key];
}

// 刪除消息
public void remove_information(object qob, string key)
{
        mapping total;
        mapping all_info;

        if (! mapp(total = query("information")))
                return;

        if (! mapp(all_info = total[qob]))
                return;

        map_delete(all_info, key);
        if (! sizeof(all_info))
        {
                // 該任務對象已經沒有消息了
                map_delete(total, qob);
                return;
        }
}

// 刪除某一個對象的所有消息
public void remove_all_information(object qob)
{
        mapping total;

        if (! mapp(total = query("information")))
                return;

        // 在刪除所有消息的同時，任務本身也去掉了 -- 為什麼
        // 這樣做，這是因為如果是一個沒有任何消息的任務（僅
        // 靠任務介紹提供信息）調用這個函數的含義就是清除任
        // 務本身，而一個提供消息的任務清除所有消息也具有相
        // 同的含義。
        map_delete(total, qob);
}

// QUEST系統重新啟動的時候收集所有任務對象的消息
protected void collect_all_quest_information()
{
        mapping total;
        object qob;
        object *obs;

        CHANNEL_D->do_channel(this_object(), "sys",
                              "任務精靈開始收集所有的任務信息。");

        if (! mapp(total = query("information")))
        {
                total = ([ ]);
                set("information", total);
        }

        obs = filter_array(objects(), (: $1->is_quest() :));

        // 掃描所有的QUEST對象，登記信息
        foreach (qob in obs)
        {
                reset_eval_cost();
                total[qob] = 0;
                catch(qob->register_information());
        }

        // 喚醒幾個子任務守護進程
        start_all_quest();
}

public void start_all_quest()
{
        string quest;
        string *qlist;
        string name;
        int pos;

        /*
        if (! VERSION_D->is_version_ok())
                // 正在同步版本？那麼不啟動任務守護進程
                return;
        */

        quest = read_file(CONFIG_DIR "quest");
        if (! stringp(quest))
                // 配置文件中沒有任務
                return;

        qlist = explode(quest, "\n");
        foreach (name in qlist)
        {
                // 防止運行超時
                reset_eval_cost();

                if (strlen(name) < 1 || name[0] == '#')
                        // 空行或者是註釋行
                        continue;

                // 去掉行尾的註釋和空格
                pos = strsrch(name, '#');
                if (pos > 1) name = name[0..pos - 1];
                name = replace_string(name, " ", "");

                // 生成文件名字
                name = QUEST_DIR + name + ".c";
                if (file_size(name) < 0)
                {
                        // 沒有這個任務
                        log_file("static/quest",
                                 sprintf("%s invalid quest: %s\n",
                                         log_time(), name));
                        continue;
                }

                // 啟動這個任務
                catch(call_other(name, "startup"));
        }
}

// 整理所有的任務
protected void heart_beat()
{
        mapping total;
        mixed key;
        int live_time;
        int t;

        // 重新啟動所有的任務進程：如果因為某種故障停止運行，
        // 此時可以將它們重新啟動，如果他們原本沒有出故障，
        // 那麼此時重新啟動會修改它們的心跳時間。
        start_all_quest();

        if (! mapp(total = query("information")))
                return;

        // 計算當前時間
        t = time();

        // 掃描所有的任務，只保留有效的任務
        foreach (key in keys(total))
        {
                reset_eval_cost();
                if (! objectp(key))
                        map_delete(total, key);
                else
                switch (key->query_status())
                {
                case QUEST_CREATE:
                        if( t-query("start_time", key)>QUEST_CREATE_PERIOD )
                        {
                                // 創建任務超過有效時間了，結束之
                                log_file("static/quest", sprintf("%s quest: %s create timeout\n%O",
                                                                 log_time(), base_name(key),
                                                                 key->query_entire_dbase()));
                                catch(key->change_status(QUEST_FINISH));
                                map_delete(total, key);
                        }
                        break;

                case QUEST_FINISH:
                        if( t - query("finish_time", key)>QUEST_FINISH_PERIOD )
                                // 結束任務超過有效時間了
                                key->change_status(QUEST_ERROR);
                        break;

                case QUEST_ERROR:
                        // 任務在運行錯誤狀態中
                        break;

                default:
                        // 任務在通常運行狀態中
                        if( (live_time=query("live_time", key))>0 &&
                            live_time < t - query("start_time", key))
                        {
                                // 生存超過了時間
                                catch(key->change_status(QUEST_FINISH));
                                map_delete(total, key);
                        }
                        break;
                }
        }
}

// 供消息靈通人士調用使用
public string generate_information(object knower, object who, string topic)
{
        mapping total;
        object *obs;
        object *dest;
        string name, title;
        object last_ob;
        mixed answer;

        total = query("information");

        switch (random(30))
        {
        case 0:
                return "阿嚏！有點感冒，不好意思。";
        case 1:
                return "等...等等，你説什麼？沒聽清楚。";
        case 2:
                return "嗯，稍等啊，就好... 好了，你剛才説啥？";
        case 3:
                return "這個... 這個... 哦，好了，啊？你問我呢？";
        case 4:
                return "唉呦！... 不好意思，是你問我麼？";
        case 5:
                return "就好... 就好... 好了，你説啥？";
        case 7:
                return "!@#$%^&*";
        }

        if (topic == "rumor" || topic == "消息")
        {
                // 生成傳聞
                if (! mapp(total) ||
                    ! sizeof(obs = filter_array(keys(total), (: objectp($1) :))))
                {
                        // 目前沒有任何任務
                        switch (random(3))
                        {
                        case 0:
                                return "最近沒啥消息。";
                        case 1:
                                return "好像最近挺太平的。";
                        default:
                                return "不知道...你去問問別人吧。";
                        }
                }

                // 過濾該小二可以散佈的消息
                obs = filter_array(obs, (: objectp($1) && $1->can_rumor_by($(knower)) :));
                if (! sizeof(obs))
                {
                        // 該人士不能散佈信息
                        switch (random(3))
                        {
                        case 0:
                                return "我倒是聽説最近江湖上出了不少事兒。";
                        case 1:
                                return "哎呀呀！你也知道了一些祕密？快給我説説！";
                        default:
                                return "這年頭，是越來越亂了。";
                        }
                }

                // 隨機選擇一個可以散佈的任務消息
                last_ob = obs[random(sizeof(obs))];
                set_temp("last_asked_quest", last_ob, knower);
                if (answer = last_ob->query_prompt(knower, who))
                        return answer;

                switch (random(3))
                {
                case 0:
                        return "你可曾聽過最近有關『" HIY +
                               last_ob->name() + NOR CYN "』的傳聞？";
                case 1:
                        return "最近正在盛傳『" HIY +
                               last_ob->name() + NOR CYN "』這件事情呢！";
                default:
                        return "你沒有聽到大家都在議論『" HIY +
                               last_ob->name() + NOR CYN "』嗎？";
                }
        }

        if (! mapp(total))
                return 0;

        // 獲得該人知道的所有任務信息
        obs = filter_array(keys(total), (: objectp($1) :));
        obs = filter_array(obs, (: $1->can_know_by($(knower)) :));

        // 查看是否問某一個任務的某一個條目
        if (sscanf(topic, "%s.%s", name, title) == 2)
        {
                dest = filter_array(obs, (: $1->name() == $(name) :));
                if (! sizeof(dest))
                        return 0;

                last_ob = dest[0];
        } else
        {
                // 查看是否問某一個任務
                dest = filter_array(obs, (: $1->name() == $(topic) :));
                if (sizeof(dest) > 0)
                {
                        last_ob = dest[0];
                        set_temp("last_asked_quest", last_ob, knower);
                        answer = last_ob->query_introduce(knower, who);
                        if (stringp(answer))
                                return answer;
                        return "你説的是" HIY + knower->name() +
                               HIY "那件事情嗎？你問我算是問對人了。" NOR;
                } else
                // 查看最後一次被詢問的任務消息中是否有該條目
                {
                        last_ob=query_temp("last_asked_quest", knower);
                        if (! objectp(last_ob) || ! mapp(total[last_ob]))
                                return 0;

                        title = topic;
                }
        }

        // 返回有關某個任務的某個條目的消息
        set_temp("last_asked_quest", last_ob, knower);
        answer = total[last_ob];

        if (! mapp(answer))
                return 0;

        // 這個任務登記了具體的信息
        answer = answer[title];
        if (functionp(answer))
                return evaluate(answer, knower, who, topic);

        if (stringp(answer))
                return answer;

        return 0;
}
