#include <ansi.h>
inherit NPC;
int ask_jian();
int ask_baojian();
void consider();
void create()
{
    set_name("步驚雲", ({"bu jingyun", "bu", "jingyun"}));
    set("nickname", HIY "不哭死神" NOR );
    set("gender", "男性");
    set("age", 25);
    set("long",
        "他就是天下會雲堂堂主步驚雲，江湖上人稱「不哭死神」。\n");
    set("attitude", "peaceful");

    set("str", 100);
    set("int", 80);
    set("con", 86);
    set("dex", 240);
    set("chat_chance", 1);
    set("chat_msg", ({
        "步驚雲嘆了口氣道：“唉 …… 我的令牌哪裡去了 ……”\n",
        "步驚雲低頭沉思，悠然不語。\n",
    }));
    set("inquiry", ([
        "令牌"     : "誰能幫我找到令牌，我什麼事都答應他! \n",
        "寶劍" : (: ask_baojian:),
        "絕世好劍" : (: ask_baojian:),
    ]));
    set("qi", 20000);
   set("max_qi", 20000);
    set("jing", 5000);
    set("max_jing", 5000);
    set("max_jingli", 3000);

    set("jingli", 3000);
    set("neili", 6000);
    set("max_neili", 20000);
    set("jiali", 300);

     set("combat_exp", 60000000);

  set_skill("force", 600);
    set_skill("huntian-baojian", 600);
     set_skill("paiyun-zhang", 300);
   set_skill("strike", 500);
     set_skill("dodge", 500);
    set_skill("zhuangzi-wu", 500);
    set_skill("parry", 500);
   set_skill("sword", 500);
    set_skill("zhuihun-jian", 500);
    set_skill("qimen-wuxing",800);
    set_skill("literate",550);           // 讀書識字
    map_skill("force"  , "huntian-baojian");
    map_skill("strike", "paiyun-zhang");
    map_skill("dodge"  , "zhuangzi-wu");
    map_skill("parry"  , "paiyun-zhang");
             prepare_skill("strike" , "paiyun-zhang"); 
    create_family("天下會", 2, "堂主");
         set("chat_chance_combat", 150);
            set("chat_msg_combat", ({ 
                    (: perform_action, "strike.paishan" :), 
            })); 


	setup();

    carry_object("/d/taohua/obj/bupao")->wear();


}

int accept_object(object who, object ob)
{

    if ( (string) ob->query("id") =="ling pai" ) {
        // 是否那劍的本人
        if(ob->query("owner") == who->query("id") )
        {
            if (!(int)who->query_temp("tmark/ling")) who->set_temp("tmark/ling", 0);
            message_vision("步驚雲看了看$N送來的令牌，點了點頭，說道：\n"
                                   "難得你將令牌送回。你送我的東西我就收下了。\n"
                                   "作為補償,我可以告訴你點秘密。\n", who);
           who->set_temp("tmark/ling", 1);
            return 1;
        }
    }
}

int ask_baojian()
{
  int p1, p2;
  if ((int)this_player()->query("_passwd")) {
 say("步驚雲不悅地說道：我不是都告訴你了嗎？我不知道。\n");
  }
if ((int)this_player()->query_temp("tmark/ling")) {
 say("步驚雲一驚，說道：你怎麼知道的？\n");
 write("步驚雲頓一頓，接著對你低聲說：那我就告訴你算了");
// p1=random(4)+1;
// p2=random(4)+1;

    p1 = random(100)+1;
    this_player()->set("_passwd", p1);
    write(CHINESE_D->chinese_number(p1));
    write("把\n寶劍，就是絕世寶劍。\n");
  }
  else {
   message("vision",
   HIY "步驚雲勃然大怒，喝道：你也窺視我的絕世寶劍？！我跟你拼了！\n"
   NOR, environment(), this_object() );
   kill_ob(this_player());
  }
  this_player()->delete_temp("tmark/ling");
  return 1;
}

int ask_jian()
{
  int p1, p2;
            object me,obj;
            me = this_player();
                if (me->query("tmark/ling")) {
 say("步驚雲一臉譏笑的樣子，說：我憑什麼告訴你？\n");
  }

    if ((int)this_player()->query("_passwd")) {
        say("步驚雲一驚，說道：你怎麼知道的？寶劍的秘密就我知道。\n");
        write("步驚雲想了下低聲說：好吧，看在你幫我過，我就告訴你：");

        //p2=(int)p1/10;
        // 這句的p1沒有初始化。這樣導致p2和p1總是為0

        write(CHINESE_D->chinese_number(p1)+"十"+CHINESE_D->chinese_number(p2));
        write("把\n寶劍，就是絕世好劍。你只要輸入“press ***”就行！\n");
                 me->delete("tmark/ling");
                 me->set("tmark/ling",1);
                me->start_busy(2);
                return 1;
    }
}
