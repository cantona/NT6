#include <ansi.h>

inherit NPC;
inherit F_MASTER;

mixed ask_skill1();
mixed ask_skill2();

void create()
{
        set_name("阿大", ({ "a da", "a", "da" }));
        set("long", @LONG
八臂神劍方東白本是丐幫四大長老之首，劍術
之精，名動江湖，只因他出劍奇快，有如生了
七八條手臂一般，因此上得了這個外號。十多
年前聽説他身染重病身亡，當時人人都感惋惜，
不覺他竟尚在人世。
LONG);
        set("title", "丐幫四大長老之首");
        set("nickname", WHT "八臂神劍" NOR);
        set("gender", "男性");
        set("age", 68);
        set("attitude", "peaceful");
        set("class", "beggar");

        set("str", 35);
        set("int", 35);
        set("con", 35);
        set("dex", 35);        
        set("max_qi", 5800);
        set("max_jing", 5800);
        set("neili", 6200);
        set("max_neili", 6200);
        set("jiali", 250);
        set("combat_exp", 3500000);
        set("score", 500000);
        set("shen_type", -1);

        set_skill("force", 300);
        set_skill("jiaohua-neigong", 280);
        set_skill("huntian-qigong", 300);
        set_skill("dodge", 280);
        set_skill("feiyan-zoubi", 280);
        set_skill("sword", 300);
        set_skill("guanri-jian", 300);
        set_skill("pichen-jian", 300);
        set_skill("parry", 280);
        set_skill("unarmed", 280);
        set_skill("cuff", 280);
        set_skill("changquan", 280);
        set_skill("staff", 280);
        set_skill("jiaohua-bangfa", 280);
        set_skill("dagou-bang", 280);
        set_skill("strike", 280);
        set_skill("dragon-strike", 280);
        set_skill("begging", 200);
        set_skill("checking", 200);
        set_skill("martial-cognize", 300);

        map_skill("force", "huntian-qigong");
        map_skill("dodge", "feiyan-zoubi");
        map_skill("sword", "guanri-jian");
        map_skill("parry", "guanri-jian");
        map_skill("unarmed", "changquan");
        map_skill("staff", "dagou-bang");
        map_skill("strike", "dragon-strike");

        prepare_skill("strike", "dragon-strike");
        set("inquiry", ([
                "傲塵劍" : (: ask_skill1 :),
                "焚陽劍" : (: ask_skill2 :),
        ]));
        set("chat_chance_combat", 120);
        set("chat_msg_combat", ({
                (: perform_action, "sword.fen" :),
                (: perform_action, "sword.guan" :),
                (: exert_function, "recover" :),
                (: exert_function, "powerup" :),
        }));

        create_family("丐幫", 17, "長老");

        set_temp("apply/damage", 100);
        set_temp("apply/unarmed_damage", 100);
        set_temp("apply/armor", 200);

        set("master_ob", 4);
        setup();
        carry_object("/d/tulong/yitian/npc/obj/jian")->wield();
        carry_object("/clone/cloth/cloth")->wear();
}

void attempt_apprentice(object ob)
{
        command("hmm");
        command("say 走開，我不收徒。");
}

int accept_fight(object ob)
{
        command("sneer");
        command("say 滾開。");
        return 0;
}

int recognize_apprentice(object ob, string skill)
{
        if( query("family/family_name", ob) != "丐幫" )
        {
                command("hmm");
                command("say 滾開。");
                return -1;
        }

        if( query("family/master_id", ob) != "madayuan"
            && query("family/master_id", ob) != "hongqigong"
            && query("family/beggarlvl", ob)<7 )
        {
                command("sneer");
                command("say 你還不配。\n");
                return -1; 
        }

        if (skill != "sword"
           && skill != "guanri-jian"
           && skill != "pichen-jian")
        {
                command("hmm");
                command("say 我只會兩手劍法，不想學就滾吧。");
                return -1;
        }

        if (skill == "sword" && ob->query_skill("sword", 1) > 179)
        {
                command("say 夠了，剩下的自己去練。");
                return -1;
        }

        if( !query_temp("can_learn/ada", ob) )
        {
                command("sigh");
                command("say 也罷，也罷。");
                command("say 這闢塵和觀日兩套劍法乃我生平絕學，就傳給你好了。");
                set_temp("can_learn/ada", 1, ob);
        }
        return 1;
}

