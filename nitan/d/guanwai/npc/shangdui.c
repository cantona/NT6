//snowman 28/02/98
#include <ansi.h>
inherit ITEM;
int j=3;
void create()
{
        set_name("清兵人馬", ({ "qingbingrenma"}));
        set("unit", "只");
        set_weight(90000000);
        set("long", "
一只遠道而來的清兵人馬，看來有不少高手。中間插
著一面大旗，似乎寫著“大清”二個大字，隊伍之中
似乎有一輛囚車。。。\n");
        set("no_get", 1);
        set("no_drop", 1);
         set("no_put",1);
}

void init()
{ remove_call_out("aaa");
  call_out("aaa", 120, this_object());  
  add_action("do_rob", "jieche");
}

int do_rob()
{
   object me, ob;   
   string arg;
   int stage, i;
   me = this_player();
   ob = this_object();
   stage = 0;
   arg = query("arg");

   if(!living(me)) return 0;
   if( !query("kill_yunlong", me) )
       return notify_fail("你膽子不小，竟敢和大清做對？\n");
   if(objectp(present("qingbing", environment(me))))
       return notify_fail("清兵看來武功不弱，你還是先打發了面前這個再說吧！\n");  

   message_vision(HIR"$N對著$n大吼一聲："+me->name()+"在此！快把囚車裡的義士給放了！\n"NOR, me, ob);
   set_temp("xx_rob", 1, me);
   remove_call_out("make_bs");
   call_out("make_bs", 1, me, ob); 
   return 1;     
}
void make_bs(object me, object ob)
{
   object obj, obj1;
        if (j>0){
          obj = new(__DIR__"xiake");
         obj->move(environment(me));
          obj->do_copy(me);
         obj1 = new(__DIR__"xiake");
         obj1->move(environment(me));
           obj1->do_copy(me);
          j=j-1;     }
else {
       message_vision(HIW"$N見已經無活人，將反清義士救出！！\n"NOR, me);    
       ;    
       obj=new(__DIR__"dashi");
       obj->move(environment(me));
//       obj->move(me);
       set("owner",query("id",  me), obj);
       addn("combat_exp", 30, me);
       addn("potential", 10, me);
       addn("shen", 100, me);
        tell_object(me,"你被獎勵了\n二百點經驗值。\n");
       delete_temp("rob_start", me);
       delete_temp("xx_rob", me);
       delete_temp("rob_job", me);
       delete_temp("j", me);
       message_vision("$N轉過幾個小山丘就不見了。\n",ob);
       destruct(ob);
    }
}

void aaa(object me)
{
        if (! me) return;
       message_vision("$N轉過幾個小山丘就不見了。\n",me);       
       destruct(me);
       return;
}
