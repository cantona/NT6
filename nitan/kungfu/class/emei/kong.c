// This program is a part of NT MudLIB
// kong.c 靜空師太

#include <command.h>
#include <ansi.h>
#include "tobebonze.h"
#include "emei.h"

inherit NPC;
inherit F_MASTER;

void create()
{
        set_name("靜空師太", ({ "jingkong shitai","jingkong","shitai"}));
        set("long",
        "她是峨嵋派三師姐，一位中年出家道姑，道冠高攏，慈眉善目。\n");
        set("gender", "女性");
        set("age", 45);
        set("attitude", "peaceful");
        set("shen_type", 1);
        set("shen", 10000);
        set("class", "bonze");
        set("inquiry",([
                "剃度"  : (: ask_for_join :),
                "出家"  : (: ask_for_join :),
                "還俗"  : "峨嵋弟子，不能還俗。你找掌門師太吧。",
        ]));

        set("str", 30);
        set("int", 30);
        set("con", 30);
        set("dex", 30);
        set("per", 30);

        set("max_qi", 1000);
        set("max_jing", 500);
        set("neili", 1500);
        set("max_neili", 1500);
        set("jingli", 1500);
        set("max_jingli", 1500);
        set("level", 10);
        set("combat_exp", 250000);
        set("score", 1000);
        set_skill("persuading", 80);
        set_skill("force", 100);
        set_skill("throwing", 80);
        set_skill("dodge", 90);
        set_skill("finger", 90);
        set_skill("parry", 80);
        set_skill("strike", 100);
        set_skill("blade", 90);
        set_skill("literate", 90);
        set_skill("mahayana", 100);
        set_skill("jinding-zhang", 90);
        set_skill("tiangang-zhi", 95);
        set_skill("yanxing-dao", 80);
        set_skill("zhutian-bu", 100);
        set_skill("emei-xinfa", 100);
        set_skill("linji-zhuang", 100);
        map_skill("force","linji-zhuang");
        map_skill("finger","tiangang-zhi");
        map_skill("dodge","zhutian-bu");
        map_skill("strike","jinding-zhang");
        map_skill("blade","yanxing-dao");
        map_skill("parry","yanxing-dao");

        create_family("峨嵋派", 4, "弟子");

        set("master_ob", 3);
        setup();
        carry_object(WEAPON_DIR"gangdao")->wield();
        carry_object(CLOTH_DIR"ni-cloth")->wear();
        carry_object(CLOTH_DIR"ni-shoe")->wear();
}
/*
void init()
{
        ::init();
        add_action("do_nod","nod");
}
*/

int do_nod(string arg)
{
        object me = this_player();

        if( !query_temp("pending/kao", me) )
                return 0;

        command("smile");
        command("say 我講個故事你聽：\n");

        message("vision", "靜空師太對着"+me->name()+"講了幾句話。\n",
                        environment(me), ({me}) );

        switch(random(3)) {
                case 0:
                write("靜空師太説：白水禪師曾住在我們萬年庵，那時叫白水寺。
            有個僧人問他：什麼是祖師西來意？　白水禪師是怎樣回答他的呢？\n\n");

                if ((int)me->query_skill("mahayana", 1) > 60 + random(5)) {
                        write("你想起在一部經書裏讀到過這個故事。\n");
                        write("你説：四溟無窯宅，一滴潤乾坤。\n\n");
                        message("vision", me->name()+"想了一下，跟靜空師太説了幾句話。\n",
                                environment(me), ({me}) );

                        command("say 阿彌陀佛，善哉！善哉！好吧，我就收下你了。");
                        command("say 希望你能以慈悲之心，以智慧之力，努力行善，濟度眾生。\n");
                        command("recruit "+query("id", me));
                }
                else {
                        write("你想了許久，也解不明白其中的禪理。\n");
                        command("say 阿彌陀佛，你多學些佛法後再來找我吧。\n");
                }
                break;

                case 1:
                write("靜空師太説：白水禪師曾住在我們萬年庵，那時叫白水寺。
            有個僧人問他：禪宗六祖一路，應談何事？　白水禪師是怎樣回答他的呢？\n\n");

                if ((int)me->query_skill("mahayana", 1) > 60 + random(5)) {
                        write("你想起在一部經書裏讀到過這個故事。\n");
                        write("你答道：澗鬆千載鶴來聚，月中香桂鳳凰歸。\n\n");
                        message("vision", me->name()+"想了一下，跟靜空師太説了幾句話。\n",
                                environment(me), ({me}) );

                        command("say 阿彌陀佛，善哉！善哉！好吧，我就收下你了。");
                        command("say 希望你能以慈悲之心，以智慧之力，努力行善，濟度眾生。\n");
                        command("recruit "+query("id", me));
                }
                else {
                        write("你想了許久，也解不明白其中的禪理。\n");
                        command("say 阿彌陀佛，你多學些佛法後在來找我吧。\n");
                }
                       break;

                case 2:
                write("靜空師太説：白水禪師曾住在我們萬年庵，那時叫白水寺。
            有個僧人問他：什麼是此經，即佛性？　白水禪師是怎樣回答他的呢？\n\n");

                if ((int)me->query_skill("mahayana", 1) > 60 ) {
                        write("你想起在一部經書裏讀到過這個故事。\n");
                        write("你答道：拋梭石女遼空響，海底泥牛夜叫頻。\n\n");
                        message("vision", me->name()+"想了一下，跟靜空師太説了幾句話。\n",
                                environment(me), ({me}) );

                        command("say 阿彌陀佛，善哉！善哉！好吧，我就收下你了。");
                        command("say 希望你能以慈悲之心，以智慧之力，努力行善，濟度眾生。\n");
                        command("recruit "+query("id", me));
                }
                else {
                        write("你想了許久，也解不明白其中的禪理。\n");
                        command("say 阿彌陀佛，你多學些佛法後在來找我吧。\n");
                }
                       break;
        }
        return 1;

}

void attempt_apprentice(object ob)
{
        if (! permit_recruit(ob))
                return;

        command("say 阿彌陀佛，善哉！善哉！在本庵修行，我要先考考你的佛法。");
        set_temp("pending/kao", 1, ob);
        command("say 你要準備好了，就告訴(nod)我吧。\n");
        add_action("do_nod", "nod");
        return;
}
