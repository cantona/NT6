// This program is a part of NT MudLIB

#include <ansi.h>
#include "xueshan.h"

#define JINLUN    "/clone/unique/jinlun"
#define JIASHA    "/clone/unique/jiasha"

inherit NPC;
inherit F_MASTER;
inherit F_QUESTER;
inherit F_COAGENT;

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

mixed ask_lun();
mixed ask_midao();

void create()
{
        object ob1, ob2;
        set_name("金輪法王", ({ "jinlun fawang", "jinlun", "fawang" }));
        set("long", @LONG
他便是雪山寺的護教法王。貴為蒙古國師，極
受成吉思汗重用，常年來隨軍隊征戰，擾亂中
原武林，地位顯赫尊崇無比。金輪法王踏足中
原後罕逢敵手，藐視中原群雄。其武道之高深
當可謂西域第一人。
LONG);
        set("nickname", HIY "蒙古國師" NOR);
        set("gender", "男性");
        set("class", "bonze");
        set("age", 58);
        set("attitude", "peaceful");
        set("shen_type", -1);

        set("str", 33);
        set("int", 35);
        set("con", 38);
        set("dex", 33);

        set("max_qi", 6500);
        set("max_jing", 5000);
        set("neili", 8000);
        set("max_neili", 8000);
        set("jiali", 220);
        set("level", 40);
        set("combat_exp", 4000000);
        set("score", 500000);

        set_skill("force", 420);
        set_skill("mizong-neigong", 420);
        set_skill("unarmed", 420);
        set_skill("longxiang-gong", 420);
        set_skill("dodge", 400);
        set_skill("shenkong-xing", 400);
        set_skill("hammer", 420);
        set_skill("riyue-lun", 420);
        set_skill("dali-chu", 400);
        set_skill("xiangmo-chu", 400);
        set_skill("sword", 400);
        set_skill("mingwang-jian", 400);
        set_skill("dagger", 480);
        set_skill("finger", 480);
        // set_skill("poxu-daxuefa", 280);
        set_skill("hand", 480);
        set_skill("dashou-yin", 480);
        set_skill("cuff", 480);
        set_skill("yujiamu-quan", 480);
        set_skill("parry", 400);
        set_skill("lamaism", 400);
        set_skill("literate", 400);
        set_skill("sanscrit", 400);
        set_skill("martial-cognize", 300);

        map_skill("force", "longxiang-gong");
        map_skill("dodge", "shenkong-xing");
        map_skill("parry", "longxiang-gong");
        map_skill("unarmed", "longxiang-gong");
        map_skill("hammer", "riyue-lun");
        map_skill("dagger", "poxu-daxuefa");
        map_skill("sword", "mingwang-jian");
        map_skill("finger", "poxu-daxuefa");
        map_skill("hand", "dashou-yin");
        map_skill("cuff", "yujiamu-quan");

        prepare_skill("unarmed", "longxiang-gong");

        set("chat_chance_combat", 120);
        set("chat_msg_combat", ({
                (: perform_action, "hammer.po" :),
                (: perform_action, "hammer.yuan" :),
                (: perform_action, "hammer.lian" :),
                (: perform_action, "unarmed.tun" :),
                (: perform_action, "unarmed.die" :),
                (: perform_action, "unarmed.ji" :),
                (: exert_function, "recover" :),
                (: exert_function, "shield" :),
                (: exert_function, "powerup" :),
        }));

        create_family("雪山寺", 2, "護教法王");

        set("inquiry", ([
                "日月金輪"  : (: ask_lun :),
                "密道"      : (: ask_midao :),
                "秘道"      : (: ask_midao :),
                "金剛印"    : (: ask_skill1 :),
                "修羅降世"  : (: ask_skill2 :),
                "若悲"      : (: ask_skill3 :),
                "降魔"      : (: ask_skill4 :),
                "破立勢"    : (: ask_skill5 :),
                "圓滿勢"    : (: ask_skill6 :),
                "五輪連轉"  : (: ask_skill7 :),
                "龍吞勢"    : (: ask_skill8 :),
                "象跌勢"    : (: ask_skill9 :),
                "般若極"    : (: ask_skill10 :),
                "真般若極"  : "這是傳說中的招式，便是我也未能領悟。",
                "破元通虛"  : "這一招你去讓霍都教你好了。",
                "轟雷萬鈞"  : "這一招你去讓達而巴教你好了。",
                "鎮魂舞"    : "這一招你去讓達而巴教你好了。",
                "龍象袈裟"  : "這是我的隨身物品，你打聽這個做甚？",
                "金輪九轉"  : "我讓你去跟唐楠接口，你來跟我說幹嘛？",
        ]));

        set("master_ob", 1);
        setup();

        set_temp("apply/damage", 100);
        set_temp("apply/unarmed_damage", 100);
        set_temp("apply/armor", 200);

        if (clonep())
        {
                //ob=new(WEAPON_DIR"treasure/jinlun");
                ob1 = find_object(JINLUN);
                if (! ob1) ob1 = load_object(JINLUN);
                if (! environment(ob1))
                {
                        ob1->move(this_object());
                        ob1->wield();
                }
        }

        if (clonep())
        {
                ob2 = find_object(JIASHA);
                if (! ob2) ob2 = load_object(JIASHA);
                if (! environment(ob2))
                {
                        ob2->move(this_object());
                        ob2->wear();
                } else
                {
                        ob2 = new("/d/xueshan/obj/p-jiasha");
                        ob2->move(this_object());
                        ob2->wear();
                }
                carry_object("/d/xueshan/obj/xuelian");
        }
        carry_object("/d/xueshan/obj/sengmao")->wear();
}

