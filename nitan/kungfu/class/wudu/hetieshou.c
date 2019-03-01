#include <ansi.h>
#include "wudu.h"

#define SHEYING     "/clone/lonely/sheying"
#define JINWUGOU    "/clone/lonely/jinwugou"
#define ZHUSUO      "/clone/lonely/zhusuo"
#define DUJING      "/clone/lonely/book/dujing3"

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
mixed ask_gou();
mixed ask_suo();
mixed ask_she();
mixed ask_jing();
int ask_me();
string ask_ling();
void create()
{
        object ob, ob2;
        set_name("何鐵手", ({ "he tieshou", "he", "tieshou" }));
        set("nickname", HIR "五毒仙子" NOR);
        set("long",@LONG
你對面的是一個一身粉紅紗裙，笑靨如花的少女。
她長得肌膚雪白，眉目如畫，赤著一雙白嫩的秀
足，手腳上都戴著閃閃的金鐲。誰能想到她就是
五毒教的教主何鐵手，武林人士提起她無不膽顫
心驚。
LONG);
        set("title", "五毒教教主");
        set("gender", "女性");
        set("age", 25);
        set("attitude", "friendly");
        set("shen_type", -1);
        set("str", 30);
        set("int", 30);
        set("con", 30);
        set("dex", 30);
        set("per", 30);

        set("max_qi", 5000);
        set("max_jing", 4000);
        set("neili", 5500);
        set("max_neili", 5500);
        set("jiali", 200);
        set("combat_exp", 2500000);
        set("score", 10000);

        set_skill("force", 600);
        set_skill("wudu-shengong", 600);
        set_skill("xiuluo-yinshagong", 600);
        set_skill("dodge", 600);
        set_skill("wudu-yanluobu", 600);
        set_skill("strike", 600);
           set_skill("tianchan-zhang", 600);
        set_skill("hand", 600);
        set_skill("qianzhu-wandushou", 600);
        set_skill("claw", 600);
        set_skill("wusheng-zhao", 600);
        set_skill("parry", 600);
        set_skill("sword", 600);
        set_skill("jinwu-goufa", 600);
        set_skill("whip", 600);
        set_skill("ruanhong-zhusuo", 600);
        set_skill("xiewei-bian", 600);
        set_skill("throwing", 600);
        set_skill("hansha-sheying", 600);
        set_skill("literate", 600);
        set_skill("poison", 600);
        set_skill("wudu-qishu", 600 );
        set_skill("martial-cognize", 600);
        set_skill("wudu-jing", 600);

        map_skill("force", "xiuluo-yinshagong");
        map_skill("dodge", "wudu-yanluobu");
        map_skill("strike", "tianchan-zhang");
        map_skill("hand", "qianzhu-wandushou");
        map_skill("claw", "wusheng-zhao");
        map_skill("throwing", "hansha-sheying");
        map_skill("parry", "jinwu-goufa");
        map_skill("sword", "jinwu-goufa");
        map_skill("whip", "ruanhong-zhusuo");
        map_skill("poison", "wudu-qishu");

        prepare_skill("claw", "wusheng-zhao");
        prepare_skill("strike", "tianchan-zhang");

        create_family("五毒教", 11, "教主");

        set("chat_chance_combat", 120);
        set("chat_msg_combat", ({
                (: perform_action, "sword.duo" :),
                (: perform_action, "whip.teng" :),
                (: perform_action, "whip.pan" :),
                (: perform_action, "whip.bohu" :),
                (: perform_action, "whip.suo" :),
                (: perform_action, "claw.lian" :),
                (: perform_action, "strike.chan" :),
                (: exert_function, "recover" :),
                (: exert_function, "powerup" :),
        }) );

        set_temp("apply/damage", 100);
        set_temp("apply/unarmed_damage", 100);
        set_temp("apply/armor", 200);

        setup();

        set("inquiry", ([
                "金蜈鉤"   : (: ask_gou :),
                "軟紅蛛索" : (: ask_suo :),
                "含沙射影" : (: ask_she :),
                "毒經"     : "你是要毒經上篇、中篇還是下篇？",
                "上篇"     : "毒經上篇你去問煉毒室的道人要吧。",
                "毒經上篇" : "毒經上篇你去問煉毒室的道人要吧。",
                "中篇"     : "毒經中篇在齊長老手中，你去問他要吧。",
                "毒經中篇" : "毒經中篇在齊長老手中，你去問他要吧。",
                "下篇"     : (: ask_jing :),
                "毒經下篇" : (: ask_jing :),
                "絕招"     : "你要問什麼絕招？",
                "絕技"     : "你要問什麼絕技？",
                //"萬毒窟"    : (: ask_me :),
                "五毒令"    : (: ask_ling :),
                "騰蛇訣"   : "這一招你去找齊長老學吧。",
                "盤鷹訣"   : (: ask_skill1 :),
                "搏虎訣"   : (: ask_skill2 :),
                "鎖龍訣"   : (: ask_skill3 :),
                "金鉤奪魄" : (: ask_skill4 :),
                "無影針"   : (: ask_skill5 :),
                "萬毒穿心" : (: ask_skill6 :),
        ]));

        if (clonep())
        {
                ob = find_object(ZHUSUO);
                ob2 = find_object(SHEYING);

                if (! ob) ob = load_object(ZHUSUO);
                if (! environment(ob))
                {
                        ob->move(this_object());
                        ob->wield();
                } else
                {
                        ob = find_object(JINWUGOU);
                        if (! ob) ob = load_object(JINWUGOU);
                        if (! environment(ob))
                        {
                                ob->move(this_object());
                                ob->wield();
                        } else
                        {
                                ob = new("/clone/weapon/changbian");
                                ob->move(this_object());
                                ob->wield();
                        }
                }
                if (! ob2) ob2 = load_object(SHEYING);
                if (! environment(ob2))
                {
                        ob2->move(this_object());
                        ob2->wear();
                }
        }
        carry_object("/clone/cloth/moon-dress")->wear();
}

