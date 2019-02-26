// This program is a part of NT MudLIB
// peng.c 彭有敬

#include <ansi.h>
#include "gaibang.h"

inherit NPC;
inherit F_MASTER;
inherit F_QUESTER;
inherit F_GUARDER;

#include "fight.h"

mixed ask_skill1();
mixed ask_skill2();

void create()
{
        set_name("彭有敬", ({ "peng youjing", "peng", "youjing" }));
        set("long", @LONG
彭有敬是丐幫中淨衣派的首領，衣着乾淨華麗
不象叫化子。他臉上掛着慈祥的笑容，一雙眼
睛有攝人心魄的力量。
LONG);
        set("nickname", WHT "掌缽龍頭" NOR);
        set("title", "丐幫九袋長老");
        set("gender", "男性");
        set("age", 48);
        set("attitude", "peaceful");
        set("class", "beggar");

        set("str", 35);
        set("int", 35);
        set("con", 35);
        set("dex", 35);

        set("max_qi", 4000);
        set("max_jing", 3000);
        set("neili", 4300);
        set("max_neili", 4300);
        set("jiali", 180);
        set("combat_exp", 2200000);
        set("level", 20);
        set("score", 300000);
        set("shen_type", -1);

        set_skill("force", 220);
        set_skill("huntian-qigong", 220);
        set_skill("dodge", 220);
        set_skill("feiyan-zoubi", 220);
        set_skill("unarmed", 220);
           set_skill("cuff", 220);
        set_skill("changquan", 220);
        set_skill("hand", 220);
        set_skill("shexing-diaoshou", 220);
        set_skill("strike", 200);
        set_skill("xiaoyaoyou", 200);
        set_skill("parry", 220);
        set_skill("staff", 240);
        set_skill("fengmo-zhang", 220);
        set_skill("blade", 220);
        set_skill("liuhe-dao", 220);
        set_skill("begging", 250);
        set_skill("checking", 250);
        set_skill("literate", 180);
        set_skill("martial-cognize", 220);

        map_skill("force", "huntian-qigong");
        map_skill("hand", "shexing-diaoshou");
        map_skill("strike", "xiaoyaoyou");
        map_skill("blade", "liuhe-dao");
        map_skill("staff", "fengmo-zhang");
        map_skill("parry", "fengmo-zhang");
        map_skill("dodge", "feiyan-zoubi");
        map_skill("unarmed", "changquan");

        prepare_skill("hand", "shexing-diaoshou");

        // set("no_teach/mihun-dafa",  "你弄錯了吧？這種下三濫的東西我怎麼會。");

        create_family("丐幫", 18, "長老");

        set("coagents", ({
                ([ "startroom" : "/d/city/gbxiaowu",
                   "id"        : "hong qigong" ]),
        }));

        set("inquiry", ([
                "羣魔亂舞" : (: ask_skill1 :),
                "懾心術"   : (: ask_skill2 :),
        ]));

        set("chat_chance_combat", 120);
        set("chat_msg_combat", ({
                (: perform_action, "staff.luan" :),
                (: exert_function, "recover" :),
                (: exert_function, "powerup" :),
        }));

        set_temp("apply/damage", 150);
        set_temp("apply/unarmed_damage", 100);
        set_temp("apply/armor", 200);

        set("master_ob",4);
        setup();
        carry_object(CLOTH_DIR"jinpao")->wear();
        carry_object(WEAPON_DIR"gangdao")->wield();
}

void attempt_apprentice(object ob)
{
        string title=query("title", ob);
        int lvl=query("family/beggarlvl", ob);

        if (! permit_recruit(ob))
                return;

        if( query("level", ob)<5 )
        {
                command("say 你的江湖經驗不夠，還是先向各位長老學習吧。");
                return;
        }

        if( query("family/beggarlvl", ob)<4 )
        {
                command("say 你在本幫的地位太低，還是先向其他師父學習吧。");
                return;
        }

        if (ob->query_skill("force") < 90)
        {
                command("say 你的內功火候還不夠，還是先向其他師父學習吧。");
                return;
        }
        command("grin");
        command("say 那你以後就跟着我吧。");
        command("recruit "+query("id", ob));

        if( query("class", ob) != "beggar" )
                set("class", "beggar", ob);

        if (lvl > 0)
        {
                set("family/beggarlvl", lvl, ob);
                set("title", title, ob);
        }
}

