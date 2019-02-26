// This program is a part of NT MudLIB

#include <ansi.h>
inherit NPC;

int ask_skill1();
int ask_skill2();
void destroying(object, object);

void create()
{
        set_name("丁典", ({ "ding dian", "ding" }));
        set("long",
                "這人滿臉虯髯，頭髮長長的直垂至頸，衣衫破爛不堪，簡直如同荒山中的野人。\n");
        set("gender", "男性");
        set("age", 35);

        set_skill("unarmed", 120);
        set_skill("dodge", 100);
        set_skill("parry", 100);
        set_skill("ding-dodge", 120);
        set_skill("ding-force", 120);
        set_skill("ding-unarmed", 120);
        set_skill("shenzhaojing", 300);
        map_skill("force", "shenzhaojing");
        map_skill("parry", "shenzhaojing");
        map_skill("unarmed", "shenzhaojing");
        map_skill("dodge","ding-dodge");
        prepare_skill("unarmed","shenzhaojing");
        set("max_neili",2000);
        set("neili",2000);
        set("jiali",100);

        set("combat_exp", 600000);
        set("shen_type", 1);
        set("chat_chance", 10);
        set("chat_msg", ({
                "丁典輕輕歎了一口氣。那歎息中，竟有憂傷、温柔之意。\n",
                "丁典嘴角掛着一絲微笑，痴望遠處高樓紗窗上那一盆鮮花。\n",
                "丁典大聲道：怎麼會忘記？決不會的！難道……難道是生了病？\n",
                "丁典喃喃道：就算是生了病，也會叫人來換花啊！\n",
        }) );
        set("inquiry", ([
                "凌霜華" : "“唉……”，然後指了指牢外那座小樓的窗口，啥也不説了。\n",
                "喚醒"   : (: ask_skill1 :),
                "療精"   : (: ask_skill2 :),
        ]));

        setup();
        carry_object("/clone/cloth/cloth")->wear();

}

int accept_object(object me, object obj)
{
        object key;
        if( query("id", obj) == "green flower" && 
             filter_color(query("name", obj),1) == "綠玉如意"){
                message("vision",me->name()+"給丁典一盆綠菊花。\n",environment(me),
                        ({me}));
                key = new("/clone/book/shenzhaojing");
                if (!key){
                        command("say 我已經託人把書帶給霜華了，不勞您大駕了。");
                        return 0;
                }

                command("touch"+query("id", me));
                command("say 這位"+RANK_D->query_respect(me)+"是霜華派來送信的吧。");
                key->move(me);
                addn("book_count", -1);
                message_vision("$n遞給$N一本書。\n", me, this_object() );
                command("say 這本書就是我練功打坐用的《神照經》，你拿去帶給霜華吧。");
                command("rumor"+query("name", me)+"弄到了一冊神照經。");
                remove_call_out("destroying");
                call_out("destroying", 1, this_object(), obj);
                return 1;
        }
        if( query("id", obj) == "green flower" && 
            filter_color(query("name", obj),1) == "春水碧波" )
        {
                message("vision",me->name()+"給丁典一盆綠菊花。\n",environment(me),
                        ({me}));
                message_vision("丁典同意指點$N一些武功的問題。\n",me);
                addn_temp("mark/丁", 1000, me);
                return 1;
        }
        return 0;
}

void destroying(object me,object obj)
{
        destruct(obj);
        return;
}

int recognize_apprentice(object ob)
{
        if( !query_temp("mark/丁", ob) )
                return 0;
        addn_temp("mark/丁", -1, ob);
        return 1;
}

int ask_skill1()
{
        object ob = this_object();
        object who = this_player();

        if( !query_temp("mark/丁", who))return 0;
        if (!who->query_skill("shenzhaojing",1)) return 0;
        if( query("can_perform/shenzhaojing/wakeup", who))return 0;
        if (who->query_skill("shenzhaojing",1) < 100)
        {
                command("say 你的神照經功力還不夠高，多學學吧。");
                return 1;
        }
        command("sign");
        command("say 不知你學得神照經是福是禍了。也罷，隨你去吧。");
        tell_object(who,HIC"丁典在你耳邊悄悄説了幾句運功的口訣，你急忙用心一一記下。\n"NOR);
        tell_object(who,HIC "你學會了「喚醒」。\n" NOR);
        set("can_perform/shenzhaojing/wakeup", 1, who);
        return 1;
}
int ask_skill2()
{
        object ob = this_object();
        object who = this_player();

        if( !query_temp("mark/丁", who))return 0;
        if (!who->query_skill("shenzhaojing",1)) return 0;
        if( query("can_perform/shenzhaojing/jingheal", who))return 0;
        if (who->query_skill("shenzhaojing",1) < 50)
        {
                command("say 你的神照經功力還不夠高，多學學吧。");
                return 1;
        }
        command("sign");
        command("say 不知你學得神照經是福是禍了。也罷，隨你去吧。");
        tell_object(who,HIC"丁典在你耳邊悄悄説了幾句運功的口訣，你急忙用心一一記下。\n"NOR);
        tell_object(who,HIC "你學會了「療精」。\n" NOR);
        set("can_perform/shenzhaojing/jingheal", 1, who);
        return 1;
}
