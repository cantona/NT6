// clone/shop/hesanqi.c
// Last modified by winder 2003.10.20
// 商業系統的初級階段：小販的商令管理者。

inherit NPC;
inherit F_BANKER;

#include <ansi.h>;

int do_join(string arg);
int do_unjoin(string arg);
int do_yao();
int do_decide();

void create()
{
        set_name("何三七", ({ "he sanqi", "he", "sanqi" }));
        set("long", @LONG
浙南雁蕩山高手何三七，自幼以賣餛飩為生，學成武功後，仍是挑
着副餛飩擔遊行江湖，這副餛飩擔可是他的標記。他雖一身武功，
但自甘淡泊，以小本生意過活，武林中人説起來都是好生相敬。天
下市巷中賣餛飩的何止千萬，但既賣餛飩而又是武林中人，那自是
非何三七不可了。
LONG);
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

        set_skill("hand", 140);
        set_skill("cuff", 140);
        set_skill("parry", 140);
        set_skill("dodge", 140);

        set_skill("changquan", 140);
        set_skill("sanshou", 140);
        set_skill("yanfly", 140);

        map_skill("parry", "changquan");
        map_skill("cuff", "changquan");
        map_skill("hand", "sanshou");
        map_skill("dodge", "yanfly");

        prepare_skill("cuff", "changquan");
        prepare_skill("hand", "sanshou");

        set("inquiry", ([
                "入會"     : "在我這，可以加入("HIY"join"CYN")商業協會。\n"NOR,
                "加入"     : "在我這，可以加入("HIY"join"CYN")商業協會。\n"NOR,
                "商業協會" : "在我這，可以加入("HIY"join"CYN")商業協會。\n"NOR,
        ]));

        create_family("雁蕩派", 5, "弟子");

        setup();
        carry_object(CLOTH_DIR"cloth")->wear();
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
        add_action("do_yao", "yao3");
        add_action("do_unjoin", "unjoin");
        delete_temp("busy");
}

int do_join(string arg)
{
        object me = this_player(), ob = this_object();

        if (! arg || arg != "商業協會")
                return notify_fail(CYN+query("name", ob)+"一楞，説道：你要加入什麼？我這裏是商業協會。\n"NOR);
        if( query("is_vendor", me) )
                return notify_fail(CYN+query("name", ob)+"皺了皺眉，説道：你不是已經加入商業協會了麼？\n"NOR);
        if( query("bad_vendor", me) )
                return notify_fail(CYN+query("name", ob)+"冷笑一聲，説道：既然你已經脱離了商業協會，又回來作甚？\n"NOR);
        tell_object(me,CYN+query("name", ob)+"點了點頭，説道：你真的打算("HIY"decide"NOR+CYN")加入商業協會麼？可考慮清楚了？\n"NOR);
        set_temp("want_join", 1, me);
        return 1;
}

int do_unjoin(string arg)
{
        object me = this_player(), ob = this_object();

        if (! arg || arg != "商業協會")
                return notify_fail(CYN+query("name", ob)+"皺了皺眉，説道：你打算脱離什麼？説話不清不楚的。\n"NOR);
        if( !query("is_vendor", me) )
                return notify_fail(CYN+query("name", ob)+"冷笑一聲，沒理你。\n"NOR);
        tell_object(me,CYN+query("name", ob)+"歎了口氣，説道：如果脱離商業協會，以後可不能反悔。你真打算("HIY"decide"NOR+CYN")這麼做麼？\n"NOR);
        set_temp("want_tuoli", 1, me);
        return 1;
}

int do_decide()
{
        object ob, me = this_player();

        if( query_temp("want_join", me) )
        {
                message_vision(HIC "$N" HIC "對着$n" HIC "微笑道：如今世道錢乃萬能之物，以後好好幹吧。\n" NOR, this_object(), me);

                set("is_vendor", 1, me);
                delete_temp("want_join", me);

                ob = new(__DIR__"shangling");
                ob->move(this_object());
                command("giveshanglingto"+query("id", me));
                return 1;
        }
        else
                if( query_temp("want_tuoli", me) )
                {
                        message_vision(HIC "$N" CYN "對着$n" HIC "點點頭，人各有志，從此以後你我再無瓜葛。\n" NOR, this_object(), me);
                        delete("is_vendor", me);
                        set("bad_vendor", 1, me);
                        delete_temp("want_tuoli", me);

                        if (objectp(ob = present("shang ling", me)));
                        {
                                message_vision(HIR "$N" HIR "將$n" HIR "的" NOR + ob->name(1) + HIR "註銷了。\n" NOR, this_object(), me);
                                destruct(ob);
                        }
                        return 1;
                 }

         return notify_fail(CYN+query("name", ob)+"瞄了你一眼，皺了皺眉，沒理你。\n"NOR);
}

int do_yao()
{
        object ob, me = this_player();
        
        ob = this_object();
        if( query("bad_vendor", me) )
                return notify_fail(CYN+query("name", ob)+"不耐煩道：走開，走開。你又回來作甚？\n"NOR);

        if( !query("is_vendor", me) )
                return notify_fail(CYN+query("name", ob)+"瞄了你一眼，沒理你。\n"NOR);

        if (objectp(present("shang ling", me)))
                return notify_fail(CYN+query("name", ob)+"皺了皺眉道：我的天，你連這都要騙？果然是奸商的料。\n"NOR);

        if( query_temp("shang-ling", me) )
                return notify_fail(CYN+query("name", ob)+"皺眉道：剛才我不是才給了你一張麼？那麼快就弄丟了？\n"NOR);

        if( SHOP_D->is_owner(query("id", me)) )
                return notify_fail(CYN+query("name", ob)+"微笑道：你現在不是已經開店了麼？還要這個幹嘛。\n"NOR);

        ob = new(__DIR__"shangling");
        ob->move(this_object());
        set_temp("shang-ling", 1, me);
        command("giveshanglingto"+query("id", me));
        command("say 吃飯的傢伙自己保管好，別老是來煩我。");
        return 1;
}