#include <ansi.h>
#include "meizhuang.h"

#define YAOQIN    "/clone/lonely/yaoqin"
#define DONGXIAO  "/clone/lonely/dongxiao"

inherit NPC;
inherit F_MASTER;
inherit F_COAGENT;

mixed ask_skill1();
mixed ask_skill2();
mixed ask_skill3();
mixed ask_xiao();
mixed ask_qin();

void create()
{
        object ob;
        set_name("黃鐘公", ({ "huangzhong gong", "huang", "zhong", "huangzhong", "gong" }));
        set("long", @LONG
這就是梅莊四位莊主排行第一的黃鐘公。只見
他身穿一件幹幹凈凈的黃色長袍。雖然已年癒
六旬，但依然精神抖擻。他身材中等，面容和
藹可親。
LONG);
        set("title", "梅莊大莊主");
        set("nickname", HIR "梅莊四友" NOR);
        set("gender", "男性");
        set("age", 62);
        set("attitude", "peaceful");
        set("shen_type", 1);
        set("str", 38);
        set("int", 38);
        set("con", 38);
        set("dex", 38);

        set("max_qi", 6000);
        set("max_jing", 5000);
        set("neili", 6000);
        set("max_neili", 6000);
        set("jiali", 200);
        set("combat_exp", 2500000);

        set_skill("force", 260);
        set_skill("wuzheng-xinfa", 240);
        set_skill("xuantian-wujigong", 260);
        set_skill("dodge", 260);
        set_skill("meihua-zhuang", 260);
        set_skill("parry", 260);
        set_skill("sword", 260);
        set_skill("unarmed", 260);
        set_skill("qixian-wuxingjian", 260);
        set_skill("cuff", 240);
        set_skill("zuiquan-sanda", 240);
        set_skill("claw", 200);
        set_skill("longzhua-gong", 200);
        set_skill("strike", 240);
        set_skill("qingmang-zhang", 240);
        set_skill("literate", 240);
        set_skill("buddhism", 150);
        set_skill("tanqin-jifa", 300);
        set_skill("guangling-san", 300);
        set_skill("qingxin-pushan", 300);
        set_skill("martial-cognize", 240);

        set("no_teach", ([
                "longzhua-gong"  : "龍爪功乃昔日方証大師所授的少林"
                                   "絕學，老夫略之一二，並不授教。",
        ]));

        map_skill("force", "xuantian-wujigong");
        map_skill("dodge", "meihua-zhuang");
        map_skill("parry", "qixian-wuxingjian");
        map_skill("sword", "qixian-wuxingjian");
        map_skill("unarmed", "qixian-wuxingjian");
        map_skill("strike", "qingmang-zhang");
        map_skill("cuff", "zuiquan-sanda");
        map_skill("claw", "longzhua-gong");
        map_skill("tanqin-jifa", "guangling-san");

        prepare_skill("unarmed", "qixian-wuxingjian");

        create_family("梅莊", 1, "莊主");

        set("inquiry", ([
                "絕招"        : "你要問什麼絕招？",
                "絕技"        : "你要問什麼絕技？",
                "任我行"      : "任我行乃日月神教上代教主，不過已經失蹤很久了。",
                "東方不敗"    : "東方教主武功深不可測，天下無敵。",
                "日月神教"    : "我們梅莊四友和日月神教已無瓜葛，你提它作甚？",
                "廣陵散"      : "唉，傳說現在《廣陵散琴譜》竟已現世，不知是真是假。",
                "七弦無形音"  : (: ask_skill1 :),
                "七弦黃龍閃"  : (: ask_skill2 :),
                "七弦連環誅"  : (: ask_skill3 :),
                "綠玉洞簫"    : (: ask_xiao :),
                "白玉瑤琴"    : (: ask_qin :),
        ]));

        set("chat_chance_combat", 100);
        set("chat_msg_combat", ({
                (: perform_action, "sword.yin" :),
                (: perform_action, "sword.shan" :),
                (: perform_action, "sword.zhu" :),
                (: exert_function, "recover" :),
                (: exert_function, "powerup" :),

        }) );

        set("master_ob",4);
        setup();

        if (clonep())
        {
                ob = find_object(YAOQIN);
                if (! ob) ob = load_object(YAOQIN);
                if (! environment(ob))
                {
                        ob->move(this_object());
                        ob->wield();
                } else
                {
                        ob = new("/d/meizhuang/obj/qin");
                        ob->move(this_object());
                        ob->wield();
                }
        }
        carry_object("/d/quanzhen/npc/obj/greenrobe")->wear();
}

