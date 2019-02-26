// This program is a part of NITAN MudLIB
// feng-buping.c  封不平

inherit NPC;
inherit F_MASTER;
inherit F_QUESTER;

#include <ansi.h>
#include "jianzong.h"

mixed ask_feilong();
mixed ask_sanxian();
string ask_me();
mixed ask_sword_martial();

void create()
{
        set_name("封不平", ({ "feng buping", "feng" }) );
        set("gender", "男性");
        set("class", "swordsman");
        set("title", "華山劍宗第十三代弟子");
        set("age", 45);
        set("long", "封不平是華山劍宗第一高手，滿臉戾氣一張黃焦焦的麪皮。\n");
        set("attitude", "peaceful");
        set("str", 28);
        set("int", 32);
        set("con", 31);
        set("dex", 29);

        set("max_qi", 6300);
        set("max_jing", 4000);
        set("neili", 6000);
        set("max_neili", 6000);
        set("jiali", 100);
        set("level", 20);
        set("combat_exp", 3000000);
        set("shen_type", -1);
        set("apprentice_available", 3);

        set("chat_chance_combat", 120);
        set("chat_msg_combat", ({
                (: perform_action, "sword.long" :),
                (: perform_action, "sword.xian" :),
                (: perform_action, "strike.piao" :),
                (: perform_action, "cuff.song" :),
                (: exert_function, "recover" :),
        }) );

        set_skill("unarmed", 400);
        set_skill("cuff", 400);
        set_skill("strike", 400);
        set_skill("hunyuan-zhang", 400);
        set_skill("sword", 600);
        set_skill("force", 400);
        set_skill("parry", 400);
        set_skill("dodge", 400);
        set_skill("literate", 400);
        set_skill("huashan-sword", 400);
        set_skill("kuangfeng-jian", 600);
        set_skill("huashan-neigong", 400);
        set_skill("huashan-quan", 400);
        set_skill("poyu-quan", 400);
        set_skill("huashan-shenfa", 400);
        set_skill("jianyi", 600); 
        set_skill("martial-cognize", 400);

        map_skill("sword", "huashan-sword");
        map_skill("parry", "huashan-sword");
        map_skill("force", "huashan-neigong");
        map_skill("strike", "hunyuan-zhang");
        map_skill("unarmed", "huashan-quan");
        map_skill("cuff", "poyu-quan");
        map_skill("dodge", "huashan-shenfa");

        prepare_skill("strike", "hunyuan-zhang");
        prepare_skill("cuff", "poyu-quan");

        set("no_teach", ([
                // "kuangfeng-jian" : "你想學的話還是找我成師弟吧！\n",
        ]));

        set("inquiry", ([
                "絕招"     : "我劍宗劍法精奇，你想學哪門絕招？\n",
                "絕技"     : "我劍宗劍法精奇，你想學哪門絕招？\n",
                "劍宗"     : "我就是劍宗傳人！\n",
                "狂風快劍" : "你想學的話還是找我成師弟吧！\n",
                "氣宗"     : "哼！氣宗武功庸俗不堪，奉氣輕劍，亂七八糟。\n",
                "嶽不羣"   : "別提那偽君子！可惡！\n",
                "華山劍法" : "那便是本派絕學，天下一等一的劍法！尤其是「天外飛龍」一招，飛劍殺敵，無人能擋。\n",
                "風清揚"   : "啊！我已多年不見風師叔，不清楚他的下落。\n",
                "劍道修養" : (: ask_sword_martial :),
                "天外飛龍" : (: ask_me :),
        ]));

        set_temp("apply/attack", 220);
        set_temp("apply/defense", 220);
        set_temp("apply/damage", 400);
        set_temp("apply/unarmed_damage", 400);

        create_family("華山劍宗", 13, "弟子");

        set("master_ob", 5);
        setup();

        carry_object("/clone/weapon/changjian")->wield();
        carry_object("/clone/cloth/cloth")->wear();
}

