#include <ansi.h>
#include "riyue.h"

#define SHENMU    "/clone/lonely/shenmu"

inherit NPC;
inherit F_MASTER;

mixed ask_back();
mixed ask_gun();
mixed ask_skill1();

void create()
{
        object ob;
        set_name("張乘風", ({"zhang chengfeng", "zhang", "chengfeng", "feng"}));
        set("nickname", HIY "金猴神魔" NOR );
        set("title", "日月神教前輩長老");
        set("long", @LONG
金猴神魔張乘風是日月神教的前輩長老，武功
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
        set_skill("hammer", 220);
        set_skill("pangu-qishi", 220);
        set_skill("club", 260);
        set_skill("jinyuan-gun", 260);
        set_skill("martial-cognize", 240);
        set_skill("literate", 180);

        map_skill("dodge", "juechen-shenfa");
        map_skill("force", "tianhuan-shenjue");
        map_skill("hammer", "pangu-qishi");
        map_skill("club", "jinyuan-gun");
        map_skill("parry", "jinyuan-gun");
        map_skill("cuff", "zhenyu-quan");
        map_skill("claw", "poyue-zhao");

        prepare_skill("claw", "poyue-zhao");
        prepare_skill("cuff", "zhenyu-quan");

        create_family("日月神教", 7, "前輩長老");

        set_temp("apply/damage", 200);
        set_temp("apply/unarmed_damage", 100);
        set_temp("apply/armor", 200);

        set("inquiry", ([
                "南海神木" : (: ask_gun :),
                "乾坤一擊" : (: ask_skill1 :),
                "上崖" : (: ask_back :),
                "回崖" : (: ask_back :),
                "回去" : (: ask_back :),
        ]));

        set("chat_chance_combat", 120);
        set("chat_msg_combat", ({
                (: perform_action, "club.qian" :),
                (: perform_action, "cuff.tong" :),
                (: perform_action, "claw.duan" :),
                (: exert_function, "recover" :),
                (: exert_function, "powerup" :),
        }) );

        set("master_ob",3);
        setup();

        if (clonep())
        {
                ob = find_object(SHENMU);
                if (! ob) ob = load_object(SHENMU);
                if (! environment(ob))
                {
                        ob->move(this_object());
                        ob->wield();
                } else
                {
                        ob = new("/d/heimuya/npc/obj/shutonggun");
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
                command("say 給我滾開，少在老夫面前説三道四！");
                return -1;
        }

        if( query("family/master_id", ob) != "renwoxing"
            && query("family/master_id", ob) != "xiangwentian" )
        {
                command("sneer");
                command("say 你還不配。");
                return -1; 
        }

        if( query("shen", ob)>-60000 )
        {
                command("hmm");
                command("say 老夫生平最痛恨的就是你這樣的假仁假義之徒！");
                return -1;
        }

        if (skill != "club" && skill != "jinyuan-gun")
        {
                command("hmm");
                command("say 我只傳授你這套棍法，其餘的找你師父學去。");
                return -1;
        }

        if (skill == "club" && ob->query_skill("club", 1) > 179)
        {
                command("say 你棍法的造詣已經非同凡響了，剩下就自己去練吧。");
                return -1;
        }

        if( !query_temp("can_learn/zhangchengfeng", ob) )
        {
                command("nod");
                command("say 念在你有心為本教出力，我就傳你這套金猿棍法。");
                set_temp("can_learn/zhangchengfeng", 1, ob);
        }
        return 1;
}

mixed ask_gun()
{
        object me;
        object ob;
        object owner;

        me = this_player();

        if( query("family/family_name", me) != "日月神教" )
                return "給我滾開！";

        if( query("family/master_id", me) != "renwoxing"
            && query("family/master_id", me) != "xiangwentian" )
                return "你還不配！";

        if( query("shen", me)>-80000 )
                return "你這樣心慈手軟，拿了神木又有什麼用？";

        if (me->query_skill("jinyuan-gun", 1) < 120)
                return "你連金猿棍法都沒學好，就算神兵在手又有何用？";

        ob = find_object(SHENMU);
        if (! ob) ob = load_object(SHENMU);
        owner = environment(ob);
        while (owner)
        {
                if (owner->is_character() || ! environment(owner))
                        break;
                owner = environment(owner);
        }

        if (owner == me)
                return "南海神木現在不就在你手裏嗎？";

        if (objectp(owner) && owner != this_object())
        {
                if (! owner->is_character())
                        return "你來晚了一步，南海神木我已經借出去了。";

                if( query("family/family_name", owner) == "日月神教" )
                        return "老夫的南海神木現在是"+query("name", owner)+
                               "在用，你要用就去找他吧。";
                else
                        return "老夫的南海神木現在落入了"+query("name", owner)+
                               "之手，你去把它取回來吧！";
        }
        ob->move(this_object());

        command("say 既然這樣，老夫這根南海神木你就拿去。");
        command("say 你用它多殺幾個正派人士，揚揚咋們日月神教的威風。");
        command("givenanhaishenmuto"+query("id", me));

        ob = new("/d/heimuya/npc/obj/shutonggun");
        ob->move(this_object());
        ob->wield();
        return 1;
}

mixed ask_skill1()
{
        object me;

        me = this_player();

        if( query("can_perform/jinyuan-gun/qian", me) )
                return "這一招我不是已經教過你了嗎？";

        if( query("family/family_name", me) != query("family/family_name") )
                return "你又不是我日月神教的，跑來搗什麼亂？";

        if (me->query_skill("jinyuan-gun", 1) < 1)
                return "你連金猿棍法都沒學，還談什麼絕招可言？";

        if( query("family/gongji", me)<800 )
                return "你在教內甚無作為，這招我暫時還不能傳你。";

        if( query("shen", me)>-100000 )
                return "你這樣心慈手軟，就算學會這招又有什麼用？";

        if (me->query_skill("force") < 180)
                return "你的內功火候尚需提高，練好了再來找我吧。";

        if (me->query_skill("jinyuan-gun", 1) < 120)
                return "你的金猿棍法還練得不到家，自己下去練練再來吧！";

        message_sort(HIY "\n$n" HIY "咳嗽一聲，對$N" HIY "點了點頭道：“看"
                     "好了！”説完便大步上前，怒吼一聲，手中熟銅棍急速舞動"
                     "，霎時間飛沙走石，罡氣激盪。便在那狂沙颶風中，$n" HIY
                     "忽然高高躍起，迎頭一棒猛然劈落。數招一氣呵成，連貫之"
                     "極，煞為壯觀。\n\n" NOR, me, this_object()); 

        command("nod2");
        command("say 看懂了麼？");
        tell_object(me, HIC "你學會了「乾坤一擊」。\n" NOR);
        if (me->can_improve_skill("club"))
                me->improve_skill("club", 1500000);
        if (me->can_improve_skill("jinyuan-gun"))
                me->improve_skill("jinyuan-gun", 1500000);
        me->improve_skill("martial-cognize", 1500000);
        set("can_perform/jinyuan-gun/qian", 1, me);
        addn("family/gongji", -800, me);

        return 1;
}

mixed ask_back()
{
            object me, myenv;
            me = this_player();

        if (find_object(query("startroom")) != environment())
                return "咦？…嗯…這個…這…你還是自己看着辦吧。";

        if( query("family/family_name", me) != query("family/family_name") )
                return "他奶奶的，你找死麼？";

        command("nod");
        message_vision(HIW "張乘風咳嗽一聲，陡然縱聲長嘯，崖上頓時落下一個大弔籃。\n\n"
                       NOR + HIY "$N" HIY "一彎腰進了弔籃，弔籃緩緩地鉸上崖去……\n\n", me);
        myenv = environment(me);
        me->move ("/d/heimuya/basket");
        me->start_call_out((: call_other, __FILE__, "up1", me :), 5);
        return 1;
}

void up1(object me)
{
            tell_object(me, HIW "\n你乘座的弔籃急速上升，籃外的朵朵白雲向下衝去。\n\n" NOR);
        me->start_call_out((: call_other, __FILE__, "up2", me :), 5);
}

void up2(object me)
{
            tell_object(me, HIW "\n你眼前一亮，一幢幢白色建築屹立眼前，霎是輝煌。\n\n" NOR);
        me->move("/d/heimuya/shanya3");
        message_vision(HIC "\n$N" HIC "乘坐弔籃上了黑木崖。\n\n" NOR, me);
}