void attempt_apprentice(object me)
{
        string purename, name, new_name;

        if (! permit_recruit(me))
                return;

        if( query("family/family_name", me) && 
             query("family/family_name", me) == "日月神教" && 
             query("family/master_name", me) == "東方不敗" )
        {
                command("hmm");
                command("say 原來是東方教主的弟子，收你…這個倒沒什麼問題。");
                command("say 但是在收你之前，我得先考察一下你的能力。");
                set("move_party/日月神教─梅莊", 1, me);
        }

        if( query("combat_exp", me)<400000 )
        {
                command("sigh");
                command("say 你的江湖經驗太淺，還是先多鍛煉鍛煉再說吧。");
                return;
        }

        if ((int)me->query_skill("force") < 180)
        {
                command("say 學我七弦無形劍，內功非精純不可，你還是先多練練吧。");
                return;
        }

        if ((int)me->query_skill("sword", 1) < 100)
        {
                command("say 如要學我七弦無形劍，你還得在劍法上多下工夫。");
                return;
        }

        if ((int)me->query_skill("unarmed", 1) < 100)
        {
                command("say 如要學我七弦無形劍，你還得在拳腳上多下工夫。");
                return;
        }

        command("say 不錯，不錯！");
        command("say 我就收下你了，不過千萬別招惹是非，給我梅莊添亂。");
        command("recruit "+query("id", me));

        if( query("move_party/日月神教─梅莊", me) )
        {
                delete("move_party/日月神教─梅莊", me);
                command("say 現在你成為我梅莊中人，望你專心練武，別再去過問教中事物。");
        }
}

mixed ask_skill1()
{
        object me;

        me = this_player();

        if( query("can_perform/qixian-wuxingjian/yin", me) )
                return "你不是已經會了嗎？";

        if( query("family/family_name", me) != query("family/family_name") )
                return RANK_D->query_respect(me) + "和本教素無瓜葛，何出此言？";

        if (me->query_skill("qixian-wuxingjian", 1) < 1)
                return "你連七弦無形劍都沒學，何談此言？";

        if( query("family/gongji", me)<500 )
                return "你對本莊所作出的貢獻不夠，這一招我暫時還不能傳你。";

        if (me->query_skill("force") < 250)
                return "你的內功火候不足，學不了這一招！";

        if (me->query_skill("qixian-wuxingjian", 1) < 160)
                return "你的七弦無形劍還練得不到家，自己下去練練再來吧。";

        if (me->query_skill("tanqin-jifa", 1) < 120)
                return "你的琴技還不夠嫻熟，運用不了這一招。";

        message_vision(HIY "$n" HIY "微微一笑，轉身從書架上取出一本"
                       "琴譜，指著其中一段對$N" HIY "細說\n良久，$N"
                       HIY "一邊聽一邊點頭。\n" NOR, me, this_object());
        command("nod");
        command("say 這便是七弦無形音的奧義所在，你可明白了？");
        tell_object(me, HIC "你學會了「七弦無形音」。\n" NOR);

        if (me->can_improve_skill("unarmed"))
                me->improve_skill("unarmed", 1500000);
        if (me->can_improve_skill("sword"))
                me->improve_skill("sword", 1500000);
        if (me->can_improve_skill("force"))
                me->improve_skill("force", 1500000);
        if (me->can_improve_skill("qixian-wuxingjian"))
                me->improve_skill("qixian-wuxingjian", 1500000);
        me->improve_skill("martial-cognize", 1500000);
        set("can_perform/qixian-wuxingjian/yin", 1, me);
        addn("family/gongji", -500, me);

        return 1;
}

