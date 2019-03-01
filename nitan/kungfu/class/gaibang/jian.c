// This program is a part of NT MudLIB
// jian.c 簡長老

#include <ansi.h>
#include "gaibang.h"

#define POBU    "/d/gaibang/npc/obj/po-bu"
#define LING    "/d/gaibang/npc/obj/qingzhu-ling"

inherit NPC;
inherit F_MASTER;
inherit F_QUESTER;
inherit F_COAGENT;

mixed ask_me();

void create()
{
        set_name("簡長老", ({ "jian zhanglao", "jian", "zhanglao" }));
        set("long", @LONG
簡長老是丐邦的執法長老，代幫主執掌法刀以
及青竹令等。他向來嫉惡如仇，弟子中有誰犯
過，出手決不容情。
LONG);
        set("nickname", HIR "執法長老" NOR);
        set("title", "丐幫九袋長老");
        set("gender", "男性");
        set("age", 50);
        set("attitude", "peaceful");

        set("str", 35);
        set("int", 35);
        set("con", 35);
        set("dex", 35);
        set("max_qi", 4200);
        set("max_jing", 3500);
        set("neili", 4500);
        set("max_neili", 4500);
        set("jiali", 180);
        set("combat_exp", 2000000);
        set("level", 20);
        set("score", 500000);
        set("shen_type", 1);

        set_skill("force", 240);
        set_skill("huntian-qigong", 240);
        set_skill("dodge", 220);
        set_skill("feiyan-zoubi", 220);
        set_skill("unarmed", 200);
        set_skill("cuff", 280);
        set_skill("changquan", 200);
        set_skill("hand", 220);
        set_skill("shexing-diaoshou", 220);
        set_skill("strike", 220);
        set_skill("xiaoyaoyou", 220);
        set_skill("parry", 220);
        set_skill("staff", 240);
        set_skill("fengmo-zhang", 220);
        set_skill("jiaohua-bangfa", 220);
        set_skill("blade", 220);
        set_skill("liuhe-dao", 220);
        set_skill("begging", 260);
        set_skill("checking", 260);
        set_skill("literate", 200);
        set_skill("martial-cognize", 200);

        map_skill("force", "huntian-qigong");
        map_skill("hand", "shexing-diaoshou");
        map_skill("unarmed", "changquan");
        map_skill("dodge", "feiyan-zoubi");
        map_skill("parry", "fumo-zhang");
        map_skill("staff", "fengmo-zhang");
        map_skill("strike", "xiaoyaoyou");
        map_skill("blade", "liuhe-dao");

        prepare_skill("hand", "shexing-diaoshou");

        create_family("丐幫", 18, "九袋長老");

        set("chat_chance_combat", 120);
        set("chat_msg_combat", ({
                (: perform_action, "staff.luan" :),
                (: exert_function, "recover" :),
                (: exert_function, "powerup" :),
        }));

        set_temp("apply/damage", 100);
        set_temp("apply/unarmed_damage", 100);
        set_temp("apply/armor", 200);

        set("inquiry", ([
                "青竹令" : (: ask_me :)
        ]));

        set("master_ob",4);
        setup();
        carry_object(__DIR__"obj/cloth")->wear();
        carry_object(WEAPON_DIR"gangzhang")->wield();
}

void init()
{
        object ob;
        mapping myfam;

        ::init();
        set_heart_beat(1);
        if (interactive(ob = this_player()) && ! is_fighting()
        &&  file_name(environment(this_object())) == "/d/gaibang/gbandao")
        {
                myfam=query("family", ob);
                if ((! myfam || myfam["family_name"] != "丐幫") &&
                        (! wizardp(ob))) {
                        remove_call_out("saying");
                        call_out("saying", 2, ob);
                }
        }
}

void saying(object ob)
{
        if (! ob || environment(ob) != environment())
                return;

        message_sort("\n\n$n看了$N一眼，冷冷地說到：“洪幫主他老人家說我不該"
                     "隨意責打丐幫弟子，你又不屬我丐幫，我打你總可以吧？”"
                     "說完右腿一抬，$N順勢應了一招青城派的「屁股向後，平沙落雁式」"
                     "－－叭嘰\n\n", ob, this_object());
        remove_call_out("kicking");
        call_out("kicking", 1, ob);

}

