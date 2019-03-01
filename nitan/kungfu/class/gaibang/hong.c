// This program is a part of NT MudLIB
// hong.c 洪七公

#include <ansi.h>;
#include "gaibang.h"

inherit NPC;
inherit F_MASTER;
inherit F_QUESTER;
inherit F_COAGENT;
inherit F_NOCLONE;

mixed ask_skill1();
mixed ask_skill2();
mixed ask_skill3();
mixed ask_skill4();
mixed ask_skill5();
mixed ask_skill6();
mixed ask_skill7();
mixed ask_skill8();
mixed ask_skill9();
mixed ask_skill10();
mixed ask_skill11();
mixed ask_skill12();
mixed ask_skill13();

mixed ask_me();

//#define YUZHU    "/clone/lonely/yuzhu"
#define YUZHU    "/clone/lonely/lvyuzhang"

int try_to_learn_ds();
int try_to_learn_db();

void create()
{
        object ob;
        set_name("洪七公", ({"hong qigong", "hong", "qigong"}));
        set("long", @LONG
他就是丐幫第十七任幫主，號稱九指神丐的洪
七公老爺子。只見他須眉皆白，周身上下邋遢
不已，模樣甚是齷齪。可是他目光如電，顯得
正義凜然，不怒而自威。
他一張長方臉，頜下微須，粗手大腳，身上衣
服東一塊西一塊的打滿了補丁，卻洗得幹幹凈
凈。
LONG);

        set("nickname", HIW "北丐" NOR);
        set("gender", "男性");
        set("class", "beggar");
        set("age", 75);
        set("attitude", "peaceful");

        set("str", 35);
        set("int", 24);
        set("con", 30);
        set("dex", 30);

        set("max_qi", 6700);
        set("max_jing", 57000);
        set("neili", 77000);
        set("max_neili", 77000);
        set("jiali", 300);
        set("combat_exp", 6000000);
        set("level", 60);
        set("score", 600000);
        set("shen_type", 1);
        set("book_count", 5);

        set_skill("force", 700);             // 基本內功
        set_skill("array", 700);
        set_skill("dagou-zhen", 700);
        set_skill("huntian-qigong", 700);    // 混天氣功
        set_skill("jiaohua-neigong", 700);
        set_skill("yijin-duangu", 700);      // 易筋鍛骨
        set_skill("unarmed", 750);
        set_skill("cuff", 750);
        set_skill("changquan", 750);
        set_skill("strike", 700);            // 基本掌法
        set_skill("dragon-strike", 700);     // 降龍十八掌
        set_skill("hand", 700);              // 基本手法
        set_skill("shexing-diaoshou", 700);  // 蛇行刁手
        set_skill("dodge", 700);             // 基本躲閃
        set_skill("feiyan-zoubi", 700);      // 飛檐走壁
        set_skill("xiaoyaoyou", 700);        // 逍遙遊掌
        set_skill("parry", 700);             // 基本招架
        set_skill("dagou-bang", 700);        // 打狗棒法
        set_skill("jiaohua-bangfa", 700);
        set_skill("staff", 700);             // 基本杖法
        set_skill("fengmo-zhang", 700);      // 瘋魔杖法
        set_skill("blade", 700);             // 基本刀法
        set_skill("liuhe-dao", 700);         // 六合刀
        set_skill("throwing", 700);          // 基本暗器
        set_skill("pomie-jinzhen", 700);     // 破滅金針
        set_skill("begging", 700);           // 叫化絕活
        set_skill("checking", 700);          // 道聽途說
        set_skill("training", 700);          // 馭獸術
        set_skill("literate", 700);          // 讀書寫字
        set_skill("bixue-danxin", 700);
        set_skill("martial-cognize", 600);   // 武學修養
        /*
        set_skill("kanglong-youhui", 700);   // 1
        set_skill("feilong-zaitian", 700);   // 2
        set_skill("jianlong-zaitian", 700);  // 3
        set_skill("hongjian-yulu", 700);     // 4
        set_skill("qianlong-wuyong", 700);   // 5
        set_skill("lishe-dachuan", 700);     // 6
        set_skill("turu-qilai", 700);        // 7
        set_skill("zhenjing-baili", 700);    // 8
        set_skill("huoyue-zaiyuan", 700);    // 9
        set_skill("shuanglong-qushui", 700); // 10
        set_skill("yuyue-yuyuan", 700);      // 11
        set_skill("shicheng-liulong", 700);  // 12
        set_skill("miyun-buyu", 700);        // 13
        set_skill("sunze-youfu", 700);       // 14
        set_skill("longzhan-yuye", 700);     // 15
        set_skill("lvshuang-bingzhi", 700);  // 16
        set_skill("diyang-chufan", 700);     // 17
        set_skill("shenlong-baiwei", 700);   // 18
        */

        map_skill("force", "huntian-qigong");
        map_skill("strike", "dragon-strike");
        map_skill("cuff", "changquan");
        map_skill("hand",  "shexing-diaoshou");
        map_skill("dodge", "xiaoyaoyou");
        map_skill("parry", "dagou-bang");
        map_skill("staff", "dagou-bang");
        map_skill("blade", "liuhe-dao");
        map_skill("throwing", "pomie-jinzhen");

        prepare_skill("strike", "dragon-strike");

        set("no_teach", ([
                "dragon-strike" : (: try_to_learn_ds :),
                "dagou-bang"    : (: try_to_learn_db :),
        ]));

        set("inquiry", ([
                "青竹令"   : "老叫花可沒功夫管這麼多閒事，你去揚州找小左吧！\n",
                "青竹林"   : "東北西北東西北。\n",
                "丐幫"     : "東北西北東西北。\n",
                "小菜"     : "最想吃的是蓉兒燒的叫化雞，牛肉條，好逑湯，炒白菜，蒸豆腐……唉！\n",
                "好吃的"   : "最想吃的是蓉兒燒的叫化雞，牛肉條，好逑湯，炒白菜，蒸豆腐……唉！\n",
                "黃蓉"     : "這小娃娃燒的叫化雞，牛肉條，好逑湯，炒白菜，蒸豆腐最好吃。\n",
                "蓉兒"     : "這小娃娃燒的叫化雞，牛肉條，好逑湯，炒白菜，蒸豆腐最好吃。\n",
                "玉竹杖"   : (: ask_me :),
                "仙遊訣"   : (: ask_skill1 :),
                "擲金針"   : (: ask_skill2 :),
                "纏字訣"   : (: ask_skill3 :),
                "戳字訣"   : (: ask_skill4 :),
                "封字訣"   : (: ask_skill5 :),
                "絆字訣"   : (: ask_skill6 :),
                "天下無狗" : (: ask_skill7 :),
                "擒龍手"   : (: ask_skill8 :),
                "雷霆一擊" : (: ask_skill9 :),
                "龍翔九天" : (: ask_skill10 :),
                "亢龍有悔" : (: ask_skill11 :),
                "排山倒海" : (: ask_skill12 :),
                "龍嘯九天" : (: ask_skill13:),
        ]));

        set("chat_chance", 1);
        set("chat_msg", ({
                "洪七公摸著肚皮嘆道：“唉，好久沒吃到蓉兒燒的小菜了……”\n",
                "洪七公往地下角落一躺，開始睡覺，邊睡邊喃喃道：“啊，叫化雞……好香！好香！”\n",
                "洪七公說道：“俗話說「吃在江南」，所以老叫化特地跑來揚州看看。”\n",
                "洪七公搖頭嘆道：“如今這幫小叫化怎麼好像都不會燒菜了？”\n",
                "洪七公喃喃道：“我們丐幫的「降龍十八掌」是天下最霸道的掌法。”\n",
        }));

        set("chat_chance_combat", 50);
        set("chat_msg_combat", ({
                (: perform_action, "strike.xiang" :),
                (: perform_action, "strike.hui" :),
                (: perform_action, "strike.lei" :),
                (: perform_action, "dodge.xian" :),
                (: perform_action, "staff.chan" :),
                (: perform_action, "staff.chuo" :),
                (: perform_action, "staff.feng" :),
                (: perform_action, "staff.ban" :),
                (: perform_action, "staff.tian" :),
                (: exert_function, "recover" :),
                (: exert_function, "powerup" :),
        }));

        create_family("丐幫", 17, "幫主");
        set_temp("apply/damage", 100);
        set_temp("apply/unarmed_damage", 100);
        set_temp("apply/armor", 200);

        set("master_ob",5);
        setup();

        if (clonep())
        {
                ob = find_object(YUZHU);
                if (! ob) ob = load_object(YUZHU);
                if (! environment(ob))
                {
                        ob->move(this_object());
                        ob->wield();
                }
        }
        //carry_object(__DIR__"obj/lvyv_bang")->wield();
        carry_object(__DIR__"obj/jiaohuaji");
        carry_object(__DIR__"obj/cloth")->wear();

        set("startroom", "/d/gaibang/gbxiaowu");
        check_clone();
}