mixed ask_skill2()
{
        object me;

        me = this_player();

        if( query("can_perform/qixian-wuxingjian/shan", me) )
                return "你不是已經會了嗎？";

        if( query("family/family_name", me) != query("family/family_name") )
                return RANK_D->query_respect(me) + "和本教素無瓜葛，何出此言？";

        if (me->query_skill("qixian-wuxingjian", 1) < 1)
                return "你連七弦無形劍都沒學，何談此言？";

        if( query("family/gongji", me)<500 )
                return "你對本莊所作出的貢獻不夠，這一招我暫時還不能傳你。";

        if (me->query_skill("force") < 250)
                return "你的內功火候不足，學不了這一招！";

        if (me->query_skill("qixian-wuxingjian", 1) < 160)
                return "你的七弦無形劍還練得不到家，自己下去練練再來吧！";

        if (me->query_skill("tanqin-jifa", 1) < 120)
                return "你的琴技還不夠嫻熟，運用不了這一招。";

        message_vision(HIY "$n" HIY "點了點頭，將$N" HIY "招至"
                       "身邊，在耳旁低聲細說良久，$N" HIY "聽"
                       "後會心的\n一笑，看來大有所悟。\n" NOR, me,
                       this_object());
        command("nod");
        command("say 剛才我所說的便是七弦黃龍閃的精要，你可記清了？");
        tell_object(me, HIC "你學會了「七弦黃龍閃」。\n" NOR);

        if (me->can_improve_skill("unarmed"))
                me->improve_skill("unarmed", 1500000);
        if (me->can_improve_skill("sword"))
                me->improve_skill("sword", 1500000);
        if (me->can_improve_skill("force"))
                me->improve_skill("force", 1500000);
        if (me->can_improve_skill("qixian-wuxingjian"))
                me->improve_skill("qixian-wuxingjian", 1500000);
        me->improve_skill("martial-cognize", 1500000);
        set("can_perform/qixian-wuxingjian/shan", 1, me);
        addn("family/gongji", -500, me);

        return 1;
}

mixed ask_skill3()
{
        object me;

        me = this_player();

        if( query("can_perform/qixian-wuxingjian/zhu", me) )
                return "能教的我已經都教了，你自己下去多多練習吧。";

        if( query("family/family_name", me) != query("family/family_name") )
                return RANK_D->query_respect(me) + "和本教素無瓜葛，何出此言？";

        if (me->query_skill("qixian-wuxingjian", 1) < 1)
                return "你連七弦無形劍都沒學，何談此言？";

        if( query("family/gongji", me)<2000 )
                return "你對本莊所作出的貢獻不夠，這一招我暫時還不能傳你。";

        if (me->query_skill("force") < 300)
                return "你的內功火候不足，學不了這一招！";

        if (me->query_skill("qixian-wuxingjian", 1) < 180)
                return "你的七弦無形劍還練得不到家，自己下去練練再來吧！";

        if (me->query_skill("tanqin-jifa", 1) < 150)
                return "你的琴技還不夠嫻熟，運用不了這一招。";

        message_vision( HIW "$n" HIW "微微一笑，也不答話，轉身懷抱手中"
                       "瑤琴，放至身前，輕輕拂弄。頓時琴聲\n四起，時緩"
                       "時急，忽爾悄然無聲，忽爾錚然大響，過了一會，琴"
                       "聲越彈越急。$N" HIW "只\n聽得心神不定，呼吸不舒"
                       "，便在此時，琴音錚錚大響，琴音響一聲，$N" HIW
                       "便退出一步，\n琴音連響五下，便不由自主的退了五"
                       "步。$N" HIW "臉色雪白，定了定神，才道：“師父這"
                       "\n無形劍法當真厲害。這六音連續狠打猛擊，江湖中"
                       "又有誰能抵受得了？”$n" HIW "聽\n後哈哈一笑。\n"
                       NOR, me, this_object());
        command("haha");
        command("say 這招便是「六丁開山」神技，又稱七弦連環誅，你看明白了多少？");
        tell_object(me, HIC "你學會了「七弦連環誅」。\n" NOR);

        if (me->can_improve_skill("unarmed"))
                me->improve_skill("unarmed", 1500000);
        if (me->can_improve_skill("sword"))
                me->improve_skill("sword", 1500000);
        if (me->can_improve_skill("force"))
                me->improve_skill("force", 1500000);
        if (me->can_improve_skill("qixian-wuxingjian"))
                me->improve_skill("qixian-wuxingjian", 1500000);
        me->improve_skill("martial-cognize", 1500000);
        set("can_perform/qixian-wuxingjian/zhu", 1, me);
        addn("family/gongji", -2000, me);

        return 1;
}

