// npc: /d/xingxiu/npc/alamuhan.c
// Jay 3/17/96

inherit NPC;

int ask_me();
int do_qiecuo();

void create()
{
        set_name("阿拉木罕", ({ "alamuhan", "ala", "muhan" }));
        set("long", "她身段不肥也不瘦。她的眉毛像彎月，她的眼睛很多情。\n");
        set("title", "牧羊姑娘");
        set("gender", "女性");
        set("age", 17);

        set_skill("unarmed", 20);
        set_skill("dodge", 40);
        set_skill("parry", 20);
        set_skill("whip", 50);

        set_temp("apply/attack", 30);
        set_temp("apply/defense", 30);
        set_temp("apply/damage", 5);

        set("combat_exp", 5000);
        set("attitude","friendly");
        set("inquiry", ([
                "姑娘追" : (: ask_me :),
                "賽馬" : (: ask_me :),
                "馬" : (: ask_me :),
        ]) );

        set("shen_type", 1);
        setup();
        carry_object(__DIR__"obj/wcloth")->wear();
        carry_object(__DIR__"obj/changbian")->wield();
}

/*void init()
{
        ::init();
        add_action("do_qiecuo", "qiecuo");
}
*/
int ask_me()
{
        if( query_temp("marks/馬", this_player())){
                say(
"阿拉木罕對" + this_player()->name() + "説：你這孩子怎麼老纏着本姑娘。\n");
                return 1;
        } else {
        say("阿拉木罕看了" + this_player()->name() + "一眼，用不太標準的漢話説道：\n本姑娘在這裏的鞭法也小有點兒名氣，這位漢族" + RANK_D->query_respect(this_player()) + "\n想不想和我切磋幾下？\n");
        set_temp("marks/馬1", 1, this_player());
        return 1;
        }
}

int accept_fight(object ob)
{
        object me;

        me = this_object();
      
        if( query_temp("marks/馬1", ob)){
           say(ob->name() + "對阿拉木罕説：好吧，那" 
             "我就同你切搓幾招吧，點到為止。\n");
          remove_call_out("checking");
          call_out("checking", 1, me, ob);
          set_temp("marks/馬1", 0, ob);
          return 1;
        }
        else
              return 0;
}

int checking(object me, object ob)
{

        object horse;
        int my_max_qi, his_max_qi;
        my_max_qi=query("max_qi", me);
        his_max_qi=query("max_qi", ob);

        if (me->is_fighting()) 
        {
                call_out("checking",2, me, ob);
                return 1;
        }

        if ( !present(ob, environment()) ) return 1; 

        if( (query("qi", me)*100/my_max_qi) <= 50 )
        {
                say(
                  "阿拉木罕説：中原武學果然不一般，小女子十分佩服。\n"
                  "送你一匹伊犁馬略表寸心。\n"
                );
                horse = new(__DIR__"obj/horse"); 
                horse->move(ob);
                set_temp("marks/馬", 1, ob);
                message_vision("$N交給$n一匹馬。\n", me, ob);
                return 1;
        }
        if( (query("qi", ob)*100/his_max_qi)<50 )
        {
                say(
                   "阿拉木罕衝着" + ob->name() + "撇了撇嘴，説道：中原武學不過如此。\n"
                );
                message("vision",
                   ob->name() + "對阿拉木罕恭恭敬敬地磕了一個頭，離開賽馬場。\n", environment(ob), ({ob}) );
                ob->move("/d/xingxiu/beijiang");
                message("vision",
                   ob->name() + "從賽馬場垂頭喪氣地走回來。\n", environment(ob), ({ob}) );
                return 1;
        }
        return 1;
}