int accept_ask(object me, string topic)
{
        if( query("family/family_name", me) != "華山劍宗" )
                return 0;

        switch (topic)
        {
        case "歷練" :
        case "歷煉" :
        case "鍛鍊" :
                return QUEST_D->accept_ask(this_object(), me, topic);
                break;

        case "風起雲湧" :
                if( query("max_neili", me)>1000000 || me->query_skill("force")>1000 )
                {
                      command("shake");
                      command("say 我劍宗以劍術為主，氣為次！你的內功修為已入了氣宗歧途，再不能修煉劍宗劍術。");
                      return 1;
                }
                return MASTER_D->teach_pfm(me, this_object(),
                        ([ "perform" : "can_perform/kuangfeng-jian/yong",
                           "name"    : "風起雲湧",
                           "sk1"     : "kuangfeng-jian",
                           "lv1"     : 140,
                           "gongxian": 800,
                           "sk2"     : "dodge",
                           "lv2"     : 140, ]));
                break;

        case "奪命連環三仙劍" :
                if( query("max_neili", me)>1000000 || me->query_skill("force")>1000 )
                {
                      command("shake");
                      command("say 我劍宗以劍術為主，氣為次！你的內功修為已入了氣宗歧途，再不能修煉劍宗劍術。");
                      return 1;
                }
                return MASTER_D->teach_pfm(me, this_object(),
                        ([ "perform" : "can_perform/huashan-sword/xian",
                           "name"    : "奪命連環三仙劍",
                           "sk1"     : "huashan-sword",
                           "lv1"     : 160,
                           "free"    : 1,
                           "gongxian": 1000,
                           "sk2"     : "dodge",
                           "lv2"     : 160, ]));
                break;

        default:
                return 0;
        }
}

void attempt_apprentice(object ob)
{
        if (query("apprentice_available"))
        {
                if (find_call_out("do_recruit") != -1)
                        command("say 慢著，一個一個來。");
                else
                        call_out("do_recruit", 2, ob);
        } else
        {
                command("say 老夫今天已經收了三個弟子，不想再收徒了。");
        }
}

void do_recruit(object ob)
{
        if( query("int", ob)<20 )
                command("say 我華山派以劍法為主，依我看" + RANK_D->query_respect(ob) + "不適合於學劍法。");
        else
        {
                command("say 好，好，好，很好。");
                command("recruit "+query("id", ob));
        }
}

int recruit_apprentice(object ob)
{
        if (::recruit_apprentice(ob))
        {
                set("title", "華山劍宗第十四代弟子", ob);
                set("class", "swordman", ob);
        }
        addn("apprentice_availavble", -1);
}

void reset()
{
        set("apprentice_available", 3);
}

// 下面的是方便氣宗的弟子學習天外飛龍，劍宗的直接找成不憂詢問
string ask_me()
{
        object ob = this_player(), me = this_object();
        mapping obfam;

        obfam=query("family", ob);

        if (! obfam || obfam["family_name"] != "華山派")
        {
                if (obfam && obfam["family_name"] == "華山劍宗")
                {
                        return "你還是找我的師弟成不憂吧。\n";
                }

                if( query_temp("feilong", ob)<3 )
                {
                        command( "sneer" );
                        addn_temp("feilong", 1, ob);
                        return "咱們豪無淵源，你問這做什麼？還是別太好奇的好。\n";
                }
                else
                {
                        message_vision("$N臉色微變，目中陰鷺一閃，發出一陣冷笑。\n", me);
                        delete_temp("feilong", ob);
                        me->kill_ob(ob);
                        remove_call_out("fast_attack");
                        call_out("fast_attack", 0, me, ob);
                        return "你三番四次想探聽華山劍法的奧密，居心叵測！是否想對本派不利？\n"
                               "你即然對華山劍法如此憧景，只好用華山劍法送你上路了。\n";
                }
        }

        command("look"+query("id", ob));

        if (ob->query_skill("huashan-sword", 1) < 400)
                return "你的華山劍法修為不夠，學不了「天外飛龍」。";

        if (ob->query_skill("zixia-shengong", 1) < 70)
                return "劍宗以劍為宗，以氣為輔，並非棄氣不用，你的紫霞神功可得再下一番苦功。";

        if (ob->query_skill("zixia-shengong", 1) > ob->query_skill("huashan-sword", 1))
        {
                command( "sneer" );
                return "你是氣宗的人，卻來向我請教，教我如何擔當得起？";
        }

        if( query("can_perform/huashan-sword/long", ob) )
                return "咦，我不是傳了你「天外飛龍」嗎？多下功夫好好練習，別墮了華山劍宗的威名！";

        command("say 好！我便傳你「天外飛龍」。看仔細了！" );

        message_vision("$N劍走龍蛇，白光如虹，凝重處如山嶽巍峙，輕靈處若清風無跡，變幻莫測。\n" +
                       "舞到急處，$N一聲大喝，長劍脱手飛出，化作一道驚虹，直沒至柄插入一株樹中。\n", me);

        set("can_perform/huashan-sword/long", 1, ob);

        return "你今後得要勤加練習，別辜負了我的一番教導。";
}

