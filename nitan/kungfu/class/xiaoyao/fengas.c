// This program is a part of NT MudLIB

#include <ansi.h>
#include "xiaoyao.h"

inherit NPC;
inherit F_MASTER;

mixed ask_item1();
mixed ask_item2();
mixed ask_me();

void create()
{
        set_name("馮阿三", ({ "feng asan", "feng" , "asan"}));
        set("long", "據説他就是魯班的後人，當代的第一巧匠。是\n"
                    "設計機關的能手。\n");
        set("title", "逍遙派函谷八友");
        set("nickname", HIY "巧匠" NOR);
        set("gender", "男性");
        set("age", 40);
        set("attitude", "friendly");
        set("class", "alchemist");
        set("shen_type", 1);
        set("str", 38);
        set("int", 28);
        set("con", 30);
        set("dex", 28);

        set("max_qi", 1800);
        set("max_jing", 1400);
        set("neili", 2200);
        set("max_neili", 2200);
        set("jiali", 70);
        set("level", 10);
        set("combat_exp", 500000);

        set_skill("force", 120);
        set_skill("xiaowuxiang", 120);
        set_skill("dodge", 120);
        set_skill("feiyan-zoubi", 120);
        set_skill("strike", 100);
        set_skill("liuyang-zhang", 100);
        set_skill("hand", 100);
        set_skill("qingyun-shou", 100);
        set_skill("parry", 120);
        set_skill("blade", 120);
        set_skill("ruyi-dao", 120);
        set_skill("literate", 100);
        set_skill("qimen-wuxing", 180);
        set_skill("construction", 180);
        set_skill("martial-cognize", 100);

        map_skill("force", "xiaowuxiang");
        map_skill("dodge", "feiyan-zoubi");
        map_skill("hand", "qingyun-shou");
        map_skill("strike", "liuyang-zhang");
        map_skill("parry", "ruyi-dao");
        map_skill("blade", "ruyi-dao");

        prepare_skill("hand", "qingyun-shou");
        prepare_skill("strike", "liuyang-zhang");

        set("inquiry", ([
                "鐵八卦" : (: ask_item1 :),
                "佈陣箱" : (: ask_item2 :),
                "機關"   : (: ask_me :),
        ]));

        if (random(5) > 3)
                set("bagua_count", 1);

        if (random(4) > 2)
                set("xiang_count", 1);

        create_family("逍遙派", 3, "弟子");

        set("chat_chance_combat", 120);
        set("chat_msg_combat", ({
                (: perform_action, "hand.zhuo" :),
                (: perform_action, "strike.pan" :),
                (: perform_action, "blade.ruyi" :),
                (: exert_function, "recover" :),
        }));

        set("master_ob", 3);
        setup();
        carry_object("/clone/cloth/cloth")->wear();
        carry_object("/clone/weapon/blade")->wield();
}

void attempt_apprentice(object ob)
{
        if (! permit_recruit(ob))
                return;

        if (ob->query_int() < 26)
        {
                command("say 你腦袋又不靈光，能跟我做什麼？");
                return;
        }

        command("say 好吧，我就收下你了，多幹活，少説話！");
        command("recruit "+query("id", ob));
}

mixed ask_item1()
{
        object me;
        object ob;

        me = this_player();

        if( query("family/family_name", me) != "逍遙派" )
                return "你是誰？哪裏來的？我認識你麼？";

        if( query("family/master_id", me) != "wuyazi"
            && query("family/master_id", me) != "suxinghe" )
                return "哈哈，你剛入我逍遙派就問我要東西？";

        if (me->query_skill("qimen-wuxing", 1) < 80)
                return "你又不懂奇門五行，拿去幹嘛用？";

        if (query("bagua_count") < 1)
                return "我這裏也沒有了，你自己去城裏買一個吧。";

        addn("bagua_count", -1);
        ob = new("/d/taohua/obj/bagua");
        ob->move(this_object());

        command("givetiebaguato"+query("id", me));
        return "這隻鐵八卦你就先拿去用吧。";
}

mixed ask_item2()
{
        object me;
        object ob;

        me = this_player();

        if( query("family/family_name", me) != "逍遙派" )
                return "你是誰？哪裏來的？我認識你麼？";

        if( query("family/master_id", me) != "wuyazi"
            && query("family/master_id", me) != "suxinghe" )
                return "哈哈，你剛入我逍遙派就問我要東西？";

        if (me->query_skill("qimen-wuxing", 1) < 80)
                return "你又不懂奇門五行，拿去幹嘛用？";

        if (query("xiang_count") < 1)
                return "我這裏也沒有了，你等兩天再來吧。";

        addn("xiang_count", -1);
        ob = new("/d/taohua/obj/xiang");
        ob->move(this_object());

        command("givebuzhenxiangto"+query("id", me));
        return "佈陣箱給你了，可別到處去瞎攪和。";
}

mixed ask_me()
{
        object ob;

        ob = this_player();
        if (random(100) < 70)
                return "我在設計機關方面是有點特長，讓大家見笑了。";

        command("laugh");
        return "別吵着我，我在看書呢。哈哈，芝麻開門。。。。這書真好笑\n";
}
