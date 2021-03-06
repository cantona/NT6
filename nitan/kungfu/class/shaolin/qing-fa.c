// Npc: /kungfu/class/shaolin/qing-fa.c
// Date: YZC 96/01/19

inherit NPC;
inherit F_MASTER;

#define DEFINED_ATTEMPT_APPRENTICE

#include "qing.h"

string ask_for_join();

void create()
{
        set_name("清法比丘", ({
                "qingfa biqiu",
                "qingfa",
                "biqiu",
        }));
        set("long",
                "他是一位體格強健的壯年僧人，他生得虎背熊腰，全身似乎藴含\n"
                "着無窮勁力。他身穿一襲白布黑邊袈裟，似乎身懷武藝。\n"
        );


        set("gender", "男性");
        set("attitude", "friendly");
        set("class", "bonze");

        set("inquiry",([
                "剃度"  : (: ask_for_join :),
                "出家"  : (: ask_for_join :),
        ]));

        set("age", 30);
        set("shen_type", 1);
        set("str", 25);
        set("int", 17);
        set("con", 50);
        set("dex", 21);
        set("max_qi", 450);
        set("max_jing", 200);
        set("neili", 350);
        set("max_neili", 350);
        set("jiali", 30);
        set("combat_exp", 5000);
        set("score", 100);

        set_skill("force", 30);
        set_skill("shaolin-xinfa", 30);
        set_skill("dodge", 50);
        set_skill("shaolin-shenfa", 50);
        set_skill("cuff", 50);
        set_skill("jingang-quan", 50);
        set_skill("parry", 30);
        set_skill("buddhism", 30);
        set_skill("literate", 30);

        map_skill("force", "shaolin-xinfa");
        map_skill("dodge", "shaolin-shenfa");
        map_skill("cuff", "jingang-quan");
        map_skill("parry", "jingang-quan");

        prepare_skill("cuff", "jingang-quan");

        create_family("少林派", 40, "弟子");

        set("master_ob",1);
        setup();

        carry_object("/d/shaolin/obj/qing-cloth")->wear();
}

void init()
{
        add_action("do_kneel", "kneel");
}

string ask_for_join()
{
        object me;

        me = this_player();

        if( query("class", me) == "bonze" )
                return "阿彌陀佛！你我同是出家人，何故跟貧僧開這等玩笑？\n";

        if( query("gender", me) == "無性" )
                return "阿彌陀佛！善哉！善哉！這位公公，你還是回去伺候皇上吧。\n";

        if( query("gender", me) == "女性" )
                return "阿彌陀佛！善哉！善哉！女施主若真心皈依我佛，可去後山庵裏受戒。\n";

        set_temp("pending/join_bonze", 1, me);
        return "阿彌陀佛！善哉！善哉！施主若真心皈依我佛，請跪下(kneel)受戒。\n";
}

int do_kneel()
{
        object me = this_player();

        string *prename =
         ({ "虛", "空", "明", "淨" });
//       ({ "虛", "空", "明", "圓", "淨", "悟", "法" });
        string name, new_name;

        if( !query_temp("pending/join_bonze", me) )
                return 0;

        message_vision(
                "$N雙手合十，恭恭敬敬地跪了下來。\n\n"
                "$n伸出手掌，在$N頭頂輕輕地摩挲了幾下，將$N的頭髮盡數剃去。\n\n",
                me, this_object() );
        name=query("name", me);
        new_name = prename[random(sizeof(prename))] + name[0..1];
        command("say 從今以後你的法名叫做" + new_name + "。");
        command("smile");
        delete_temp("pending/join_bonze", me);

        set("name", new_name, me);
        set("class", "bonze", me);
        set("K_record",query("PKS",  me)+query("MKS", me), me);
        set("shen_record",query("shen",  me), me);
        set("shen", 0, me);

        return 1;
}

void attempt_apprentice(object ob)
{
        if (! permit_recruit(ob))
                return;

        if( query("gender", ob) == "女性" )
        {
                command ("say 阿彌陀佛！女施主呀，貧僧可不敢開這等玩笑啊。");
                return;
        }

        if( query("gender", ob) == "無性" )
        {
                command ("say 阿彌陀佛！這位公公，你還是回去伺候皇上吧。");
                return;
        }
        
        if( query("class", ob) != "bonze" )
        {
                command ("say 阿彌陀佛！貧僧就收下你做『俗家弟子』了。");
        }
        command("say 阿彌陀佛，善哉！善哉！");
        command("recruit "+query("id", ob));
}
