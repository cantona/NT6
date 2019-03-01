// jiang-yaoting.c 江耀亭  處理玩家離婚
// by llm 99/06
#include <ansi.h>
inherit NPC;
int do_unmarry(string arg);
int zou(object me);
int do_kill();
int do_chat();

void create()
{
        set_name("江耀亭", ({ "jiang yaoting", "jiang" }));
        set("title", "汝州知府");
   set("gender", "男性");
   set("age", 43);
   set("str", 20);
   set("dex", 20);
   set("long", "他就是江耀亭，汝州現任知府，因紅娘莊在其轄境，親手負責玩家離婚之事。\n");
   set("combat_exp", 30000);
   set("shen_type", 0);
   set("attitude", "heroism");

   set_skill("unarmed", 50);
   set_skill("force", 50);
   set_skill("sword", 50);
   set_skill("dodge", 50);
   set_skill("parry", 50);
   set_temp("apply/attack", 150);
   set_temp("apply/defense", 150);
   set_temp("apply/armor", 150);
   set_temp("apply/damage", 150);

   set("neili", 500);
   set("max_neili", 500);
   set("jiali", 10);

   setup();
//   carry_object("/clone/weapon/gangjian")->wield();
   carry_object("/clone/misc/cloth")->wear();
}

void init()
{
        ::init();
   add_action("do_chat", "chat");
   add_action("do_chat","chat*");
   add_action("do_unmarry","unmarry");
   add_action("do_kill",({"kill","fight","hit","touxi"}));
}

int accept_object(object me, object ob)
{
   if( !query("money_id", ob) )
             return notify_fail("江耀亭冷冷地看了你一眼道：“是不是活得不耐煩了，敢拿本知府開玩笑？！”\n");
          if(ob->value() < 1000000)
              return notify_fail("江耀亭皺了皺眉頭說道：“你記性不好還是怎麼著？100 gold，少一文也別想辦！”\n");
        message_vision("江耀亭接過錢點點說：“好吧！我們來辦理吧！”\n",me);
        set_temp("money", me->name(), this_object());
          return 1;
}

int do_chat()
{
   object me;
   me=this_player();

   message_vision(HIW "江知府臉色一沉，驚堂木一拍喝道：“大堂之上，竟敢喧嘩！來人呀！”\n"
   "“在！”兩邊衙役齊聲應道。江耀亭一指$N喝道：“把他給我重打二十大板！”\n"NOR,me);
   call_out("zou",1,me);
   return 0;
}

int zou(object me)
{
   message_vision(HIW"一群衙役沖上前來，不由分說，把$N掀翻在地，一陣大板隨即跟上……\n"NOR,me);
   tell_object(me,HIR"你剛發現不對，四肢已經被按牢在地，只覺一板板打得你痛入骨髓……\n"NOR);
        if( query("combat_exp", me)>10000
            && query("qi", me)>20 )
   {
                me->receive_damage("qi", 20);
                me->receive_wound("qi",  20);
   }
   else
      me->unconcious();
          return 1;
}

int do_kill()
{
        object ob;
        int i;

        command("say 大膽，竟敢在公堂上動武，來人呀！");
        message_vision("四周的衙役立刻群起對$N發動攻擊！\n", this_player());

        for(i=0; i<4; i++)
   {
                if( objectp( ob = present("ya yi " + (i+1), environment(this_object())) ) )
                        ob->kill_ob(this_player());
                else
              this_object()->kill_ob(this_player());
        }
        return 1;
}

