// dizangwang

#include <ansi.h>

inherit NPC;

void greeting(object me);

void create()
{
        set_name("地藏王", ({ "dizang", }));
        set("long", "他容貌威嚴，不可一世。哇！他可是掌管人間生死的神仙。\n");
        set("gender", "男性");
        set("age", 99);
        set("attitude", "peaceful");
        set("shen_type", 0);
        set("per", 18);

        setup();
        carry_object("/clone/cloth/cloth.c")->wear();
        create_family("冥府地藏王殿前", 1, "幽冥之主");
        set("title", HIR "幽冥之主" NOR);
}

void init()
{
        object me;

        ::init();
        me = this_player();
        if (! objectp(me) || ! userp(me))
                return;

        greeting(me);
}

void greeting(object me)
{
        object ob;

        if (! objectp(me) || environment(me) != environment(this_object()))
                return;

        if (! query("startroom") || base_name(environment()) != query("startroom"))
                return;

        if( undefinedp(query("born", me)) )
        {
                command("say"+query("name", me)+"，你快快在無憂池中洗脫筋骨(wash)，然後投胎去吧！");
        } else
        {
                if (wizardp(me))
                        command("heihei"+query("id", me));
                else
                {
                        command("kick"+query("id", me));
                        command("say 凡人跑到這裡來幹什麼？");
                        message_vision("$N一腳把$n踢得無影無蹤。\n\n",
                                       this_object(), me);
                        me->move(VOID_OB);
                        message_vision("\n$N跌落地上，捂著屁股哇哇叫了幾聲。\n",
                                       me);
                }
        }

        if( undefinedp(query("born", me)) && !objectp(present("book",me)) )
        {
                command("say 看你初來乍到，未必懂得規矩。給你一本書，你可以看看！(read book)");
                ob = new ("/clone/misc/newbie");
                ob->move(this_object());
                command("givebookto"+query("id", me));
        }
}

int attempt_apprentice(object ob)
{
        if( !query("born", ob) )
        {
                command("say 你快投胎去，在這裡瞎攪和什麼？");
                return 0;
        }

        command("say 滾！給我一邊兒去！");
}
