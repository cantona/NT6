// due.c

inherit NPC;
inherit F_MASTER;
inherit F_QUESTER;

#define FUMODAO         "/d/shaolin/obj/fumo-dao"
#define HEISUO          "/clone/lonely/heisuo1"
#define JIUHUAN         "/clone/lonely/jiuhuan"

mixed ask_me();
mixed ask_dao();
mixed ask_zhang();

void create()
{
        object ob1, ob2;
        set_name("渡厄", ({ "du e", "e" }) );
        set("title", "少林長老");
        set("gender", "男性");
        set("age", 90);
        set("long",
                "這是一個面頰深陷，瘦骨零丁的老僧，他臉色"
                "枯黃，如同一段枯木。\n");

        set("attitude", "peaceful");
        set("class", "bonze");
        set("combat_exp", 2350000);

        set("str", 34);
        set("int", 36);
        set("con", 35);
        set("dex", 33);

        set("qi", 5800);
        set("max_qi", 2900);
        set("neili", 7200);
        set("max_neili", 7200);
        set("level", 40);
        set("jiali", 110);

        create_family("少林派", 35, "弟子");
        assign_apprentice("弟子", 0);

        set_skill("buddhism", 320);
        set_skill("force", 270);
        set_skill("whip", 270);
        set_skill("parry", 270);
        set_skill("dodge", 260);

        set_skill("hunyuan-yiqi", 270);
        set_skill("shaolin-xinfa", 270);
        set_skill("riyue-bian", 270);
        set_skill("shaolin-shenfa", 260);

        map_skill("force", "hunyuan-yiqi");
        map_skill("whip",  "riyue-bian");
        map_skill("parry", "riyue-bian");
        map_skill("dodge", "shaolin-shenfa");

        set_skill("finger", 260);
        set_skill("strike", 260);
        set_skill("nianhua-zhi", 260);
        set_skill("sanhua-zhang", 260);
        set_skill("martial-cognize", 220);

        map_skill("finger", "nianhua-zhi");
        map_skill("strike", "sanhua-zhang");

        prepare_skill("finger", "nianhua-zhi");
        prepare_skill("strike", "sanhua-zhang");

        set_skill("medical", 250);
        set_skill("shaolin-yishu", 250);

        set("inquiry", ([
                "伏魔杖"     : (: ask_me :),
                "伏魔刀"     : (: ask_dao :),
                "九環錫杖"   : (: ask_zhang :),
        ]));

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

                ob2 = find_object(JIUHUAN);
                if (! ob2) ob2 = load_object(JIUHUAN);
                if (! environment(ob2))
                {
                        ob2->move(this_object());
                        set_temp("handing", ob2);
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
                command("say 大膽鼠輩，乳臭未乾，竟敢偷入金剛伏魔圈，且讓老衲來超度與你！");
                kill_ob(this_player());
                return 1;
        }

        if( query_temp("valid_in_fumoquan", this_player()) != 1 )
        {
                command("heng");
                return 1;
        }

        if (present("fumo zhang", this_player()))
                return RANK_D->query_respect(this_player()) +
                "寶杖只有一把，而且就在你身上，真是貪得無饜！";

        if (present("fumo zhang", environment()) )
                return RANK_D->query_respect(this_player()) +
                "寶杖只有一把，而且就在這裏任你取走，真是貪得無饜！";

        ob = get_object("/d/shaolin/obj/fumo-zhang");
        if (! ob || environment(ob) && environment(ob) != this_object())
                return "抱歉，你來晚了，伏魔杖已經給人取走了。";
        ob->move(this_player());

        message_vision("\n渡厄長笑一聲，點點頭，從身後的樹洞裏取出伏魔杖交給$N。\n\n", this_player());

        return "你既然能闖進金剛伏魔圈來，必然是當今武林中的非凡人物，這伏魔杖是適逢其主了！";
}

mixed ask_dao()
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

        ob = find_object(FUMODAO);
        if (! ob) ob = load_object(FUMODAO);

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
                return "此時伏魔刀並不在老衲手中。";

        ob->move(this_object());

        command("buddhi");
        command("give fumo dao to "+query("id", me));
        return 1;
}

mixed ask_zhang()
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

        ob = find_object(JIUHUAN);
        if (! ob) ob = load_object(JIUHUAN);

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
                return "此時九環錫杖並不在老衲手中。";

        ob->move(this_object());

        command("buddhi");
        command("give jiuhuan xizhang to "+query("id", me));
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

        case "纏繞訣" :
                return MASTER_D->teach_pfm(me, this_object(),
                        ([ "perform" : "can_perform/riyue-bian/chan",
                           "name"    : "纏繞訣",
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