void attempt_apprentice(object ob)
{
        string title=query("title", ob);
        int lvl=query("family/beggarlvl", ob);

        if (! permit_recruit(ob))
                return;

        if( query("level", ob)<3 )
        {
                command("hmm");
                command("say 你的經驗這麼差，又能跟我學什麼？");
                return;
        }

        if (ob->query_str() < 40 && ob->query_int() < 40
            && ob->query_con() < 40 && ob->query_dex() < 40)
        {
                command("say 我說你這人體格也不行，腦筋也不靈光，還能和我學什麼？");
                return;
        }

        if ((int)ob->query_skill("force") < 180)
        {
                command("hmm");
                command("say 你的內功火候太差了，先好好練練再來找我。");
                return;
        }

        if( query("max_neili", ob)<2000 )
        {
                command("hmm");
                command("say 就你那點內力哪裡學得了什麼上乘武功？");
                return;
        }
        command("say 念你平時用功努力，今日老叫花就收下你。");
        command("say 以後好好練功，可別給我丟臉。");
        command("recruit "+query("id", ob));

        if( query("class", ob) != "beggar" )
                set("class", "beggar", ob);

        if (lvl > 0)
        {
                set("family/beggarlvl", lvl, ob);
                set("title", title, ob);
        }
}

int recognize_apprentice(object me, string skill)
{
        if( !query("can_learn/hong/dragon-strike", me )
             && !query("can_learn/hong/xiaoyaoyou", me) )
        {
                command("say 你是誰？哪裡來的？要幹啥？");
                return -1;
        }

        if( (query("can_learn/hong/dragon-strike", me )
            && skill != "dragon-strike"
            && skill != "strike")
             || (query("can_learn/hong/xiaoyaoyou", me )
            && skill != "xiaoyaoyou"
            && skill != "strike"))
        {
                command("say 老叫花教你什麼就學什麼，你不學就算了。");
                return -1;
        }

        if (skill == "strike"
            && me->query_skill("strike", 1) > 379)
        {
                command("say 到此為止，你的功力也不差了，剩下的自己去練。");
                return -1;
        }
        return 1;
}

int try_to_learn_db()
{
        object me;

        me = this_player();
        if( query("can_learn/hong/dagou-bang", me) )
                return 0;

        if( query("family/beggarlvl", me)<7 )
        {
                command("say 也不看看你是什麼輩分，居然想學打狗棒法？");
                return -1;
        }

        if( query("shen", me)<80000 )
        {
                command("say 你的俠義正事還做得不夠，這套杖法我暫時還不能傳你。");
                return -1;
        }

        command("sigh");
        command("say 這套打狗棒法乃歷代相傳，本來只有歷代繼任幫主才能研學。");
        command("say 不過現在江湖爭亂，你也算是本幫高手，便是學之無妨。");
        set("can_learn/hong/dagou-bang", 1, me);
        return 0;
}

