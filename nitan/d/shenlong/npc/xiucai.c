// /d/shenlong/npc/xiucai.c
// Last Modified by winder on Jul. 12 2002

#include <ansi.h>
inherit NPC;

int do_forge();

void create()
{
        set_name(HIY"落第秀才"NOR, ({ "xiucai" }));
        set("long","他年青時頗有抱負，後來自暴自棄。\n只憑一點墨才經常幹些偷樑換柱的勾當度日。\n"); 
        set("gender", "男性");
        set("age", 35);

        set_skill("unarmed", 10);
        set_skill("dodge", 10);
        set_skill("parry", 10);
        set_temp("apply/attack", 10);
        set_temp("apply/defense", 10);

        set("combat_exp", 2000);
        set("shen_type", -1);

        set("inquiry", ([
                "偽造" : (: do_forge :),
                "weizao" : (: do_forge :),
                "forge" : (: do_forge :),
        ]) );

        setup();
}
int do_forge()
{
        object me = this_player(); 

        if( !query_temp("cbs_落第/a", me))return 0;
        delete_temp("cbs_落第/a", me);
        command("hehe");
        command("whisper"+query("id", me)+""+"一兩黃金，不二價。\n");
        set_temp("cbs_落第/b", 1, me);
        return 1;
}
int accept_object(object who, object ob)
{
        object obj;

        if( ob->name() == "甲骨文" )
        {
                command("ah"+query("id", who));
                set_temp("cbs_落第/a", 1, who);
                call_out("destroy", 1, ob);
                return 1;
        }
        if( ob->value() >= 10000 && query_temp("cbs_落第/b", who) )
        {
                delete_temp("cbs_落第", who);
                say("落第秀才笑嘻嘻說道：這幅頌詞保証錯不了。\n");

                obj = new("/d/shenlong/obj/songci");
                obj->move(who);
                message_vision("$N將一"+query("unit", obj)+query("name", obj)+"交給$n。\n",this_object(),who);
                return 1;
        }

        return 0;
}

void destroy(object ob)
{
        destruct(ob);
}
