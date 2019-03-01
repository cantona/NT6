#include <ansi.h>
#include "kunlun.h"

#define LIANGJI    "/clone/lonely/liangjijian"

inherit NPC;
inherit F_MASTER;
inherit F_QUESTER; 

mixed ask_skill1();
mixed ask_skill2();
mixed ask_skill3();
mixed ask_skill4();
mixed ask_jian();

void create()
{
        object ob;
        set_name("何足道", ({"he zudao", "he", "zudao"}));
        set("title", "昆侖派開山祖師");
        set("nickname", HIY "昆侖三聖" NOR);
        set("long", @LONG
這就是昆侖派開山祖師，號稱琴劍棋三絕的昆
侖三聖何足道。見他長臉深目，面目清秀。卻
是瘦骨棱棱，身著一青衫。
LONG);
        set("gender", "男性");
        set("age", 95);
        set("attitude", "friendly");
        set("shen_type", 1);
        set("str", 40);
        set("int", 40);
        set("con", 40);
        set("dex", 40);
        set("max_qi", 6000);
        set("max_jing", 5000);
        set("neili", 6000);
        set("max_neili", 6000);
        set("jiali", 200);
        set("combat_exp", 4000000);

        set_skill("force", 600);
        set_skill("kunlun-xinfa", 600);
        set_skill("liangyi-shengong", 600);
        set_skill("dodge", 600);
        set_skill("chuanyun-bu", 600);
        set_skill("strike", 600);
        set_skill("kunlun-zhang", 600);
        set_skill("hand", 600);
        set_skill("sanyin-shou", 600);
        set_skill("cuff", 600);
        set_skill("zhentian-quan", 600);
        set_skill("parry", 600);
        set_skill("sword", 600);
        set_skill("kunlun-jian", 600);
        set_skill("xunlei-jian", 600);
        set_skill("zhengliangyi-jian", 600);
        set_skill("qiankun-jian", 600);
        set_skill("throwing", 600);
        set_skill("kunlun-qifa", 600);
        set_skill("tanqin-jifa", 600);
        set_skill("jian-jia", 600);
        set_skill("qiuyue-lai", 600);
        set_skill("tieqin-yin", 600);
        set_skill("chess", 600);
        set_skill("literate", 600);
        set_skill("martial-cognize", 600);

        map_skill("force", "liangyi-shengong");
        map_skill("dodge", "chuanyun-bu");
        map_skill("parry", "zhengliangyi-jian");
        map_skill("sword", "qiankun-jian");
        map_skill("cuff", "zhentian-quan");
        map_skill("strike", "kunlun-zhang");
        map_skill("hand", "sanyin-shou");
        map_skill("throwing", "kunlun-qifa");
        map_skill("tanqin-jifa", "jian-jia");

        prepare_skill("strike", "kunlun-zhang");
        prepare_skill("hand", "sanyin-shou");

        create_family("昆侖派", 1, "祖師");

        set("inquiry", ([
                "絕招"      : "你要問什麼絕招？",
                "絕技"      : "你要問什麼絕技？",
                "乾坤勁"    : (: ask_skill1 :),
                "日月乾坤"  : (: ask_skill2 :),
                "逆轉乾坤"  : (: ask_skill3 :),
                "日入空山"  : (: ask_skill4 :),
                "兩極劍"    : (: ask_jian :),
        ]));

        set("chat_chance_combat", 100);
        set("chat_msg_combat", ({
                (: perform_action, "sword.ni" :),
                (: perform_action, "sword.riyue" :),
                (: perform_action, "strike.kong" :),
                (: exert_function, "recover" :),
                (: exert_function, "powerup" :),

        }) );

        set("master_ob",5);
        setup();

        set_temp("apply/damage", 100);
        set_temp("apply/unarmed_damage", 100);
        set_temp("apply/armor", 200);

        if (clonep())
        {
                ob = find_object(LIANGJI);
                if (! ob) ob = load_object(LIANGJI);
                if (! environment(ob))
                {
                        ob->move(this_object());
                        ob->wield();
                } else
                {
                        ob=new(WEAPON_DIR"changjian");
                        ob->move(this_object());
                        ob->wield();
                }
        }
        /*
        if (clonep())
        {
                ob=new(WEAPON_DIR"treasure/jiaowei-qin");
                if (ob->violate_unique())
                {
                        destruct(ob);
                        ob=new(WEAPON_DIR"changjian");
                }
                ob->move(this_object());
                set_temp("handing", carry_object(ob));
        }
        */
        carry_object("/d/kunlun/obj/pao2")->wear();
}

