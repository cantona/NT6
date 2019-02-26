#include <ansi.h>
#include "duan.h"

inherit NPC;
inherit F_MASTER;

mixed ask_skill1();

void create()
{
        set_name("華赫艮", ({ "hua hegen", "hua", "hegen" }));
        set("title", "大理國護國三公" );
        set("nickname", HIW "司徒" NOR);
        set("long", @LONG
他是大理國三大公之一。華司徒本名阿根，出身貧
賤，現今在大理國位列三公，未發跡時，幹部的卻
是盜墓掘墳的勾當，  最擅長的本領是偷盜王公巨
賈的墳墓。這些富貴人物死後，必有珍異寶物殉葬，
華阿根從極遠處挖掘地道，通入墳墓，然後盜取寶
物。所花的一和雖巨，卻由此而從未為人發覺。有
一次他掘入一墳，在棺木中得到了一本殉葬的武功
祕訣，依法修習，練成了一身卓絕的外門功夫，便
捨棄了這下賤的營生，輔佐保定帝，累立奇功，終
於升到司徒之職。
LONG);
        set("gender", "男性");
        set("age", 46);
        set("class", "officer");
        set("attitude", "friendly");
        set("shen_type", 1);
        set("str", 30);
        set("int", 20);
        set("con", 25);
        set("dex", 25);

        set("max_qi", 3000);
        set("max_jing", 1800);
        set("neili", 3200);
        set("max_neili", 3200);
        set("jiali", 150);
        set("combat_exp", 1500000);
        set("score", 10000);

        set_skill("force", 180);
        set_skill("duanshi-xinfa", 180);
        set_skill("dodge", 180);
        set_skill("tiannan-bu", 180);
        set_skill("cuff", 160);
        set_skill("jinyu-quan", 160);
        set_skill("strike", 160);
        set_skill("wuluo-zhang", 160);
        set_skill("claw", 180);
        set_skill("yuezhao-gong", 180);
        set_skill("parry", 180);
        set_skill("literate", 120);
        set_skill("martial-cognize", 160);

        map_skill("force", "duanshi-xinfa");
        map_skill("dodge", "tiannan-bu");
        map_skill("cuff", "jinyu-quan");
        map_skill("strike", "wuluo-zhang");
        map_skill("claw", "yuezhao-gong");
        map_skill("parry", "yuezhao-gong");

        prepare_skill("claw", "yuezhao-gong");

        set("inquiry", ([
                "弒元訣"   : (: ask_skill1 :),
        ]));

        create_family("段氏皇族", 15, "司徒");

        set("chat_chance_combat", 120);
        set("chat_msg_combat", ({
                (: perform_action, "claw.shi" :),
                (: exert_function, "recover" :),
        }));

        set("master_ob", 3);
        setup();
        carry_object("/d/dali/npc/obj/junfu")->wear();
        add_money("silver", 10);
}

void attempt_apprentice(object ob)
{
        if (! permit_recruit(ob))
                return;

        command("smile");
        command("say 世子殿下何需如此，只要有事吩咐在下一聲便是。");
        command("say 若世子不嫌棄，我這裏倒是有一套爪法可以傳授予你。");

        return;
}

int recognize_apprentice(object ob, string skill)
{
        if( query("family/family_name", ob) != "段氏皇族" )
        {
                command("sneer");
                command("say 我與閣下素不相識，不知閣下此話從何説起？");
                return -1;
        }

        if (skill != "yuezhao-gong" && skill != "claw")
        {
                command("say 我生平所就這套爪法最為精妙，其它的還是讓王爺親自教你吧。");
                return -1;
        }

        if( !query_temp("can_learn/huahegen", ob) )
        {
                command("nod");
                command("say 既然世子有心習武，在下理當竭盡所能傳授。");
                set_temp("can_learn/huahegen", 1, ob);
        }
        return 1;
}

mixed ask_skill1()
{
        object me;

        me = this_player();
        if( query("can_perform/yuezhao-gong/shi", me) )
                return "我不是已經教給你了嗎？";

        if( query("family/family_name", me) != query("family/family_name") )
                return RANK_D->query_respect(me) + "和我素無瓜葛，何出此言？";

        if (me->query_skill("yuezhao-gong", 1) < 1)
                return "哈哈，你連我越爪功都未學，怎麼來絕招一説？";

        if( query("family/gongji", me)<400 )
                return "恕在下無禮，王爺吩咐過，不得傳功給無功子弟。";

        if (me->query_skill("force") < 200)
                return "你的內功修為太差，學不了這一招。";

        if( query("max_neili", me)<1800 )
                return "你的內力修為太差，學不了這一招。";

        if (me->query_skill("yuezhao-gong", 1) < 130)
                return "你越爪功的火候還不夠，學不了這一招。";

        message_sort(HIY "\n$n" HIY "哈哈一笑，對$N" HIY "讚許的説道：“想"
                     "不到世子殿下的爪法造詣竟然如此精湛，今日華某便傳你這"
                     "招。”説罷，$n" HIY "隨即擺開架勢，慢慢的演示招數。\n"
                     "\n" NOR, me, this_object()); 

        command("nod");
        command("say 這招看似花巧，其實並不難練，下去後仍需勤加練習。");
        tell_object(me, HIC "你學會了「弒元訣」。\n" NOR);
        if (me->can_improve_skill("claw"))
                me->improve_skill("claw", 1500000);
        if (me->can_improve_skill("yuezhao-gong"))
                me->improve_skill("yuezhao-gong", 1500000);
        me->improve_skill("martial-cognize", 1500000);
        set("can_perform/yuezhao-gong/shi", 1, me);
        addn("family/gongji", -400, me);
        return 1;
}