void attempt_apprentice(object ob)
{
        if (! permit_recruit(ob))
                return;

        if( query("gender", ob) != "男性" )
        {
                command("say 修習密宗內功需要純陽之體。");
                command("say 這位" + RANK_D->query_respect(ob) +
                        "還是請回吧！");
                return;
        }

        if( query("class", ob) != "bonze" )
        {
                command("say 我佛門的清規戒律甚多。");
                command("say 這位" + RANK_D->query_respect(ob) +
                        "還是請回吧！");
                return;
        }

        if( query("combat_exp", ob)<450000 )
        {
                command("say 你的實戰經驗不足，還是回去再練練先。");
                return;
        }

        if( query("shen", ob)>-80000 )
        {
                command("say 你這人太過心軟，成不了什麼氣候。");
                return;
        }

        if ((int)ob->query_skill("mizong-neigong", 1) < 120)
        {
                command("say 你內功這麼差，怎麼修行高深的武技？");
                return;
        }

        if ((int)ob->query_skill("lamaism", 1) < 150)
        {
                command("say 入我雪山寺，修習密宗心法是首要的。");
                command("say 這位" + RANK_D->query_respect(ob) +
                        "是否還應該多多鑽研本門的心法？");
                return;
        }

        command("nod");
        command("say 念你力求上進，以後就跟著我吧！");
        command("recruit "+query("id", ob));
}

