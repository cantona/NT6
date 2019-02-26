#include <ansi.h>
#include "riyue.h"

inherit NPC;
inherit F_MASTER;

void create()
{
        set_name("趙鶴", ({"zhao he", "zhao", "he"}));
            set("nickname", HIW "飛天神魔" NOR);
        set("title", "日月神教前輩長老");
        set("long", @LONG
飛天神魔趙鶴乃是日月神教的前輩長老，武功
高強，位尊無比。曾一度掃除五嶽劍派聯盟。
LONG);
        set("gender", "男性");
        set("class", "scholar");
        set("age", 61);
        set("attitude", "friendly");
        set("shen_type", -1);
        set("str", 36);
        set("int", 36);
        set("con", 36);
        set("dex", 36);
        
        set("max_qi", 5400);
        set("max_jing", 4000);
        set("neili", 7000);
        set("max_neili", 7000);
        set("jiali", 220);
        set("combat_exp", 3000000);
        set("score", 50000);

        set_skill("force", 260);
        set_skill("tianhuan-shenjue", 260);
        set_skill("riyue-xinfa", 220);
        set_skill("dodge", 220);
        set_skill("juechen-shenfa", 220);
        set_skill("cuff", 240);
        set_skill("zhenyu-quan", 240);
        set_skill("claw", 240);
        set_skill("poyue-zhao", 240);
        set_skill("parry", 240);
        set_skill("hammer", 260);
        set_skill("pangu-qishi", 260);
        set_skill("club", 220);
        set_skill("jinyuan-gun", 220);
        set_skill("martial-cognize", 240);
        set_skill("literate", 180);

        map_skill("dodge", "juechen-shenfa");
        map_skill("force", "tianhuan-shenjue");
        map_skill("hammer", "pangu-qishi");
        map_skill("club", "jinyuan-gun");
        map_skill("parry", "pangu-qishi");
        map_skill("cuff", "zhenyu-quan");
        map_skill("claw", "poyue-zhao");

        prepare_skill("claw", "poyue-zhao");
        prepare_skill("cuff", "zhenyu-quan");

        create_family("日月神教", 7, "前輩長老");

        set_temp("apply/damage", 200);
        set_temp("apply/unarmed_damage", 100);
        set_temp("apply/armor", 200);

        set("inquiry", ([
                "開天闢地" : "你去讓我師兄教你吧。",
        ]));

        set("chat_chance_combat", 120);
        set("chat_msg_combat", ({
                (: perform_action, "hammer.kai" :),
                (: perform_action, "cuff.tong" :),
                (: perform_action, "claw.duan" :),
                (: exert_function, "recover" :),
                (: exert_function, "powerup" :),
        }) );

        set("master_ob",3);
        setup();

        carry_object("/d/heimuya/npc/obj/leizhendang")->wield();
        carry_object("/d/heimuya/npc/obj/jinpao")->wear();
}

void attempt_apprentice(object ob)
{
        if (! permit_recruit(ob))
                return;

        command("say 走開，我不收徒。");
}

int recognize_apprentice(object ob, string skill)
{
        if( query("family/family_name", ob) != "日月神教" )
        {
                command("killair");
                command("say 給我滾開，少在老夫面前説三道四！");
                return -1;
        }

        if( query("family/master_id", ob) != "renwoxing" )
        {
                command("sneer");
                command("say 你還不配。");
                return -1; 
        }

        if( query("shen", ob)>-80000 )
        {
                command("hmm");
                command("say 老夫生平最痛恨的就是你這樣的假仁假義之徒！");
                return -1;
        }

        if (skill != "hammer" && skill != "pangu-qishi")
        {
                command("hmm");
                command("say 我只傳授你這套錘法，其餘的找你師父學去。");
                return -1;
        }

        if (skill == "hammer" && ob->query_skill("hammer", 1) > 179)
        {
                command("say 你錘法的造詣已經非同凡響了，剩下就自己去練吧。");
                return -1;
        }

        if( query("str", ob)<32 )
        {
                command("say …唉…本來老夫可以傳授你一套絕技。");
                command("say 可是怪你先天膂力太差，可惜啊…可惜……");
                return -1;
        }

        if( !query_temp("can_learn/zhaohe", ob) )
        {
                command("haha");
                command("say 想不到後輩中居然還有你這樣的人物。");
                command("say 這套盤古七勢乃本教神技，今日我就傳授予你。");
                set_temp("can_learn/zhaohe", 1, ob);
        }
        return 1;
}