void init()
{
        add_action("do_show", "show");
}

void attempt_apprentice(object ob)
{
        if (! permit_recruit(ob))
                return;

        if( query("shen", ob)>-1000 )
        {
                command("say 我越看你越象六扇門派來的臥底。");
                return;
        }

        if( query("shen", ob)>-50000 )
        {
                command("say 像你這樣心慈手軟的人是幹不成大事的！");
                return;
        }

        if( query("combat_exp", ob)<350000 )
        {
                command("say 你現在經驗尚淺，不能領會高深的武功，還是先去增長點經驗吧。");
                return;
        }

        if ((int)ob->query_skill("wudu-shengong", 1) < 120)
        {
                command("say 你的五毒心法還學的不夠啊。");
                return;
        }

        if ((int)ob->query_skill("wudu-qishu", 1) < 120)
        {
                command("say 你把本門的施毒絕學鑽研透了再來找我吧。");
                return;
        }

        command("say 好吧，既然如此本姑娘就收下你這個徒弟。");
        command("recruit "+query("id", ob));
        set("title", "五毒教長老", ob);
        return;
}

mixed ask_gou()
{
        object me;
        object ob;
        object owner;

        me = this_player();
        if (me->is_good())
        {
                if( query("family/family_name", me) == "五毒教" )
                        message_vision(CYN "$N" CYN "冷哼一聲，對$n" CYN "道："
                                       "“你身為我五毒教弟子，反而學起假仁假義"
                                       "來了，居然還有臉問我要金鉤？”\n" NOR,
                                       this_object(), me);
                else
                        message_vision(CYN "$N" CYN "冷笑一聲，對$n" CYN "說道"
                                       "：“你是什麼人？居然敢在我面前打聽這個"
                                       "！”\n" NOR,
                                       this_object(), me);
                return 1;
        }

        if( query("family/family_name", me) != "五毒教" )
                return "你不是我們五毒教的，打聽它幹什麼？";

        if( query("family/master_id", me) != query("id") )
                return "只有我的弟子才能用金蜈鉤，你拿去用只會替我丟臉。";

        if( query("shen", me)>-35000 )
                return "你這樣心慈手軟，這金鉤你不用也罷。";

        if (me->query_skill("jinwu-goufa", 1) < 120)
                return "你連金蜈鉤法都沒學好，就算用金鉤也是白搭。";

        ob = find_object(JINWUGOU);
        if (! ob) ob = load_object(JINWUGOU);
        owner = environment(ob);
        while (owner)
        {
                if (owner->is_character() || ! environment(owner))
                        break;
                owner = environment(owner);
        }

        if (owner == me)
                return "嗯？金蜈鉤現在不是你拿著在用嗎？";

        if (objectp(owner) && owner != this_object())
        {
                if (! owner->is_character())
                        return "你來晚了一步，我已經把金蜈鉤借給你同門師兄弟用去了。";

                if( query("family/family_name", owner) == "五毒教" )
                        return "金蜈鉤現在暫時是你同門師兄弟"+query("name", owner)+
                               "在用，你要用就去找他吧。";
                else
                        return "本門的金蜈鉤現在落在"+query("name", owner)+
                               "手中，你去把它搶回來吧！";
        }

        ob->move(this_object());

        ob = new("clone/weapon/changbian");
        ob->move(this_object());
        ob->wield();

        message_vision(CYN "$N" CYN "微微一笑，道：“這柄金蜈鉤你就"
                       "拿去，讓那些正派人士嘗嘗咱五毒教的厲害！”\n" NOR,
                       this_object(), me);
          command("give jinwu gou to "+query("id", me));
        return 1;
}

