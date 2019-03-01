//kangxi.c 康熙大帝

#include <ansi.h>
inherit NPC;
inherit F_UNIQUE;

string * officer = ({
        "守備",
        "都司",
        "遊擊",
        "參將",
        "副將",
        "總兵",
        "提督",
        "總督",
        "大將軍",
});
int ask_officer();
void dest(object ob);

void create()
{
        set_name(HIR "康熙大帝" NOR, ({"kang xi", "kang"}));
        set("title", "清聖祖");
        set("gender", "男性");
        set("age", 36);
        set("str", 25);
        set("dex", 20);
        set("int", 28);
        set("con", 28);
        set("per", 27);
        set("long", HIR @LONG
這位高大魁梧，英俊瀟洒的男子就是天下獨尊的康熙大帝。
LONG NOR
        );

        set("combat_exp", 500000);
        set("score", 20000);
        set("shen_type", 1);
        set("attitude", "peaceful");


        set_skill("unarmed", 100);
        set_skill("dodge", 100);
        set_skill("literate", 100);
        set_skill("force", 100);
        set_skill("hunyuan-yiqi", 100);
        set_skill("shaolin-shenfa", 100);
        set_skill("finger", 100);
        set_skill("nianhua-zhi", 100);
        map_skill("force", "hunyuan-yiqi");
        map_skill("dodge", "shaolin-shenfa");
        map_skill("parry", "nianhua-zhi");
        map_skill("finger", "nianhua-zhi");
        prepare_skill("finger", "nianhua-zhi");

        set_temp("apply/attack", 50);
        set_temp("apply/defence", 50);
        set_temp("apply/armor", 30);
        set_temp("apply/damage", 35);

        set("qi", 1000);
        set("max_qi", 1000);
        set("jing", 600);
        set("max_jing", 600);
        set("neili", 2000);
        set("max_neili", 2000);
        set("jiali", 80);

        set("inquiry", ([
                "韋小寶" : "\n小寶是我的心腹,我讓他為我收集各大官員的消息.\n",
                "鰲拜": "\n鰲拜雖是開朝元老,但太驕橫跋負了,終是我的心腹大患.\n",
                "官職" : (:ask_officer:),
                "職務" : (:ask_officer:),
                "封賞" : (:ask_officer:),
        ]));
        set("chat_chance", 3);
        set("chat_msg", ({
    "康熙往匾額上看了看。\n",
                "康熙說道：普天之下，莫非王土；率土之濱，莫非王臣。\n",
                "康熙說道：天下取士，非賢積德。我朝馬上得天下，不能馬上治天下。 \n",
                "康熙說道：想要官職，當然問朕了。\n",
                "康熙說道：收齊四十二章經者，朕重重有賞。\n",
        }) );
        setup();
        carry_object(__DIR__"obj/jinduan")->wear();
        add_money("gold", 5);
}
int ask_officer()
{
        int lv, worked;
        string officerlvl;
        object ob = this_player();
        lv=query("officerlvl", ob);
        worked=query("bt/worked", ob);
        if (lv < 1) 
        {
                command("say"+query("name", ob)+"，朕沒有給揚州知府下旨，你來此何幹？！\n");
                return 1;
  }
  if( query_temp("guard", ob) )
   {
    command("say"+query("name", ob)+"，朕已經給你封賞官職了，你下去吧！");
    return 1;
   }
  officerlvl = officer[lv-1];
        command("chat"+query("name", ob)+"，你秉承旨意，忠君愛民，朕甚嘉許。著兵部實授"+officerlvl+"之職！\n");
        set("guard", HIY+officerlvl+NOR, ob);
        set_temp("guard", 1, ob);
        return 1;
}

int accept_object(object me, object ob)
{
        object gold;
        object cloth;
        int exp,pot,score;
        if( !me || environment(me) != environment() ) return 0;
        if ( !objectp(ob) ) return 0; 
        if ( !present(ob, me) ) return notify_fail("你沒有這件東西。");
        if( query("id", ob) == "book1" )
        {
                set_temp("book14/1", 1, me);
                command("smile"+query("id", me));
                call_out("dest",0,ob);
        }
        else if( query("id", ob) == "book2" )
        {
                set_temp("book14/2", 1, me);
                command("smile"+query("id", me));
                call_out("dest",0,ob);
        }
        else if( query("id", ob) == "book3" )
        {
                set_temp("book14/3", 1, me);
                command("smile"+query("id", me));
                call_out("dest",0,ob);
        }
        else
        if( query("id", ob) == "book4" )
        {
                set_temp("book14/4", 1, me);
                command("smile"+query("id", me));
                call_out("dest",0,ob);
        }
        else
        if( query("id", ob) == "book5" )
        {
                set_temp("book14/5", 1, me);
                command("smile"+query("id", me));
                call_out("dest",0,ob);
        }
        else
        if( query("id", ob) == "book6" )
        {
                set_temp("book14/6", 1, me);
                command("smile"+query("id", me));
                call_out("dest",0,ob);
        }
        else
        if( query("id", ob) == "book7" )
        {
                set_temp("book14/7", 1, me);
                command("smile"+query("id", me));
                call_out("dest",0,ob);
        }
        else
        if( query("id", ob) == "book8" )
        {
                set_temp("book14/8", 1, me);
                command("smile"+query("id", me));
                call_out("dest",0,ob);
        }
        else
        {
                command("shake ");
                command("say 朕只是想找四十二章經，你且退下。");
        }
        if( query_temp("book14/1", me) && 
             query_temp("book14/2", me) && 
             query_temp("book14/3", me) && 
             query_temp("book14/4", me) && 
             query_temp("book14/5", me) && 
             query_temp("book14/6", me) && 
             query_temp("book14/7", me) && 
             query_temp("book14/8", me) )
        {
                command("chat"+query("name", me)+"，你找回八部四十二章經，有功于社稷，賜黃馬褂一件！\n");
                cloth = new(__DIR__"obj/ycloth");
                delete_temp("book14", me);
                cloth -> move(me);
                gold = new("/clone/money/gold");
                gold->set_amount(20);
                gold->move(this_object());
                command("give20goldto"+query("id", me));
                if( !query("skybook/luding/42jing", me) )
   {
                 set("skybook/luding/42jing", 1, me);
                 exp=500+random(1000);
     pot=exp/2;
     score=pot/2;
     addn("combat_exp", exp, me);
     addn("potential", pot, me);
             tell_object(me,HIC"你成功得到了康熙的信任！\n在這次歷練中你獲得了"+
                      chinese_number(exp)+"點經驗、"+
               chinese_number(pot)+"點潛能以及"+
               chinese_number(score)+"點江湖閱歷。\n\n"NOR);
                }
                
        }
        return 1;
}

void dest(object ob)
{
        destruct(ob);
}