mixed ask_xiao()
{
        object me;
        object ob;
        object owner;

        me = this_player();

        if( query("family/family_name", me) != "梅莊" )
                return "你和本莊素無淵源，打聽它幹什麼？";

        if( query("family/master_id", me) != query("id") )
                return "只有我的弟子才配使用這綠玉洞簫。";

        ob = find_object(DONGXIAO);
        if (! ob) ob = load_object(DONGXIAO);
        owner = environment(ob);
        while (owner)
        {
                if (owner->is_character() || ! environment(owner))
                        break;
                owner = environment(owner);
        }

        if (owner == me)
                return "現在這綠玉洞簫不正是你拿著嗎，為何無故來消遣老夫？";

        if (objectp(owner) && owner != this_object())
        {
                if (! owner->is_character())
                        return "你來晚了一步，我已經把這綠玉洞簫借給你同門師兄用去了。";

                if( query("family/family_name", owner) == "梅莊" )
                        return "綠玉洞簫現在暫時是你同門"+query("name", owner)+
                               "在用，你要用就去找他吧。";
                else
                        return "我的綠玉洞簫現在落在了"+query("name", owner)+
                               "手中，你去把它找回來吧！";
        }

        ob->move(this_object());
        message_vision(HIC "$N" HIC "微微一笑，道：“好，我這就將我珍藏已久的綠玉洞簫借給"
                       "你。”\n" NOR, this_object(), me);
        command("givelvyudongxiaoto"+query("id", me));
        return 1;
}

mixed ask_qin()
{
        object me;
        object ob;

        me = this_player();

        if( query("family/family_name", me) != "梅莊" )
                return "你和本莊素無淵源，打聽它幹什麼？";

        if( query("family/master_id", me) != query("id") )
                return "只有我的弟子才配使用這白玉瑤琴。";

        if (me->query_skill("qixian-wuxingjian", 1) < 150)
                return "你還是下去將你的七弦無形劍練練再來吧。";

        if (me->query_skill("tanqin-jifa", 1) < 150)
                return "你連琴都彈不好，幹嘛還要用我這白玉瑤琴？";

        if (present("baiyu yaoqin", me))
                return "現在白玉瑤琴不就在你身上嗎，為何無故來消遣老夫？";

        ob = present("baiyu yaoqin", this_object());

        if (! objectp(ob))
                return "現在白玉瑤琴已經不在我這裡了。";

        ob->move(this_object());
        command("givebaiyuyaoqinto"+query("id", me));

        ob = new("/d/meizhuang/obj/qin");
        ob->move(this_object());
        ob->wield();

        return "很好，既然這樣，我這白玉瑤琴你就暫時拿去用吧。";
}

int accept_object(object me, object ob)
{
        if (base_name(ob) != DONGXIAO
           && base_name(ob) != YAOQIN)
        {
                command("say 你給我這種東西幹什麼？");
                return 0;
        }

        if( query("family/master_id", me) != query("id") )
                command("say 多謝這位" + RANK_D->query_respect(me) +
                        "將我的寶貝交回。");
        else
                command("say 很好，很好！");
        destruct(ob);
        return 1;
}