mixed ask_suo()
{
        object me;
        object ob;
        object owner;

        me = this_player();
        if (me->is_good())
        {
                if( query("family/family_name", me) == "五毒教" )
                        message_vision(CYN "$N" CYN "冷哼一聲，對$n" CYN "道："
                                       "“你身為我五毒教弟子，反而學起假仁假義"
                                       "來了，居然還有臉問我要軟紅蛛索？”\n" NOR,
                                       this_object(), me);
                else
                        message_vision(CYN "$N" CYN "冷笑一聲，對$n" CYN "說道"
                                       "：“你是什麼人？居然敢在我面前打聽這個"
                                       "！”\n" NOR,
                                       this_object(), me);
                return 1;
        }

        if( query("family/family_name", me) != "五毒教" )
                return "你不是我們五毒教的，打聽它幹什麼？";

        if( query("family/master_id", me) != query("id") )
                return "只有我的弟子才能用軟紅蛛索，你拿去用只會替我丟臉。";

        if( query("shen", me)>-35000 )
                return "你這樣心慈手軟，這蛛索你不用也罷。";

        if (me->query_skill("ruanhong-zhusuo", 1) < 150)
                return "你連軟紅蛛索都沒學好，就算用蛛索也是白搭。";

        ob = find_object(ZHUSUO);
        if (! ob) ob = load_object(ZHUSUO);
        owner = environment(ob);
        while (owner)
        {
                if (owner->is_character() || ! environment(owner))
                        break;
                owner = environment(owner);
        }

        if (owner == me)
                return "嗯？軟紅蛛索現在不是你拿著在用嗎？";

        if (objectp(owner) && owner != this_object())
        {
                if (! owner->is_character())
                        return "你來晚了一步，我已經把軟紅蛛索借給你同門師兄弟用去了。";

                if( query("family/family_name", owner) == "五毒教" )
                        return "軟紅蛛索現在暫時是你同門師兄弟"+query("name", owner)+
                               "在用，你要用就去找他吧。";
                else
                        return "本門的軟紅蛛索現在落在"+query("name", owner)+
                               "手中，你去把它搶回來吧！";
        }

        ob->move(this_object());

        ob = new("/clone/weapon/changbian");
        ob->move(this_object());
        ob->wield();

        message_vision(CYN "$N" CYN "微微一笑，道：“這根軟紅蛛索你就"
                       "拿去，讓那些正派人士嘗嘗咱五毒教的厲害！”\n" NOR,
                       this_object(), me);
          command("give ruanhong zhusuo to "+query("id", me));
        return 1;
}

