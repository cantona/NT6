#include <ansi.h>
#include "yaowang.h"


inherit NPC;
inherit F_MASTER;
int ask_shi();
void create()
{
        set_name("慕容景嶽", ({ "murong jingyue", "murong", "jingyue" }));
        set("nickname", HIC "大弟子" NOR);
        set("long",@LONG
藥王谷第二代弟子大師兄慕容景嶽。
LONG );

        set("gender", "男性");
        set("age", 33);
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

        set_skill("force", 200);
        set_skill("yaogu-xinfa", 200);
        set_skill("dodge", 200);
        set_skill("xuefu-mizong", 200);
        set_skill("strike", 200);
        set_skill("dusha-zhang", 200);
        set_skill("hand", 200);
        set_skill("lansha-shou", 200);
        set_skill("jiuqu-zhegufa", 200);
        set_skill("parry", 200);
        set_skill("staff", 200);
        set_skill("shennong-zhang", 200);
        set_skill("throwing", 200);
        set_skill("xuwen-qixingding", 200);
        set_skill("wuxing-jueming", 200);
        set_skill("literate", 200);
        set_skill("poison", 200);
        set_skill("dispel-poison", 200 );
        set_skill("yaowang-shenxin", 200 );
        set_skill("medical", 200);
        set_skill("yaowang-miaoshu", 200 );
        set_skill("baicao-jue", 200 );
        set_skill("bencao-changshi", 200);
        set_skill("hunting", 180);

        map_skill("force", "yaogu-xinfa");
        map_skill("dodge", "xuefu-mizong");
        map_skill("strike", "dusha-zhang");
        map_skill("hand", "jiuqu-zhegufa");
        map_skill("throwing", "wuxing-jueming");
        map_skill("parry", "jiuqu-zhegufa");
        map_skill("staff", "shennong-zhang");
        map_skill("poison", "yaowang-shenxin");
        map_skill("medical", "baicao-jue");

        prepare_skill("hand", "jiuqu-zhegufa");

        create_family("藥王谷", 2, "弟子");
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
                "七星海棠" : "七星海棠乃天下第一毒，無藥可治！",
                "石萬嗔"   : (: ask_shi :),
         ]) );

        carry_object("/clone/cloth/cloth")->wear();
}

void attempt_apprentice(object ob)
{
        if (! permit_recruit(ob))
                return;

        if( query("combat_exp", ob)<50000 )
        {
                command("say 你現在經驗尚淺，領會不了什麼，還是先去增長點經驗吧。");
                return;
        }

        if ((int)ob->query_skill("yaogu-xinfa", 1) < 50)
        {
                command("say 你本門的心法還學的不夠啊。");
                return;
        }

        if ((int)ob->query_skill("literate", 1) < 100)
        {
                command("say 你連最基本的學問都沒學好，我如何傳授你高深的毒技醫術。");
                return;
        }

        if ((int)ob->query_skill("medical", 1) < 100)
        {
                command("say 你先把醫術鑽研透徹了再來找我吧。");
                return;
        }


        command("pat"+query("id", ob));
        command("say 不錯，不錯！既然你如此有心，我就收下你這個徒弟。");
        command("recruit "+query("id", ob));
        if( query("class", ob) != "bonze" )
                set("class", "bonze", ob);
        return;
}

int ask_shi()
{
        object me;
        object ob;

        me = this_player();
        
        if( query("family/family_name", me) != "藥王谷" )
                return notify_fail( "你不是我們藥王谷的，打聽它幹什麼？");

        

        if( query("shen", me)<-100000 )
                return notify_fail("你俠義正事做得太多，去了他也不見你。");


        message_vision(HIC "$N" HIC "微微一笑，道：“我師叔就在後山"
                       "哪兒的路徑是左右右右右右！”\n" NOR,
                       this_object(), me);
        set_temp("murong_ask", 1, me);
        return 1;
}
void unconcious()
{
        die();
}

