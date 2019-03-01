#include <ansi.h>
#include "riyue.h"

#define POYANG    "/clone/lonely/poyangfu"

inherit NPC;
inherit F_MASTER;

mixed ask_fu();
mixed ask_skill1();

void create()
{
        object ob;
        set_name("范鬆", ({"fan song", "fan", "song"}));
        set("nickname", HIR "大力神魔" NOR );
        set("title", "日月神教前輩長老");
        set("long", @LONG
大力神魔范鬆乃是日月神教的前輩長老，武功
高強，位尊無比。曾一度掃除五岳劍派聯盟。
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
                "破陽神斧" : (: ask_fu :),
                "開天辟地" : (: ask_skill1 :),
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

        if (clonep())
        {
                ob = find_object(POYANG);
                if (! ob) ob = load_object(POYANG);
                if (! environment(ob))
                {
                        ob->move(this_object());
                        ob->wield();
                } else
                {
                        ob = new("/d/heimuya/npc/obj/dafu");
                        ob->move(this_object());
                        ob->wield();
                }
        }
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
                command("say 給我滾開，少在老夫面前說三道四！");
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
                command("say 我只傳授你這套錘法，其余的找你師父學去。");
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

        if( !query_temp("can_learn/fansong", ob) )
        {
                command("haha");
                command("say 想不到後輩中居然還有你這樣的人物。");
                command("say 這套盤古七勢乃本教神技，今日我就傳授予你。");
                set_temp("can_learn/fansong", 1, ob);
        }
        return 1;
}

mixed ask_fu()
{
        object me;
        object ob;
        object owner;

        me = this_player();

        if( query("family/family_name", me) != "日月神教" )
                return "給我滾開！";

        if( query("family/master_id", me) != "renwoxing" )
                return "你還不配！";

        if( query("shen", me)>-100000 )
                return "你這樣心慈手軟，拿了神斧又有什麼用？";

        if (me->query_skill("pangu-qishi", 1) < 150)
                return "你連盤古七勢都沒學好，就算神兵在手又有何用？";

        ob = find_object(POYANG);
        if (! ob) ob = load_object(POYANG);
        owner = environment(ob);
        while (owner)
        {
                if (owner->is_character() || ! environment(owner))
                        break;
                owner = environment(owner);
        }

        if (owner == me)
                return "破陽神斧現在不就在你手裡嗎？";

        if (objectp(owner) && owner != this_object())
        {
                if (! owner->is_character())
                        return "你來晚了一步，破陽神斧我已經借出去了。";

                if( query("family/family_name", owner) == "日月神教" )
                        return "老夫的破陽神斧現在是"+query("name", owner)+
                               "在用，你要用就去找他吧。";
                else
                        return "老夫的破陽神斧現在落入了"+query("name", owner)+
                               "之手，你去把它取回來吧！";
        }
        ob->move(this_object());

        command("say 既然這樣，老夫這柄神斧你就拿去。");
        command("say 你用它多殺幾個正派人士，揚揚咋們日月神教的威風。");
        command("givepoyangfuto"+query("id", me));

        ob = new("/d/heimuya/npc/obj/dafu");
        ob->move(this_object());
        ob->wield();
        return 1;
}

mixed ask_skill1()
{
        object me;

        me = this_player();

        if( query("can_perform/pangu-qishi/kai", me) )
                return "這一招我不是已經教過你了嗎？";

        if( query("family/family_name", me) != query("family/family_name") )
                return "你又不是我日月神教的，跑來搗什麼亂？";

        if (me->query_skill("pangu-qishi", 1) < 1)
                return "你連盤古七勢都沒學，還談什麼絕招可言？";

        if( query("family/gongji", me)<1200 )
                return "你在教內甚無作為，這招我暫時還不能傳你。";

        if( query("shen", me)>-120000 )
                return "你這樣心慈手軟，就算學會這招又有什麼用？";

        if (me->query_skill("force") < 300)
                return "你的內功火候尚需提高，練好了再來找我吧。";

        if (me->query_skill("pangu-qishi", 1) < 180)
                return "你的盤古七勢還練得不到家，自己下去練練再來吧！";

        message_sort(HIY "\n$n" HIY "朝$N" HIY "微微點了點頭，說道：“看"
                     "好了！”說完$n" HIY "一聲斷喝，手中巨斧如山岳巍峙，"
                     "攜著開天辟地之勢猛劈而下，氣勢恢弘之極。頓時只聽轟"
                     "然一聲巨響，$n" HIY "面前的山壁已被劈出一道人來寬的"
                     "裂縫，威力之強，真可謂是驚天地，泣鬼神。直把$N" HIY
                     "看得目瞪口呆。\n\n" NOR, me, this_object()); 

        command("nod2");
        command("say 招式便是如此，你自己下去練吧。");
        tell_object(me, HIC "你學會了「開天辟地」。\n" NOR);
        if (me->can_improve_skill("hammer"))
                me->improve_skill("hammer", 1500000);
        if (me->can_improve_skill("pangu-qishi"))
                me->improve_skill("pangu-qishi", 1500000);
        me->improve_skill("martial-cognize", 1500000);
        set("can_perform/pangu-qishi/kai", 1, me);
        addn("family/gongji", -1200, me);

        return 1;
}
