#include <ansi.h>
#include "yaowang.h"

#define SHENNONG    "/clone/lonely/shennongjian"
#define SHENPIAN    "/clone/lonely/yaowang_book"

inherit NPC;
inherit F_MASTER;
inherit F_QUESTER;
inherit F_COAGENT;

mixed ask_shennong();
mixed ask_shenpian();

void create()
{
        set_name("無嗔", ({ "wu chen", "wu", "chen" }));
        set("nickname", HIR "毒手藥王" NOR);
        set("long",@LONG
這是一位身著樸素的老者，面色慈祥，竟不知他便是
號稱「毒手藥王」的無嗔。他出家之前，脾氣很是暴
躁。他出家後法名大嗔，後來他經修性養心，頗有進
益，于是更名一嗔。收程靈素法名再更作微嗔。時至
現在，法名已作無嗔。
LONG );
        set("title", HIG "藥王谷谷主" NOR);
        set("gender", "男性");
        set("age", 68);
        set("attitude", "friendly");
        set("shen_type", 1);
        set("str", 40);
        set("int", 40);
        set("con", 40);
        set("dex", 40);
        set("per", 20);

        set("max_qi", 6000);
        set("max_jing", 5000);
        set("neili", 6000);
        set("max_neili", 6000);
        set("jiali", 200);
        set("combat_exp", 2500000);
        set("score", 10000);

        set_skill("force", 380);
        set_skill("yaogu-xinfa", 360);
        set_skill("shennong-xinjing", 380);
        set_skill("dodge", 360);
        set_skill("xuefu-mizong", 300);
        set_skill("strike", 300);
        set_skill("dusha-zhang", 300);
        set_skill("hand", 300);
        set_skill("lansha-shou", 300);
        set_skill("jiuqu-zhegufa", 300);
        set_skill("parry", 300);
        set_skill("staff", 320);
        set_skill("shennong-zhang", 320);
        set_skill("throwing", 320);
        set_skill("xuwen-qixingding", 300);
        set_skill("wuxing-jueming", 320);
        set_skill("literate", 350);
        set_skill("poison", 300);

        set_skill("dispel-poison", 500 );
        set_skill("yaowang-shenxin", 500 );
        set_skill("medical", 500);
        set_skill("yaowang-miaoshu", 500 );
        set_skill("baicao-jue", 500 );
        set_skill("bencao-changshi", 500);
        set_skill("hunting", 300);

        map_skill("force", "shennong-xinjing");
        map_skill("dodge", "xuefu-mizong");
        map_skill("strike", "dusha-zhang");
        map_skill("hand", "jiuqu-zhegufa");
        map_skill("throwing", "wuxing-jueming");
        map_skill("parry", "jiuqu-zhegufa");
        map_skill("staff", "shennong-zhang");
        map_skill("poison", "yaowang-shenxin");
        map_skill("medical", "baicao-jue");

        prepare_skill("hand", "jiuqu-zhegufa");

        create_family("藥王谷", 1, "谷主");
        set("class", "bonze");

        set("chat_chance_combat", 80);
        set("chat_msg_combat", ({
                (: perform_action, "sword.duo" :),
                (: perform_action, "whip.tengshe" :),
                (: perform_action, "whip.panying" :),
                (: perform_action, "whip.bohu" :),
                (: perform_action, "whip.suolong" :),
                (: perform_action, "claw.lianhuan" :),
                (: perform_action, "strike.duchan" :),
                (: exert_function, "recover" :),
                (: exert_function, "powerup" :),

        }) );

        setup();

        set("inquiry", ([
                "神農□"   : (: ask_shennong :),
                "藥王神篇" : (: ask_shenpian :),
                "七星海棠" : "七星海棠乃天下第一毒，無藥可治！",
                "苗人鳳"   : "呵呵，當年我和那個家伙比武，結果少了一根指頭，不過後來還是報復回來了。",
         ]) );

        carry_object("/clone/cloth/cloth")->wear();
}

void attempt_apprentice(object ob)
{
        if (! permit_recruit(ob))
                return;

        if( query("shen", ob)<0 )
        {
                command("say 我已有三個為非作歹的徒弟了，不想再作添加。");
                return;
        }

        if( query("shen", ob)<100000 )
        {
                command("say 欲習我毒技醫術，必須將德行放在首位，我可不希望你像我另外三個徒弟一般。");
                return;
        }

        if( query("combat_exp", ob)<300000 )
        {
                command("say 你現在經驗尚淺，領會不了什麼，還是先去增長點經驗吧。");
                return;
        }
        if( query("family/master_name", ob) == "石萬嗔" )
        {
                command("say 你既已經入石萬嗔門下，好自為之!");
                return;
        }

        if ((int)ob->query_skill("yaogu-xinfa", 1) < 150)
        {
                command("say 你本門的心法還學的不夠啊。");
                return;
        }

        if ((int)ob->query_skill("literate", 1) < 120)
        {
                command("say 你連最基本的學問都沒學好，我如何傳授你高深的毒技醫術。");
                return;
        }

        if ((int)ob->query_skill("yaowang-miaoshu", 1) < 120)
        {
                command("say 你先把藥王妙術鑽研透徹了再來找我吧。");
                return;
        }

        if ((int)ob->query_skill("dispel-poison", 1) < 120)
        {
                command("say 你的妙手驅毒研究透徹了嗎？");
                return;
        }

        command("pat"+query("id", ob));
        command("say 不錯，不錯！既然你如此有心，老夫就收下你這個徒弟。");
        command("say 本門中人不能放蠱，又有九種沒解藥的毒藥決計不能使用。且記!");
        command("recruit "+query("id", ob));
        set("title", "毒手藥王親傳弟子", ob);
        return;
}