mixed ask_she()
{
        object me;
        object ob;
        object owner;

        me = this_player();
        if (me->is_good())
        {
                if( query("family/family_name", me) == "五毒教" )
                        message_vision(CYN "$N" CYN "冷哼一聲，對$n" CYN "道："
                                       "“你身為我五毒教弟子，反而學起假仁假義"
                                       "來了，居然還有臉問我要含沙射影？”\n" NOR,
                                       this_object(), me);
                else
                        message_vision(CYN "$N" CYN "冷笑一聲，對$n" CYN "說道"
                                       "：“你是什麼人？居然敢在我面前打聽這個"
                                       "！”\n" NOR,
                                       this_object(), me);
                return 1;
        }

        if( query("family/family_name", me) != "五毒教" )
                return "你不是我們五毒教的，打聽它幹什麼？";

        if( query("shen", me)>-10000 )
                return "你這樣心慈手軟，這含沙射影你不用也罷。";

        if (me->query_skill("hansha-sheying", 1) < 50)
                return "你這門暗器手法太差，用不好還會傷及自身。";

        //ob = new("/d/wudu/npc/obj/hanshasheying");
        ob = find_object(SHEYING);
        if (! ob) ob = load_object(SHEYING);
        owner = environment(ob);
        while (owner)
        {
                if (owner->is_character() || ! environment(owner))
                        break;
                owner = environment(owner);
        }

        if (owner == me)
                return "嗯？含沙射影現在不是你拿著在用嗎？";

        if (objectp(owner) && owner != this_object())
        {
                if (! owner->is_character())
                        return "含沙射影現在不在我這裡。";

                if( query("family/family_name", owner) == "五毒教" )
                        return "含沙射影現在暫時是你同門"+query("name", owner)+
                               "在用，你要用就去找他吧。";
                else
                        return "我的含沙射影現在落在"+query("name", owner)+
                               "手中，你去把它搶回來吧！";
        }
        ob->move(this_object());

        message_vision(CYN "$N" CYN "微微一笑，道：含沙射影你拿去吧，叫他們嘗嘗我"
                       "們五毒教的厲害！\n" NOR, this_object(), me);
          command("give hansha sheying to "+query("id", me));
        command("whisper"+query("id", me)+"這含沙射影裡的毒針用完了，可以拿"
                "(show)回來讓我給你裝。");
        return 1;
}

mixed ask_skill1()
{
        object me;

        me = this_player();

        if( query("can_perform/ruanhong-zhusuo/panying", me) )
                return "你不是已經會了嗎？";

        if( query("family/family_name", me) != query("family/family_name") )
                return RANK_D->query_respect(me) + "和本教素無瓜葛，何出此言？";

        if (me->query_skill("ruanhong-zhusuo", 1) < 1)
                return "你連軟紅蛛索都沒學，何談此言？";

        if( query("family/gongji", me)<300 )
                return "你在教中所作的貢獻還不夠，這招我不忙傳你。";

        if( query("shen", me)>-30000 )
                return "心慈手軟的人永遠成不了大器，這招你不學也罷！";

        if (me->query_skill("ruanhong-zhusuo", 1) < 130)
                return "你的軟紅蛛索還練得不到家，自己下去練練再來吧！";

        message_sort(HIY "\n$n" HIY "點了點頭，從腰間取下長索，手腕輕輕一抖，頓"
                     "時鞭影重重，完全籠罩$N" HIY "的四周，直看得$N" HIY "目瞪口"
                     "呆。\n\n" NOR, me, this_object());

        command("nod");
        command("say 這一招便是軟紅蛛索絕技盤鷹訣，你可看明白了？");
        tell_object(me, HIC "你學會了「盤鷹訣」。\n" NOR);

        if (me->can_improve_skill("whip"))
                me->improve_skill("whip", 1500000);
        if (me->can_improve_skill("ruanhong-zhusuo"))
                me->improve_skill("ruanhong-zhusuo", 1500000);
        me->improve_skill("martial-cognize", 1500000);
        set("can_perform/ruanhong-zhusuo/panying", 1, me);
        addn("family/gongji", -300, me);

        return 1;
}

mixed ask_skill2()
{
        object me;

        me = this_player();

        if( query("can_perform/ruanhong-zhusuo/bohu", me) )
                return "你不是已經會了嗎？";

        if( query("family/family_name", me) != query("family/family_name") )
                return RANK_D->query_respect(me) + "和本教素無瓜葛，何出此言？";

        if (me->query_skill("ruanhong-zhusuo", 1) < 1)
                return "你連軟紅蛛索都沒學，何談此言？";

        if( query("family/gongji", me)<1300 )
                return "你在教中所作的貢獻還不夠，這招我不忙傳你。";

        if( query("shen", me)>-50000 )
                return "心慈手軟的人永遠成不了大器，這招你不學也罷！";

        if (me->query_skill("ruanhong-zhusuo", 1) < 160)
                return "你的軟紅蛛索還練得不到家，自己下去練練再來吧！";

        message_sort(HIY "\n$n" HIY "點了點頭，道：“本姑娘今天便傳你這招，你可"
                     "看好了！”$n" HIY "說罷，從腰間取下長索，一聲嬌喝，手中長"
                     "索狂舞，漫天鞭影頓時幻作無數小圈，舖天蓋地罩向$N" HIY "。"
                     "\n\n" NOR, me, this_object());

        command("nod");
        command("say 這一招便是軟紅蛛索絕技搏虎訣，你可看明白了？");
        tell_object(me, HIC "你學會了「搏虎訣」。\n" NOR);

        if (me->can_improve_skill("whip"))
                me->improve_skill("whip", 1500000);
        if (me->can_improve_skill("ruanhong-zhusuo"))
                me->improve_skill("ruanhong-zhusuo", 1500000);
        me->improve_skill("martial-cognize", 1500000);
        set("can_perform/ruanhong-zhusuo/bohu", 1, me);
        addn("family/gongji", -1300, me);

        return 1;
}

