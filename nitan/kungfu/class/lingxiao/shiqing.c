#include <ansi.h>;

#define MOJIAN    "/clone/lonely/mojian"

inherit NPC;

mixed ask_jian();
mixed ask_skill1();
mixed ask_skill2();

void create()
{
        object ob;
        set_name("石清", ({ "shi qing", "shi", "qing"}));
        set("gender", "男性");
        set("title", "江南玄素莊莊主");
        set("nickname", HIW "玄素雙劍" NOR);
        set("age", 37);
        set("long", @LONG
這便是江南玄素莊莊主石清，他在江湖中名聲
極好，為人很是狹義。只見他丰神俊朗，衣衫
飄飄，腰間掛着一柄長劍。
LONG );
        set("attitude", "peaceful");
        set("shen_type", 1);
        set("str", 32);
        set("int", 31);
        set("con", 33);
        set("dex", 31);

        set("max_qi", 4500);
        set("max_jing", 3000);
        set("neili", 5000);
        set("max_neili", 5000);
        set("jiali", 180);
        set("combat_exp", 2200000);
        set("score", 25000);

        set_skill("force", 220);
        set_skill("wuwang-shengong", 220);
        set_skill("sword", 220);
        set_skill("shangqing-jian", 220);
        set_skill("dodge", 220);
        set_skill("feiyan-zoubi", 220);
        set_skill("strike", 220);
        set_skill("piaoxu-zhang", 220);
        set_skill("parry", 220);
        set_skill("literate", 250);
        set_skill("martial-cognize", 180);

        map_skill("force", "wuwang-shengong");
        map_skill("sword", "shangqing-jian");
        map_skill("dodge", "feiyan-zoubi");
        map_skill("parry", "shangqing-jian");
        map_skill("strike", "piaoxu-zhang");

        prepare_skill("strike", "piaoxu-zhang");

        set("inquiry", ([
                "墨劍"   : (: ask_jian :),
                "濁流劍" : (: ask_skill1 :),
                "清流劍" : (: ask_skill2 :),
                "閔柔"   : "她是在下的內子，你問他做甚？",
                "封萬里" : "我虧欠他實在太多，實在太多。",
                "白自在" : "凌宵城主“威德先生”白自在號稱天下武功第一，劍法舉世無雙。",
                "白萬劍" : "他是凌宵城主威德先生之子，號稱“氣寒西北”，劍法很是了得。",
                "石破天" : "他是在下的犬子，教子不嚴，我恨不得親手殺了他。",
                "玄鐵令" : "哎……如果有此令，便能請到謝煙客為他做三件事。",
                "謝煙客" : "謝煙客便是“摩天居士”，當年就他散佈玄鐵令三枚。",
        ]));

        set("chat_chance_combat", 100);
        set("chat_msg_combat", ({
                (: perform_action, "sword.zhuo" :),
                (: perform_action, "sword.qing" :),
                (: exert_function, "recover" :),
        }) );

        setup();

        if (clonep())
        {
                ob = find_object(MOJIAN);
                if (! ob) ob = load_object(MOJIAN);
                if (! environment(ob))
                {
                        ob->move(this_object());
                        ob->wield();
                } else
                {
                        ob = new("/clone/weapon/changjian");
                        ob->move(this_object());
                        ob->wield();
                }
        }

        carry_object("/clone/cloth/cloth")->wear();
        add_money("silver", 50);
}

int recognize_apprentice(object ob, string skill)
{
        if( interactive(ob) && (!query("family", ob) || 
           query("family", ob)["master_name"] != "白自在") )
        {
                command("hmm");
                command("say 石某與閣下素無淵源，何談傳授二字？\n");
                return -1;

        }

        if( query("shen", ob)<10000 )
        {
                command("heng");
                command("say 我石某豈能將恩師的劍法傳於你這種江湖宵小？");
                return -1;
        }

        if (skill != "shangqing-jian" && skill != "sword")
        {
                command("shake");
                command("say 我只傳授上清劍法與一些基本的劍法知識，其它去找你"
                        "師父學吧。");
                return -1;
        }

        if (skill == "sword" && ob->query_skill("sword", 1) > 179)
        {
                command("hmm");
                command("say 你的劍法造詣已經非同凡響了，剩下就自己去練吧。");
                return -1;
        }

        if( !query_temp("can_learn/shiqing", ob) )
        {
                command("sigh");
                command("say 哎……我虧欠你雪山派實在太多，傳授你這套劍法也是"
                        "應該的。");
                set_temp("can_learn/shiqing", 1, ob);
        }
        return 1;
}

mixed ask_skill1()
{
        object me;

        me = this_player();
        if( query("can_perform/shangqing-jian/zhuo", me) )
                return "這招閣下不是已經練成了嗎？";

        if( query("family/family_name", me) != "凌霄城" )
                return "石某與閣下素無淵源，不知閣下這話從何而來？";

        if (me->query_skill("shangqing-jian", 1) < 1)
                return "你連上清劍法都沒學，還談什麼絕招可言？";

        if( query("family/gongji", me)<800 )
                return "嗯，你在雪山派中的地位還不足以讓我傳你這一招。";

        if( query("shen", me)<15000 )
                return "學武之人，自應以德義為先。你俠義正事做得不夠，這招我不能傳你。";

        if (me->query_skill("force") < 200)
                return "你的內功修行太淺，用不了這一招！";

        if (me->query_skill("shangqing-jian", 1) < 140)
                return "你上清劍法尚未修煉得精深，沒法用這招。";

        message_vision(HIY "$n" HIY "微微一笑，從懷中輕輕取出了一本"
                       "劍譜，指着其中一段對$N" HIY "細\n説良久，$N"
                       HIY "一邊聽一邊點頭。\n" NOR, me, this_object());

        command("nod");
        command("say 剛才我所説的全是這招的精妙所在，你下去慢慢練吧。");
        tell_object(me, HIC "你學會了「濁流劍」。\n" NOR);

        if (me->can_improve_skill("sword"))
                me->improve_skill("sword", 1500000);
        if (me->can_improve_skill("shangqing-jian"))
                me->improve_skill("shangqing-jian", 1500000);
        me->improve_skill("martial-cognize", 1500000);
        set("can_perform/shangqing-jian/zhuo", 1, me);
        addn("family/gongji", -800, me);
        return 1;
}

