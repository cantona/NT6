// This program is a part of NT MudLIB
// liang.c 樑長老

#include <ansi.h>
#include "gaibang.h"

inherit NPC;
inherit F_MASTER;
inherit F_COAGENT;
inherit F_GUARDER;

#include "fight.h"

mixed  ask_skill1();
string ask_baicao();
string ask_xhwan();

void create()
{
        set_name("樑長老", ({ "liang zhanglao", "liang", "zhanglao" }));
        set("long", @LONG
樑長老是丐幫出道最久，武功最高的長老，在
武林中享名已久。丐幫武功向來較強，近來樑
長老一力整頓，更是蒸蒸日上。
LONG);
        set("nickname", HIR "傳功長老" NOR);
        set("title", "丐幫九袋長老");
        set("gender", "男性");
        set("age", 48);
        set("attitude", "peaceful");
        set("class", "beggar");

        set("str", 35);
        set("int", 35);
        set("con", 35);
        set("dex", 35);

        set("max_qi", 4200);
        set("max_jing", 3200);
        set("neili", 4500);
        set("max_neili", 4500);
        set("jiali", 200);
        set("combat_exp", 2200000);
        set("level", 20);
        set("score", 350000);
        set("shen_type", 1);
        set("baicao", 10);
        set("xhwan", 10);

        set_skill("force", 240);
        set_skill("huntian-qigong", 240);
        set_skill("dodge", 240);
        set_skill("feiyan-zoubi", 240);
        set_skill("unarmed", 240);
           set_skill("cuff", 240);
        set_skill("changquan", 240);
        set_skill("hand", 240);
        set_skill("shexing-diaoshou", 240);
        set_skill("strike", 240);
        set_skill("xiaoyaoyou", 240);
        set_skill("parry", 240);
        set_skill("staff", 240);
        set_skill("fengmo-zhang", 240);
        set_skill("jiaohua-bangfa", 240);
        set_skill("blade", 240);
        set_skill("liuhe-dao", 240);
        set_skill("begging", 280);
        set_skill("checking", 280);
        set_skill("literate", 220);
        set_skill("martial-cognize", 240);

        map_skill("force", "huntian-qigong");
        map_skill("hand", "shexing-diaoshou");
        map_skill("unarmed", "changquan");
        map_skill("strike", "xiaoyaoyou");
        map_skill("blade", "liuhe-dao");
        map_skill("parry", "liuhe-dao");
        map_skill("staff", "fengmo-zhang");
        map_skill("dodge", "feiyan-zoubi");

        prepare_skill("strike", "xiaoyaoyou");

        create_family("丐幫", 18, "長老");

        set("chat_chance_combat", 120);
        set("chat_msg_combat", ({
                (: perform_action, "blade.lianhuan" :),
                (: perform_action, "blade.shan" :),
                (: exert_function, "recover" :),
                (: exert_function, "powerup" :),
        }));

        set("inquiry", ([
                "閃刀訣" : (: ask_skill1 :),
                // "雄黃丸" : (: ask_xhwan :),
                // "百草丹" : (: ask_baicao :),
        ]));

        set_temp("apply/damage", 100);
        set_temp("apply/unarmed_damage", 100);
        set_temp("apply/armor", 200);

        set("master_ob",4);
        setup();
        carry_object(__DIR__"obj/cloth")->wear();
        carry_object(WEAPON_DIR"gangdao")->wield();
}

void init()
{
        object ob;
        mapping myfam;

        ::init();
        if (interactive(ob = this_player()) && ! is_fighting()
        &&  file_name(environment(this_object())) == "/d/city/gbandao")
        {
                myfam=query("family", ob);
                if (! myfam || myfam["family_name"] != "丐幫")
                {
                        remove_call_out("saying");
                        call_out("saying", 1, ob);
                }
        }
}

void saying(object ob)
{
        if (! ob || environment(ob) != environment())
                return;

        message_vision("\n粱長老看到$N闖進來，大喝一聲：你不是丐幫弟子，給我滾出去！\n\n", ob);
        call_out("kicking", 0, ob);
}