mixed ask_skill1()
{
        object me;

        me = this_player();

        if( query("can_perform/dashou-yin/yin", me) )
                return "這招我已經教過你了，自己下去多練習練習吧。";

        if( query("family/family_name", me) != query("family/family_name") )
                return "閣下與貧僧素無淵源，不知此話從何談起？";

        if (me->query_skill("dashou-yin", 1) < 1)
                return "你連大手印都沒學，還談什麼絕招？";

        if( query("family/gongji", me)<200 )
                return "你為雪山寺效力不夠，這招暫時還不能傳你。";

        if( query("shen", me)>-15000 )
                return "你為人太過心軟，這一招你不學也罷。";

        if (me->query_skill("force") < 140)
                return "你的內功修為不足，尚且學不了這一招。";

        if( query("max_neili", me)<1000 )
                return "你的內力修為不足，還是修煉高點再來吧。";

        if (me->query_skill("dashou-yin", 1) < 100)
                return "等你把大手印練熟了再來找老夫。";

        message_sort(HIY "\n$n" HIY "微微一愣，上下打量了$N" HIY "一番，點"
                     "了點頭。當下凝神沉履，面容莊重，雙手攜著勁風奮力向$N"
                     HIY "面前的一座舍利佛塔拍落，頓時只聽得轟然聲悶響，佛"
                     "塔內的香灰被$n" HIY "的掌力激盪得四處飛揚，塵煙彌漫"
                     "，待得煙消雲散後，$N" HIY "這才發現那座舍利佛塔上豁"
                     "然嵌著一雙掌印。\n\n" NOR, me, this_object());

        command("nod");
        command("say 只要內功精純，這招並不難練。");
        tell_object(me, HIC "你學會了「金剛印」。\n" NOR);

        if (me->can_improve_skill("hand"))
                me->improve_skill("hand", 1500000);
        if (me->can_improve_skill("dashou-yin"))
                me->improve_skill("dashou-yin", 1500000);
        me->improve_skill("martial-cognize", 1500000);
        set("can_perform/dashou-yin/yin", 1, me);
        addn("family/gongji", -200, me);

        return 1;
}

mixed ask_skill2()
{
        object me;

        me = this_player();

        if( query("can_perform/yujiamu-quan/jiang", me) )
                return "這招我已經教過你了，自己下去多練習練習吧。";

        if( query("family/family_name", me) != query("family/family_name") )
                return "閣下與貧僧素無淵源，不知此話從何談起？";

        if (me->query_skill("yujiamu-quan", 1) < 1)
                return "你連金剛瑜迦母拳都沒學，還談什麼絕招？";

        if( query("family/gongji", me)<300 )
                return "你為雪山寺效力不夠，這招暫時還不能傳你。";

        if( query("shen", me)>-18000 )
                return "你為人太過心軟，這一招你不學也罷。";

        if (me->query_skill("force") < 150)
                return "你的內功修為不足，尚且學不了這一招。";

        if( query("max_neili", me)<1200 )
                return "你的內力修為不足，還是修煉高點再來吧。";

        if (me->query_skill("yujiamu-quan", 1) < 100)
                return "等你把金剛瑜迦母拳練熟了再來找老夫。";

        message_sort(HIY "\n$n" HIY "略微點了點頭，深深呼入一口氣，縱步上"
                     "前，嗔目大喝，拳招迭出，疾如奔雷，霎時已向$N" HIY "攻"
                     "出數拳，招式甚為精妙。實乃$N" HIY "前所未聞。\n\n"
                     NOR, me, this_object());;

        command("nod");
        command("say 看清楚了？");
        tell_object(me, HIC "你學會了「修羅降世」。\n" NOR);

        if (me->can_improve_skill("cuff"))
                me->improve_skill("cuff", 1500000);
        if (me->can_improve_skill("yujiamu-quan"))
                me->improve_skill("yujiamu-quan", 1500000);
        me->improve_skill("martial-cognize", 1500000);
        set("can_perform/yujiamu-quan/jiang", 1, me);
        addn("family/gongji", -300, me);

        return 1;
}