void attempt_apprentice(object me)
{
        if (! permit_recruit(me))
                return;

        if( query("shen", me)<10000 )
        {
                command("say 武學之道深久長遠，要成為當之無愧的大俠，德"
                        "行還在首位。");
                command("say 我那幾個後輩不成氣候，但卻希望"
                        + RANK_D->query_respect(me) + "你能夠多多注意。");
                return;
        }

        if( query("combat_exp", me)<400000 )
        {
                command("sigh");
                command("say 你的江湖經驗太淺，我就算收了你，恐怕你也難"
                        "有所作為。");
                return;
        }

        if (me->query_int() < 38)
        {
                command("say 高深的武功以及精深的技藝都需靈性極高的人才"
                        "能悟其真諦，不致背道而馳。");
                command("say 我看" + RANK_D->query_respect(me) + "還是"
                        "先回去多讀點書吧。");
                return;
        }

        if ((int)me->query_skill("liangyi-shengong", 1) < 100)
        {
                command("say 修習我的武功及劍法都需強大的內力為輔。");
                command("say 我看" + RANK_D->query_respect(me) + "是否"
                        "還應該先在本門的內功上多下點功夫？");
                return;
        }

        if ((int)me->query_skill("zhengliangyi-jian", 1) < 100)
        {
                command("say 本派的正兩儀劍法乃武林一絕，，我看"
                        + RANK_D->query_respect(me) + "對此還練"
                        "得不夠。");
                return;
        }

        command("say 看來你也是性情中人，我就教你一些琴劍棋的知識吧。");
        command("recruit "+query("id", me));
}

mixed ask_skill1()
{
        object me;

        me = this_player();

        if( query("can_perform/qiankun-jian/qian", me) )
                return "咦？這招你不是已經會了嗎？";

        if( query("family/family_name", me) != query("family/family_name") )
                return RANK_D->query_respect(me) + "和本派素無瓜葛，何出此言？";

        if (me->query_skill("qiankun-jian", 1) < 1)
                return "你連乾坤神劍都沒學，還談什麼絕招可言？";

        if( query("family/gongji", me)<300 )
                return "你對本派所作出的貢獻不夠，這一招我暫時還不能傳你。";

        if (me->query_skill("force") < 150)
                return "你的內功火候不足，學不了這一招！";

        if (me->query_skill("qiankun-jian", 1) < 100)
                return "你的乾坤神劍修為還不夠，自己下去練練再來吧。";

        message_vision(HIY "$n" HIY "微微一笑，轉身從弦琴上取出一本"
                       "劍經，指著其中一段對$N" HIY "細說\n良久，$N"
                       HIY "一邊聽一邊點頭。\n" NOR, me, this_object());
        command("nod");
        command("say 這是我早年所創的劍法，並不強勁，下去後稍加練習便成。");
        tell_object(me, HIC "你學會了「乾坤勁」。\n" NOR);

        if (me->can_improve_skill("sword"))
                me->improve_skill("sword", 1500000);
        if (me->can_improve_skill("qiankun-jian"))
                me->improve_skill("qiankun-jian", 1500000);
        me->improve_skill("martial-cognize", 1500000);
        set("can_perform/qiankun-jian/qian", 1, me);
        addn("family/gongji", -300, me);

        return 1;
}