int try_to_learn_ds()
{
        object me;
        object sob;
        int i;
        int flag;
        string *sub_skills;

        me = this_player();

        if( !query("can_learn/hong/dragon-strike", me) )
                return -1;

        if( query("family/family_name", me) != query("family/family_name") )
        {
                command("say 本來想傳授你降龍十八掌，但可惜你不是我丐幫的。");
                delete("can_learn/hong/dragon-strike", me);
                return -1;
        }

        if( query("family/family_name", me) == query("family/family_name" )
             && query("family/beggarlvl", me)<9 )
        {
                command("say 你要學降龍十八掌？等你升到本幫長老再說吧！");
                return -1;
        }

        if( query("family/family_name", me) != query("family/family_name" )
             && !query("can_learn/hong/dragon-strike", me) )
        {
                command("say 你是哪裡來的？一邊呆著去。");
                return -1;
        }

        if( query("shen", me)<80000 )
        {
                command("say 你的俠義正事還做得不夠，我可不放心傳你絕技。");
                return -1;
        }

        sob = find_object(SKILL_D("dragon-strike"));

        if (! sob)
        sob = load_object(SKILL_D("dragon-strike"));

        if (! sob->valid_learn(me))
                return 0;

        if (me->query_skill("dragon-strike", 1))
        {
                command("say 你不是已經會了麼？自己好好練吧。");
                return -1;
        }

        sub_skills = keys(sob->query_sub_skills());

        flag = 0;
        for (i = 0; i < sizeof(sub_skills); i++)
        {
                if (me->query_skill(sub_skills[i], 1) >= 10)
                        continue;

                me->set_skill(sub_skills[i], 10);

                if (! flag)
                {
                        flag = 1;
                        command("nod");
                        command("say 我將十八路掌法傳授與你，假以時"
                                "日，必能融會貫通。");
                }
                tell_object(me, HIC "你對" + to_chinese(sub_skills[i]) + "有了"
                            "一些領悟。\n" NOR);
        }

        if (! flag)
        {
                command("say 不是說了待到你融會貫通再來向我討教嗎？");
                return -1;
        }

        command("say 你先將這十八路掌法融會貫通，合而為一再說吧。");
        notify_fail("你自己下去好好練習吧。\n");
        return -1;
}

int accept_object(object who, object ob)
{
        int lv;
        string by;
        object me;
        string hid;
        object hob;
        int r;

        me = this_object();

        if (r = ::accept_object(who, ob))
                return r;

        if( !query("food_supply", ob) )
        {
                command("say 這東西看上去也沒啥特別的，你自個留著吧。");
                return -1;
        }

        if( !intp(lv=query("level", ob) )
            || lv < 1
             || !stringp(by=query("by", ob)) )
        {
                command("say 這東西看上去也沒啥特別的，你自個留著吧。");
                return -1;
        }

        if (lv < 100)
        {
                message_vision(CYN "$N" CYN "嗅了嗅" + ob->name() +
                               CYN "，皺眉道：這東西你還是自個留著"
                               "吧。\n" NOR, me);
                return -1;
        }

        if (lv < 120)
        {
                message_vision(CYN "$N" CYN "嗅了嗅" + ob->name() +
                               CYN "道：味道不錯，可還是稍微欠那麼"
                               "點兒火候。\n" NOR, me);
                return -1;
        }

        message_vision(HIW "$N" HIW "嗅了嗅$n" HIW "遞來的" + ob->name() +
                       HIW "，嘗了幾口，直咂舌頭，連聲稱讚。\n" NOR, me, who);

        if (! who->id(by))
        {
                command("say 可惜不知道是誰做的，有空可得給我引見引見。");
                return 1;
        }

/*
        if( query("gender", who) != "女性" )
        {
                command("say 想不到你一個大老爺們手藝也不錯。難得，難得。");
                return 1;
        }
*/

        if( query("family/family_name", who) != query("family/family_name") )
        {
                command("say 可惜你不是本幫裡的人，否則到可以傳授你一些功夫。");
                return 1;
        }

        if( query("can_learn/hong/xiaoyaoyou", who) >= 1 &&
            query("can_learn/hong/dragon-strike", who) >= 1 )
        {
                command("pat "+query("id", who));
                command("say 又給老叫花解攙來了？多謝，多謝。");
                return 1;
        }
        command("stuff");
        command("say 老叫花沒啥值錢的，就傳你一套拳法作為報答吧。");

        tell_object(who, HIC "\n洪七公同意傳授你「逍遙遊拳法」。\n" NOR);
        addn("can_learn/hong/xiaoyaoyou", 1, who);
        // who->improve_skill("martial-cognize", 1700000);

        // if (lv >= 200 && (string)ob->query("name") == "叫化雞")
        if (lv >= 200)
        {
                // message_vision("洪七公叫道：啊……這正是我想吃的叫化雞呀！\n",
                                // me, who);
                message_vision(CYN "\n$N" CYN "沉思良久，又道：想不"
                               "到除了黃丫頭，居然還有人能做出如此美"
                               "味。\n" NOR, me, who);

                hid=query("couple/couple_id", who);
                if( 1 )
                {
/*
                        if( query("family/family_name", who) != query("family/family_name") ||
                            !query("reborn", who) )
                        {
                                command("say 卻不知你如今有婆家了沒有，可要"
                                        "老叫花給你介紹？");
                                return 1;
                        } else
*/
                        {
                                tell_object(who, HIC "\n洪七公同意傳授你「降龍十八掌」。\n" NOR);
                                addn("can_learn/hong/dragon-strike", 1, who);
                                who->improve_skill("martial-cognize", 1700000);
                                return 1;
                        }
                }

                if (! objectp(hob = find_player(hid)))
                {
                        command("sigh");
                        command("say 可惜你那位不在，否則我倒是可以"
                                "傳他兩手功夫。罷了，罷了。");
                        return 1;
                }

                if( query("family/family_name", hob) != query("family/family_name") )
                {
                        command("say " + hob->name(1) + "能娶到你這"
                                "樣的老婆，也不枉了。");
                        return 1;
                }
                if( query("can_learn/hong/dragon-strike", hob) )
                {
                        command("say " + hob->name(1) + "已經會了「降龍十八掌」，看"
                                "來我這回是白吃了，多謝，多謝。");
                        return 1;
                }

                command("say 什麼時候空了也叫你那位來，我也教他點東西。");

                tell_object(hob, HIC "\n洪七公同意傳授你「降龍十八掌」。\n" NOR);
                set("can_learn/hong/dragon-strike", 1, hob);
                hob->improve_skill("martial-cognize", 1700000);
        }
        destruct(ob);
        return 1;
}

