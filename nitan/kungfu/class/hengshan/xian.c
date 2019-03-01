// Last Modified by Sir on May. 22 2001
// xian.c
inherit NPC;
inherit F_MASTER;
inherit F_QUESTER;
inherit F_MANAGER;

#include <ansi.h>;
#include "hengshan.h";

string ask_me();
string ask_yao();
void create()
{
        set_name("定閒師太", ({ "dingxian shitai", "shitai", "dingxian" }) );
        set("long", "她就是恆山派的定閒師太，她身材瘦高，慈眉善目，\n"
                "是現任恆山派掌門人。\n");
        set("gender", "女性");
        set("title", HIB"恆山派第十三代掌門"NOR);
        set("class", "bonze");
        set("age", 45);
        set("attitude", "peaceful");
        set("per", 24);
        set("str", 26);
        set("con", 30);
        set("dex", 30);
        set("int", 28);
        set("inquiry",([
                "剃度"  : "貧尼不剃度弟子。",
                "出家"  : "貧尼不剃度弟子。",
                "還俗"  : "恆山弟子，不能還俗。",
                "白雲熊膽丸" : (: ask_yao :),
                "秘籍"         : (: ask_me :),
                "天長掌法譜" : (: ask_me :),
        ]));
        set("no_get",1);

        set("chat_chance_combat", 60);
        set("chat_msg_combat", ({
                (: exert_function, "recover" :),
                (: exert_function, "recover" :),
                (: perform_action, "sword.yuyin" :),
                (: perform_action, "sword.yuyin" :),
                (: perform_action, "sword.yuyin" :),
                (: perform_action, "sword.liuyun" :),
                (: perform_action, "sword.liuyun" :),
                (: perform_action, "sword.liuyun" :),
                (: command("unwield changjian") :),
                (: command("unwield changjian") :),
                (: command("unwield changjian") :),
                (: command("unwield changjian") :),
                (: command("wield changjian") :),
                (: command("wield changjian") :),
                (: command("wield chacngjian") :),
                (: command("wield changjian") :),
                (: perform_action, "hand.break" :),
                (: perform_action, "hand.break" :),
                (: perform_action, "hand.break" :),
                (: perform_action, "strike.diezhang" :),
                (: perform_action, "strike.diezhang" :),
                (: perform_action, "strike.diezhang" :),
        }));


        set("max_qi", 4000);
        set("max_jing", 2000);
        set("neili", 4000);
        set("max_neili", 4000);
        set("jiali",100);
        set("jingli", 1500);
        set("max_jingli", 1500);
        set("combat_exp", 3000000);
        set("score", 1000);
        set("book_count", 1);
        set("yao_count", 1);

        set_skill("unarmed", 600);
        set_skill("sword", 600);
        set_skill("force", 600);
        set_skill("parry", 600);
        set_skill("dodge", 600);
        set_skill("strike", 600);
        set_skill("hand", 600);
        set_skill("buddhism", 600);
        set_skill("baiyun-xinfa",600);
        set_skill("hengshan-jian", 600);
        set_skill("chuanyun-shou",600);
        set_skill("tianchang-zhang",600);
        set_skill("lingxu-bu", 600);
        set_skill("literate", 600);

        map_skill("force","baiyun-xinfa");
        map_skill("sword", "hengshan-jian");
        map_skill("strike","tianchang-zhang");
        map_skill("hand","chuanyun-shou");
        map_skill("parry", "hengshan-jian");
        map_skill("dodge", "lingxu-bu");

        prepare_skill("hand", "chuanyun-shou");
        prepare_skill("strike", "tianchang-zhang");

        create_family("恆山派", 13, "掌門");
        setup();

        carry_object("/clone/weapon/changjian")->wield();
        carry_object("/d/shaolin/obj/xuan-cloth")->wear();
}
void init()
{
        add_action("do_qiecuo","qiecuo");
}

void attempt_apprentice(object ob)
{
        string name, new_name;

        if (! permit_recruit(ob))
                return;

        if( query("class", ob) != "bonze" )
        {
                command ("say 阿彌陀佛！貧尼不收俗家弟子。");
                return;
        }

        if ((int)ob->query_skill("baiyun-xinfa",1) < 90 )
        {
                command("say 你的本門內功心法火候不足,難以領略更高深的武功。");
                return;
        }
        if( query("shen", ob)<100000 )
        {
                command( "say 你若能多為俠義之舉，當能承我衣砵。\n");
                return;
        }
        command("say 阿彌陀佛，善哉！善哉！好吧，我就收下你了。");
        command("say 希望你能努力行善，濟度眾生，以光大我恆山派。");
        command("recruit "+query("id", ob));
        name=query("name", ob);
        new_name = "儀" + name[2..3];
        command("say 從今以後你的法名叫做" + new_name + "。");
        set("name", new_name, ob);
}


string ask_me()
{
        object ob;

        if( query("family/family_name", this_player()) != "恆山派" )
                return RANK_D->query_respect(this_player()) +
                "與本派毫無瓜葛，我派的武功典籍可不能交給你。";
        if (query("book_count") < 1)
                return "你來晚了，本派的秘籍不在此處。";
        addn("book_count", -1);
        ob = new("/clone/book/tianchang-zhangpu");
        ob->move(this_player());
        command("rumor"+query("name", this_player())+"拿到天長掌法譜啦。\n");
        return "好吧，這本「天長掌法譜」你拿回去好好鑽研。";
}
string ask_yao()
{
        object ob;

        if( query("family/master_id", this_player()) != "dingxianshitai" )
                return RANK_D->query_respect(this_player()) +
                "非我弟子，不知此話從何談起？";
        if (query("yao_count") < 1 || random(3) > 0)
                return "你來晚了，白雲熊膽丸剛巧給人了。";
        addn("yao_count", -1);
        ob = new("/clone/medicine/nostrum/baiyunwan");
        ob->move(this_player());
        return "好吧，這粒白雲熊膽丸就先給你吧。";
}
