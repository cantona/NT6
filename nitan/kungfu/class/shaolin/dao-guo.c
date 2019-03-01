// Npc: /kungfu/class/shaolin/dao-guo.c
// Date: YZC 96/01/19

#include <ansi.h>

inherit NPC;
inherit F_MASTER;

#include "dao.h"

string ask_me();

void create()
{
        set_name("道果禪師", ({
                "daoguo chanshi",
                "daoguo",
                "chanshi",
        }));
        set("long",
                "他是一位身材高大的中年僧人，兩臂粗壯，膀闊腰圓。他手持兵\n"
                "刃，身穿一襲灰布鑲邊袈裟，似乎有一身武藝。\n"
        );


        set("gender", "男性");
        set("attitude", "friendly");
        set("class", "bonze");

        set("age", 40);
        set("shen_type", 1);
        set("str", 20);
        set("int", 20);
        set("con", 20);
        set("dex", 20);
        set("max_qi", 400);
        set("max_jing", 300);
        set("neili", 450);
        set("max_neili", 450);
        set("jiali", 40);
        set("combat_exp", 10000);
        set("score", 100);

        set_skill("force", 50);
        set_skill("hunyuan-yiqi", 50);
        set_skill("shaolin-xinfa", 50);
        set_skill("dodge", 50);
        set_skill("shaolin-shenfa", 50);
        set_skill("strike", 50);
        set_skill("banruo-zhang", 50);
        set_skill("parry", 50);
        set_skill("sword", 50);
        set_skill("damo-jian", 50);
        set_skill("buddhism", 50);
        set_skill("literate", 50);

        map_skill("force", "hunyuan-yiqi");
        map_skill("dodge", "shaolin-shenfa");
        map_skill("strike", "banruo-zhang");
        map_skill("sword", "damo-jian");
        map_skill("parry", "damo-jian");

        prepare_skill("strike", "banruo-zhang");

        create_family("少林派", 39, "弟子");

        set("inquiry", ([
                "木人"     : (: ask_me :),
                "修理"           : (: ask_me :),
                "修木人"   : (: ask_me :)
        ]));

        set("master_ob",1);
        setup();

        carry_object("/d/shaolin/obj/changjian")->wield();
        carry_object("/d/shaolin/obj/dao-cloth")->wear();
}

void init()
{        
        object me, ob;

        me = this_object();

        ::init();
        if( objectp(ob = present("mu ren", environment())) )
        {
                remove_call_out("repairing_1");
                call_out("repairing_1", 5, me, ob);
        }
}

int repairing_1(object me, object ob)
{
        if ( !present(ob, environment()) ) return 1; 

        command("say 是這個木人吧？ 唔，我來瞧瞧！ 你在邊上呆着，看能幫我什麼忙。");
        
        remove_call_out("repairing_2");
        call_out("repairing_2", 2+random(3), me, ob);

        return 1;
}

int repairing_2(object me, object ob)
{
        if ( !present(ob, environment()) ) return 1; 

        if( query("damaged", ob) )
        {
                message_vision(GRN "\n道果禪師對着木人瞧了一會，又試着扳動木人的四肢和腦袋，嘴裏喃喃唸叨着什麼。\n\n" NOR, me);
                remove_call_out("repairing_3");
                call_out("repairing_3", 2+random(2), me, ob);
        }
        else
        {
                command("say 這木人好端端地又沒壞！ 還大老遠地拖着我過來！");
                command("follow none");

                message_vision(GRN "\n道果禪師氣鼓鼓地走了。\n" NOR, me);
                me->move("/d/shaolin/guangchang3");

                remove_call_out("do_back");
                call_out("do_back", random(15), me);
        }

        return 1;
}
        
int repairing_3(object me, object ob)
{
        command("say 唔，原來如此，我來修修看吧！");
        message_vision(GRN "\n他接着從懷裏掏出一大堆工具來，打開木人的身體，擺弄了幾下。\n\n" NOR, me);

        remove_call_out("repairing_4");
        call_out("repairing_4", 3+random(3), me, ob);

        return 1;
}

int repairing_4(object me, object ob)
{
        if( random(2) == 0 ) 
        {                
                command("say 好，修好了！");
                delete("damaged", ob);
                set("fight_times", 0, ob);
                message_vision(GRN "\n木人的身體吱吱地扭動了幾下，恢復了正常站立的姿態。\n\n" NOR, me);
        }
        else 
                message_vision(GRN "\n道果禪師歎了口氣，説道：看來不行，這木人損壞得太厲害了，沒法子修了！\n" NOR, me);

        command("say 好，那我走了！");
        command("wave");
        command("follow none");

        message_vision(GRN "\n道果禪師走了出去。\n" NOR, me);
        me->move("/d/shaolin/guangchang3");

        remove_call_out("do_back");
        call_out("do_back", random(15), me);

        return 1;
}

int do_back(object me)
{
        me->move("/d/shaolin/twdian");
        return 1;
}

string ask_me()
{
        mapping fam; 
        object ob;

        ob = this_player();
        
        if( !(fam=query("family", ob)) || fam["family_name"] != "少林派" )
                return RANK_D->query_respect(ob) + 
                "與本派素無來往，不知此話從何談起？";

        command("say 木人打壞了是吧？ 好吧，我跟你去看看。");
        command("follow"+query("id", ob));

        return "我們走罷！\n";
}