mixed ask_skill1()
{
        object me;
        me = this_player();

        if( query("can_perform/xiaoyaoyou/xian", me) )
                return "我不是已經教過你了麼？";

        if( query("family/family_name", me) != "丐幫"
             && !query("can_learn/hong/xiaoyaoyou", me) )
                return "你打聽這個幹嘛？我認識你麼？";

        if (me->query_skill("xiaoyaoyou", 1) < 1)
                return "你連逍遙遊拳法都沒學過，哪裡來絕招？";

        if( query("family/family_name", me) == "丐幫"
             && query("family/gongji", me)<300 )
                return "你在幫中無所作為，還想讓我傳功給你？。";

        if( query("shen", me)<10000 )
                return "你俠義之事做得不夠，我可不放心傳功予你。";

        if (me->query_skill("force") < 120)
                return "你的內功火候不足，先下去練熟了再來。";

        if (me->query_skill("xiaoyaoyou", 1) < 100)
                return "你的逍遙遊拳法火候未到，再下去練練。";

        message_sort(HIY "\n$n" HIY "愣了一愣，隨即伸手將$N"
                     HIY "招到了面前，在$N" HIY "耳邊輕聲嘀"
                     "咕了些話。$N" HIY "聽了半天，突然間不"
                     "由會心的一笑，看來大有所悟。\n\n" NOR,
                     me, this_object());

        command("say 口訣都傳給你了，自己下去領悟吧。");
        tell_object(me, HIC "你學會了「仙遊訣」。\n" NOR);

        if (me->can_improve_skill("dodge"))
                me->improve_skill("dodge", 1700000);
        if (me->can_improve_skill("xiaoyaoyou"))
                me->improve_skill("xiaoyaoyou", 1700000);
        me->improve_skill("martial-cognize", 1700000);
        set("can_perform/xiaoyaoyou/xian", 1, me);

        if( query("family/family_name", me) == "丐幫" )
                addn("family/gongji", -300, me);

        return 1;
}

mixed ask_skill2()
{
        object me;
        me = this_player();

        if( query("can_perform/pomie-jinzhen/du", me) )
                return "我不是已經教過你了麼？還羅嗦什麼？";

        if( query("family/family_name", me) != query("family/family_name") )
                return "幹啥？我什麼時候說過要教你？";

        if (me->query_skill("pomie-jinzhen", 1) < 1)
                return "你連漫天花雨都沒學過，哪裡來絕招？";

        if( query("family/gongji", me)<500 )
                return "你在幫中無所作為，還想讓我傳功給你？。";

        if( query("shen", me)<10000 )
                return "你俠義之事做得不夠，我可不放心傳功予你。";

        if (me->query_skill("force") < 200)
                return "你的內功火候不足，先下去練熟了再來。";

        if (me->query_skill("pomie-jinzhen", 1) < 150)
                return "你的漫天花雨火候未到，再下去練練。";

        message_sort(HIY "\n$n" HIY "哈哈一笑，將$N" HIY "招至跟前，輕"
                     "聲在$N" HIY "耳旁嘀咕了半天。隨後又伸出右手，十指"
                     "箕張，一伸一縮，看樣子是一種很特別的暗器法門。\n"
                     "\n" NOR, me, this_object());

        command("say 這招的精要就是出手迅捷，攻敵不備，記好了？");
        tell_object(me, HIC "你學會了「擲金針」。\n" NOR);

        if (me->can_improve_skill("throwing"))
                me->improve_skill("throwing", 1700000);
        if (me->can_improve_skill("pomie-jinzhen"))
                me->improve_skill("pomie-jinzhen", 1700000);
        me->improve_skill("martial-cognize", 1700000);
        set("can_perform/pomie-jinzhen/du", 1, me);
        addn("family/gongji", -500, me);

        return 1;
}

mixed ask_skill3()
{
        object me;
        me = this_player();

        if( query("can_perform/dagou-bang/chan", me) )
                return "我不是已經教過你了麼？還羅嗦什麼？";

        if( query("family/family_name", me) != query("family/family_name") )
                return "幹啥？我什麼時候說過要教你？";

        if (me->query_skill("dagou-bang", 1) < 1)
                return "你連打狗棒法都沒學過，哪裡來絕招？";

        if( query("family/gongji", me)<300 )
                return "你在幫中無所作為，還想讓我傳功給你？。";

        if( query("shen", me)<80000 )
                return "你俠義之事做得不夠，我可不放心傳功予你。";

        if (me->query_skill("force") < 100)
                return "你的內功火候不足，回去練高點再來。";

        if (me->query_skill("dagou-bang", 1) < 60)
                return "你的打狗棒法火候未到，再回去練練。";

        message_sort(HIY "\n$n" HIY "看了$N" HIY "一眼，皺了皺眉，當"
                     "下拍了拍身上的塵土，起身而立。$N" HIY "正感疑惑"
                     "間，卻只見眼前一道綠芒閃過，四周皆是$n" HIY "揮"
                     "出的棒影，竄動不已，頓被鬧了個手忙腳亂。\n\n"
                     NOR, me, this_object());

        command("haha");
        command("say 打狗棒招式以輕盈靈巧著稱，你在這方面得多下工夫。");
        tell_object(me, HIC "你學會了「纏字訣」。\n" NOR);

        if (me->can_improve_skill("staff"))
                me->improve_skill("staff", 1700000);
        if (me->can_improve_skill("dagou-bang"))
                me->improve_skill("dagou-bang", 1700000);
        me->improve_skill("martial-cognize", 1700000);
        set("can_perform/dagou-bang/chan", 1, me);
        addn("family/gongji", -300, me);

        return 1;
}

