#include <ansi.h>
#include "lingxiao.h"

inherit NPC;
inherit F_MASTER;
inherit F_QUESTER;
inherit F_COAGENT;

mixed ask_skill1();
mixed ask_skill2();

void create()
{
        set_name("白自在", ({"bai zizai", "bai", "zizai"}));
        set("nickname", HIY "威德先生" NOR);
        set("long", "他就是凌宵城城主，雪山劍派的掌門人，江湖人稱威\n"
                    "德先生的百自在。相傳他年輕時巧逢靈藥，因而功力\n"
                    "大增。後來習武成性，自認為天下武功第一。\n");
        set("gender", "男性");
        set("age", 65);
        set("attitude", "friendly");
        set("shen_type", 1);
        set("str", 40);
        set("int", 40);
        set("con", 40);
        set("dex", 40);
        set("max_qi", 5500);
        set("max_jing", 5000);
        set("neili", 6000);
        set("max_neili", 6000);
        set("jiali", 200);
        set("combat_exp", 3500000);

        set("inquiry",([
                "風回雪舞" : "這招你讓吾兒教你便成，用不著來麻煩老夫。",
                "雪花六出" : "這招你讓吾兒教你便成，用不著來麻煩老夫。",
                "劍氣封喉" : (: ask_skill1 :),
                "三連環"   : (: ask_skill2 :),
                "神倒鬼跌三連環" : (: ask_skill2 :),
        ]));

        set_skill("force", 700);
        set_skill("xueshan-neigong", 680);
        set_skill("wuwang-shengong", 700);
        set_skill("dodge", 660);
        set_skill("taxue-wuhen", 660);
        set_skill("cuff", 660);
        set_skill("lingxiao-quan", 660);
        set_skill("strike", 660);
        set_skill("piaoxu-zhang", 660);
        set_skill("sword", 680);
        set_skill("hanmei-jian", 680);
        set_skill("yunhe-jian", 680);
        set_skill("xueshan-jian", 680);
        set_skill("shangqing-jian", 680);
        set_skill("parry", 660);
        set_skill("literate", 650);
        set_skill("martial-cognize", 650);

        set("no_teach", ([
                "shangqing-jian" : "老夫這套上清劍法乃是得上清觀上代掌門天虛道長所授，並不外傳。\n"
                "白自在又道：這劍法雖不及我雪山劍法精妙，但也頗具威力，玄素莊莊主石清與我交好，他"
                "可傳你此劍法。",
        ]));

        map_skill("force", "wuwang-shengong");
        map_skill("dodge", "taxue-wuhen");
        map_skill("cuff", "lingxiao-quan");
        map_skill("strike", "piaoxu-zhang");
        map_skill("sword", "xueshan-jian");
        map_skill("parry", "shangqing-jian");

        prepare_skill("strike", "piaoxu-zhang");
        prepare_skill("cuff", "lingxiao-quan");

        create_family("凌霄城", 5, "掌門");

        set("chat_chance_combat", 120);
        set("chat_msg_combat", ({
                (: perform_action, "sword.hui" :),
                (: perform_action, "sword.chu" :),
                (: perform_action, "sword.feng" :),
                (: perform_action, "cuff.san" :),
                (: exert_function, "recover" :),
                (: exert_function, "powerup" :),
        }));

        setup();

        carry_object("/d/lingxiao/obj/icesword")->wield();
        carry_object(CLOTH_DIR+"bai")->wear();
}

void attempt_apprentice(object me)
{
        if (! permit_recruit(me))
                return;

        if( query("shen", me)<10000 )
        {
                command("heng");
                command("say 我威德先生乃人人稱道的正人君子，豈能收你為徒？");
                return;
        }

        if( query("combat_exp", me)<400000 )
        {
                command("heng");
                command("say 你的江湖經驗太淺，就算拜到老夫為師，也難有所作為。");
                return;
        }

        if ((int)me->query_skill("xueshan-neigong", 1) < 120)
        {
                command("hmm");
                command("say 你本門內功差成這樣，居然也好意思來找老夫！");
                return;
        }

        if ((int)me->query_skill("xueshan-jian", 1) < 120)
        {
                command("say 你冤在我雪山派待了這麼久，居然連我雪山劍法都沒練好。");
                command("say 真是暴殄天物，氣煞老夫也。");
                return;
        }

        command("say 不錯，不錯。");
        command("say 你運氣好，碰巧老夫今日高興，就收下你吧！");
        command("recruit "+query("id", me));
}

