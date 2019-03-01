//NPC /npc/xiaoqing.c
#include <ansi.h>
inherit NPC;

void greeting(object);
void init();
string inquiry_gao();

void create()
{
        set_name("小青", ( { "qing", "xiao qing" }) );
        set("title", "藥劑師");
        set("gender", "女性" );
        set("age", 17);
        set("long",
              "這是個聰明乖巧的小姑娘，打扮的很樸素，一襲青衣，卻也顯得落落有致。\n"
             );
        set("attitude", "friendly");
        set("shen_type", -1);

        set("str", 20);
        set("int", 29);
        set("con", 23);
        set("dex", 22);

        set("max_qi", 430);
        set("max_jing", 220);
        set("neili", 320);
        set("max_neili", 320);

        set("combat_exp", 60000);
        set("score", 1000);

        set_skill("force", 40);
        set_skill("dodge", 50);
        set_skill("unarmed", 35);
        set_skill("parry", 40);
        set_temp("apply/attack", 10);
        set_temp("apply/defense", 15);
        set_temp("apply/damage", 17);
        set_temp("apply/armor", 10);

        set_temp("dan",0);
        set_temp("times",5);

        set("inquiry", ([
            "海口大碗" : "這『海口大碗』你可以拿到頂東頭小院兒去，灌水喝。\n",
            "藥罐" : "藥罐在那兒，你自己看吧！\n",
            "蛇膽膏" : (: inquiry_gao :),
        ]));

        setup();
        carry_object("/d/baituo/obj/qingpao")->wear();
        carry_object("/d/baituo/obj/zheng");
}

void init()
{
        object ob;

        ::init();

        if( interactive(ob = this_player()) && !is_fighting() )
        {
                remove_call_out("greeting");
                call_out("greeting", 1, ob);
        }
}

void greeting(object ob)
{

        if( !ob || environment(ob) != environment() ) return;
        if(random(2)==1)
        {
                say("小青笑吟吟地說道：這位" + RANK_D->query_respect(ob) +
                    "請進，見到你真高興。\n");
                return;
        } else
        {
                say("小青笑了笑說道：這位" + RANK_D->query_respect(ob) +
                    "快請進吧。 \n");
                return;
        }
}

string inquiry_gao()
{
        object ob = this_player();

        if (query_temp("dan") == 3)
                return "你沒見我已經作好了嘛！\n";

        if (query_temp("times") < 1)
                return "莊主現在已經不叫我做『蛇膽膏』了！\n";

        say("這位" + RANK_D->query_respect(ob)+
            "不瞞您說。師傅讓我作『蛇膽膏』，\n可我",ob);
        switch (query_temp("dan"))
        {
        case 0: write(HIY "差一只青蛇膽，一只金蛇膽。\n" NOR);
                break;
        case 1: write(HIY "還差一只金蛇膽。\n" NOR);
                break;
        case 2: write(HIY "還差一只青蛇膽。\n" NOR);
                break;
        }
        return "不知哪位好心人能幫幫我呢？\n";
}


int accept_object(object who, object ob)
{
        object obn;

        if( query("id", ob) != "qingdan" && 
            query("id", ob) != "jindan" )
        {
                command("shake");
                command("say 這是啥呀？我可不要哦。");
                return 0;
        }

        if (query_temp("times") < 1)
        {
                command("sigh");
                command("say 我現在已經不做『蛇膽膏』了。");
                return 0;
        }

        if( query("id", ob) == "jindan" )
        {
                if (query_temp("dan") == 2)
                {
                        message_vision("小青一看是金蛇膽，滿臉遺憾地對\n"
                                       "$N說：我還差青蛇膽，不缺金蛇膽。\n", who);
                        return 0;
                }
                addn_temp("dan", 2);
                if (query_temp("dan") == 2)
                {
                        message_vision("你把金蛇膽遞給了小青，她高興得跳了起來。\n"
                                       "摟著$N的脖子說：還差青蛇膽就大功告成了！\n",who);
                        destruct(ob);
                        return 1;
                }
        }
        if( query("id", ob) == "qingdan" )
        {
                if (query_temp("dan") == 1)
                {
                        message_vision("小青一看是青蛇膽，滿臉遺憾\n"
                                       "地對$N說：我還差金蛇膽，不缺青蛇膽。\n",who);
                        return 0;
                }
                addn_temp("dan", 1);
                if (query_temp("dan") == 1)
                {
                        message_vision("你把青蛇膽遞給了小青，她高興得跳了起來。\n"
                                       "摟著$N的脖子說：還差就金蛇膽大功告成了！\n",who);
                        destruct(ob);
                        return 1;
                }
        }

        command("kiss"+query("id", who));
        write(HIY "只見小青手腳麻利地把兩只蛇膽投入藥罐中，又加入一些\n"
              "不知是什麼的藥粉，然後把稀裡嘩啦一搖，嘿！『蛇膽膏』做\n"
              "成了。\n" NOR );
        message_vision("小青很神秘地湊近$N悄悄說了些什麼。\n", who);
        tell_object(who,"我偷偷拿了一點『蛇膽膏』送給你，莊主不會發現的。\n");
        message_vision("小青深情地望了$N一眼，臉紅了。\n",who);
        obn = new("/d/baituo/obj/shedangao");
        obn->move(who);
        set_temp("dan",0);
        addn_temp("times", -1);
        destruct(ob);
        return 1;
}