mixed ask_skill4()
{
        object me;
        me = this_player();

        if( query("can_perform/dagou-bang/chuo", me) )
                return "我不是已經教過你了麼？還羅嗦什麼？";

        if( query("family/family_name", me) != query("family/family_name") )
                return "幹啥？我什麼時候說過要教你？";

        if (me->query_skill("dagou-bang", 1) < 1)
                return "你連打狗棒法都沒學過，哪裡來絕招？";

        if( query("family/gongji", me)<600 )
                return "你在幫中無所作為，還想讓我傳功給你？。";

        if( query("shen", me)<80000 )
                return "你俠義之事做得不夠，我可不放心傳功予你。";

        if (me->query_skill("force") < 160)
                return "你的內功火候不足，回去練高點再來。";

        if (me->query_skill("dagou-bang", 1) < 100)
                return "你的打狗棒法火候未到，再回去練練。";

        message_sort(HIY "\n$n" HIY "哈哈一笑，將$N" HIY "招至跟前，輕"
                     "聲在$N" HIY "耳旁嘀咕了半天。隨後又拔出腰間的玉竹"
                     "杖虛擊劃圓，再猛的直刺而出，看樣子是一種很精妙的"
                     "杖法絕學。$N" HIY "一邊聽一邊不住的點頭。\n\n" NOR,
                     me, this_object());

        command("nod");
        command("say 這招容易制敵殘廢，使用時得多加留意。");
        tell_object(me, HIC "你學會了「戳字訣」。\n" NOR);

        if (me->can_improve_skill("staff"))
                me->improve_skill("staff", 1700000);
        if (me->can_improve_skill("dagou-bang"))
                me->improve_skill("dagou-bang", 1700000);
        me->improve_skill("martial-cognize", 1700000);
        set("can_perform/dagou-bang/chuo", 1, me);
        addn("family/gongji", -600, me);

        return 1;
}

mixed ask_skill5()
{
        object me;
        me = this_player();

        if( query("can_perform/dagou-bang/feng", me) )
                return "我不是已經教過你了麼？還羅嗦什麼？";

        if( query("family/family_name", me) != query("family/family_name") )
                return "幹啥？我什麼時候說過要教你？";

        if (me->query_skill("dagou-bang", 1) < 1)
                return "你連打狗棒法都沒學過，哪裡來絕招？";

        if( query("family/gongji", me)<1700 )
                return "你在幫中無所作為，還想讓我傳功給你？。";

        if( query("shen", me)<80000 )
                return "你俠義之事做得不夠，我可不放心傳功予你。";

        if (me->query_skill("force") < 180)
                return "你的內功火候不足，回去練高點再來。";

        if (me->query_skill("dagou-bang", 1) < 120)
                return "你的打狗棒法火候未到，再回去練練。";

        message_sort(HIY "\n$n" HIY "愣了一愣，隨即伸手將$N"
                     HIY "招到了面前，在$N" HIY "耳邊輕聲嘀"
                     "咕了些話。$N" HIY "聽了半天，突然間不"
                     "由會心的一笑，看來大有所悟。\n\n" NOR,
                     me, this_object());

        command("nod");
        command("say 遇強時使用這招足當自保，下去後再多練練。");
        tell_object(me, HIC "你學會了「封字訣」。\n" NOR);

        if (me->can_improve_skill("staff"))
                me->improve_skill("staff", 1700000);
        if (me->can_improve_skill("dagou-bang"))
                me->improve_skill("dagou-bang", 1700000);
        me->improve_skill("martial-cognize", 1700000);
        set("can_perform/dagou-bang/feng", 1, me);
        addn("family/gongji", -1700, me);

        return 1;
}