mixed ask_skill3()
{
        object me;

        me = this_player();

        if( query("can_perform/mingwang-jian/ruo", me) )
                return "這招我已經教過你了，自己下去多練習練習吧。";

        if( query("family/family_name", me) != query("family/family_name") )
                return "閣下與貧僧素無淵源，不知此話從何談起？";

        if (me->query_skill("mingwang-jian", 1) < 1)
                return "你連不動明王劍都沒學，還談什麼絕招？";

        if( query("family/gongji", me)<100 )
                return "你為雪山寺效力不夠，這招暫時還不能傳你。";

        if( query("shen", me)>-10000 )
                return "你為人太過心軟，這一招你不學也罷。";

        if (me->query_skill("force") < 140)
                return "你的內功修為不足，尚且學不了這一招。";

        if( query("max_neili", me)<1200 )
                return "你的內力修為不足，還是修煉高點再來吧。";

        if (me->query_skill("mingwang-jian", 1) < 100)
                return "等你把不動明王劍練熟了再來找老夫。";

        message_sort(HIY "\n$n" HIY "微微一笑，也不答話，從$N" HIY "手"
                     "中接過長劍，手腕輕輕一抖，長劍頓時發出一陣低沉的"
                     "輕鳴，鳴音入耳，$N" HIY "只感到心頭一震，竟湧上一"
                     "股莫名的悲哀。\n\n" NOR, me, this_object());

        command("haha");
        command("say 這道理很簡單，你自己下去練吧。");
        tell_object(me, HIC "你學會了「若悲」。\n" NOR);

        if (me->can_improve_skill("sword"))
                me->improve_skill("sword", 1500000);
        if (me->can_improve_skill("mingwang-jian"))
                me->improve_skill("mingwang-jian", 1500000);
        me->improve_skill("martial-cognize", 1500000);
        set("can_perform/mingwang-jian/ruo", 1, me);
        addn("family/gongji", -100, me);

        return 1;
}

mixed ask_skill4()
{
        object me;

        me = this_player();

        if( query("can_perform/mingwang-jian/xiang", me) )
                return "這招我已經教過你了，自己下去多練習練習吧。";

        if( query("family/family_name", me) != query("family/family_name") )
                return "閣下與貧僧素無淵源，不知此話從何談起？";

        if (me->query_skill("mingwang-jian", 1) < 1)
                return "你連不動明王劍都沒學，還談什麼絕招？";

        if( query("family/gongji", me)<400 )
                return "你為雪山寺效力不夠，這招暫時還不能傳你。";

        if( query("shen", me)>-15000 )
                return "你為人太過心軟，這一招你不學也罷。";

        if (me->query_skill("force") < 180)
                return "你的內功修為不足，尚且學不了這一招。";

        if( query("max_neili", me)<1600 )
                return "你的內力修為不足，還是修煉高點再來吧。";

        if (me->query_skill("mingwang-jian", 1) < 140)
                return "等你把不動明王劍練熟了再來找老夫。";

        message_sort(HIY "\n$n" HIY "對$N" HIY "微微一笑，隨即伸出右手，中"
                     "食二指並攏，捏作劍訣，“嗤”的一聲空點而出，霎時破"
                     "空之聲驟響，一股氣勁從指尖迸發，將$N" HIY "所穿戴的"
                     "僧袍刺透出一個小孔。\n\n" NOR, me, this_object());

        command("nod");
        command("say 此招不外乎是以劍作媒，以氣傷人。");
        tell_object(me, HIC "你學會了「降魔」。\n" NOR);

        if (me->can_improve_skill("sword"))
                me->improve_skill("sword", 1500000);
        if (me->can_improve_skill("mingwang-jian"))
                me->improve_skill("mingwang-jian", 1500000);
        me->improve_skill("martial-cognize", 1500000);
        set("can_perform/mingwang-jian/xiang", 1, me);
        addn("family/gongji", -400, me);

        return 1;
}

