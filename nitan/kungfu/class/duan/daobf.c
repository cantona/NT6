#include <ansi.h>
#include "duan.h"

inherit NPC;
inherit F_MASTER;
// inherit F_QUESTER;

mixed ask_skill1();

void create()
{
        set_name("刀白鳳", ({ "dao baifeng", "dao", "baifeng" }));
        set("title",  "大理國鎮南王妃");
        set("nickname",  CYN "玉虛散人" NOR);
        set("gender", "女性");
        set("long", @LONG
這是個容貌秀麗的中年道姑，是個擺夷族女子，頗
有雍容氣質。她本是大理國皇帝段正淳的正房原配
夫人。因惱丈夫風流不羈，沾花惹草，一怒之下跑
到這裡出了家。
LONG );
        set("age", 35);
        set("class", "royal");
        set("attitude", "friendly");
        set("shen_type", 1);
        set("str", 25);
        set("int", 25);
        set("con", 25);
        set("dex", 25);

        set("max_qi", 2500);
        set("max_jing", 1200);
        set("neili", 3000);
        set("max_neili", 3000);
        set("jiali", 100);
        set("combat_exp", 800000);
        set("score", 8000);

        set_skill("force", 160);
        set_skill("duanshi-xinfa", 100);
        set_skill("kurong-changong", 160);
        set_skill("dodge", 160);
        set_skill("tiannan-bu", 160);
        set_skill("cuff", 140);
        set_skill("jinyu-quan", 140);
        set_skill("strike", 140);
        set_skill("wuluo-zhang", 140);
        set_skill("sword", 120);
        set_skill("duanjia-jian", 120);
        set_skill("whip", 400);
        set_skill("feifeng-bian", 160);
        set_skill("finger", 120);
        set_skill("qiantian-zhi", 120);
        set_skill("parry", 240);
        set_skill("buddhism", 200);
        set_skill("literate", 200);
        set_skill("martial-cognize", 140);

        map_skill("force", "kurong-changong");
        map_skill("dodge", "tiannan-bu");
        map_skill("finger", "qiantian-zhi");
        map_skill("cuff", "jinyu-quan");
        map_skill("strike", "wuluo-zhang");
        map_skill("whip", "feifeng-bian");
        map_skill("sword", "duanjia-jian");
        map_skill("parry", "feifeng-bian");

        prepare_skill("cuff", "jinyu-quan");
        prepare_skill("strike", "wuluo-zhang");

        set("inquiry", ([
                "鳳棲于梧"   : (: ask_skill1 :),
        ]));

        create_family("段氏皇族", 15, "王妃");

        set("chat_chance_combat", 120);
        set("chat_msg_combat", ({
                (: perform_action, "whip.xi" :),
                (: perform_action, "cuff.man" :),
                (: perform_action, "strike.bian" :),
                (: exert_function, "recover" :),
        }));

        set("master_ob", 4);
        setup();
        carry_object("/d/dali/npc/obj/cynrobe")->wear();
        carry_object("/d/dali/obj/fuchen")->wield();
        add_money("silver", 10);
}

void attempt_apprentice(object ob)
{
        if (! permit_recruit(ob))
                return;

        command("sigh");
        command("say 我早已看破紅塵，你又來煩我做甚？");

        if( query("gender", ob) == "女性" )
                command("say 待他日你功力深厚，我倒是可以傳你一套鞭法。");

        return;
}

int recognize_apprentice(object ob, string skill)
{
        if( query("family/family_name", ob) != "段氏皇族" )
        {
                command("?");
                command("say 我與閣下素不相識，不知閣下此番是何用意？");
                return -1;
        }

        if( query("gender", ob) != "女性" )
        {
                command("sigh");
                command("say 我這點微末功夫算什麼，你還是去跟你爹爹學吧。");
                return -1;
        }

        if( query("combat_exp", ob)<30000 )
        {
                command("say 你現在經驗尚淺，過段時間再來找我吧。\n");
                return -1;
        }

        if (skill != "feifeng-bian" && skill != "whip")
        {
                command("say 我只傳授你這套飛鳳鞭法，其余的還是去找你爹爹學吧。");
                return -1;
        }

        if( !query_temp("can_learn/daobaifeng", ob) )
        {
                command("sigh");
                command("say 既然你還念念不忘娘親，今日我就教你好了。");
                set_temp("can_learn/daobaifeng", 1, ob);
        }
        return 1;
}

mixed ask_skill1()
{
        object me;

        me = this_player();
        if( query("can_perform/feifeng-bian/xi", me) )
                return "我不是已經教給你了嗎？還有什麼不懂就自己研究。";

        if( query("family/family_name", me) != query("family/family_name") )
                return RANK_D->query_respect(me) + "和我素無瓜葛，何出此言？";

        if (me->query_skill("feifeng-bian", 1) < 1)
                return "你連我飛鳳鞭法都未學，怎麼來絕招一說？";

        if( query("shen", me)<0 )
                return "哼，你還嫌你在外面惹的禍事不夠麼？";

        if( query("family/gongji", me)<300 )
                return "你在族裡碌碌無為，叫我如何信得過你？";

        if (me->query_skill("force") < 150)
                return "你的內功修為太差，學不了這一招。";

        if( query("max_neili", me)<1200 )
                return "你的內力弱成這樣，怎麼學習這一招？";

        if (me->query_skill("feifeng-bian", 1) < 120)
                return "你飛鳳鞭法的火候還不夠，回去練練再來。";

        message_sort(HIY "\n$n" HIY "對$N" HIY "點了點頭，隨即取出腰"
                     "間拂塵，力貫梢柄，急速揮舞，拂塵頓時畫出一個又"
                     "一個的圈子，緊逼$N" HIY "而去，招式變化甚為精巧"
                     "。\n\n" NOR, me, this_object());

        command("nod");
        command("say 這招看似花巧，其實並不難練，下去後仍需勤加練習。");
        tell_object(me, HIC "你學會了「鳳棲于梧」。\n" NOR);
        if (me->can_improve_skill("whip"))
                me->improve_skill("whip", 1500000);
        if (me->can_improve_skill("feifeng-bian"))
                me->improve_skill("feifeng-bian", 1500000);
        me->improve_skill("martial-cognize", 1500000);
        set("can_perform/feifeng-bian/xi", 1, me);
        addn("family/gongji", -300, me);
        return 1;
}