void kicking(object ob)
{
        if (! ob || environment(ob) != environment())
                return;

        ob->move("/d/gaibang/pomiao");
        message("vision","只聽“□”地一聲，緊接著"+query("name", ob)+
                "從小門裡飛了出來，屁股上有一個清楚的鞋印。\n", environment(ob), ob);
}

void attempt_apprentice(object ob)
{
        command("hmm");
        command("say 老夫不收徒弟，你還是請回吧。");
}

mixed ask_me()
{
        object ob, me;
        int lvl, gx;

        me = this_player();

        if( query("family/family_name", me) != query("family/family_name") )
                return "閣下與本幫素無來往，不知此話從何談起？";

        if( query("combat_exp", me)<10000 )
                return "嘿嘿，你就這點本事也好意思來要青竹令？";

        lvl=query("family/beggarlvl", me);

        if (lvl >= 9)
                return "你已經是本幫長老了，又何去跟後輩們計較。";

        if (lvl <= 0)
                gx = 100;
        else
                gx = lvl * 100 + 200;

        if( query("family/gongji", me)<gx )
                return "你為本幫效力不夠，暫時不能給你升袋。";

        if (present("qingzhu ling", me))
                return "你身上不是已經有青竹令了嗎？";

        if( time()-query_temp("have_ling", me)<100 )
                return "我不是剛剛才給了你一面嗎？稍微等會吧。";

        ob = new(LING);
        ob->move(this_object());

          command("give qingzhu ling to "+query("id", me));
        set_temp("have_ling", time(), me);

        return "憑這面青竹令，你可自由向你的同門大師兄挑戰。";
}

int accept_object(object ob, object obj)
{
        object me = this_object();
        int r;
        int lvl, exp, pot, sc, ww, gx;
        string msg;

        if (r = ::accept_object(ob, obj))
                return r;

        if (base_name(obj) != POBU)
        {
                command("say 你給我這種東西幹什麼？");
                return 0;
        }

        if( query("owner", obj) != ob->name() )
        {
                command("say 你這快破布是從哪裡偷來的？");
                return 0;
        }

        if( query_temp("have_cloth", ob)<1 )
        {
                command("say 你真的挑勝了麼？我怎麼就沒聽說？");
                return 0;
        }

        lvl=query("family/beggarlvl", ob);

        if (lvl >= 9)
        {
                command("say 你已經是本幫長老了，還想當幫主？");
                return 0;
        }

        if (lvl <= 0)
                gx = 100;
        else
                gx = lvl * 100 + 200;

        if( query("family/gongji", ob)<gx )
        {
                command("say 這個…你為本幫效力不夠，暫時不能給你升袋。");
                return 0;
        }

        addn("family/beggarlvl", 1, ob);
        set("title",query_temp("newtitle",  ob), ob);
        delete_temp("have_cloth", ob);
        delete_temp("newtitle", ob);

        message_vision(HIY "\n$N" HIY "接過了破布，然後將其釘"
                       "在$n" HIY "的破衣服上，儼然一個新口袋"
                       "。\n\n" NOR, me, ob);
        command("nod");
        command("say 既然升袋，就當牢記幫規，為民除害！");

        lvl = lvl + 1;
        exp = lvl * 600 + random(lvl * 400);
        pot = lvl * 300 + random(lvl * 200);
        sc = lvl * 80 + random(lvl * 50);
        ww = lvl * 50 + random(lvl * 30);

        addn("combat_exp", exp, ob);
        addn("potential", pot, ob);
        addn("score", sc, ob);
        addn("weiwang", ww, ob);
        addn("family/gongji", -gx, ob);

        msg = HIC "\n通過升袋的經歷，你獲得了" +
              chinese_number(exp) + "點經驗、" +
              chinese_number(pot) + "點潛能、" +
              chinese_number(sc) + "點江湖閱歷以及" +
              chinese_number(ww) + "點江湖威望，同時"
              "消耗了" + chinese_number(gx) + "點門"
              "派貢獻，武學得到了精進。\n\n" NOR;

        tell_object(ob, sort_string(msg, 54));
        ob->improve_skill("martial-cognize", 1500000);

        destruct(obj);
        return 1;
}