mixed ask_skill5()
{
        object me;

        me = this_player();

        if( query("can_perform/riyue-lun/po", me) )
                return "你又來幹什麼？自己下去多練。";

        if( query("family/family_name", me) != query("family/family_name") )
                return "閣下與貧僧素無淵源，不知此話從何談起？";

        if (me->query_skill("riyue-lun", 1) < 1)
                return "你連日月輪法都沒學，還談什麼絕招？";

        if( query("family/gongji", me)<800 )
                return "你為雪山寺效力不夠，這招暫時還不能傳你。";

        if( query("shen", me)>-50000 )
                return "你為人太過心軟，這一招你不學也罷。";

        if (me->query_skill("longxiang-gong", 1) < 30)
                return "你的龍象般若功修為不足，還學不了這一招。";

        if (me->query_skill("force") < 180)
                return "你的內功修為不足，尚且學不了這一招。";

        if( query("max_neili", me)<1500 )
                return "你的內力修為不足，還是修煉高點再來吧。";

        if (me->query_skill("riyue-lun", 1) < 120)
                return "等你把日月輪法練熟了再來找我。";

        message_sort(HIY "\n$n" HIY "沉思片刻，方才點了點頭，伸手將$N" HIY
                     "招至身邊，俯身在$P" HIY "耳旁低聲細說良久，$N" HIY
                     "聽後不禁會心的一笑，似乎對$n" HIY "的教導大有所悟"
                     "。\n\n" NOR, me, this_object());

        command("grin");
        command("say 把我剛才說的記牢，自己下去練吧。");
        tell_object(me, HIC "你學會了「破立勢」。\n" NOR);

        if (me->can_improve_skill("hammer"))
                me->improve_skill("hammer", 1500000);
        if (me->can_improve_skill("riyue-lun"))
                me->improve_skill("riyue-lun", 1500000);
        me->improve_skill("martial-cognize", 1500000);
        set("can_perform/riyue-lun/po", 1, me);
        addn("family/gongji", -800, me);

        return 1;
}

mixed ask_skill6()
{
        object me;

        me = this_player();

        if( query("can_perform/riyue-lun/yuan", me) )
                return "你又來幹什麼？自己下去多練。";

        if( query("family/family_name", me) != query("family/family_name") )
                return "閣下與貧僧素無淵源，不知此話從何談起？";

        if (me->query_skill("riyue-lun", 1) < 1)
                return "你連日月輪法都沒學，還談什麼絕招？";

        if( query("family/gongji", me)<800 )
                return "你為雪山寺效力不夠，這招暫時還不能傳你。";

        if( query("shen", me)>-50000 )
                return "你為人太過心軟，這一招你不學也罷。";

        if (me->query_skill("longxiang-gong", 1) < 30)
                return "你的龍象般若功修為不足，還學不了這一招。";

        if (me->query_skill("force") < 180)
                return "你的內功修為不足，尚且學不了這一招。";

        if( query("max_neili", me)<1500 )
                return "你的內力修為不足，還是修煉高點再來吧。";

        if (me->query_skill("riyue-lun", 1) < 120)
                return "等你把日月輪法練熟了再來找我。";

        message_sort(HIY "\n$n" HIY "沉思片刻，方才點了點頭，伸手將$N" HIY
                     "招至身邊，俯身在$P" HIY "耳旁低聲細說良久，$N" HIY
                     "聽後不禁會心的一笑，似乎對$n" HIY "的教導大有所悟"
                     "。\n\n" NOR, me, this_object());

        command("nod");
        command("say 雖然這招可使自身不受傷害，但卻會減弱攻勢。");
        tell_object(me, HIC "你學會了「圓滿勢」。\n" NOR);

        if (me->can_improve_skill("hammer"))
                me->improve_skill("hammer", 1500000);
        if (me->can_improve_skill("riyue-lun"))
                me->improve_skill("riyue-lun", 1500000);
        me->improve_skill("martial-cognize", 1500000);
        set("can_perform/riyue-lun/yuan", 1, me);
        addn("family/gongji", -800, me);

        return 1;
}