void kicking(object ob)
{
        if (! ob || environment(ob) != environment()) return;

        ob->move("/d/gaibang/inhole");
        message("vision","只聽“乒”地一聲，"+query("name", ob)+
                "從小門裏飛了出來。\n", environment(ob), ob);
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

        if( query("can_perform/liuhe-dao/shan", me) )
                return "這招我不是已經教會你了嗎？";

        if( query("family/family_name", me) != query("family/family_name") )
                return "閣下與在下素不相識，不知此話從何説起？";

        if (me->query_skill("liuhe-dao", 1) < 1)
                return "你連六合刀都沒學，何談絕招可言？";

        if( query("family/gongji", me)<400 )
                return "你在我們丐幫內甚無作為，這招我暫時還不能傳你。";

        if (me->query_skill("liuhe-dao", 1) < 120)
                return "你的六合刀火候還不夠，還是下去練高點再來吧。";

        if (me->query_skill("force") < 150)
                return "你現在的內功修為不足，還是練高點再來吧。";

        message_sort(HIY "\n$n" HIY "點了點頭，對$N" HIY "説道：“給"
                     "我看清楚了。”突然陡聽$n" HIY "一聲暴喝，手中鋼"
                     "刀一陣亂舞，竟似毫無章理，揮舞出數道刀影，氣勢"
                     "澎湃，力不可擋。正是六合刀的精要所在。\n\n" NOR,
                     me, this_object());

        command("say 明白了麼。");
        tell_object(me, HIC "你學會了「閃刀訣」。\n" NOR);
        if (me->can_improve_skill("blade"))
                me->improve_skill("blade", 1500000);
        if (me->can_improve_skill("liuhe-dao"))
                me->improve_skill("liuhe-dao", 1500000);
        me->improve_skill("martial-cognize", 1500000);
        set("can_perform/liuhe-dao/shan", 1, me);
        addn("family/gongji", -400, me);

        return 1;
}

string ask_xhwan()
{
        object me = this_object(), ob = this_player(), wan;

        if( !query("family", ob) || query("family/family_name", ob) != "丐幫" )
        {
                return "你非本幫弟子，怎能索取本幫靈藥？\n\n";
        }

        if (! ob->query_condition("xx_poison") || ! ob->query_condition("snake_poison")
        ||  ! ob->query_condition("insect_poison"))
        {
                message_vision("$N向$n臉上仔細地打量了一陣，便皺起眉頭。\n", me, ob);
                return "你並未中毒，要雄黃丸幹嗎？\n\n";
        }

        message_vision("$N向$n臉上仔細地打量了一陣，抓起$n手腕打脈。\n", me, ob);

        if( query("xhwan", me)<1 )
        {
                message_vision("然後$N伸手入懷，但摸索良久，似乎沒找着。\n", me);
                return "我身上此刻沒有雄黃丸，你還是快到城裏去找大夫吧！\n\n";
        }

        addn("xhwan", -1, me);
        wan = new(DRUG_D("xh-wan"));
        wan->move(ob);

        message_vision("然後$N伸手入懷，取出一顆雄黃丸給$n。\n", me, ob);
        return "快把雄黃丸吃下，別要讓毒素入侵內腑！\n\n";
}

string ask_baicao()
{
        object me = this_object(), ob = this_player(), wan;

        if( !query("family", ob) || query("family/family_name", ob) != "丐幫" )
        {
                return "你非本幫弟子，怎能索取本幫靈藥？\n\n";
        }

        if( query("eff_qi", ob) == query("max_qi", ob )
         && query("eff_jing", ob) == query("max_jing", ob) )
        {
                message_vision("$N向$n臉上仔細地打量了一陣，便皺起眉頭。\n", me, ob);
                return "你並未受傷，要百草丹干嗎？\n\n";
        }

        message_vision("$N向$n臉上仔細地打量了一陣，抓起$n手腕打脈。\n", me, ob);

        if( query("baicao", me)<1 )
        {
                message_vision("然後$N伸手入懷，但摸索良久，似乎沒找着。\n", me);
                return "我身上此刻沒有百草丹，你還是快到城裏去找大夫吧！\n\n";
        }

        addn("baicao", -1, me);
        wan = new(DRUG_D("baicao-dan"));
        wan->move(ob);

        message_vision("然後$N伸手入懷，取出一顆百草丹給$n。\n", me, ob);
        return "快把百草丹吃下，別要讓傷勢繼續加重！\n\n";
}