mixed ask_skill1()
{
        object me;
        me = this_player();

        if( query("can_perform/pichen-jian/ao", me) )
                return "自己去領悟吧，好自為之。";

        if( query("family/family_name", me) != query("family/family_name") )
                return "給我滾開。";

        if( query("family/master_id", me) != "madayuan"
            && query("family/master_id", me) != "hongqigong"
            && query("family/beggarlvl", me)<7 )
                return "我什麼時候説過要教你？";

        if (me->query_skill("pichen-jian", 1) < 1)
                return "你學過闢塵劍法嗎？不學哪來絕招。";

        if( query("family/gongji", me)<300 )
                return "你在幫內毫無作為可言，這樣的人不值得我憐憫。";

        if (me->query_skill("pichen-jian", 1) < 100)
                return "你的闢塵劍法還不到家，要多練練。";

        message_sort(HIY "\n$n" HIY "一聲長歎，搖頭道：“也罷，也"
                     "罷，你過來。”説完便將$N" HIY "招到一旁的僻"
                     "靜處，輕聲在$N" HIY "耳邊低聲嘀咕了半天，不"
                     "時還伸指捏作劍訣，比劃演示劍招，所示全為闢塵"
                     "劍法絕招的精微要詣，$N" HIY "聽後大有所悟。"
                     "\n\n" NOR, me, this_object());

        command("sigh");
        command("say 你好好努力吧，別像我……唉。");
        tell_object(me, HIC "你學會了「傲塵劍」。\n" NOR);

        if (me->can_improve_skill("sword"))
                me->improve_skill("sword", 1500000);
        if (me->can_improve_skill("pichen-jian"))
                me->improve_skill("pichen-jian", 1500000);

        me->improve_skill("martial-cognize", 1500000);
        set("can_perform/pichen-jian/ao", 1, me);
        addn("family/gongji", -300, me);
        return 1;
}

mixed ask_skill2()
{
        object me;
        me = this_player();

        if( query("can_perform/guanri-jian/fen", me) )
                return "自己去領悟吧，好自為之。";

        if( query("family/family_name", me) != query("family/family_name") )
                return "給我滾開。";

        if( query("family/master_id", me) != "madayuan"
            && query("family/master_id", me) != "hongqigong"
            && query("family/beggarlvl", me)<7 )
                return "我什麼時候説過要教你？";

        if (me->query_skill("guanri-jian", 1) < 1)
                return "你學過觀日劍法嗎？不學哪來絕招。";

        if( query("family/gongji", me)<1200 )
                return "你在幫內毫無作為可言，這樣的人不值得我憐憫。";

        if (me->query_skill("guanri-jian", 1) < 150)
                return "你的觀日劍法還不到家，要多練練。";

        if( query("max_neili", me)<2000 )
                return "你內力修為不夠，學不了這一招。";

        message_sort(HIY "\n$n" HIY "一聲長歎，搖頭道：“也罷，也"
                     "罷，你過來。”説完便將$N" HIY "招到一旁的僻"
                     "靜處，輕聲在$N" HIY "耳邊低聲嘀咕了半天，不"
                     "時還伸指捏作劍訣，比劃演示劍招，所示全為闢塵"
                     "劍法絕招的精微要詣，$N" HIY "聽後大有所悟。"
                     "\n\n" NOR, me, this_object());

        command("sigh");
        command("say 你好好努力吧，別像我……唉。");
        tell_object(me, HIC "你學會了「焚陽劍」。\n" NOR);

        if (me->can_improve_skill("sword"))
                me->improve_skill("sword", 1500000);
        if (me->can_improve_skill("guanri-jian"))
                me->improve_skill("guanri-jian", 1500000);

        me->improve_skill("martial-cognize", 1500000);
        set("can_perform/guanri-jian/fen", 1, me);
        addn("family/gongji", -1200, me);
        return 1;
}