mixed ask_skill2()
{
        object me;

        me = this_player();
        if( query("can_perform/shangqing-jian/qing", me) )
                return "這招閣下不是已經練成了嗎？";

        if( query("family/family_name", me) != "凌霄城" )
                return "石某與閣下素無淵源，不知閣下這話從何而來？";

        if (me->query_skill("shangqing-jian", 1) < 1)
                return "你連上清劍法都沒學，還談什麼絕招可言？";

        if( query("family/gongji", me)<1600 )
                return "嗯，你在雪山派中的地位還不足以讓我傳你這一招。";

        if( query("shen", me)<30000 )
                return "學武之人，自應以德義為先。你俠義正事做得不夠，這招我不能傳你。";

        if( !query("can_perform/shangqing-jian/zhuo", me) )
                return "欲練清流劍必先通曉濁流劍訣，你先學那招吧。";

        if (me->query_skill("force") < 220)
                return "你的內功修行太淺，用不了這一招！";

        if (me->query_skill("shangqing-jian", 1) < 160)
                return "你上清劍法尚未修煉得精深，沒法用這招。";

        message_vision( HIY "$n" HIY "哈哈一笑，對$N" HIY "笑道：“沒想"
                        "到你身在雪山派，卻將我上清觀\n的劍法練得如此出"
                        "神入化，石某今日便傳你這招好了。”只聽$n" HIY
                        "\n説完，便開始慢慢的演示劍招，如此反覆了數遍。"
                        "$N" HIY "在一旁仔細觀\n看，隨後會心一笑，似乎"
                        "明白了什麼。\n" NOR, me, this_object());
        command("nod");
        command("say 剛才我演示的你就記清了嗎？記清了就自己下去練吧。");
        tell_object(me, HIC "你學會了「清流劍」。\n" NOR);

        if (me->can_improve_skill("sword"))
                me->improve_skill("sword", 1500000);
        if (me->can_improve_skill("shangqing-jian"))
                me->improve_skill("shangqing-jian", 1500000);
        me->improve_skill("martial-cognize", 1500000);
        set("can_perform/shangqing-jian/qing", 1, me);
        addn("family/gongji", -1600, me);
        return 1;
}

mixed ask_jian()
{
        object me;
        object ob;
        object owner;

        me = this_player();
        if (me->is_bad())
        {
                if( query("family/family_name", me) == "凌霄城" )
                        message_vision(CYN "$N" CYN "冷哼一聲，對$n" CYN "道："
                                       "“你若再敢在我面前説三道四，小心我替雪"
                                       "山派清除你這個敗類！”\n" NOR,
                                       this_object(), me);
                else
                        message_vision(CYN "$N" CYN "冷笑一聲，對$n" CYN "説道"
                                       "：“閣下什麼來頭？居然敢打聽石某的配劍"
                                       "？”\n" NOR,
                                       this_object(), me);
                return 1;
        }

        if( query("family/family_name", me) != "凌霄城" )
                return "石某與閣下素不相識，不知閣下無故打聽在下的配劍究是為何？";

        if( query("family/master_id", me) != "baizizai" )
                return "哼，就憑你也配要石某的配劍？要拿找你師父來吧！";

        if( query("shen", me)<30000 )
                return "學武之人，自應以德義為先。我的配劍不會隨便給人，你走吧。";

        if (me->query_skill("shangqing-jian", 1) < 150)
                return "墨劍只有配合我上清觀的劍法才能顯示其威力，你劍法練好後再來吧。";

        ob = find_object(MOJIAN);
        if (! ob) ob = load_object(MOJIAN);
        owner = environment(ob);
        while (owner)
        {
                if (owner->is_character() || ! environment(owner))
                        break;
                owner = environment(owner);
        }

        if (owner == me)
                return "嗯？石某的墨劍不就在你身上嗎？";

        if (objectp(owner) && owner != this_object())
        {
                if (! owner->is_character())
                        return "你來晚了一步，我的配劍已經讓別人取去了。";

                if( query("family/family_name", owner) == "凌霄城" )
                        return "我的配劍被你雪山派的"+query("name", owner)+
                               "取去了，你要用就去找他吧。";
                else
                        return "我的配劍被"+query("name", owner)+
                               "取去了，你去找他吧！";
        }
        ob->move(this_object());

        ob = new("/clone/weapon/changjian");
        ob->move(this_object());
        ob->wield();

        message_vision(CYN "$N" CYN "歎道：“我的配劍你拿去用吧，但"
                       "切記行走江湖，一切一俠義為重！”\n" NOR,
                       this_object(), me);
        command("give mo jian to "+query("id", me));
        return 1;
}