mixed ask_skill2()
{
        object me;

        me = this_player();

        if( query("can_perform/qiankun-jian/riyue", me) )
                return "咦？這招你不是已經會了嗎？";

        if( query("family/family_name", me) != query("family/family_name") )
                return RANK_D->query_respect(me) + "和本派素無瓜葛，何出此言？";

        if (me->query_skill("qiankun-jian", 1) < 1)
                return "你連乾坤神劍都沒學，還談什麼絕招可言？";

        if( query("family/gongji", me)<1500 )
                return "你對本派所作出的貢獻不夠，這一招我暫時還不能傳你。";

        if (me->query_skill("force") < 220)
                return "你的內功火候不足，學不了這一招！";

        if (me->query_skill("qiankun-jian", 1) < 150)
                return "你的乾坤神劍修為還不夠，自己下去練練再來吧。";

        message_vision(HIY "$n" HIY "點了點頭，道：我將這招給你演示一"
                       "遍，你可看好了。$n" HIY "話\n音剛落，只見他身"
                       "形一展，以指作劍，指尖微顫，將乾坤劍法連環施而"
                       "\n出。$N" HIY "霎時只覺劍影重重，直看得眼花繚"
                       "亂。\n" NOR, me, this_object());
        command("nod");
        command("say 這便是日月乾坤，你看懂了多少？");
        tell_object(me, HIC "你學會了「日月乾坤」。\n" NOR);

        if (me->can_improve_skill("sword"))
                me->improve_skill("sword", 1500000);
        if (me->can_improve_skill("qiankun-jian"))
                me->improve_skill("qiankun-jian", 1500000);
        me->improve_skill("martial-cognize", 1500000);
        set("can_perform/qiankun-jian/riyue", 1, me);
        addn("family/gongji", -1500, me);

        return 1;
}

mixed ask_skill3()
{
        object me;

        me = this_player();

        if( query("can_perform/qiankun-jian/ni", me) )
                return "咦？這招你不是已經會了嗎？";

        if( query("family/family_name", me) != query("family/family_name") )
                return RANK_D->query_respect(me) + "和本派素無瓜葛，何出此言？";

        if (me->query_skill("qiankun-jian", 1) < 1)
                return "你連乾坤神劍都沒學，還談什麼絕招可言？";

        if( query("family/gongji", me)<1800 )
                return "你對本派所作出的貢獻不夠，這一招我暫時還不能傳你。";

        if( !query("can_perform/qiankun-jian/qian", me) )
                return "要學此招，必須先通曉「乾坤勁」的奧秘。";

        if (me->query_skill("force") < 300)
                return "你的內功火候不足，學不了這一招！";

        if (me->query_skill("qiankun-jian", 1) < 180)
                return "你的乾坤神劍修為還不夠，自己下去練練再來吧。";

        message_vision(HIW "$n" HIW "微笑道：既然你的劍術已經到達超凡的"
                       "境界，今日我就傳你這招。\n$n" HIW "說著“刷”的"
                       "一聲響，從背負的瑤琴底下抽出一柄長劍，縱身近\n前"
                       "，長劍陡然彎彎彈出，劍尖直刺$N" HIW "胸口，出招"
                       "之快真乃為任何劍法所\n不及。$N" HIW "頓時措手不"
                       "及，當場呆立，完全不知道該如何應招。$n" HIW "哈"
                       "\n哈一笑，收起長劍，說道：剛才這一招不是直刺，卻"
                       "是先聚內力，然後\n蓄勁彈出。這逆轉乾坤的奧秘便是"
                       "將乾坤劍法逆行施展即可。\n" NOR, me,
                       this_object());
        command("haha");
        command("say 這招乃是乾坤神劍的精髓，你下去後自己勤加練習吧。");
        tell_object(me, HIC "你學會了「逆轉乾坤」。\n" NOR);

        if (me->can_improve_skill("force"))
                me->improve_skill("force", 1500000);
        if (me->can_improve_skill("liangyi-shengong"))
                me->improve_skill("liangyi-shengong", 1500000);
        if (me->can_improve_skill("sword"))
                me->improve_skill("sword", 1500000);
        if (me->can_improve_skill("qiankun-jian"))
                me->improve_skill("qiankun-jian", 1500000);
        me->improve_skill("martial-cognize", 1500000);
        set("can_perform/qiankun-jian/ni", 1, me);
        addn("family/gongji", -1800, me);

        return 1;
}