mixed ask_shennong()
{
        object me;
        object ob;
        object owner;

        me = this_player();
        if (me->is_bad())
        {
                if( query("family/family_name", me) == "藥王谷" )
                        message_vision(CYN "$N" CYN "冷哼一聲，對$n" CYN "道："
                                       "“你難道忘記了我是怎麼教你的嗎？現在居"
                                       "然和那三個家伙一樣走上了邪道，居然還有"
                                       "臉問我要神農□？”\n" NOR,
                                       this_object(), me);
                else
                        message_vision(CYN "$N" CYN "冷笑一聲，對$n" CYN "說道"
                                       "：“好一個邪派妖徒，竟敢貪圖本派寶物！"
                                       "”\n" NOR,
                                       this_object(), me);
                return 1;
        }

        if( query("family/family_name", me) != "藥王谷" )
                return "你不是我們藥王谷的，打聽它幹什麼？";

        if( query("family/master_id", me) != query("id") )
                return "只有我的弟子才能用神農□。";

        if( query("shen", me)<100000 )
                return "你俠義正事做得還不夠，這神農□我不能教給你。";

        if (me->query_skill("shennong-zhang", 1) < 120)
                return "你連神農杖法都沒學好，就算用神農□也是白搭。";

        ob = find_object(SHENNONG);
        if (! ob) ob = load_object(SHENNONG);
        owner = environment(ob);
        while (owner)
        {
                if (owner->is_character() || ! environment(owner))
                        break;
                owner = environment(owner);
        }

        if (owner == me)
                return "神農□現在不就在你手裡嗎？";

        if (objectp(owner) && owner != this_object())
        {
                if (! owner->is_character())
                        return "你來晚了一步，我已經把神農□借給你同門師兄弟用去了。";

                if( query("family/master_id", owner) == query("id") )
                        return "嗯，神農□現在暫時是你同門師兄弟"+query("name", owner)+
                               "在用，你要用就去找他吧。";
                else
                        return "本門的神農□現在落入了"+query("name", owner)+
                               "之手，你去把它取回來吧！";
        }

        ob->move(this_object());
        message_vision(HIC "$N" HIC "微微一笑，道：“這柄神農□你就"
                       "拿去，記住，千萬不可用它為非作歹！”\n" NOR,
                       this_object(), me);
        command("giveshennongjianto"+query("id", me));
        return 1;
}

mixed ask_shenpian()
{
        object me;
        object ob;
        object owner;

        me = this_player();
        if (me->is_bad())
        {
                if( query("family/family_name", me) == "藥王谷" )
                        message_vision(CYN "$N" CYN "冷哼一聲，對$n" CYN "道："
                                       "“你難道忘記了我是怎麼教你的嗎？現在居"
                                       "然和那三個家伙一樣走上了邪道，我如何能"
                                       "將《藥王神篇》交予你？”\n" NOR,
                                       this_object(), me);
                else
                        message_vision(CYN "$N" CYN "冷笑一聲，對$n" CYN "說道"
                                       "：“好一個邪派妖徒，竟敢貪圖本派寶物！"
                                       "”\n" NOR,
                                       this_object(), me);
                return 1;
        }

        if( query("family/family_name", me) != "藥王谷" )
                return "你不是我們藥王谷的，打聽它幹什麼？";

        if( query("family/master_id", me) != query("id") )
                return "你尚未成為我的弟子，我不能將《藥王神篇》交給你！";

        if( query("shen", me)<100000 )
                return "你俠義正事做得還不夠，《藥王神篇》我不能給你。";

        if (me->query_skill("yaowang-shenxin", 1) < 100)
                return "你藥王神辛尚未學好，給了你你也讀不懂。";

        ob = find_object(SHENPIAN);
        if (! ob) ob = load_object(SHENPIAN);
        owner = environment(ob);
        while (owner)
        {
                if (owner->is_character() || ! environment(owner))
                        break;
                owner = environment(owner);
        }

        if (owner == me)
                return "我這《藥王神篇》現在不就在你手裡嗎？";

        if (objectp(owner) && owner != this_object())
        {
                if (! owner->is_character())
                        return "你來晚了一步，我已經把《藥王神篇》借給你同門師兄弟了。";

                if( query("family/master_id", owner) == query("id") )
                        return "嗯，《藥王神篇》現在在你同門師兄弟"+query("name", owner)+
                               "手裡，你去找他吧。";
                else
                        return "本門的《藥王神篇》現在落入了"+query("name", owner)+
                               "之手，你去把它取回來吧！";
        }

        ob->move(this_object());
        message_vision(HIC "$N" HIC "微微一笑，道：“這本《藥王神篇》現在"
                       "給你，記住，千萬不可用它為非作歹！”\n" NOR,
                       this_object(), me);
        command("giveyaowangshenpianto"+query("id", me));
        return 1;
}

int accept_object(object me, object ob)
{
        int r;
        if (r = ::accept_object(me, ob))

                return r;

        if (base_name(ob) != SHENNONG)
        {
                command("say 你給我這種東西幹什麼？");
                return 0;
        }

        if( query("family/master_id", me) != query("id") )
                command("say 多謝這位" + RANK_D->query_respect(me) + "將本門寶物交回。");
        else
                command("say 很好，很好！");
        destruct(ob);
        return 1;
}

void unconcious()
{
        die();
}