mixed ask_skill3()
{
        object me;

        me = this_player();

        if( query("can_perform/ruanhong-zhusuo/suolong", me) )
                return "你不是已經會了嗎？";

        if( query("family/family_name", me) != query("family/family_name") )
                return RANK_D->query_respect(me) + "和本教素無瓜葛，何出此言？";

        if (me->query_skill("ruanhong-zhusuo", 1) < 1)
                return "你連軟紅蛛索都沒學，何談此言？";

        if( query("shen", me)>-80000 )
                return "心慈手軟的人永遠成不了大器，這招你不學也罷！";

        if( query("family/gongji", me)<1500 )
                return "你在教中所作的貢獻還不夠，這招我不忙傳你。";

        if (me->query_skill("ruanhong-zhusuo", 1) < 160)
                return "你的軟紅蛛索還練得不到家，自己下去練練再來吧！";

        message_sort(HIY "\n$n" HIY "對$N" HIY "讚許地點了點頭，道：“既然你如"
                     "此有心，本姑娘就再傳你這招！”說完$n" HIY "招了招手，$N"
                     HIY "連忙湊上前去，只見$n" HIY "輕聲在$N" HIY "說了些話，"
                     "接著手中長索一抖，登時幻出漫天鞭影，宛如蛟龍通天，無數鞭"
                     "影一齊向四面八方席卷而去！\n\n" NOR, me, this_object());

        command("sweat");
        command("nod");
        command("say 這一招便是軟紅蛛索絕技鎖龍訣，你下去需勤加練習！");
        tell_object(me, HIC "你學會了「鎖龍訣」。\n" NOR);

        if (me->can_improve_skill("whip"))
                me->improve_skill("whip", 1500000);
        if (me->can_improve_skill("ruanhong-zhusuo"))
                me->improve_skill("ruanhong-zhusuo", 1500000);
        me->improve_skill("martial-cognize", 1500000);
        set("can_perform/ruanhong-zhusuo/suolong", 1, me);
        addn("family/gongji", -1500, me);

        return 1;
}

mixed ask_skill4()
{
        object me;

        me = this_player();
        if( query("can_perform/jinwu-goufa/duo", me) )
                return "這招我已經教過你了，還是自己下去多多練習吧！";

        if( query("family/family_name", me) != query("family/family_name") )
                return RANK_D->query_respect(me) + "和本教素無瓜葛，何出此言？";

        if (me->query_skill("jinwu-goufa", 1) < 1)
                return "你連金蜈鉤法都沒學，何談此言？";

        if( query("family/gongji", me)<1300 )
                return "你在教中所作的貢獻還不夠，這招我不忙傳你。";

        if( query("shen", me)>-80000 )
                return "哼！你這樣心慈手軟能幹成什麼事？這招你不學也罷！";

        if (me->query_skill("jinwu-goufa", 1) < 160)
                return "你的金蜈鉤法還練得不到家，自己下去練練再來吧！";

        message_sort(HIY "\n$n" HIY "微微點了點頭，在$N" HIY "耳邊輕聲說了些話"
                     "，一邊說還一邊比劃著些什麼。如此這般，過了良久……\n\n"
                     NOR, me, this_object());

        command("say 剛才那些便是這招的口訣和練功的要領，你可要記牢了。");
        command("nod");
        command("say 這招金鉤奪魄比較難練，你自己下來後要多加研究。");
        tell_object(me, HIC "你學會了「金鉤奪魄」。\n" NOR);
        if (me->can_improve_skill("sword"))
                me->improve_skill("sword", 1500000);
        if (me->can_improve_skill("jinwu-goufa"))
                me->improve_skill("jinwu-goufa", 1500000);
        me->improve_skill("martial-cognize", 1500000);
        set("can_perform/jinwu-goufa/duo", 1, me);
        addn("family/gongji", -1300, me);

        return 1;
}