mixed ask_skill6()
{
        object me;
        me = this_player();

        if( query("can_perform/dagou-bang/ban", me) )
                return "我不是已經教過你了麼？還羅嗦什麼？";

        if( query("family/family_name", me) != query("family/family_name") )
                return "幹啥？我什麼時候說過要教你？";

        if (me->query_skill("dagou-bang", 1) < 1)
                return "你連打狗棒法都沒學過，哪裡來絕招？";

        if( query("family/gongji", me)<1800 )
                return "你在幫中無所作為，還想讓我傳功給你？。";

        if( query("shen", me)<100000 )
                return "你俠義之事做得不夠，我可不放心傳功予你。";

        if (me->query_skill("force") < 240)
                return "你的內功火候不足，回去練高點再來。";

        if (me->query_skill("dagou-bang", 1) < 180)
                return "你的打狗棒法火候未到，再回去練練。";

        message_sort(HIY "\n$n" HIY "看了$N" HIY "一眼，皺了皺眉，當"
                     "下拍了拍身上的塵土，起身而立。$N" HIY "正感疑惑"
                     "間，卻只見眼前一道綠芒閃過，四周皆是$n" HIY "揮"
                     "出的棒影，竄動不已，頓被鬧了個手忙腳亂。\n\n"
                     NOR, me, this_object());

        command("haha");
        command("say 這招的精要乃是出奇制勝，你下去後自己體會吧。");
        tell_object(me, HIC "你學會了「絆字訣」。\n" NOR);

        if (me->can_improve_skill("staff"))
                me->improve_skill("staff", 1700000);
        if (me->can_improve_skill("dagou-bang"))
                me->improve_skill("dagou-bang", 1700000);
        me->improve_skill("martial-cognize", 1700000);
        set("can_perform/dagou-bang/ban", 1, me);
        addn("family/gongji", -1800, me);

        return 1;
}
/*
mixed ask_skill7()
{
        object me;
        me = this_player();

        if( query("can_perform/dagou-bang/tian", me) )
                return "自己去練吧，老纏著我幹什麼？";

        if( query("family/family_name", me) != query("family/family_name") )
                return "幹啥？我什麼時候說過要教你？";

        if (me->query_skill("dagou-bang", 1) < 1)
                return "你連打狗棒法都沒學過，哪裡來絕招？";

        if( query("family/gongji", me)<2000 )
                return "你在幫中無所作為，還想讓我傳功給你？。";

        if( query("shen", me)<100000 )
                return "你俠義之事做得不夠，我可不放心傳功予你。";

        if( query("family/beggarlvl", me)<9 )
                return "你在幫中的輩分還不夠，等成為長老再說吧。";

        if( !query("can_perform/dagou-bang/chan", me )
            || !query("can_perform/dagou-bang/chuo", me )
            || !query("can_perform/dagou-bang/feng", me )
            || !query("can_perform/dagou-bang/ban", me) )
                return "你打狗棒法的四個棒訣都了解透徹了麼？";

        if (me->query_skill("force") < 300)
                return "你的內功火候不足，回去練高點再來。";

        if (me->query_skill("dagou-bang", 1) < 220)
                return "你的打狗棒法火候未到，再回去練練。";

        message_sort(HIY "\n$n" HIY "凝視了$N" HIY "好一會，方才"
                     "點了點頭，隨手抄起玉竹杖，驀地一卷，帶起陣"
                     "陣風聲，便猶若千百根相似，層層疊疊將$N" HIY
                     "籠罩于勁風之中，招式精奇，無與倫比，令人嘆"
                     "為觀止。\n\n" NOR, me, this_object());

        command("stuff");
        command("say 你到了這個程度，我也沒啥好教的了，自己多練吧。");
        tell_object(me, HIC "你學會了「天下無狗」。\n" NOR);

        if (me->can_improve_skill("staff"))
                me->improve_skill("staff", 1700000);
        if (me->can_improve_skill("staff"))
                me->improve_skill("staff", 1700000);
        if (me->can_improve_skill("staff"))
                me->improve_skill("staff", 1700000);
        if (me->can_improve_skill("dagou-bang"))
                me->improve_skill("dagou-bang", 1700000);
        if (me->can_improve_skill("dagou-bang"))
                me->improve_skill("dagou-bang", 1700000);
        if (me->can_improve_skill("dagou-bang"))
                me->improve_skill("dagou-bang", 1700000);
        me->improve_skill("martial-cognize", 1700000);
        set("can_perform/dagou-bang/tian", 1, me);
        addn("family/gongji", -2000, me);

        return 1;
}
*/
mixed ask_skill7()
{
        object me, obj;

        me = this_player();

        if( query("family/family_name", me) != query("family/family_name") )
                return "你一邊去。";

        if (me->query_skill("dagou-bang", 1) < 250)
                return "你的打狗棒法學得怎麼樣啊？我看還差得遠呢！";

        if (query("book_count") <1)
                return "你來晚了，打狗棒秘籍我已經借出去了。";
        obj = new(__DIR__"obj/book.c");
        set("master",query("id",  me), obj);
        obj->move(me);
        tell_object(me, "洪七公說道：“好吧，這本秘籍你拿去好好研究吧！”\n");
        addn("book_count", -1);
        return 1;
}

mixed ask_skill8()
{
        object me;
        me = this_player();

        if( query("can_perform/dragon-strike/qin", me) )
                return "我不是已經教過你了麼？";

        if( query("family/family_name", me) != "丐幫"
            && !query("can_learn/hong/dragon-strike", me) )
                return "你打聽這個幹嘛？我認識你麼？";

        if (me->query_skill("dragon-strike", 1) < 1)
                return "你連降龍十八掌都沒學過，哪裡來絕招？";

        if( query("family/family_name", me) == "丐幫"
            && query("family/gongji", me)<800 )
                return "你在幫中無所作為，這招暫時還不能傳你。";

        if( query("shen", me)<100000 )
                return "你俠義之事做得不夠，我可不放心傳功予你。";

        if (me->query_skill("force") < 300)
                return "你內功火候不足，暫時還無法運用這招。";

        if (me->query_skill("dragon-strike", 1) < 150)
                return "你的降龍十八掌火候未到，再下去練練。";

        message_sort(HIY "\n$n" HIY "點了點頭，轉過身來對$N" HIY "說"
                     "道：“我給你演示一遍，看好了。”話音剛落，聽得"
                     "$n" HIY "一聲暴喝，全身內勁迸發，氣貫右臂奮力外"
                     "扯。一時間你只覺周圍氣流湧動，地上塵土盡數向$n"
                     HIY "的掌心湧去。\n\n" NOR, me, this_object());

        command("say 招式便是如此，你自己下去領悟吧。");
        tell_object(me, HIC "你學會了「擒龍手」。\n" NOR);

        if (me->can_improve_skill("strike"))
                me->improve_skill("strike", 1700000);
        if (me->can_improve_skill("dragon-strike"))
                me->improve_skill("dragon-strike", 1700000);
        me->improve_skill("martial-cognize", 1700000);
        set("can_perform/dragon-strike/qin", 1, me);

        if( query("family/family_name", me) == "丐幫" )
                addn("family/gongji", -800, me);

        return 1;
}

