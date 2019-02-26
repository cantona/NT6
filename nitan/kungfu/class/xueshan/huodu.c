#include <ansi.h>
#include "xueshan.h"

inherit NPC;
inherit F_MASTER;

mixed ask_skill1();

void create()
{
        set_name("霍都", ({ "huo du", "huo", "du" }));
        set("long", @LONG
他是金輪法王座下的二弟子。深得法王的真傳。
霍都貴為蒙古王子，地位極其尊貴。
LONG);
        set("nickname", HIY "蒙古王子" NOR);
        set("gender", "男性");
        set("age", 31);
        set("attitude", "peaceful");
        set("shen_type", -1);

        set("str", 35);
        set("int", 20);
        set("con", 25);
        set("dex", 20);

        set("max_qi", 3200);
        set("max_jing", 2200);
        set("neili", 3800);
        set("max_neili", 3800);
        set("jiali", 120);
        set("level", 20);
        set("combat_exp", 800000);

        set_skill("force", 180);
        set_skill("mizong-neigong", 180);
        set_skill("dodge", 160);
        set_skill("shenkong-xing", 160);
        set_skill("dagger", 180);
        set_skill("finger", 180);
        // set_skill("poxu-daxuefa", 180);
        set_skill("sword", 160);
        set_skill("mingwang-jian", 160);
        set_skill("hand", 160);
        set_skill("dashou-yin", 160);
        set_skill("cuff", 160);
        set_skill("yujiamu-quan", 160);
        set_skill("parry", 160);
        set_skill("lamaism", 180);
        set_skill("literate", 100);
        set_skill("sanscrit", 100);
        set_skill("martial-cognize", 160);

        map_skill("force", "mizong-neigong");
        map_skill("dodge", "shenkong-xing");
        map_skill("parry", "mingwang-jian");
        map_skill("sword", "mingwang-jian");
        // map_skill("dagger", "poxu-daxuefa");
        // map_skill("finger", "poxu-daxuefa");
        map_skill("hand", "dashou-yin");
        map_skill("cuff", "yujiamu-quan");

        // prepare_skill("finger", "poxu-daxuefa");

        set("chat_chance_combat", 100);
        set("chat_msg_combat", ({
                (: perform_action, "finger.tong" :),
                (: exert_function, "recover" :),
        }));

        create_family("雪山寺", 3, "弟子");

        set("inquiry", ([
                // "破元通虛" : (: ask_skill1 :),
        ]));

        set("master_ob", 3);
        setup();

        // carry_object("/d/xueshan/obj/gushan")->wield();
        carry_object("/clone/cloth/cloth")->wear();
}

void attempt_apprentice(object ob)
{
        if (! permit_recruit(ob))
                return;

        if( query("gender", ob) == "女性" )
        {
                command("say 嘿？你一個姑娘跑到雪山寺來幹什麼？");
                return;
        }

        if( query("gender", ob) != "男性" )
        {
                command("say 我平生最討厭不男不女的閹人，給我滾開。");
                return;
        }

        if( query("class", ob) != "bonze" )
        {
                command("say 雪山寺除了我以外全是喇嘛，你自然也不能破例。");
                return;
        }

        if( query("shen", ob)>-5000 )
        {
                command("say 我從來不和正派人士打交道，給我滾開。");
                return;
        }

        if ((int)ob->query_skill("mizong-neigong", 1) < 50)
        {
                command("say 你內功這麼差，也好意思來麻煩我？");
                return;
        }

        command("nod");
        command("say 小王看得起你，以後就跟着我吧。");
        command("recruit "+query("id", ob));
}

mixed ask_skill1()
{
        object me;

        me = this_player();

        if( query("can_perform/poxu-daxuefa/tong", me) )
                return "這招小王不是已經教過你了麼？";

        if( query("family/family_name", me) != query("family/family_name") )
                return "給我滾開！";

        if (me->query_skill("poxu-daxuefa", 1) < 1)
                return "你連破虛打穴法都沒學，跟小王羅嗦什麼？";

        if( query("family/gongji", me)<400 )
                return "你為雪山寺效力不夠，這招暫時還不能傳你。";

        if( query("shen", me)>-10000 )
                return "嘿！你為人如此正派，看來這招不適合你。";

        if (me->query_skill("force") < 160)
                return "你的內功修為不足，還學不了這一招。";

        if (me->query_skill("poxu-daxuefa", 1) < 120)
                return "等你把破虛打穴法練熟了再來找小王吧。";

        message_sort(HIY "\n$n" HIY "沉思片刻，方才點了點頭，伸手將$N" HIY
                     "招至身邊，俯身在$P" HIY "耳旁低聲細説良久，$N" HIY
                     "聽後不禁會心的一笑，似乎對$n" HIY "的教導大有所悟"
                     "。\n\n" NOR, me, this_object());

        command("grin");
        command("say 這招的精髓都告訴你了，可得用心練習。");
        tell_object(me, HIC "你學會了「破元通虛」。\n" NOR);

        if (me->can_improve_skill("dagger"))
                me->improve_skill("dagger", 1500000);
        if (me->can_improve_skill("finger"))
                me->improve_skill("finger", 1500000);
        if (me->can_improve_skill("poxu-daxuefa"))
                me->improve_skill("poxu-daxuefa", 1500000);
        me->improve_skill("martial-cognize", 1500000);
        set("can_perform/poxu-daxuefa/tong", 1, me);
        addn("family/gongji", -400, me);

        return 1;
}