mixed ask_skill7()
{
        object me;

        me = this_player();

        if( query("can_perform/riyue-lun/lian", me) )
                return "你又來幹什麼？自己下去多練。";

        if( query("family/family_name", me) != query("family/family_name") )
                return "閣下與貧僧素無淵源，不知此話從何談起？";

        if (me->query_skill("riyue-lun", 1) < 1)
                return "你連日月輪法都沒學，還談什麼絕招？";

        if( query("family/gongji", me)<2000 )
                return "你為雪山寺效力不夠，這招暫時還不能傳你。";

        if( query("shen", me)>-80000 )
                return "你為人太過心軟，這一招你不學也罷。";

        if (me->query_skill("force") < 250)
                return "你的內功修為不足，尚且學不了這一招。";

        if( query("max_neili", me)<3000 )
                return "你的內力修為不足，還是修煉高點再來吧。";

        if (me->query_skill("riyue-lun", 1) < 150)
                return "等你把日月輪法練熟了再來找我。";

        message_sort(HIY "\n$n" HIY "凝視了$N" HIY "半天，才頗為讚許的點"
                     "了點頭，說道：“你能有此實力也屬不易，今日為師就"
                     "傳你這招，瞧仔細了！”說罷$n" HIY "便取出日月金輪"
                     "，嗔目大喝，單手陡然一振，驀地將日月金輪飛擲而出"
                     "，幻作數道光芒，相互盤旋著壓向$N" HIY "，招術當真"
                     "精奇之極！\n\n" NOR, me, this_object());

        command("haha");
        command("say 這招倘若是配合我的日月金輪施展，更能見有神效。");
        tell_object(me, HIC "你學會了「五輪連轉」。\n" NOR);

        if (me->can_improve_skill("hammer"))
                me->improve_skill("hammer", 1500000);
        if (me->can_improve_skill("hammer"))
                me->improve_skill("hammer", 1500000);
        if (me->can_improve_skill("hammer"))
                me->improve_skill("hammer", 1500000);
        if (me->can_improve_skill("riyue-lun"))
                me->improve_skill("riyue-lun", 1500000);
        if (me->can_improve_skill("riyue-lun"))
                me->improve_skill("riyue-lun", 1500000);
        if (me->can_improve_skill("riyue-lun"))
                me->improve_skill("riyue-lun", 1500000);
        me->improve_skill("martial-cognize", 1500000);
        set("can_perform/riyue-lun/lian", 1, me);
        addn("family/gongji", -2000, me);

        return 1;
}

mixed ask_skill8()
{
        object me;

        me = this_player();

        if( query("can_perform/longxiang-gong/tun", me) )
                return "我不是已經教過你了麼？還羅嗦什麼。";

        if( query("family/family_name", me) != query("family/family_name") )
                return "閣下與貧僧素無淵源，不知此話從何談起？";

        if (me->query_skill("longxiang-gong", 1) < 1)
                return "你連龍象般若功都沒學，還談什麼絕招？";

        if( query("family/gongji", me)<1800 )
                return "你為雪山寺效力不夠，這招暫時還不能傳你。";

        if( query("shen", me)>-80000 )
                return "你為人太過心軟，這一招你不學也罷。";

        if( query("max_neili", me)<3000 )
                return "你的內力修為不足，還是修煉高點再來吧。";

        if (me->query_skill("longxiang-gong", 1) < 180)
                return "你的龍象般若功修為不足，練練再來吧。";

        message_sort(HIY "\n$n" HIY "沉思片刻，方才點了點頭，伸手將$N" HIY
                     "招至身邊，俯身在$P" HIY "耳旁低聲細說良久，$N" HIY
                     "聽後不禁會心的一笑，似乎對$n" HIY "的教導大有所悟"
                     "。\n\n" NOR, me, this_object());

        command("nod");
        command("say 剛才我說的全是這招的精髓，自己下去領悟吧。");
        tell_object(me, HIC "你學會了「龍吞勢」。\n" NOR);

        if (me->can_improve_skill("force"))
                me->improve_skill("force", 1500000);
        if (me->can_improve_skill("force"))
                me->improve_skill("force", 1500000);
        if (me->can_improve_skill("unarmed"))
                me->improve_skill("unarmed", 1500000);
        if (me->can_improve_skill("unarmed"))
                me->improve_skill("unarmed", 1500000);
        if (me->can_improve_skill("longxiang-gong"))
                me->improve_skill("longxiang-gong", 1500000);
        if (me->can_improve_skill("longxiang-gong"))
                me->improve_skill("longxiang-gong", 1500000);
        me->improve_skill("martial-cognize", 1500000);
        set("can_perform/longxiang-gong/tun", 1, me);
        addn("family/gongji", -1800, me);

        return 1;
}