mixed ask_skill5()
{
        object me;

        me = this_player();
        if( query("can_perform/hansha-sheying/zhen", me) )
                return "這招我不是已經教過你了嗎？";

        if( query("family/family_name", me) != query("family/family_name") )
                return RANK_D->query_respect(me) + "和本教素無瓜葛，何出此言？";

        if (me->query_skill("hansha-sheying", 1) < 1)
                return "你連含沙射影都沒學，何談此言？";

        if( query("family/gongji", me)<300 )
                return "你在教中所作的貢獻還不夠，這招我不忙傳你。";

        if( query("shen", me)>-80000 )
                return "哼！你這樣心慈手軟能幹成什麼事？這招你不學也罷！";

        if (me->query_skill("hansha-sheying", 1) < 120)
                return "你的含沙射影還練得不到家，自己下去練練再來吧！";

        message_sort(HIY "\n$n" HIY "微微一笑，伸手將$N" HIY "招到面前，在$N"
                     HIY "耳邊輕聲嘀咕了些話。$N" HIY "聽了半天，突然間不由會"
                     "心的一笑，看來大有所悟。\n\n" NOR, me, this_object());

        command("nod");
        command("say 這招並不復雜，但是用來偷襲和暗算敵人卻很有效，你多練練吧！");
        tell_object(me, HIC "你學會了「無影針」。\n" NOR);
        if (me->can_improve_skill("throwing"))
                me->improve_skill("throwing", 1500000);
        if (me->can_improve_skill("hansha-sheying"))
                me->improve_skill("hansha-sheying", 1500000);
        me->improve_skill("martial-cognize", 1500000);
        set("can_perform/hansha-sheying/zhen", 1, me);
        addn("family/gongji", -300, me);
        return 1;
}

mixed ask_skill6()
{
        object me;

        me = this_player();
        if( query("can_perform/qianzhu-wandushou/chuan", me) )
                return "這招我不是已經教過你了嗎？";

        if( query("family/family_name", me) != query("family/family_name") )
                return RANK_D->query_respect(me) + "和本教素無瓜葛，何出此言？";

        if( !query("reborn/times", me) )
                return "你還未歷經劫難，本門絕技可不能隨便傳給你。";

        if( query("family/gongji", me)<2000 )
                return "你在教中所作的貢獻還不夠，這招我不忙傳你。";

        if( query("shen", me)>-100000 )
                return "哼！你這樣心慈手軟能幹成什麼事？這招你不學也罷！";

        if (me->query_skill("qianzhu-wandushou", 1) < 800)
                return "你的千蛛萬毒手還練得不到家，自己下去練練再來吧！";

        message_sort(HIY "\n$n" HIY "微微一笑，伸手將$N" HIY "招到面前，在$N"
                     HIY "耳邊輕聲嘀咕了些話。$N" HIY "聽了半天，突然間不由會"
                     "心的一笑，看來大有所悟。\n\n" NOR, me, this_object());

        command("nod");
        command("say 這招可是本門秘傳，極為博大精深，你下去後可得多練習練習！");
        tell_object(me, HIC "你學會了「萬毒穿心」。\n" NOR);
        if (me->can_improve_skill("qianzhu-wandushou"))
                me->improve_skill("qianzhu-wandushou", 1500000);
        if (me->can_improve_skill("hand"))
                me->improve_skill("qianzhu-wandushou", 1500000);
        me->improve_skill("martial-cognize", 1500000);
        set("can_perform/qianzhu-wandushou/chuan", 1, me);
        addn("family/gongji", -2000, me);
        return 1;
}