int do_unmarry(string arg)
{
        object me, obj,ob,*inv;
mapping my_skl;
string *skl_name;
int i,*level;

        me = this_player();
        if (me->is_busy())
                return notify_fail("江知府眉頭一皺說道：“你看看你自己那個忙樣！”\n");

        if( me->is_fighting() )
        {
                if( !this_object()->is_killing(me) )
                        this_object()->kill_ob(me);
                return notify_fail("江耀亭怒火中燒：“大膽逆賊，來來來，本官送你去陰間去離婚！”\n");
        }

        if( this_object()->is_fighting() )
                return notify_fail("江知府說道：“你先退下，等本官處理了這裡搗亂的人再說！”\n");

        if( !living(this_object()) )
                return notify_fail("你還是先想辦法把知府大人救醒吧。\n");

        if( !environment()||base_name(environment()) != query("startroom") )
                return notify_fail("知府哼了一聲說道：“急什麼？等本官升堂了再說！”\n");

   if( query_temp("unmarry", me) )
           return notify_fail("江耀亭黑著臉看看你：“本官不是剛剛幫你們辦過離婚手續？還來煩我！？”\n");

        if( !mapp(query("couple", me)) || !query("couple/have_couple", me) )
        {
                if( query("gender", me) == "女性" )
                        say("江耀亭臉一沉喝道：“大膽刁婦，你分明沒有丈夫，還敢戲弄本官，來人呀！打她二十大板！”\n");
                else
                        say("江耀亭臉一沉喝道：“大膽刁民，你分明沒有妻室，還敢戲弄本官，來人呀！打他二十大板！”\n");
      call_out("zou",1,me);
      return 1;
        }
   if( !arg || arg != query("couple/couple_id", me) )
           return notify_fail("江知府皺了皺眉頭：你要和誰離婚？\n");
//   ob = new(LOGIN_OB);
//        ob->set("id",(string)me->query("couple/couple_id"));
//        if( !ob->restore() )
        seteuid(getuid());
        if( file_size(DATA_DIR + "login/" + arg[0..0] + "/" + arg + ".o")<0 )
   {
       message_vision("江耀亭聽了$N的陳述，仔細查看了案卷，點點頭道：“既然你的愛人已經不在人世，我就給你\n"
       "單獨辦理離婚手續，錢也不必要交了！”然後在案卷上作了記錄後，蓋上了官印，對師爺招手\n"
       "道：“送一份給紅娘莊！”然後又對$N說：“你走吧，你已經是單身了！”\n",me);
                CHANNEL_D->do_channel(this_object(), "mudnews",
                sprintf( "經本府明查：由于%s的配偶已經去世，他們的婚姻關系自然解除！\n", me->name()));
                addn("couple/unmarried", 1, me);
      set("couple/have_couple", 0, me);
        set("couple/couple_id", 0, me);
        set("couple/couple_name", 0, me);
        set("couple/couple_gender", 0, me);
      return 1;
   }
        else if( !objectp(obj=present(query("couple/couple_id", me),environment(me)) )
                  || !find_player(query("couple/couple_id", me)) )
                return notify_fail("江知府懶懶地看了看你道：“你的愛人現在不在場，要兩人一起來才能辦離婚。”\n");

   if(query_temp("money")!=me->name()
           &&query_temp("money")!=obj->name())
           return notify_fail("江知府拍了拍桌子：“離婚的手續費100 gold你還沒交，沒錢就回去湊合著過日子，不要來煩本官！\n");

        if( query_temp("pending/unmarry", obj) != me )
        {
                set_temp("pending/unmarry", obj, me);
                message_vision(MAG "\n$N看了看$n長嘆一口氣道：“罷罷罷……我們還是好聚好散吧！?”\n"
                        "江耀亭眯起眼睛問問$n：“你願不願意離婚呢？說出來，本官為你作主！”\n"NOR,me,obj);
      tell_object(obj,"如果你同意離婚，請你也對"+me->name()+"("+query("id", me)+
                               ")"+"下一次unmarry"+query("id", me)+"的指令。\n");
                write(MAG "現在你正等待著你的伴侶的回答...\n" NOR);
                return 1;
        }
        message_vision(MAG "\n$N對著$n哼了一聲說道：“事已至今，既然無緣，咱們就各走各的路吧。”\n\n"NOR, me,obj);
   set_temp("unmarry", 1, me);
   set_temp("unmarry", 1, obj);
        message_vision(HIY "江耀亭看了看點點頭說道：“$N和$n，既然你們都同意離婚，那本官也就給你們辦了！”\n"
           "說完，在姻緣簿上重重地劃去了兩個名字。\n" NOR, obj, me);
        CHANNEL_D->do_channel(this_object(), "mudnews",
        sprintf( "經本府宣判：從今天起，%s和%s的婚姻關系解除！\n", me->name(), obj->name()));

      set("couple/have_couple", 0, me);
        set("couple/couple_id", 0, me);
        set("couple/couple_name", 0, me);
        set("couple/couple_gender", 0, me);

        my_skl=me->query_skills();
        if(mapp(my_skl)) {
                        skl_name = keys(my_skl);
                        level=values(my_skl);
                        for (i=0;i<sizeof(skl_name);i++)
{
if (level[i]>3)
                        me->set_skill(skl_name[i],level[i]-2);
}
                  }

        set("couple/have_couple", 0, obj);
        set("couple/couple_id", 0, obj);
        set("couple/couple_name", 0, obj);
        set("couple/couple_gender", 0, obj);
//        my_skl=obj->query_skills();
//        if(mapp(my_skl)) {
//                        skl_name = keys(my_skl);
//                        level=values(my_skl);
//                        for (i=0;i<sizeof(skl_name);i++)
//{
//if (level[i]>3)
//                        obj->set_skill(skl_name[i],level[i]-2);
//}
//                  }

        return 1;
}