int fast_attack(object me, object ob)
{
        int i, num;

        if( !query_temp("weapon", me))return 1;
        num = random(2) + 3;

        message_combatd(RED "\n封不平臉色沉重，使出其絕技「狂風快劍」，運劍如風似電般向$N連刺了" + chinese_number(num) + "劍。\n" NOR, ob);

        for (i = 1; i < num + 1; i++)
        {
                if (! me->is_fighting(ob)) break;
                COMBAT_D->do_attack(me,ob,query_temp("weapon", me));
        }

        return 1;
}

/*
mixed ask_me()
{
        object me;

        me = this_player();
        if( query("can_perform/huashan-sword/feilong", me) )
                return "你還不快去練習武功，一雪我們劍宗羞恥？";

        if( query("family/family_name", me) != query("family/family_name") )
                return RANK_D->query_respect(me) + "不是我們華山劍宗的人，請走吧！";

        if (me->query_skill("huashan-sword", 1) < 150)
                return "你的華山劍法還不到家，不要再給我丟臉了！";

        message_vision(HIY "$n" HIY "大喝一聲，手中粘了一個石子"
                       "奮力擊出，飛至半空突然化作粉末！\n"
                       HIY "$n" HIY "回頭凝視着$N" HIY "道：這一"
                       "招沒什麼稀奇，就是要捨生忘死，運足內力！"
                       "你雖為劍宗弟子，也要好好修煉內力！\n" NOR,
                       me, this_object());
        tell_object(me, HIG "你學會了天外飛龍。\n" NOR);
        if (me->can_improve_skill("sword"))
                me->improve_skill("sword", 90000);
        set("can_perform/huashan-sword/feilong", 1, me);
        return 1;
}
*/


mixed ask_sword_martial()
{
        object ob;
        object me;

        me = this_player();
        if( query("family/family_name", me) != query("family/family_name") )
                return RANK_D->query_respect(me) +
                       "，劍道漫漫，自己要勤加修煉啊！";

        if( query("combat_exp", me)<200000 )
                return "你這點武功也來向我求教劍道奧妙？好好給我練功去！";

        if (me->query_skill("sword-cognize", 1) < 50)
                return "你毫無劍道修養根基，我如何與你談其中奧妙？";

        if (me->query_skill("sword-cognize", 1) >= 200)
                return "你劍道瞭解得已經不少了，我是沒什麼好再教你的了。";

        if( query_temp("last_ask/murongbo/martial", me)+240>time() )
                return "改日再談吧，今天你要多想想，好好體會體會。";

        message_vision("$N看看$n，道：“好吧，我就與你談談我在劍道方面的心得。”\n",
                       this_object(), me);

        if( query("potential", me)-query("learned_points", me)<100 )
        {
                tell_object(me, "你聽得迷迷糊糊的，沒聽出個所以然，看來是潛能不夠。\n");
                return 1;
        }

        addn("learned_points", 100, me);
        tell_object(me, HIG "你聽的心中豁然開朗，通曉了不少劍道的奧妙。\n" NOR);
        set_temp("last_ask/murongbo/martial", time(), me);
        me->improve_skill("sword-cognize", 1500 + random(2000));
        return 1;
}
