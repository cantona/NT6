inherit BUNCHER; 
inherit F_BANKER;

#include <ansi.h>

int do_join(string arg);
int do_unjoin(string arg);
int do_yao();
int do_decide();

void create()
{
        set_name("黃真", ({ "huang zhen", "zhen", "huang" }));
        set("title", HIW"商業協會"HIR"會長"NOR);
        set("long", @LONG
黃真是神劍仙猿穆人清的開門大弟子，也是這
個錢莊的老板，管理襄陽軍餉。
LONG);
        set("nickname", HIY "銅筆鐵算盤" NOR);
        set("gender", "男性");
        set("age", 59);
        set("attitude", "peaceful");
        set("per", 21);
        set("str", 26);
        set("con", 30);
        set("dex", 30);
        set("int", 30);

        set("max_qi", 3500);
        set("max_jing", 2000);
        set("neili", 3000);
        set("max_neili", 300);
        set("jiali", 200);

        set("combat_exp", 500000);
        set("shen_type", 1);

        set("chat_chance_combat", 80);
        set("chat_msg_combat", ({
                (: exert_function, "powerup" :),
                (: exert_function, "recover" :)
        }) );

        set_skill("strike", 140);
        set_skill("cuff", 140);
        set_skill("sword", 140);
        set_skill("force", 140);
        set_skill("parry", 140);
        set_skill("dodge", 140);
        set_skill("literate", 60);

        set_skill("huashan-sword", 140);
        set_skill("huashan-neigong", 140);
        set_skill("poyu-quan", 140);
        set_skill("hunyuan-zhang", 140);
        set_skill("feiyan-huixiang", 140);

        map_skill("sword", "huashan-sword");
        map_skill("parry", "huashan-sword");
        map_skill("force", "huashan-neigong");
        map_skill("cuff", "poyu-quan");
        map_skill("strike", "hunyuan-zhang");
        map_skill("dodge", "feiyan-huixiang");

        prepare_skill("cuff", "poyu-quan");
        prepare_skill("strike", "hunyuan-zhang");

        set("inquiry", ([
                "入會"     : "在我這裡，可以加入(" HIY "join" NOR +
                             CYN ")商業協會。\n" NOR,
                "加入"     : "在我這裡，可以加入(" HIY "join" NOR +
                             CYN ")商業協會。\n" NOR,
                "商業協會" : "在我這裡，可以加入(" HIY "join" NOR +
                             CYN ")商業協會。\n" NOR,
        ]));

        create_family("華山派", 21, "弟子");

        setup();
        carry_object("/clone/misc/cloth")->wear();
}

void init()
{
        add_action("do_check", "check");
        add_action("do_check", "chazhang");
        add_action("do_convert", "convert");
        add_action("do_convert", "duihuan");
        add_action("do_deposit", "deposit");
        add_action("do_deposit", "cun");
        add_action("do_withdraw", "withdraw");
        add_action("do_withdraw", "qu");
        add_action("do_join", "join");
        add_action("do_decide", "decide");
        add_action("do_yao", "yao");
        add_action("do_unjoin", "unjoin");
        delete_temp("busy");
}

int do_join(string arg)
{
        object me = this_player();

        if (! arg || arg != "商業協會")
                return notify_fail(CYN "黃真一楞，說道：你要加入什麼？我"
                                   "這裡是商業協會。\n" NOR);

        if( query("is_vendor", me) )
                return notify_fail(CYN "黃真皺了皺眉，說道：你不是已經加"
                                   "入商業協會了麼？\n" NOR);

        if( query("bad_vendor", me) )
                return notify_fail(CYN "黃真冷笑一聲，說道：既然你已經脫"
                                   "離了商業協會，又回來作甚？\n" NOR);

        tell_object(me, CYN "\n黃真點了點頭，說道：你真的打算(" HIY "dec"
                        "ide" NOR + CYN ")加入商業協會麼？可考慮清楚了？"
                        "\n" NOR);
        set_temp("want_join", 1, me);
        return 1;
}

int do_unjoin(string arg)
{
        object me = this_player();

        if (! arg || arg != "商業協會")
                return notify_fail(CYN "黃真皺了皺眉，說道：你打算脫離什"
                                   "麼？說話不清不楚的。\n" NOR);

        if( !query("is_vendor", me) )
                return notify_fail(CYN "黃真冷笑一聲，沒理你。\n" NOR);

        tell_object(me, CYN "\n黃真嘆了口氣，說道：如果脫離商業協會，以後"
                        "可不能反悔。你真打算(" HIY "decide" NOR + CYN ")"
                        "這麼做麼？\n" NOR);
        set_temp("want_tuoli", 1, me);
        return 1;
}

int do_decide()
{
        object ob, me;
        string *pro;
        me = this_player();

        if( query_temp("want_join", me) )
        {
                message_vision(HIC "$N" HIC "對著$n" HIC "微笑道：如今世"
                               "道錢乃萬能之物，以後好好幹吧。\n" NOR,
                               this_object(), me);

                set("is_vendor", 1, me);
                delete_temp("want_join", me);

                ob = new("/clone/misc/shang-ling");
                ob->move(this_object());
                command("give shang ling to "+query("id", me));
                pro = query("profession", me);
                if( !pro ) pro = ({});
                pro += ({ "vendor" });
                set("profession", pro, me);
                return 1;
        } else
        if( query_temp("want_tuoli", me) )
        {
                message_vision(HIC "$N" CYN "對著$n" HIC "點點頭，人各有"
                               "志，從此以後你我再無瓜葛。\n" NOR,
                               this_object(), me);

                delete("is_vendor", me);
                set("bad_vendor", 1, me);
                delete_temp("want_tuoli", me);

                pro = query("profession", me);
                pro -= ({ "vendor" });
                set("profession", pro, me);
                if (objectp(ob = present("shang ling", me)));
                {
                        message_vision(HIR "$N" HIR "將$n" HIR "的" NOR +
                                       ob->name(1) + HIR "注銷了。\n" NOR,
                                       this_object(), me);
                        destruct(ob);
                }
                return 1;
         }

         return notify_fail(CYN "黃真瞄了你一眼，皺了皺眉，沒理你。\n" NOR);
}

int do_yao()
{
        object ob, me = this_player();

        if( query("bad_vendor", me) )
                return notify_fail(CYN "黃真不耐煩道：走開，走開。你又回"
                                   "來作甚？\n" NOR);

        if( !query("is_vendor", me) )
                return notify_fail(CYN "黃真瞄了你一眼，沒理你。\n" NOR);

        if (present("shang ling", me))
                return notify_fail(CYN "黃真皺了皺眉道：我的天，你連這都"
                                   "要騙？果然是姦商的料。\n" NOR);

        if( query_temp("shang-ling", me) )
                return notify_fail(CYN "黃真皺眉道：剛才我不是才給了你一"
                                   "張麼？那麼快就弄丟了？\n" NOR);

        if( SHOP_D->is_owner(query("id", me)) )
                return notify_fail(CYN "黃真微笑道：你現在不是已經開店了"
                                   "麼？還要這個幹嘛。\n" NOR);

        ob = new("/clone/misc/shang-ling");
        ob->move(this_object());
        set_temp("shang-ling", 1, me);
        command("give shang ling to "+query("id", me));
        command("say 吃飯的家伙自己保管好，別老是來煩我。");
        return 1;
}