mixed ask_skill9()
{
        object me;

        me = this_player();

        if( query("can_perform/longxiang-gong/die", me) )
                return "我不是已經教過你了麼？還羅嗦什麼。";

        if( query("family/family_name", me) != query("family/family_name") )
                return "閣下與貧僧素無淵源，不知此話從何談起？";

        if (me->query_skill("longxiang-gong", 1) < 1)
                return "你連龍象般若功都沒學，還談什麼絕招？";

        if( query("family/gongji", me)<2200 )
                return "你為雪山寺效力不夠，這招暫時還不能傳你。";

        if( query("shen", me)>-120000 )
                return "你為人太過心軟，這一招你不學也罷。";

        if( query("max_neili", me)<4000 )
                return "你的內力修為不足，還是修煉高點再來吧。";

        if (me->query_skill("longxiang-gong", 1) < 240)
                return "你的龍象般若功修為不足，練練再來吧。";

        message_sort(HIY "\n$n" HIY "看了$N" HIY "一眼，當下也不答話，陡"
                     "然伸出右手，往$N" HIY "胸口探去。$N" HIY "慌忙招"
                     "架，卻哪知這看似不經意的一掌，竟然暗含了龍象般若"
                     "功第八成的功力，$N" HIY "根本無暇躲避，頓時被這招"
                     "所制，重重的摔了出去。\n\n" NOR, me, this_object());

        command("say 懂了麼？");
        tell_object(me, HIC "你學會了「象跌勢」。\n" NOR);

        if (me->can_improve_skill("force"))
                me->improve_skill("force", 1500000);
        if (me->can_improve_skill("force"))
                me->improve_skill("force", 1500000);
        if (me->can_improve_skill("unarmed"))
                me->improve_skill("unarmed", 1500000);
        if (me->can_improve_skill("unarmed"))
                me->improve_skill("unarmed", 1500000);
        if (me->can_improve_skill("longxiang-gong"))
                me->improve_skill("longxiang-gong", 1500000);
        if (me->can_improve_skill("longxiang-gong"))
                me->improve_skill("longxiang-gong", 1500000);
        me->improve_skill("martial-cognize", 1500000);
        set("can_perform/longxiang-gong/die", 1, me);
        addn("family/gongji", -2200, me);

        return 1;
}

mixed ask_skill10()
{
        object me;

        me = this_player();

        if( query("can_perform/longxiang-gong/ji", me) )
                return "我不是已經教過你了麼？還羅嗦什麼。";

        if( query("family/family_name", me) != query("family/family_name") )
                return "閣下與貧僧素無淵源，不知此話從何談起？";

        if (me->query_skill("longxiang-gong", 1) < 1)
                return "你連龍象般若功都沒學，還談什麼絕招？";

        if( query("family/gongji", me)<2500 )
                return "你為雪山寺效力不夠，這招暫時還不能傳你。";

        if( query("shen", me)>-160000 )
                return "你為人太過心軟，這一招你不學也罷。";

        if( query("max_neili", me)<5000 )
                return "你的內力修為不足，還是修煉高點再來吧。";

        if (me->query_skill("longxiang-gong", 1) < 300)
                return "你的龍象般若功修為不足，練練再來吧。";

        message_sort(HIY "\n$n" HIY "微微點了點頭，只是隨手搭在$N" HIY
                     "的肩上，突然$N" HIY "陡覺全身筋脈劇震，內息澎湃"
                     "洶湧之極，猶如江河絕堤，便欲沖關破出一般，不由大"
                     "驚。\n\n" NOR, me, this_object());

        command("haha");
        command("say 剛才我這一招，你看明白了多少？");
        tell_object(me, HIC "你學會了「般若極」。\n" NOR);

        if (me->can_improve_skill("force"))
                me->improve_skill("force", 1500000);
        if (me->can_improve_skill("force"))
                me->improve_skill("force", 1500000);
        if (me->can_improve_skill("force"))
                me->improve_skill("force", 1500000);
        if (me->can_improve_skill("unarmed"))
                me->improve_skill("unarmed", 1500000);
        if (me->can_improve_skill("unarmed"))
                me->improve_skill("unarmed", 1500000);
        if (me->can_improve_skill("unarmed"))
                me->improve_skill("unarmed", 1500000);
        if (me->can_improve_skill("longxiang-gong"))
                me->improve_skill("longxiang-gong", 1500000);
        if (me->can_improve_skill("longxiang-gong"))
                me->improve_skill("longxiang-gong", 1500000);
        if (me->can_improve_skill("longxiang-gong"))
                me->improve_skill("longxiang-gong", 1500000);
        me->improve_skill("martial-cognize", 1500000);
        set("can_perform/longxiang-gong/ji", 1, me);
        addn("family/gongji", -2500, me);

        return 1;
}

