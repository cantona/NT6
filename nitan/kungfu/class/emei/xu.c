// This program is a part of NT MudLIB
// xu.c 靜虛師太

#include <command.h>
#include <ansi.h>
#include "tobebonze.h"
#include "emei.h"

inherit NPC;
inherit F_MASTER;
int peiyao();
int liandan();
void create()
{

        set_name("靜虛師太", ({ "jingxu shitai","jingxu","shitai"}));
        set("long",
          "她是峨嵋派二師姐，峨嵋門下多年，一套峨嵋掌法名動江湖。。\n");
        set("gender", "女性");
        set("age", 43);
        set("attitude", "peaceful");
        set("shen_type", 1);
        set("shen", 10000);
        set("class", "bonze");
        set("inquiry",([
                "剃度"  : (: ask_for_join :),
                "出家"  : (: ask_for_join :),
                "配藥"  : ( : peiyao :),
                "霹靂彈": ( : liandan : ),
                "還俗"  : "峨嵋弟子，不能還俗。你找掌門師太吧。",
        ]));

        set("str", 30);
        set("int", 30);
        set("con", 30);
        set("dex", 30);
        set("per", 20);

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
        set_skill("throwing", 80);
        set_skill("force", 100);
        set_skill("dodge", 90);
        set_skill("finger", 100);
        set_skill("parry", 90);
        set_skill("strike", 80);
        set_skill("blade", 100);
        set_skill("literate", 90);
        set_skill("mahayana", 100);
        set_skill("jinding-zhang", 100);
        set_skill("tiangang-zhi", 90);
        set_skill("yanxing-dao", 100);
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

        message("vision", "靜虛師太對着"+me->name()+"講了幾句話。\n",
                        environment(me), ({me}) );

        switch(random(2)) {
                case 0:
                write("靜虛師太説：大承和尚曾住在峨嵋山。
            有個僧人問他：什麼是勝峯？　大承説；直聳煙嵐。
            僧人又問：向上事（即脱俗之事）如何？　他答：立地三尺五。
            僧人又問：什麼是佛法？　他就説：興義門前咚咚鼓。
            那僧説：這我不懂。　大承和尚是怎樣回答他的呢？\n\n");

                if ((int)me->query_skill("mahayana", 1) > 50 + random(8)) {
                        write("你想起在一部經書裏讀到過這個故事。\n");
                        write("你説：朝打三千，暮打八百。\n\n");
                        message("vision", me->name()+"想了一下，跟靜虛師太説了幾句話。\n",
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
                write("靜虛師太説：慧真廣悟曾在峨嵋山出家。
            慧真廣悟開堂那天，有個僧人出來問：什麼是佛法大意？
            慧真廣悟説：日出方知天下朗，無油哪點佛前燈？
            僧人又問：什麼是雙峯境？　慧真廣悟是怎樣回答他的呢？\n\n");

                if ((int)me->query_skill("mahayana", 1) > 50 + random(8)) {
                        write("你想起在一部經書裏讀到過這個典故。\n");
                        write("你答道：夜聽水流庵後竹，晝起看雲面前山。\n\n");
                        message("vision", me->name()+"想了一下，跟靜虛師太説了幾句話。\n",
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
int peiyao()
{
        object me = this_player();
        object ob = this_object();
        object obj;
        int i;

        if(!objectp(present("caoyao 3",me)))
        {
                command("say 你的身上沒有那麼多草藥。");
                return 1;
        }
        for(i=0;i<3;i++)
        {
                obj=present("caoyao",me);
                destruct(obj);
        }
        command("smile");
        command("say 好吧，我就給你配藥了。");
        obj=new("/d/emei/obj/zhongyao");
        obj->move(me);
        message_vision("靜慈師太給$N一包中藥。\n",me);
        return 1;
}
int liandan()
{
        object me = this_player();
        object ob = this_object();
        object obj;
        int i;
        if(!objectp(present("liuhuang",me)))
        {
                command("say 你的身上沒有煉製霹靂彈用的硫磺。");
                return 1;
        }
        obj=present("liuhuang",me);
        destruct(obj);
        command("smile");
        command("say 好吧，我就給你煉製一粒霹靂彈。");
        obj=new("/d/emei/obj/pilidan");
        obj->move(me);
        message_vision("靜慈師太給$N一粒霹靂彈。\n",me);
        return 1;
}