mixed ask_skill4()
{
        object me;

        me = this_player();

        if( query("can_perform/kunlun-zhang/kong", me) )
                return "咦？這招你不是已經會了嗎？";

        if( query("family/family_name", me) != query("family/family_name") )
                return RANK_D->query_respect(me) + "和本派素無瓜葛，何出此言？";

        if (me->query_skill("kunlun-zhang", 1) < 1)
                return "你連昆侖掌法都沒學，還談什麼絕招可言？";

        if( query("family/gongji", me)<600 )
                return "你對本派所作出的貢獻不夠，這一招我暫時還不能傳你。";

        if (me->query_skill("force") < 150)
                return "你的內功火候不足，學不了這一招！";

        if (me->query_skill("kunlun-zhang", 1) < 120)
                return "你的昆侖掌法修為還不夠，自己下去練練再來吧。";

        message_vision(HIY "$n" HIY "點了點頭，將$N" HIY "招至"
                       "身邊，在耳旁低聲細說良久，$N" HIY "聽"
                       "後會心的\n一笑，看來大有所悟。\n" NOR, me,
                       this_object());
        command("nod");
        command("say 剛才我所說的便是日入空山的精要，你可記清了？");
        tell_object(me, HIC "你學會了「日入空山」。\n" NOR);

        if (me->can_improve_skill("strike"))
                me->improve_skill("strike", 1500000);
        if (me->can_improve_skill("kunlun-zhang"))
                me->improve_skill("kunlun-zhang", 1500000);
        me->improve_skill("martial-cognize", 1500000);
        set("can_perform/kunlun-zhang/kong", 1, me);
        addn("family/gongji", -600, me);

        return 1;
}

mixed ask_jian()
{
        object me;
        object ob;
        object owner;

        me = this_player();

        if( query("family/family_name", me) != "昆侖派" )
                return "閣下素來和本派並無淵源，何故來打聽我的隨身之物？";

        if( query("family/master_id", me) != query("id") )
                return "只有我的弟子才有資格使用我的隨身寶劍，閣下還是請回吧。";

        if (me->query_skill("qiankun-jian", 1) < 150)
                return "等你劍術大成之日，我自然不會吝惜佩劍，你再下去練練吧。";

        if (me->query_skill("tanqin-jifa", 1) < 120
           && me->query_skill("chess", 1) < 120)
                return "你跟了我這麼久，琴和棋卻是這般…唉。";

        if (query("family/gongji", me) < 500)
                return "你為師門所做的貢獻還不夠，這寶劍不能給你使用。";

        ob = find_object(LIANGJI);
        if (! ob) ob = load_object(LIANGJI);
        owner = environment(ob);

        while (owner)
        {
                if (owner->is_character() || ! environment(owner))
                        break;
                owner = environment(owner);
        }

        if (owner == me)
                return "我的佩劍不正是你拿著在用嗎，為何還反倒問起我來了？";

        if (objectp(owner) && owner != this_object())
        {
                if (! owner->is_character())
                        return "你來晚了，我的兩極劍現在並不在我手中。";

                if( query("family/family_name", owner) == "昆侖派" )
                        return "我的佩劍現在暫時是你同門"+query("name", owner)+
                               "在用，你要用就去找他吧。";
                else
                        return "我的那柄兩極劍現在落在了"+query("name", owner)+
                               "手中，你去把它找回來吧。";
        }
        ob->move(this_object());
        command("give liangji jian to "+query("id", me));
        addn("family/gongji", -500, me);

        ob = new("clone/weapon/changjian");
        ob->move(this_object());
        ob->wield();

        return "既然這樣，我這柄兩極劍你就暫時拿去用吧。";
}

int accept_object(object me, object ob)
{
        if (base_name(ob) != LIANGJI)
        {
                command("say 你給我這種東西幹什麼？");
                return 0;
        }

        if( query("family/master_id", me) != query("id") )
                command("say 多謝這位" + RANK_D->query_respect(me) +
                        "將我的寶劍交回。");
        else
                command("say 很好，很好！");
        destruct(ob);
        return 1;
}

void init()
{
        object ob;

        if (interactive(ob = this_player())
           && ! is_fighting() && random(10) < 3)
        {
                remove_call_out("greeting");
                call_out("greeting", 1, ob);
        }
}

void greeting(object ob)
{
        if (! ob || environment(ob) != environment())
                return;

        command("play jian-jia");
        return;
}
