// chacha.c

#include <ansi.h>
#include <command.h>
#include <login.h>

inherit NPC;

string *death_msg = ({
        HIW "判官用奇異的眼光盯着你，好像要看穿你的一切似的。\n\n" NOR,
        HIW "判官對你説道：喂！該你了！\n\n" NOR,
        HIW "判官「哼」的一聲，從袖中掏出一本像帳冊的東西翻看著。\n\n" NOR,
        HIW "判官合上冊子，説道：嗯，你陽壽未盡，怎麼跑到這裏來了？\n\n" NOR,
        HIW "判官搔了搔頭，歎道：罷了罷了，你還是回陽間吧。\n\n"
                "一股陰冷的濃霧突然出現，很快地包圍了你。\n\n" NOR,
});

void create()
{
        set_name(YEL "判官" NOR, ({ "pan guan","guan" }) );
        set("long", @LONG
地獄陰司中執掌管帶眾鬼，以施獎懲之官，手中拿着記載人壽命的生死簿。
LONG);
        set("gender","男性");
        set("str",1000);
        set("title",HIW "查察司" NOR);                        
        set("attitude", "peaceful");
        set("age", 1000);
        set("combat_exp", 100000000);
        set("max_jing", 10000);
        set("max_qi", 10000);
        set("max_neili",10000);
        set("neili",10000);
        setup();
        carry_object( __DIR__"obj/shsbu" )->wear();
}


void init()
{
        object ob;
        ::init();
        if( !(ob=previous_object())||!userp(ob)) 
                return;
        if(!ob->is_ghost() && !wizardp(ob)) 
        {
                command("say 喂！陽人來陰間做什麼？");
                kill_ob(ob);
                ob->fight_ob(this_object());
                return;
        }
        call_out( "check_rein",2, ob);
}

void check_rein(object ob)
{
        int mud_age, rein_time;
        mud_age=query("mud_age", ob);
        rein_time=(query("PKS", ob)*20)+(query("MKS", ob)/10);
        if( query("age", ob) <= 15 || mud_age >= rein_time )
        {
                remove_call_out("death_stage");
                call_out("death_stage" ,1,ob,0);
        }
}

void death_stage(object ob, int stage)
{
        object *obs, mailbox;
        int i;

        if( !ob || !present(ob) ) return;
        if( stage != 4 )
                tell_object(ob, death_msg[stage]);
        else
        {
                obs = deep_inventory(ob);
                if(sizeof(obs))
                {
                        command("hmm");
                        tell_object(ob,HIW"判官説道：“不過陰間的東西是不能帶到陽間的，你先要把你身上的東西放下來。”\n"NOR);
                        return;
                }
                else
                        tell_object(ob,death_msg[stage]);
        }
        if( ++stage < sizeof(death_msg) ) {
                call_out( "death_stage", 3, ob, stage );
                return;
        }
        ob->reincarnate();
        obs = all_inventory(ob);
        for (i = 0; i < sizeof(obs); i++)
                DROP_CMD->do_drop(ob, obs[i]);
        if (!mailbox=present("mailbox",ob))
        mailbox = new("/clone/misc/mailbox");
        mailbox->move(ob);
  if( time()-query_temp("LAST_PKER_TIME", ob)<7200 )
       ob->move("/d/city/shilijie4");
   else
      ob->move(REVIVE_ROOM);
        message("vision",
                "你忽然發現前面多了一個人影，不過那人影又好像已經在那裏\n"
                "很久了，只是你一直沒發覺。\n", environment(ob), ob);
}