mixed ask_skill1()
{
        object me;

        me = this_player();

        if( query("can_perform/fengmo-zhang/luan", me) )
                return "這招我不是已經教會你了嗎？";

        if( query("family/family_name", me) != query("family/family_name") )
                return "閣下與在下素不相識，不知此話從何説起？";

        if (me->query_skill("fengmo-zhang", 1) < 1)
                return "你連瘋魔杖法都沒學，何談絕招可言？";

        if( query("family/gongji", me)<400 )
                return "你在我們丐幫內甚無作為，這招我暫時還不能傳你。";

        if (me->query_skill("fengmo-zhang", 1) < 120)
                return "你的瘋魔杖法火候還不夠，還是下去練高點再來吧。";

        if (me->query_skill("force") < 150)
                return "你現在的內功修為不足，還是練高點再來吧。";

        message_sort(HIY "\n$n" HIY "點了點頭，對$N" HIY "説道：“給"
                     "我看清楚了。”突然陡聽$n" HIY "一聲暴喝，手中鐵"
                     "杖一陣亂舞，竟似毫無章理，揮舞出數道杖影，氣勢"
                     "澎湃，力不可擋。正是瘋魔杖法的精要所在。\n\n" NOR,
                     me, this_object());

        command("say 明白了麼。");
        tell_object(me, HIC "你學會了「羣魔亂舞」。\n" NOR);
        if (me->can_improve_skill("staff"))
                me->improve_skill("staff", 1500000);
        if (me->can_improve_skill("fengmo-zhang"))
                me->improve_skill("fengmo-zhang", 1500000);
        me->improve_skill("martial-cognize", 1500000);
        set("can_perform/fengmo-zhang/luan", 1, me);
        addn("family/gongji", -400, me);

        return 1;
}

mixed ask_skill2()
{
        object me;

        me = this_player();

        if( query("can_exert/huntian-qigong/shexin", me) )
                return "這招我不是已經教會你了嗎？";

        if( query("family/family_name", me) != query("family/family_name") )
                return "閣下與在下素不相識，不知此話從何説起？";

        if( query("family/gongji", me)<400 )
                return "你在我們丐幫內甚無作為，這招我暫時還不能傳你。";

        if (me->query_skill("huntian-qigong", 1) < 120)
                return "你的混天氣功火候還不夠，還是下去練高點再來吧。";

        if (me->query_skill("force") < 150)
                return "你現在的內功修為不足，還是練高點再來吧。";

        message_sort(HIY "\n$n" HIY "點了點頭，對$N" HIY "鬼祟的説道：“給"
                     "我聽清楚了”。然後開始小聲地對$N講解攝心術的精要所在。\n\n" NOR,
                     me, this_object());

        command("say 明白了麼。");
        tell_object(me, HIC "你學會了「攝心術」。\n" NOR);
        if (me->can_improve_skill("force"))
                me->improve_skill("force", 1500000);
        if (me->can_improve_skill("huntian-qigong"))
                me->improve_skill("huntian-qigong", 1500000);
        me->improve_skill("martial-cognize", 1500000);
        set("can_exert/huntian-qigong/shexin", 1, me);
        addn("family/gongji", -400, me);

        return 1;
}

int accept_ask(object me, string topic)
{
        switch (topic)
        {
        case "歷練" :
        case "歷煉" :
        case "鍛鍊" :
                return QUEST_D->accept_ask(this_object(), me, topic);
                break;

        case "連環訣" :
                return MASTER_D->teach_pfm(me, this_object(),
                        ([ "perform" : "can_perform/liuhe-dao/lian",
                           "name"    : "連環訣",
                           "sk1"     : "liuhe-dao",
                           "lv1"     : 100,
                           "sk2"     : "force",
                           "lv2"     : 140,
                           "neili"   : 2000,
                           "gongxian": 600,
                           "shen"    : 4000, ]));
                break;

        case "混天神罡" :
                return MASTER_D->teach_pfm(me, this_object(),
                        ([ "perform" : "can_exert/huntian-qigong/shengang",
                           "name"    : "混天神罡",
                           "sk1"     : "huntian-qigong",
                           "lv1"     : 140,
                           "sk2"     : "force",
                           "lv2"     : 120,
                           "gongxian": 1000,
                           "shen"    : 60000, ]));
                break;

        default:
                return 0;
        }
}
