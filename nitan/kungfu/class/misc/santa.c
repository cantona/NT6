//Cracked by Kafei
// kungfu/class/misc/santa.c
// sdong, 12/24/98

#include <ansi.h>
inherit NPC;
inherit F_UNIQUE;
string ask_gift();
void greeting();

void create()
{
        seteuid(getuid());
        set_name(HIR"聖誕老人"NOR, ({ "shengdan laoren","santa","laoren"}) );
        set("gender", "男性" );
        set("age", 63);
        set("long", HIR"一位紅光滿面，笑呵呵的白鬍子老爺爺。\n"NOR);
        set("attitude", "peaceful");

        set("str", 25);
        set("con", 25);
        set("int", 25);
        set("dex", 100);
        set("kar", 100);

        set("max_qi", 50000);
        set("max_jing", 100);
        set("neili", 50000);
        set("max_neili", 50000);
        set("shen_type", 1);
   set("env/yield","yes");

        set("startroom","/d/city/wumiao");

        set("combat_exp", 100000);

        set_skill("force", 400);
        set_skill("hand", 40);
        set_skill("sword", 50);
        set_skill("dodge", 400);
        set_skill("parry", 400);
        set_skill("huntian-qigong", 400);

        map_skill("force", "huntian-qigong");

        set("chat_chance", 20);
        set("chat_msg", ({
                "聖誕老人笑呵呵説道: 聖誕快樂！快樂！~~\n",
                "聖誕老人快活地唱道: 叮叮鐺，叮叮鐺，鈴兒響叮鐺~~\n",
                "聖誕老人笑呵呵説道: 想要禮物嗎？我就是神派來送聖誕禮物的。 \n",
                "聖誕老人笑道: 只要是乖孩子，就有聖誕禮物。 \n",
                (: random_move :),
                (: greeting :),
        }) );

        set("inquiry", ([
                                         "gift" : (: ask_gift :),
                                         "聖誕禮物" : (: ask_gift:),
                                         "禮物" : (: ask_gift:),
                                  ]) );



        setup();

        ::create();
}


void init()
{
        object ob;

        ::init();
        if( interactive(ob = this_player()) ) {
                remove_call_out("greeting");
                call_out("greeting", 1);
        }
}

string ask_gift()
{
        object ppl = this_player();
        object santa = this_object();
        object ob;

        if( ppl->query_condition("santa") )
        {
                message_vision("$N對着$n笑道：你才拿到禮物，就又想要啦？\n",santa,ppl);
                random_move();
                return "呵呵呵\n";
        }

        if( query("combat_exp", ppl)<300 )
        {
                random_move();
                return "DUMMY是不需要禮物的:)";
        }

        seteuid(getuid());

        if (random(8) == 1) {
                 ob = new("/clone/drug/lingzhi");
                 ob->move(santa);
        }
        else if (random(16) == 1) {
                 ob = new("/clone/drug/puti-zi");
                 ob->move(ppl);
        }
        else if (random(16) == 1) {
                 ob = new("/clone/drug/sheli-zi");
                 ob->move(santa);
        }
        else if (random(6) == 1) {
                 ob = new("/clone/drug/xueteng");
                 ob->move(santa);
        }
        else if (random(6) == 1) {
                 ob = new("/clone/drug/xuelian");
                 ob->move(santa);
        }
        else if (random(6) == 1) {
                 ob = new("/clone/drug/cb_renshen");
                 ob->move(santa);
        }
        else if (random(6) != 1) {
                 ob = new("/clone/drug/renshen_guo");
                 ob->move(santa);
        }
        else
        {
                 ob=new("/clone/money/gold");
                 ob->set_amount( 3 + random(5) );
                 ob->move(santa);
        }

        command("pat"+query("id", ppl));
        if( query("env/no_accept", ppl) )
        {
                command("hmm");
                command("say "+ppl->name()+"不想接受任何東西？");
        }
        else
                command("give"+query("id", ob)+"to"+query("id", ppl));

        ppl->apply_condition( "santa",20+random(10) );

        return "祝你聖誕快樂！快樂！~~\n";
}

void destroy_me(object me)
{
        destruct(me);
}

void greeting()
{
        object me = this_object();

        command("say 祝你聖誕快樂！快樂~~\n");

        if( strsrch(base_name(environment()), "/d/city/") == -1 )
        {
                message_vision(HIY"$N"+HIY"乘坐風車凌空飛去，轉眼就不見了.\n"NOR,me);
                me->move("d/city/wumiao");
                message_vision(HIG"只聽空中一陣鈴鐺聲響，$N"+HIG"乘坐風車凌空飛來.\n"NOR,me);
        }

        if( strsrch(ctime(time()), "Dec 25") == -1 )
        {
                message_vision(HIY"$N"+HIY"悽婉地説：聖誕節結束了，我也該回天堂了.\n"NOR,me);
                command("goodbye");
                message_vision(HIY"$N"+HIY"乘坐風車凌空飛去，轉眼就不見了.\n"NOR,me);
                call_out("destroy_me",1,me);
        }

        if( random(150) == 0 )
        {
                message_vision(HIY"$N"+HIY"乘坐風車凌空飛去，轉眼就不見了.\n"NOR,me);
                call_out("destroy_me",1,me);
        }
}

int accept_object(object me, object obj)
{
        if( query("money_id", obj) && obj->value() >= 1){
                         command("smile");
                         command("say 多謝啦 ! 你好心必有好報的 !");
        }

        return 0;
}

int accept_fight(object me)
{
        command("say " + RANK_D->query_respect(me) + "，老頭子我是不打架的:)ⅵ\n");
        return 0;
}

int accept_kill(object victim)
{
                  object me = this_object();
                  object player = this_player();
                  int flag;

                  command("say " + RANK_D->query_respect(player) + "，怎麼這麼兇？不該不該呀！\n");
                  command("benger"+query("id", player));
                  if( query("env/immortal", player) )
                                flag=1;
                  delete("env/immortal", player);
                  player->unconcious();
                  if( flag)set("env/immortal", 1, player);
        command("halt");
                  random_move();
                  return 0;
}