int accept_object(object me, object ob)
{
        int r;
        if (r = ::accept_object(me, ob))
                return r;

        if (base_name(ob) != JINWUGOU
        && base_name(ob) != ZHUSUO)
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

mixed ask_jing()
{
        object me;
        object ob;
        object owner;

        me = this_player();

        if( query("family/family_name", me) != "五毒教" )
                return "你是誰？我認識你麼？";

        if( query("shen", me)>-30000 )
                return "你這人心腸那麼好，又去學毒做甚？";

        if( query("combat_exp", me)<150000 )
                return "你現在經驗太淺，不用忙著去閱讀毒經。";

        if (me->query_skill("wudu-qishu", 1) > 149)
                return "你對本門的毒技已經通曉得比較透徹了，還是自己多研究吧。";

        ob = find_object(DUJING);
        if (! ob) ob = load_object(DUJING);
        owner = environment(ob);
        while (owner)
        {
                if (owner->is_character() || ! environment(owner))
                        break;
                owner = environment(owner);
        }

        if (owner == me)
                return "不就是你拿著麼？怎麼反倒問我來了？";

        if (objectp(owner) && owner != this_object())
        {
                if (! owner->is_character())
                        return "…嗯…毒經下篇現在不在我手裡。";

                if( query("family/family_name", owner) == "五毒教" )
                        return "毒經現在是你同門"+query("name", owner)+
                               "在看，去找他吧。";
                else
                        return "我教的毒經現落在"+query("name", owner)+
                               "的手中，你去把它奪回來吧！";
        }
        ob->move(this_object());
        message_vision(CYN "$N" CYN "點頭道：你拿去看吧，若有不解之處"
                       "可以來問我。\n" NOR, this_object(), me);
          command("give du jing3 to "+query("id", me));
        return 1;
}

int do_show(string arg)
{
        object ob;
        object me;
        int n;

        if (! arg)
                return notify_fail("你要亮出什麼東西？\n");

        me = this_player();

        if (! objectp(ob = present(arg, me)))
                return notify_fail("你身上沒有這種東西。\n");

        if( query("family/family_name", me) != "五毒教" )
                return notify_fail(CYN "何鐵手冷冷望了你一眼，沒理你。\n" NOR);

        if( query("id", ob) != "hanshasheying" )
                return notify_fail(CYN "何鐵手皺了皺眉頭，說道：你給我看這個"
                                   "幹嘛？\n" NOR);

        if( query("equipped", ob) )
                return notify_fail(CYN "何鐵手說道：你不把含沙射影脫下來，叫"
                                   "我怎麼幫你裝針？\n" NOR);

        if( query("zhen", ob)>5 )
                return notify_fail(CYN "何鐵手說道：含沙射影裡的毒針用了一半"
                                   "還不到，你瞎急什麼！\n" NOR);

        message_vision(HIC "\n何鐵手微微一笑，從$N" HIC "手中接過含沙射影，輕"
                       "輕撥弄幾下，又還給了$N" HIC "。\n\n" NOR, me);

        command("say 行了，含沙射影裡的毒針已經補滿了。");
        set("zhen", 10, ob);
        return 1;
}

string ask_ling()
{
        mapping fam;
        object *allob,env,ob,me=this_player();
        string *sname;
        int i, count, here = 0;

        if (query("ling_count") < 1)
                return "你來晚了，五毒令別的教眾正在用呢。\n";
        if( !(fam=query("family", me)) || fam["family_name"] != "五毒教" )
                return RANK_D->query_respect(me) + "與本派素無來往，不知此話從何談起？";

        if( query("duchong_cun", me) == 1 )
                return "你的毒蟲不是在毒叟那好好的麼？";

        env = environment(me);
        allob = all_inventory(env);
        count = 0;
        for(i=0; i<sizeof(allob); i++)
                if(allob[i] != me && allob[i]!=this_object() )
                {
                        if( query("host_id", allob[i]) == query("id", me) )
                        {
                                here = 1;
                        }
                        count++;
                }
        if (here == 1)
                return "你的毒蟲不是帶在身邊了嗎！？";
        if( query("duchong_cun", me) == 0 && count >= 1 )
                return "現在人多眼雜，你回頭再來吧！";

        if( !query("du/id", me) )
                return "你沒養毒蟲吧！";

        addn("ling_count",-1);
        ob = new(__DIR__"obj/wudu-ling");
        ob->move(me);
        message_vision("$N獲得一面五毒令。\n",me);
        remove_call_out ("give_wuduling");
        call_out ("give_wuduling", 600); // 10 分鐘

        return "好吧，憑這面五毒令，你可去要回你的毒蟲。";

}

void unconcious()
{
        die();
}
