// dunan.c

inherit NPC;
inherit F_MASTER;
inherit F_QUESTER;

#define HEISUO          "/clone/lonely/heisuo2"
#define CAOJIE          "/clone/lonely/caojie"

mixed ask_me();
mixed ask_cao();

void create()
{
        object ob1, ob2;
        set_name("渡難", ({ "du nan", "nan" }) );
        set("title", "少林長老");
        set("gender", "男性");
        set("age", 90);
        set("long",
                "這是一個面頰深陷，瘦骨零丁的老僧，他臉色漆黑，象是生鐵鑄成。\n");

        set("attitude", "peaceful");
        set("class", "bonze");
        set("combat_exp", 2500000);

        set("str", 33);
        set("int", 32);
        set("con", 34);
        set("dex", 31);

        set("qi", 5200);
        set("max_qi", 2600);
        set("neili", 7400);
        set("max_neili", 7400);
        set("level", 40);
        set("jiali", 100);

        create_family("少林派", 35, "弟子");
        assign_apprentice("弟子", 0);

        set_skill("buddhism", 300);
        set_skill("force", 260);
        set_skill("whip", 260);
        set_skill("parry", 260);
        set_skill("dodge", 250);

        set_skill("hunyuan-yiqi", 260);
        set_skill("shaolin-xinfa", 260);
        set_skill("riyue-bian", 260);
        set_skill("shaolin-shenfa", 250);

        map_skill("force", "hunyuan-yiqi");
        map_skill("whip",  "riyue-bian");
        map_skill("parry", "riyue-bian");
        map_skill("dodge", "shaolin-shenfa");

        set_skill("strike", 260);
        set_skill("xumishan-zhang", 260);
        set_skill("claw", 250);
        set_skill("hand", 250);
        set_skill("longzhua-gong", 250);
        set_skill("qianye-shou", 250);
        set_skill("martial-cognize", 220);

        map_skill("strike", "xumishan-zhang");

        prepare_skill("strike", "xumishan-zhang");

        set_skill("medical", 220);
        set_skill("shaolin-yishu", 220);

        set("inquiry", ([
                "菩提子"     : (: ask_me :),
                "神草結"     : (: ask_cao :),
        ]));

        set("count", 0);
        if (random(16) == 8) addn("count", 1);

        set("master_ob",4);
        setup();

        if (clonep())
        {
                ob1 = find_object(HEISUO);
                if (! ob1) ob1 = load_object(HEISUO);
                if (! environment(ob1))
                {
                        ob1->move(this_object());
                        ob1->wield();
                } else
                {
                        ob1 = new("/d/shaolin/obj/changbian");
                        ob1->move(this_object());
                        ob1->wield();
                }

                ob2 = find_object(CAOJIE);
                if (! ob2) ob2 = load_object(CAOJIE);
                if (! environment(ob2))
                {
                        ob2->move(this_object());
                        ob2->wear();
                }
        }
        carry_object("/d/shaolin/obj/xuan-cloth")->wear();
}

mixed ask_me()
{
        mapping fam;
        object ob;

        if( !query_temp("valid_in_fumoquan", this_player()) )
        {
                command("say 大膽鼠輩，乳臭未幹，竟敢偷入金剛伏魔圈，且讓老衲來超度與你！");
                kill_ob(this_player());
                return 1;
        }

        if( query_temp("valid_in_fumoquan", this_player()) != 1 )
        {
                command("heng");
                return 1;
        }

        if (uptime() < 1800)
                return "菩提子乃天地之靈物，制煉艱難無比，我現在可沒有。";

        if ( present("puti zi", this_player()) )
                return RANK_D->query_respect(this_player()) +
                "菩提子只有一顆，而且就在你身上，真是貪得無饜！";

        if ( present("puti zi", environment()) )
                return RANK_D->query_respect(this_player()) +
                "菩提子只有一顆，而且就在這裡任你取走，真是貪得無饜！";

        if (query("count") < 1)
                return "菩提子乃天地之靈物，採集艱難無比，我這裡現在可沒有。";

        ob = new("/d/shaolin/obj/puti-zi");
        ob->move(this_player());

        addn("count", -1);

        message_vision("\n渡難慘然一笑，接著長嘆一聲，從樹洞裡取出個白玉磁瓶，倒出菩提子遞給$N。\n\n", this_player());

        return "我等昔年于佛祖座前發下宏願，每十年遍訪名山大川，歷盡艱險，\n" +
               "方採得數顆菩提子，君乃有緣人，能得此造化奇物，望好自為之！";
}

mixed ask_cao()
{
        object ob;
        object me;
        object owner;

        me = this_player();

        if( !query_temp("valid_in_fumoquan", me) )
        {
                command("say 大膽鼠輩，竟敢偷入金剛伏魔圈，且讓老衲來超度與你！");
                kill_ob(me);
                return 1;
        }

        if( query_temp("valid_in_fumoquan", me) != 1 )
        {
                command("heng");
                return 1;
        }

        if( query("combat_exp", me)<1000000 )
                return "你這點微末本事，打聽達摩祖師留下的利器作甚？";

        ob = find_object(CAOJIE);
        if (! ob) ob = load_object(CAOJIE);

        owner = environment(ob);
        while (owner)
        {
                if (owner->is_character() || ! environment(owner))
                        break;
                owner = environment(owner);
        }

        if (owner == me)
                return "東西不已經給你了麼？你還打算怎的？";

        if (owner == environment(me))
        {
                command("sneer");
                command("get"+query("id", ob));
                return "百年來還沒人敢愚弄老衲，滾開！";
        }

        if (objectp(owner) && owner != this_object())
                return "此時神草結並不在老衲手中。";

        ob->move(this_object());

        command("sigh");
        command("giveshencaojieto"+query("id", me));
        return 1;
}

int accept_ask(object me, string topic)
{
        switch (topic)
        {
        case "歷練" :
        case "歷煉" :
        case "鍛煉" :
                return QUEST_D->accept_ask(this_object(), me, topic);
                break;

        case "傷字訣" :
                return MASTER_D->teach_pfm(me, this_object(),
                        ([ "perform" : "can_perform/riyue-bian/shang",
                           "name"    : "傷字訣",
                           "sk1"     : "riyue-bian",
                           "lv1"     : 100,
                           "sk2"     : "force",
                           "lv2"     : 100,
                           "gongxian": 1000, ]));
                break;

        default:
                return 0;
        }
}

#include "/kungfu/class/shaolin/du.h"
