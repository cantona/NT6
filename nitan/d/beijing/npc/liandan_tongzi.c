// liandan_tongzi.c

#include <ansi.h>

inherit NPC;

mixed ask_caiyao();

void create()
{
        set_name("小童", ({"xiao tong", "xiao", "tong"}));
        set("gender", "男性");
        set("age", 12);
        set("long",
                "這是煉丹房中的掌管藥材的童子。他年紀不大，但看起來\n"
                "顯得少年老成。\n");
        set("attitude", "friendly");
        set("shen_type",1);
        set("str", 21);
        set("int", 22);
        set("con", 23);
        set("dex", 22);
        set("qi", 600);
        set("max_qi", 600);
        set("jing", 400);
        set("max_jing", 400);
        set("neili", 1200);
        set("max_neili", 1200);;

        set("combat_exp", 300000);

        set("inquiry", ([
                "藥材" : (: ask_caiyao :),
                "藥"   : (: ask_caiyao :),
                "採藥" : (: ask_caiyao :),
                "草藥" : (: ask_caiyao :),
                "yaocai" : (: ask_caiyao :),
        ]) );
        set("caiyao", 12);

        setup();
}

mixed ask_caiyao()
{
        object me = this_player();

        switch(query_temp("caiyao", me) )
        {
        case 1:
                return "叫你去採藥，還呆在這幹嘛！";

        case 2:
                return "藥採來了？還不快給我！";
        }

        switch(query_temp("liandan", me) )
        {
        case 1:
                // 已經打聽過了練丹的消息了
                break;

        case 2:
                return "藥材已經準備好，可以去了。";

        case 3:
                return "你不是在裡面煉藥嗎？怎麼出來了。";

        case 4:
                return "還是先去復命吧。";

        default:
                return "你又不煉藥，要藥材幹什麼？";
        }

        message_vision(CYN "小童對$N" CYN "說道：好吧，那你"
                       "去城西的林子裡挖幾樣新鮮的草藥來。\n" NOR, me);
        set_temp("caiyao", 1, me);
        addn("caiyao", -1);
        return 1;
}

int accept_object(object me, object ob)
{
        int exp, pot;

        if (userp(ob) || ob->is_character() || ob->is_item_make())
                return 0;

        if( query_temp("caiyao", me)<1 )
        {
                command("say 我什麼時候叫你拿這個給我的？");
        } else
        if( query_temp("caiyao", me) == 1 )
        {
                command("say 是誰幫你找的東西來敷衍我，別以為我小就好騙。");
        } else
        if( strsrch(query("name", ob),"不知名草藥")<0 )
        {
                command("say 你欺我小啊？拿這種東西騙我。\n");
        } else
        {
                command("say 好吧，讓我來給你加工。");
                command("say 加工好了，你現在直接去丹房煉丹（liandan）就行了。");
                delete_temp("caiyao", me);
                set_temp("liandan", 2, me);

                if( query("combat_exp", me)<1000000 )
                {
                        exp = 100 + random(140);
                        pot = exp / 3;
                }
                else
                {
                        exp = 20 + random(100);
                        pot = exp / 3;
                }

                GIFT_D->work_bonus(me, ([ "exp" : exp, "pot" : pot ]));
                destruct(ob);
                return 1;
        }
        return 0;
}