mixed ask_midao()
{
        object me;

        me = this_player();
        if( query("family/family_name", me) != "雪山寺" )
                return "你找死麼？";

        command("whisper"+query("id", me)+"你既然投入我雪山寺，以"
                "後若\n要去中原辦事，即可用我雪山寺先輩們留下的密道，直"
                "接去禪\n室轉動(" HIY "turn lunpan" NOR + WHT ") 輪盤觸"
                "發機關，地面便會開啟密道，然\n後你順著密道前進便能到達"
                "中原揚州。若要回寺可找我雪山寺\n伏在中原的唐楠，接口的"
                "密語是" HIY "金輪九轉" NOR + WHT "，可記清楚了。\n");
        return "此秘密不可泄露于他人，否則我饒不了你！";
}

mixed ask_lun()
{
        object me;
        object ob;
        object owner;

        me = this_player();
        if (me->is_good())
        {
                if( query("family/family_name", me) == "雪山寺" )
                        message_vision(CYN "$N" CYN "大怒，對$n" CYN "道：“你身"
                                       "為我雪山寺弟子，反而學起假仁假義來了，給"
                                       "我滾吧！”\n" NOR, this_object(), me);
                else
                        message_vision(CYN "$N" CYN "大怒，對$n" CYN "喝道：“你"
                                       "是什麼人？居然敢貪圖我的隨身利器，活得不"
                                       "耐煩了？”\n" NOR, this_object(), me);
                return 1;
        }

        if( query("family/family_name", me) != "雪山寺" )
                return "日月金輪是我的隨身兵器，你打聽它幹什麼？";

        if( query("family/master_id", me) != query("id") )
                return "只有我的弟子才配使用金輪，你還是自己下去練練吧。";

        if( query("shen", me)>-50000 )
                return "哼！你既然如此俠義，還是別用金輪的好。";

        ob = find_object(JINLUN);
        if (! ob) ob = load_object(JINLUN);
        owner = environment(ob);
        while (owner)
        {
                if (owner->is_character() || ! environment(owner))
                        break;
                owner = environment(owner);
        }

        if (owner == me)
                return "怎麼？日月金輪不就是你拿著在用嗎？";

        if (objectp(owner) && owner != this_object())
        {
                if (! owner->is_character())
                        return "你來晚了一步，日月金輪現在不在我手中。";

                if( query("family/family_name", owner) == "雪山寺" )
                        return "金輪現在暫時是你同門師兄"+query("name", owner)+
                               "在用，你要用就去找他吧。";
                else
                        return "我的日月金輪現在落在"+query("name", owner)+
                               "手中，你去把他做了，把金輪搶回來！";
        }

        ob->move(this_object());
        message_vision(CYN "$N" CYN "微微笑道：念在你平時刻苦努力，我這柄"
                       "金輪你就拿去用吧。\n" NOR, this_object(), me);
        command("giveriyuejinlunto"+query("id", me));
        return 1;
}

/*
void unconcious()
{
        die();
}
*/