mixed ask_skill1()
{
        object me;

        me = this_player();
        if( query("can_perform/xueshan-jian/feng", me) )
                return "這招我不是已經教過你了嗎？自己下去多練吧！";

        if( query("family/family_name", me) != query("family/family_name") )
                return "你是哪裡來的？快給我快快滾開！";

        if (me->query_skill("xueshan-jian", 1) < 1)
                return "你連雪山劍法都沒學，還談什麼絕招可言？";

        if( query("family/gongji", me)<2000 )
                return "哼，你在本派中無所作為，這一招我暫時還不能傳你。";

        if (me->query_skill("force") < 650)
                return "你的內功修行太淺，用不了這一招！";

        if (me->query_skill("xueshan-jian", 1) < 160)
                return "你雪山劍法尚未修煉得精深，沒法用這招。";

        message_vision( HIY "$n" HIY "哈哈一笑，對$N" HIY "讚道：“不錯，"
                        "不錯，真不愧是老夫的徒\n弟。今日老夫高興，傳你這"
                       "招，可要看好了！”$n" HIY "話音剛落\n隨即一聲清嘯"
                        "，手中長劍龍吟不止，迸出萬道光華疾閃而過。頓\n時"
                       "石屑飛濺，只聽“嗤嗤嗤嗤”數聲，$N" HIY "對面的青"
                       "石牢壁竟已被\n$n" HIY "手中長劍激盪出的劍芒貫穿，"
                       "留下條一人高，半尺寬的裂\n縫，直看得$N" HIY "目瞪"
                       "口呆。\n" NOR, me, this_object());
        command("haha");
        command("say 剛才我所演示的全是這招的精妙所在，你下去慢慢練吧。");
        tell_object(me, HIC "你學會了「劍氣封喉」。\n" NOR);

        if (me->can_improve_skill("sword"))
                me->improve_skill("sword", 1500000);
        if (me->can_improve_skill("xueshan-jian"))
                me->improve_skill("xueshan-jian", 1500000);
        me->improve_skill("martial-cognize", 1500000);
        set("can_perform/xueshan-jian/feng", 1, me);
        addn("family/gongji", -2000, me);
        return 1;
}

mixed ask_skill2()
{
        object me;

        me = this_player();
        if( query("can_perform/lingxiao-quan/san", me) )
                return "自己下去練，別老跟我糾纏不休！";

        if( query("family/family_name", me) != query("family/family_name") )
                return "你是哪裡來的？快給我快快滾開！";

        if (me->query_skill("lingxiao-quan", 1) < 1)
                return "你連凌霄拳法都沒學，還談什麼絕招可言？";

        if( query("family/gongji", me)<1500 )
                return "哼，你在本派中無所作為，這一招我暫時還不能傳你。";

        if (me->query_skill("force") < 650)
                return "你的內功修行實在太差，下去練練再來！";

        if (me->query_skill("lingxiao-quan", 1) < 180)
                return "虧你凌霄拳法練成這樣，也好意思來找我。";

        message_vision(HIY "$n" HIY "望著$N" HIY "哈哈一笑，道：“好！好！"
                       "好！你過來，我傳你此\n招。”$N" HIY "聽罷走至他跟"
                       "前，便聽$n" HIY "說道：“你瞧著，我這麼\n伸手，揪"
                       "住你的後頸，便摔你一個筋……”右手一探，果然已揪\n"
                       "住了$N" HIY "後頸。這一下出手既快，方位又奇，$N"
                       HIY "如何避得，只覺白\n自在手上力道大得出奇，給他一"
                       "抓之下，身子便騰空而起，跌在\n了地上。$n" HIY "一"
                       "笑，左手隨即探出，又已抓住$N" HIY "胸口，順勢一\n"
                       "甩，再次將$N" HIY "摔倒。此時卻見$n" HIY "左腳隨著"
                       "絆去，剎那間把快\n要倒地的$N" HIY "又給絆了一跤。\n"
                       NOR, me, this_object());
        command("haha");
        command("say 師父這一揪、一抓、一絆，接連三招，號稱神倒鬼跌三連環。");
        command("say 這三招你下去後慢慢練，日後受益無窮。");
        tell_object(me, HIC "你學會了「神倒鬼跌三連環」。\n" NOR);

        if (me->can_improve_skill("cuff"))
                me->improve_skill("cuff", 1500000);
        if (me->can_improve_skill("lingxiao-quan"))
                me->improve_skill("lingxiao-quan", 1500000);
        me->improve_skill("martial-cognize", 1500000);
        set("can_perform/lingxiao-quan/san", 1, me);
        addn("family/gongji", -1500, me);
        return 1;
}
