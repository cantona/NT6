// renwoxing.c
// Update by haiyan

#include <ansi.h>
#include "riyue.h"

inherit NPC;
inherit F_MASTER;
inherit F_QUESTER;

int ask_bijian();
string ask_jing();
mixed no_learn();
mixed ask_pfm();

void create()
{
        set_name("任我行", ({ "ren woxing", "ren","woxing" }));
        set("title", GRN "日月神教教主" NOR );
        set("long", "只見他一張長長的臉孔，臉色雪白，更無半分血色，眉目清秀，
身材甚高，一頭黑發，穿的是一襲青衫。\n");
        set("gender", "男性");
        set("class", "scholar");
        set("age", 55);
        set("attitude", "friendly");
        set("shen_type", -1);
        set("str", 30);
        set("per", 27);
        set("int", 30);
        set("con", 30);
        set("dex", 30);
        set("yijinjing_count", 1);

        set("max_qi", 7000);
        set("max_jing", 1000);
        set("neili", 4000);
        set("max_neili", 4000);
        set("jiali", 400);
        set("combat_exp", 6000000);
        set("score", 500000);

        set_skill("force", 700);
        set_skill("riyue-xinfa", 700);
        set_skill("xixing-dafa", 700);
        set_skill("yijinjing", 600);
        set_skill("tianmo-jian", 700);
        set_skill("riyue-jian", 700);
        set_skill("cuff", 700);
        set_skill("xuwu-piaomiao", 700);
        set_skill("hand", 700);
        set_skill("huanmo-longtianwu", 700);
        set_skill("literate", 700);
        set_skill("dodge", 700);
        set_skill("unarmed", 700);
        set_skill("piaomiao-shenfa", 700);
        set_skill("parry", 700);
        set_skill("sword", 700);
        set_skill("damo-jian", 600);
        set_skill("taiji-jian", 600);
        set_skill("huifeng-jian", 600);
        set_skill("taishan-sword", 600);
        set_skill("hengshan-jian", 600);
        set_skill("hengshan-sword", 600);
        set_skill("huashan-sword", 600);
        set_skill("songshan-sword", 600);
        set_skill("richu-dongfang", 600);
        set_skill("martial-cognize", 600);

        map_skill("dodge", "piaomiao-shenfa");
        map_skill("force", "xixing-dafa");
        map_skill("sword", "tianmo-jian");
        map_skill("parry", "tianmo-jian");
        map_skill("cuff", "xuwu-piaomiao");
        map_skill("hand", "huanmo-longtianwu");

        prepare_skill("cuff", "xuwu-piaomiao");
        prepare_skill("hand", "huanmo-longtianwu");

        set("no_teach", ([
            "xixing-dafa"    : "我已將吸星大法寫成拓本，你去找來自己研讀，我沒空教你。",
            "yijinjing"      : "易筋經神功乃少林絕技，我雖習得，卻也未得要領。",
            "damo-jian"      : (: no_learn :),
            "taiji-jian"     : (: no_learn :),
            "huifeng-jian"   : (: no_learn :),
            "taishan-sword"  : (: no_learn :),
            "hengshan-jian"  : (: no_learn :),
            "hengshan-sword" : (: no_learn :),
            "huashan-sword"  : (: no_learn :),
            "songshan-sword" : (: no_learn :),
        ]));

        create_family("日月神教", 1, "教主");

        set("inquiry", ([
                "吸星大法" : "我寫的拓本還遺留在梅莊未曾取回，你去找找吧。\n",
                "比劍"     : (: ask_bijian :),
                "劍法"     : (: ask_bijian :),
                "易筋經"   : (: ask_jing :),
                "黑木令"   : "要拿黑木令？老夫想先看看你的劍法！\n",
                "絕招"     : (: ask_pfm :),
                "一劍穿心" : (: ask_pfm :),
        ]) );

        set("master_ob",4);
        setup();
        carry_object("/d/wudang/obj/bluecloth")->wear();
        carry_object("/clone/weapon/changjian")->wield();
}

void attempt_apprentice(object ob)
{
     if(! permit_recruit(ob))  return;

     if( query("family/master_name", ob) == "東方不敗" )
     {
          command("say 好你個" + RANK_D->query_rude(ob) +
                  "，既已跟隨那個閹賊，還來找我做什麼？快給我滾！");
          return;
     }

     if( query("combat_exp", ob)<250000 )
     {
          command("say 你經驗太低了，還需要再多加磨練！");
          return;
     }

     if((int)ob->query_skill("riyue-xinfa", 1) < 140)
     {
          command("say 本教的內功心法你還沒練好，還要多下苦功才行！");
          return;
     }

     command("haha");
     command("recruit "+query("id", ob));
     command("say 好！老夫今日又得一高徒，東方不敗那閹賊死期就要到了！");
     set("title", HIR"日月神教大護法"NOR, ob);
}

int ask_bijian()
{
        object obj, me = this_player(), ob = this_object();
        message_vision("$N躬身說道：“晚輩今日有幸拜見任老前輩，還望多加指教。”\n
$n笑道：“不用客氣，你來解我寂寞，可多謝你啦。”\n", me, ob );
        message_vision("$N道：“不敢。”\n
$n點了點頭，說道：“我只想瞧瞧你的劍法，並非真的過
招，再說，我也未必能勝得了你。”\n\n", me, ob);
        command("enable sword damo-jian");
        say(HIR"任我行大喝一聲：“少林劍法！”"NOR);
        COMBAT_D->do_attack(ob, me, query_temp("weapon"));
        if( query("qi", me)<0 || !present(me,environment()) )
        {
                say("任我行嘆了口氣，說道：“才一招。”\n");
                command("enable sword tianmo-jian");
                return 1;
        }
        command("enable sword taiji-jian");
        say(HIR"任我行大喝一聲：“武當劍法！”"NOR);
        COMBAT_D->do_attack(ob, me, query_temp("weapon"));
        if( query("qi", me)<0 || !present(me,environment()) )
        {
                say("任我行嘆了口氣，說道：“才兩招。”\n");
                command("enable sword tianmo-jian");
                return 1;
        }
        command("enable sword huifeng-jian");
        say(HIR"任我行大喝一聲：“峨嵋劍法！”"NOR);
        COMBAT_D->do_attack(ob, me, query_temp("weapon"));
        if( query("qi", me)<0 || !present(me,environment()) )
        {
                say("任我行嘆了口氣，說道：“才三招。”\n");
                command("enable sword tianmo-jian");
                return 1;
        }
        command("enable sword songshan-sword");
        say(HIR"任我行大喝一聲：“嵩山劍法！”"NOR);
        COMBAT_D->do_attack(ob, me, query_temp("weapon"));
        if( query("qi", me)<0 || !present(me,environment()) )
        {
                say("任我行嘆了口氣，說道：“才四招。”\n");
                command("enable sword tianmo-jian");
                return 1;
        }

        command("enable sword taishan-sword");
        say(HIR"任我行大喝一聲：“泰山劍法！”"NOR);
        COMBAT_D->do_attack(ob, me, query_temp("weapon"));
        if( query("qi", me)<0 || !present(me,environment()) )
        {
                say("任我行嘆了口氣，說道：“才五招。”\n");
                command("enable sword tianmo-jian");
                return 1;
        }
        command("enable sword huashan-sword");
        say(HIR"任我行大喝一聲：“華山劍法！”"NOR);
        COMBAT_D->do_attack(ob, me, query_temp("weapon"));
        if( query("qi", me)<0 || !present(me,environment()) )
        {
                say("任我行嘆了口氣，說道：“才六招。”\n");
                command("enable sword tianmo-jian");
                return 1;
        }
        command("enable sword hengshan-sword");
        say(HIR"任我行大喝一聲：“衡山劍法！”"NOR);
        COMBAT_D->do_attack(ob, me, query_temp("weapon"));
        if( query("qi", me)<0 || !present(me,environment()) )
        {
                say("任我行嘆了口氣，說道：“才七招。”\n");
                command("enable sword tianmo-jian");
                return 1;
        }
        command("enable sword hengshan-jian");
        say(HIR"任我行大喝一聲：“恆山劍法！”"NOR);
        COMBAT_D->do_attack(ob, me, query_temp("weapon"));
        if( query("qi", me)<0 || !present(me,environment()) )
        {
                say("任我行嘆了口氣，說道：“還是沒過八招。”\n");
                command("enable sword tianmo-jian");
                return 1;
        }
        if( query_temp("heimuling", me) )
            say("任我行說道：“哈哈，這位" + RANK_D->query_respect(me) +
                "武功不錯，快去幫我殺了東方不敗那個閹賊！”\n");
        else
        {
            say("任我行說道：“這位" + RANK_D->query_respect(me) +
                "不錯，我就送你一塊黑木令吧。”\n");
            set_temp("heimuling", 1, me);
        }
            obj = new("/d/heimuya/obj/heimu-ling");
            obj -> move(me);
        command("enable sword tianmo-jian");
        return 1;
}

mixed no_learn()
{
        command("shake");
        command("say 這功夫是我閒時練來玩的，也不知練得對不對，你就不要學了。");
        return -1;
}

mixed ask_pfm()
{
     object me = this_player();

     if( query("can_perform/tianmo-jian/chuanxin", me) )
           return RANK_D->query_respect(me) + "是想和老夫切磋一下武藝？";

     if( query("family/family_name", me) != query("family/family_name") )
           return "本教武功獨步武林，這位" + RANK_D->query_respect(me) +
                  "既然想學，不如入我日月神教如何？";

     if (me->query_skill("tianmo-jian", 1) < 250)
           return "你的天魔劍法尚欠火候，還領悟不了這招，再多練練去吧！";

     message_vision(HIY "$n" HIY "對$N" HIY "點了點頭：這招講究以意馭劍，瞧仔細了。\n" HIW
                    "只見$n" HIW "雙足一點，騰空而起，手中長劍前探，緊跟著身子連轉" HIW
                    "數圈，一道白影筆直向$N" HIW "射來。\n" NOR,
                    me, this_object());
     say(HIC"任我行飄然而落，還劍入鞘，微笑道：“看懂了沒有？”\n"NOR);
     tell_object(me, HIY "你學會了「一劍穿心」這一招。\n" NOR);
     if (me->can_improve_skill("sword"))
             me->improve_skill("sword", 160000);
     set("can_perform/tianmo-jian/chuanxin", 1, me);
     return 1;
}

string ask_jing()
{
     object me, ob;
     string msg;

     me = this_player();
     if( query("family/family_name", me) != query("family/family_name") )
            return "少林易筋經神功名滿江湖，若有幸習得，終生受用不盡。";

     if( query("family/master_id", me) != query("id") )
            return "據說曾有少林高僧將經文記錄下來，不知是真是假。";


     if (objectp(present("yijinjing", me)))
            return "你不是已有經書了，還問我做什麼。";

     if( query_temp("ask_jing", me) && time()-query_temp("ask_jing", me)<120 )
            return "跟你說了經書不在老夫身上，你不相信麼？";

     if (random(3) != 0 || query("yijinjing_count") < 1)
     {
            if( query_temp("ask_jing", me) )
                  msg = "老夫還未曾將經書找回，你再等等吧。";
            else
                  msg = "經書此時並不在老夫身上。";
            set_temp("ask_jing", time(), me);
            return msg;
     }

     addn("yijinjing_count", -1);
     ob = new("/clone/book/yijinjing");
     ob->move(me);
     return "這卷經文你可要小心收好，千萬勿示于他人。";
}

void reset()
{
     set("yijinjing_count", 1);
}
