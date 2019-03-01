 //liwenxiu.c 李文秀

#include <ansi.h>

inherit NPC;
int ask_supu();
int ask_parent();
int ask_gaochang();
void dest(object ob);

void create()
{
        set_name("李文秀", ({ "li wenxiu", "li", "wenxiu" }));
        set("gender", "女性");
        set("age", 18);
        set("long", "她長得清純脫秀，嫣然一笑，不禁讓人怦然心動。\n");

        set("combat_exp", 100000);
        set("shen_type", 1);
        set("per", 28);
        set("max_neili", 500);
        set("neili", 500);
        set("jiali", 10);
        set("map_count", 1);

        set_skill("force", 40);
        set_skill("sword", 100);
        set_skill("unarmed", 50);
        set_skill("dodge", 100);
        set_skill("parry", 100);

        set("inquiry", ([
                "蘇普" : (: ask_supu :),
                "supu" : (: ask_supu :),
                "父母" : (: ask_parent :),
                "parent" : (: ask_parent :),
                "高昌地圖" : (: ask_gaochang:),
                "高昌迷宮" : (: ask_gaochang :),
                "map" : (: ask_gaochang:),
        ]) );

        set_temp("apply/attack", 50);
        set_temp("apply/defense", 50);
        set_temp("apply/damage", 15);

        setup();
        carry_object("/clone/weapon/changjian")->wield();
}

int ask_supu()
{
        say("李文秀黯然的說：他是我兒時的伙伴，他現在和阿曼在一起了，\n");
        set_temp("marks/李1", 1, this_player());
        return 1;
}

int ask_parent()
{
        object map;
        object me = this_player(); 
        if( query_temp("marks/李1", this_player()) )
        {
                say("李文秀哽嚥的說道：我的父母是被姦人害死的，姦人覬覦我們家的高昌地圖。\n我一定要手刃仇人，為我父母報仇。\n");
                set_temp("marks/李2", 1, me);
                return 1;
        }
        else
        {
                say("李文秀說道：父母之仇，不共戴天。\n");
                return 1;
        }
}

int ask_gaochang()
{
        object map, me = this_player(), ob = this_object();
        int exp,pot,score;
        if (query("map_count") < 1)
        {
                say("李文秀一愣，忙道：地圖？我沒說過什麼地圖啊。\n");        
                return 1;
        }
        if( query_temp("marks/李2", me) )
        {
//                say( "李文秀一驚，說道：你怎麼知道的？噢，我剛才說露嘴了。\n那我就把地圖送給你吧。你看看高昌迷宮到底有什麼？\n");
//          map=new("/d/gaochang/obj/map");
//                map->move(me);
//                addn("map_count", -1);
                say( "李文秀一驚，說道：你怎麼知道的？噢，我剛才說露嘴了。\n我把高昌地圖給蘇普了，你去找他吧。\n");
    set_temp("marks/李3", 1, me);
        }
        else
        {
                message("vision", HIY"李文秀勃然大怒，喝道：你也窺視我父母的高昌地圖？！我跟你拼了！\n"NOR, environment(), this_object() );
                ob->kill_ob(me);
                delete_temp("marks/李1", me);
                delete_temp("marks/李2", me);
        }
        return 1;
}
int accept_object(object me,object ob)
{
        object li=this_object();
        object map;
        int exp,pot,score;
        if( !query_temp("marks/李3", me) )
        {
                command("shake");
                command("say 計爺爺說不能別人的貪圖財物。");
    return 0;
        }
  if( query("id", ob) == "shoujuan" && query("blood_soaked", ob) >= 2 )
  {
          call_out("dest",0,ob);
          if( !query("owner", ob) || query("owner", ob) != query("id", me) )
          {
                  message_vision("$N勃然大怒：你哪裡偷來的這塊手絹！\n",li);
                  me->fight_ob(li);
                  li->kill_ob(me);
                  return 1;
          }
    message_vision("$N驚叫：這不正是高昌地圖嗎？\n",li);
    map=new(__DIR__"obj/map");
                map->move(me);
                ob=new(__DIR__"obj/shoujuan2");
                ob->move(me);
                addn("map_count", -1, li);
          if( !query("skybook/baima/map", me) )
          {
           set("skybook/baima/map", 1, me);
           exp=500+random(1000);
     pot=exp/2;
     score=pot/2;
     addn("combat_exp", exp, me);
     addn("potential", pot, me);
     addn("score", score, me);
             tell_object(me,HIC"你成功得到了高昌地圖！\n在這次歷練中你獲得了"+
                      chinese_number(exp)+"點經驗、"+
               chinese_number(pot)+"點潛能以及"+
               chinese_number(score)+"點江湖閱歷。\n\n"NOR);
          }        
          return 1;
  }
  return 0;
}
void dest(object ob)
{
        destruct(ob);
}