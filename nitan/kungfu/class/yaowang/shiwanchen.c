#include <ansi.h>
#include "yaowang.h"

#define SHENPIAN    "/clone/lonely/yaowang_book"

inherit NPC;
inherit F_MASTER;
inherit F_QUESTER;


void create()
{
        set_name("石萬嗔", ({ "shi wanchen", "shi", "wanchen" }));
        set("nickname", HIR "毒手神梟" NOR);
        set("long",@LONG
這是一位身着樸素的老者，雙目失明，他便是號稱
「毒手神梟」的石萬嗔。數次和無嗔鬥法，每一回
均是屈居下風。在最後一次鬥毒之際，石萬嗔終於
被“斷腸草”薰瞎了雙目，逃往緬甸野人山。但在
野人山中花了數十年功夫，不但解除了“斷腸草”
的毒性，而且練出了更多毒藥。
LONG );
        set("title", HIG "藥王門掌門" NOR);
        set("gender", "男性");
        set("age", 68);
        set("attitude", "friendly");
        set("shen_type", 1);
        set("str", 40);
        set("int", 40);
        set("con", 40);
        set("dex", 40);
        set("per", 20);

        set("max_qi", 60000);
        set("max_jing", 50000);
        set("neili", 60000);
        set("max_neili", 60000);
        set("jiali", 200);
        set("combat_exp", 2500000);
        set("score", 10000);

        set_skill("force", 350);
        set_skill("yaogu-xinfa", 350);
        set_skill("shennong-xinjing", 350);
        set_skill("dodge", 350);
        set_skill("xuefu-mizong", 300);
        set_skill("strike", 300);
        set_skill("dusha-zhang", 300);
        set_skill("hand", 300);
        set_skill("lansha-shou", 300);
        set_skill("jiuqu-zhegufa", 300);
        set_skill("parry", 300);
        set_skill("staff", 300);
        set_skill("shennong-zhang", 300);
        set_skill("throwing", 300);
        set_skill("xuwen-qixingding", 300);
        set_skill("wuxing-jueming", 300);
        set_skill("literate", 280);
        set_skill("poison", 600);
        set_skill("dispel-poison", 600 );
        set_skill("yaowang-shenxin", 600 );
        set_skill("medical", 400);
        set_skill("yaowang-miaoshu", 400 );
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

        create_family("藥王谷", 1, "掌門");
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
                "七星海棠" : "七星海棠乃天下第一毒，無藥可治！但據説程靈素哪個小丫頭到是有點辦法。",
                "碧蠶毒蠱" : "碧蠶毒蠱乃苗人的三大蠱毒之一，無藥可治！",
                "苗人鳳"   : "呵呵，當年他和胡一刀比武，就是用的我的毒陷害的。",
         ]) );

        carry_object("/clone/cloth/cloth")->wear();
}

void attempt_apprentice(object ob)
{
        if (! permit_recruit(ob))
                return;
        
        if( query("character", ob) == "光明磊落" )
        {
                command("say 你性格不適合學毒，我不能收你。");
                return;
        }
        if( query("shen", ob)>-100000 )
        {
                command("say 欲習我毒技醫術，必須心狠手辣。");
                return;
        }
        
        if( query("combat_exp", ob)<300000 )
        {
                command("say 你現在經驗尚淺，領會不了什麼，還是先去增長點經驗吧。");
                return;
        }
        if( !query_temp("yaowang_give", ob) )
        {
                command("say 你先把本門的《藥王神篇》找來給我!");
                return;
        }

        if ((int)ob->query_skill("yaogu-xinfa", 1) < 100)
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
        command("say “本門中人不能放蠱，又有九種沒解藥的毒藥決計不能使用”的規矩在我這兒就取消了!");
        command("say 凡是對己不利者直接用毒，越毒越好!");
        command("recruit "+query("id", ob));
        set("title", "毒手神梟親傳弟子", ob);
        return;
}


int accept_object(object me, object ob)
{
        int r;
        if (r = ::accept_object(me, ob))
                return r;

        if (base_name(ob) != SHENPIAN)
        {
                command("say 你給我這種東西幹什麼？");
                return 0;
        }

        if( query("family/master_id", me) != query("id") )
        {
                command("say 多謝這位" + RANK_D->query_respect(me) + "將本門寶物交給我。");
                set_temp("yaowang_give", 1, me);
        }
        else
                command("say 很好，很好！");
        destruct(ob);
        return 1;
}

void unconcious()
{
        die();
}