mixed ask_skill9()
{
        object me;
        me = this_player();

        if( query("can_perform/dragon-strike/lei", me) )
                return "我不是已經教過你了麼？";

        if( query("family/family_name", me) != "丐幫"
            && !query("can_learn/hong/dragon-strike", me) )
                return "你打聽這個幹嘛？我認識你麼？";

        if (me->query_skill("dragon-strike", 1) < 1)
                return "你連降龍十八掌都沒學過，哪裡來絕招？";

        if( query("family/family_name", me) == "丐幫"
            && query("family/gongji", me)<2000 )
                return "你在幫中無所作為，這招暫時還不能傳你。";

        if( query("shen", me)<100000 )
                return "你俠義之事做得不夠，我可不放心傳功予你。";

        if (me->query_skill("force") < 300)
                return "你內功火候不足，暫時還無法運用這招。";

        if (me->query_skill("dragon-strike", 1) < 150)
                return "你的降龍十八掌火候未到，再下去練練。";

        message_sort(HIY "\n$n" HIY "點了點頭，轉過身來對$N" HIY "說"
                     "道：“我給你演示一遍，看好了。”話音剛落，聽得"
                     "$n" HIY "一聲暴喝，全身真氣鼓動，雙掌排山倒海般"
                     "壓出。頓時只聽“喀嚓”一聲脆響，$n" HIY "身前那"
                     "棵碗口粗的鬆樹應聲而倒，直看得$N" HIY "目瞪口呆"
                     "，半天說不出話來。\n\n" NOR, me, this_object());

        command("sweat");
        command("say 招式便是如此，你自己下去領悟吧。");
        tell_object(me, HIC "你學會了「雷霆一擊」。\n" NOR);

        if (me->can_improve_skill("strike"))
                me->improve_skill("strike", 1700000);
        if (me->can_improve_skill("dragon-strike"))
                me->improve_skill("dragon-strike", 1700000);
        me->improve_skill("martial-cognize", 1700000);
        set("can_perform/dragon-strike/lei", 1, me);

        if( query("family/family_name", me) == "丐幫" )
                addn("family/gongji", -2000, me);

        return 1;
}

mixed ask_skill10()
{
        object me;
        me = this_player();

        if( query("can_perform/dragon-strike/xiang", me) )
                return "我不是已經教過你了麼？";

        if( query("family/family_name", me) != "丐幫"
            && !query("can_learn/hong/dragon-strike", me) )
                return "你打聽這個幹嘛？我認識你麼？";

        if (me->query_skill("dragon-strike", 1) < 1)
                return "你連降龍十八掌都沒學過，哪裡來絕招？";

        if( query("family/family_name", me) == "丐幫"
            && query("family/gongji", me)<3000 )
                return "你在幫中無所作為，這招暫時還不能傳你。";

        if( query("shen", me)<100000 )
                return "你俠義之事做得不夠，我可不放心傳功予你。";

        if (me->query_skill("force") < 300)
                return "你內功火候不足，暫時還無法運用這招。";

        if (me->query_skill("dragon-strike", 1) < 150)
                return "你的降龍十八掌火候未到，再下去練練。";

        message_sort(HIY "\n$n" HIY "沉思良久，方才緩緩點了點頭，伸"
                     "手將$N" HIY "招至身旁，低聲講解了良久。過得片"
                     "刻，卻見$n" HIY "驀地起身而立，深深吸入一口氣"
                     "，雙掌猛然翻滾，宛如一條神龍攀蜒于九天之上，氣"
                     "勢恢弘，盪氣回腸。\n\n" NOR, me, this_object());

        command("nod");
        command("say 修煉這招頗為不易，你下去後需勤加練習。");
        tell_object(me, HIC "你學會了「龍翔九天」。\n" NOR);

        if (me->can_improve_skill("strike"))
                me->improve_skill("strike", 1700000);
        if (me->can_improve_skill("dragon-strike"))
                me->improve_skill("dragon-strike", 1700000);
        me->improve_skill("martial-cognize", 1700000);
        set("can_perform/dragon-strike/xiang", 1, me);

        if( query("family/family_name", me) == "丐幫" )
                addn("family/gongji", -3000, me);

        return 1;
}

mixed ask_skill11()
{
        object me;
        me = this_player();

        if( query("can_perform/dragon-strike/hui", me) )
                return "我不是已經教過你了麼？";

        if( query("family/family_name", me) != "丐幫"
            && !query("can_learn/hong/dragon-strike", me) )
                return "你打聽這個幹嘛？我認識你麼？";

        if (me->query_skill("dragon-strike", 1) < 1)
                return "你連降龍十八掌都沒學過，哪裡來絕招？";

        if( query("family/family_name", me) == "丐幫"
            && query("family/gongji", me)<3000 )
                return "你在幫中無所作為，這招暫時還不能傳你。";

        if( query("shen", me)<120000 )
                return "你俠義之事做得不夠，我可不放心傳功予你。";

        if (me->query_skill("force", 1) < 260)
                return "你基本內功火候不足，暫時還無法運用這招。";

        if (me->query_skill("dragon-strike", 1) < 220)
                return "你的降龍十八掌火候未到，再下去練練。";

        message_sort(HIY "\n$n" HIY "沉思良久，方才緩緩點了點頭，伸"
                     "手將$N" HIY "招至身旁，低聲講解了良久。過得片"
                     "刻，忽然$n" HIY "身形激進，左手一劃，右手呼的一掌"
                     "拍向虛空，正是降龍十八掌“亢龍有悔” 。力自掌生之"
                     "際說到便到，以排山倒海之勢向虛空狂湧而去，當真石"
                     "破天驚，威力無比。\n\n" NOR, me, this_object());

        command("nod");
        command("say 修煉這招頗為不易，你下去後需勤加練習。");
        tell_object(me, HIC "你學會了「亢龍有悔」。\n" NOR);

        if (me->can_improve_skill("strike"))
                me->improve_skill("strike", 1700000);
        if (me->can_improve_skill("dragon-strike"))
                me->improve_skill("dragon-strike", 1700000);
        me->improve_skill("martial-cognize", 1700000);
        set("can_perform/dragon-strike/hui", 1, me);

        if( query("family/family_name", me) == "丐幫" )
                addn("family/gongji", -3000, me);

        return 1;
}

