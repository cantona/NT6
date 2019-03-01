// This program is a part of NT MudLIB
// chen.c 陳玄風

#include <ansi.h>;
inherit NPC;

#define ZHENJING    "/clone/book/jiuyin2"

void create()
{
        object ob;
        set_name("陳玄風", ({ "chen xuanfeng", "chen", "xuanfeng" }));
        set("title", "黑風雙煞");
        set("nickname", YEL "銅屍" NOR);
        set("gender", "男性");
        set("age", 35);
        set("long", "此人是黃藥師的二弟子，他濃眉大眼，背厚膀寬，軀體甚\n"
                    "是壯健，只是面色微微泛黃。\n");
        set("attitude", "aggressive");
        set("str", 28);
        set("int", 25);
        set("con", 30);
        set("dex", 25);
        set("shen_type", -1);

        set("max_qi", 5000);
        set("max_jing", 3500);
        set("neili", 6000);
        set("max_neili", 6000);
        set("jiali", 220);
        set("level", 20);
        set("combat_exp", 2000000);

        set_skill("claw", 240);
        set_skill("strike", 240);
        set_skill("force", 220);
        set_skill("parry", 240);
        set_skill("dodge", 220);
        set_skill("bibo-shengong", 240);
        set_skill("cuixin-zhang", 240);
        set_skill("jiuyin-baiguzhao", 240);
        set_skill("luoying-shenfa", 220);
        set_skill("martial-cognize", 220);

        map_skill("force", "bibo-shengong");
        map_skill("parry", "jiuyin-zhao");
        map_skill("dodge", "luoying-shenfa");
        map_skill("claw", "jiuyin-zhao");
        map_skill("strike", "cuixin-zhang");

        prepare_skill("claw", "jiuyin-zhao");
        prepare_skill("strike", "cuixin-zhang");

        set("chat_chance_combat", 120);
        set("chat_msg_combat", ({
                (: perform_action, "claw.duo" :),
                (: perform_action, "claw.sha" :),
                (: perform_action, "strike.cui" :),
                (: exert_function, "recover" :),
        }));

        create_family("桃花島", 2, "被逐弟子");
        set("inquiry", ([
                "銅屍" : "江湖上的人都這麼叫我的，你怕不怕？哈哈哈哈。",
                "東邪" : "那是我師父的綽號。",
                "西毒" : "那是與家師齊名的高手之一，是個老毒物，住在白駝山。",
                "南帝" : "段王爺已出家當和尚去了，法名叫一燈。",
                "北丐" : "北丐統領中原的丐幫，勢力頗為強大。",
                "黃蓉" : "她是我師父的獨女，最是刁蠻任性。",
                "洪七公" : "洪七公武功高強，而且教會郭靖那小兒降龍十八掌，可恨！",
                "梅超風" : "她是我的師妹，也是我的內室。",
                "陳玄風" : "不就是我麼？你是白痴啊？",
                "黃藥師" : "他是我師父。"
        ]));
        set_temp("apply/damage", 100);
        set_temp("apply/unarmed_damage", 100);
        set_temp("apply/armor", 200);

        setup();
        if (clonep())
        {
                ob = find_object(ZHENJING);
                if (! ob) ob = load_object(ZHENJING);

                if (environment(ob) && random(3) == 1)
                {
                        ob = new(ZHENJING);
                        ob->move(this_object());
                }
                else if (! environment(ob))
                        ob->move(this_object());
        }
        carry_object("/clone/cloth/bupao")->wear();
}

void attempt_apprentice(object ob)
{
        command("say 少煩我，快滾！");
}

int accept_fight(object me)
{
        command("say 給我滾開！");
        return 0;
}

int accept_hit(object me)
{
        command("say 找死！");
        kill_ob(me);
        return 1;
}

void kill_ob (object ob)
{
        object me = this_object();
        object where = environment(me);
        object guard = present("mei chaofeng", where);

        set_temp("my_killer", ob);
        ::kill_ob(ob);

        if (guard && ! guard->is_fighting())
        {
                message_vision(HIW "\n$N" HIW "大怒道：居然欺負到我們黑風雙煞"
                               "頭上來了，死吧！\n\n" NOR, guard);
                guard->kill_ob(ob);
        }
}

void die()
{
        object obj, me;
        int i, flag;

        flag = 0;
        me = this_object();
        if (objectp(obj = query_last_damage_from()))
                set_temp("kill_xuanfeng", 1, obj);
        else
                return;

        if( query_temp("kill_chaofeng", obj) )
        {
                set("kill_th_traitor", 1, obj);
                flag = 1;
        }

        if (flag)
                message_vision(HIR"陳玄風慘嚎一聲，道：賊婆娘，我陪你來了！！！\n"NOR, this_object());
        else
                message_vision(HIR"陳玄風慘嚎一聲，道：賊婆娘，給我報仇！！！\n"NOR, this_object());

        ::die();
}
