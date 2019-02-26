// dizangwang

#include <ansi.h>

inherit NPC;

void greeting(object me);

void create()
{
        set_name("盤古", ({ "pan gu", }));
        set("long", "他容貌威嚴，不可一世。哇！他就是開天闢地的神仙。\n");
        set("gender", "男性");
        set("age", 999);
        set("attitude", "peaceful");
        set("shen_type", 0);
        set("per", 30);

        setup();
        carry_object("/clone/cloth/cloth.c")->wear();
        carry_object("/clone/weapon/bigaxe.c")->wield();
        create_family("萬物之神", 1, "天地之主");
        set("title", HIY "萬物之神" NOR);
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
                command("say "+query("name", me)+"，你快快選擇(choose)好角色性格，然後投胎去吧！");
                tell_object(me, CYN "特別提示：雖然性格對你拜哪個門派並沒有影響，但是它會影響你學某些武功！\n" NOR);
                tell_object(me, HIY "新手導師：請輸入 help start 來獲知針對各個門派所推薦的性格。(拜師之前可以在北京文廟調整性格)\n" NOR);
                tell_object(me, "您可以選擇(choose)的角色性格如下：\n"
                            HIC "1" NOR ".光明磊落  "
                            HIC "2" NOR ".狡黠多變  "
                            HIC "3" NOR ".心狠手辣  "
                            HIC "4" NOR ".陰險奸詐 ("
                            HIC "choose 1" NOR "-" HIC "4" NOR ")\n\n");

        } else
        {
                if (wizardp(me))
                        command("heihei "+query("id", me));
                else
                {
                        command("kick "+query("id", me));
                        command("say 凡人跑到這裏來幹什麼？");
                        message_vision("$N一腳把$n踢得無影無蹤。\n\n",
                                       this_object(), me);
                        me->move(VOID_OB);
                        message_vision("\n$N跌落地上，捂着屁股哇哇叫了幾聲。\n",
                                       me);
                }
        }

        if( undefinedp(query("born", me)) && !objectp(present("book",me)) )
        {
                command("say 看你初來乍到，未必懂得規矩。給你一本書，你可以看看！(read book)");
                ob = new ("/clone/misc/newbie");
                ob->move(this_object());
                command("give book to "+query("id", me));
        }
}

int attempt_apprentice(object ob)
{
        if( !query("born", ob) )
        {
                command("say 你快投胎去，在這裏瞎攪和什麼？");
                return 0;
        }

        command("say 滾！給我一邊兒去！");
}