mixed ask_skill12()
{
        object me;
        me = this_player();

        if( query("can_perform/dragon-strike/pai", me) )
                return "我不是已經教過你了麼？";

        if( query("family/family_name", me) != "丐幫"
            && !query("can_learn/hong/dragon-strike", me) )
                return "你打聽這個幹嘛？我認識你麼？";

        if (me->query_skill("dragon-strike", 1) < 1)
                return "你連降龍十八掌都沒學過，哪裡來絕招？";

        if( query("family/family_name", me) == "丐幫"
            && query("family/gongji", me)<1000 )
                return "你在幫中無所作為，這招暫時還不能傳你。";

        if( query("shen", me)<120000 )
                return "你俠義之事做得不夠，我可不放心傳功予你。";

        if (me->query_skill("force", 1) < 260)
                return "你基本內功火候不足，暫時還無法運用這招。";

        if (me->query_skill("dragon-strike", 1) < 220)
                return "你的降龍十八掌火候未到，再下去練練。";

        message_sort(HIY "\n$n" HIY "沉思良久，方才緩緩點了點頭，伸"
                     "手將$N" HIY "招至身旁，低聲講解了良久。過得片"
                     "刻，忽然$n" HIY "身形激進，全身真氣鼓動，雙掌"
                     "以排山倒海之勢向虛空狂湧而去，當真石"
                     "破天驚，威力無比。\n\n" NOR, me, this_object());

        command("nod");
        command("say 修煉這招頗為不易，你下去後需勤加練習。");
        tell_object(me, HIC "你學會了「排山倒海」。\n" NOR);

        if (me->can_improve_skill("strike"))
                me->improve_skill("strike", 1700000);
        if (me->can_improve_skill("dragon-strike"))
                me->improve_skill("dragon-strike", 1700000);
        me->improve_skill("martial-cognize", 1700000);
        set("can_perform/dragon-strike/pai", 1, me);

        if( query("family/family_name", me) == "丐幫" )
                addn("family/gongji", -1000, me);

        return 1;
}

mixed ask_skill13()
{
        object me;
        me = this_player();

        if( query("can_perform/dragon-strike/xiao", me) )
                return "我不是已經教過你了麼？";

        if( query("family/family_name", me) != "丐幫"
            && query("reborn/family_name", me) != "丐幫" )
                return "你打聽這個幹嘛？我認識你麼？";

        if( !query("reborn/times", me) )
                return "你還未經歷過轉世重生的考驗，難以領悟此招真諦。";
        
        /*
        if( !query("can_perform/dragon-strike/qu", me) )
                return "你還未學會雙龍取水，無法領悟□□九天。";
        if( !query("can_perform/dragon-strike/zhen", me) )
                return "你還未學會震驚百裡，無法領悟□□九天。";
        if( !query("can_perform/dragon-strike/hui", me) )
                return "你還未學會亢龍有悔，無法領悟□□九天。";
        if( !query("can_perform/dragon-strike/long", me) )
                return "你還未學會飛龍在天，無法領悟□□九天。";                                                
        */
        
        if (me->query_skill("dragon-strike", 1) < 1)
                return "你連降龍十八掌都沒學過，哪裡來絕招？";

        if( query("family/family_name", me) == "丐幫"
            && query("family/gongji", me)<10000 )
                return "你在幫中無所作為，這招暫時還不能傳你。";

        if( query("shen", me)<8000000 )
                return "你俠義之事做得不夠，我可不放心傳功予你。";

        if (me->query_skill("force", 1) < 1000)
                return "你基本內功火候不足，暫時還無法運用這招。";

        if (me->query_skill("dragon-strike", 1) < 1000)
                return "你的降龍十八掌火候未到，再下去練練。";

        if( query("max_neili", me)<10000 )
                return "你內力修為不足，再下去練練吧。";

        message_sort(HIY "\n$n" HIY "沉思良久，方才緩緩點了點頭，伸"
                     "手將$N" HIY "招至身旁，低聲講解了良久。\n\n" NOR, 
                     me, this_object());

        command("nod");
        command("say 修煉這招頗為不易，你下去後需勤加練習。");
        tell_object(me, HIC "你學會了「□□九天」。\n" NOR);
        addn("str", 1, me);
        tell_object(me, HIY "你的先天臂力永久增加一點。\n" NOR);

        if (me->can_improve_skill("strike"))
                me->improve_skill("strike", 1500000);
        if (me->can_improve_skill("dragon-strike"))
                me->improve_skill("dragon-strike", 1500000);
        me->improve_skill("martial-cognize", 1500000);
        set("can_perform/dragon-strike/xiao", 1, me);
        
        if( query("family/family_name", me) == "丐幫" )
                addn("family/gongji", -10000, me);
        me->save();

        return 1;
}
mixed ask_me()
{
        object me;
        object ob;
        object owner;

      int cost;
        me = this_player();

        if( query("family/family_name", me) != "丐幫" )
                return "你問這個幹嘛？呆一邊去。";

        if( query("family/master_id", me) != query("id") )
                return "嘿，就憑你也想用玉竹杖？";

        if (me->query_skill("dagou-bang", 1) < 150)
                return "就你這樣的棒法也想用玉竹杖？";

        if( query("shen", me)<80000 )
                return "你俠義之事做得不夠，我豈能將丐幫信物交與你？";

// 增加門忠要求
   if( query("family/first", me) ) cost = 250; 
             else cost = 500; 
             if( query("family/gongji", me) < cost ) 
                     return "你為我丐幫效力還不夠，等你擁有足夠的師門功績再來兌換玉竹杖使用時間吧。";
        ob = find_object(YUZHU);
        if (! ob) ob = load_object(YUZHU);
        owner = environment(ob);

        while (owner)
        {
                if (owner->is_character() || ! environment(owner))
                        break;
                owner = environment(owner);
        }

        if (owner == me)
                return "玉竹杖不就是你拿著嗎，怎麼還反倒問起我來了？";

        if (objectp(owner) && owner != this_object())
        {
                if (! owner->is_character())
                        return "玉竹杖現在不在我這裡。";

                if( query("family/family_name", owner) == "丐幫" )
                        return "玉竹杖現在暫時是你同門"+query("name", owner)+
                               "在用，你要用就去找他吧。";
                else
                        return "本幫的玉竹杖現在落在了"+query("name", owner)+
                               "手中，你去把它找回來吧。";
        }
        ob->move(me);
        ob->start_borrowing();
addn("family/gongji", -cost, me); 
        // command("give yuzhu zhang to " + me->query("id"));
        return "這根玉竹杖你就暫時拿去用吧，可別給我丐幫丟臉。";
}

void reset()
{
        set("book_count", 1);
}
