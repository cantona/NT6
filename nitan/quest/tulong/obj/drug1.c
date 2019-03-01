#include <ansi.h>

inherit ITEM;

void init()
{
    set("no_get", "你拿不起來這樣東西。試試挖挖(dig)。\n");
    set("no_give","這麼珍貴的藥，哪能隨便給人？\n");
    set("no_drop","這麼寶貴的丹藥，扔了多可惜呀！\n");
    set("no_sell","凡人哪裡知道"+query("name", this_object())+"的價值？還是自己留著吧。\n");

    add_action("do_dig", "dig");
    add_action("do_eat", "eat");
}

void create()
{
  set_name(RED "瓊草嫩芽" NOR, ({"qiong cao","cao"}));
  set_weight(200);
  if (clonep())
    set_default_object(__FILE__);
  else {
    set("unit", "顆");
    set("long", "一顆紫紅色的小草。\n");
    set("value", 0);
    set("drug_type", "補品");
  }
  
  // the following line is added by snowcat
  set("is_monitored",1);
  setup();
}
int do_dig(string arg)
{
   object spirit, who, me, where;
   who=this_player();
   me=this_object();
   where=environment(me);

   if( query("can_eat", me) )
     return notify_fail("什麼？\n");

   if( !arg || (arg!="qiong cao" && arg!="cao"))
     return notify_fail("你要挖什麼？\n");

   if(who->is_fighting() && who->is_busy())
     return notify_fail("你很忙，沒時間挖草。\n"); 

   if( spirit=present("spirit")){
     message_vision("日光精靈身周光芒大盛，對$N發起了攻擊。\n", who);
     spirit->kill_ob(who);
     who->fight_ob(spirit);
     return 1;
   }
     message_vision("$N輕輕將$n挖了起來。\n", who, me);
     set("can_eat", 1, me);
     me->move(who);
   tell_object(who, HIY "\n\n日光精靈化為一片明亮的光芒，第五個封印解開了！\n"NOR);  
   message("channel:chat",HBMAG"【精靈神界】"+query("name", me)+"成功的解開了第五封印.\n"NOR,users());
        set_temp("m_success/瓊草", 1, me);
     remove_call_out("grow_a");
     remove_call_out("grow_b");
                remove_call_out("grow_c");
                remove_call_out("grow_d");
                remove_call_out("grow_e");
                remove_call_out("grow_f");
                remove_call_out("grow_g");
     delete("grow_grass", where);

   if( !spirit && query("eatable", me)){
     seteuid(getuid());
     spirit=new("/quest/tulong/npc/spirit1");
     spirit->move(environment(who));
   tell_room(environment(who), "忽然光芒大盛，日光精靈的身形現了出來。\n");
   spirit->kill_ob(who);
   who->fight_ob(spirit);
   }
   return 1;
}

int do_eat(string arg)
{
   object me=this_object();
   object who=this_player();
   int neili_add;
   
     if (!id(arg))
         return notify_fail("你要吃什麼？\n");
   if( !query("can_eat", me) )
     return notify_fail("你要吃什麼？\n");

   set("food", who->max_food_capacity(), who);
     set("water", who->max_water_capacity(), who);

   if( !query("eatable", me)){
     message_vision("$N狼吞虎嚥般地將一顆$n吃了下去。\n", who, me);
     destruct(me);
     return 1;
   }

   neili_add=30;
   
   message_vision("$N將一顆$n輕輕嚼著嚥下了肚，臉上泛起陣紅暈。\n", who, me);
   tell_object(who, "你覺得一陣熱氣直通七竅，渾身上下好象有使不完的力氣。\n");

  set("eff_jing",query("max_jing",  who), who);
  set("jing",query("max_jing",  who), who);
  set("eff_qi",query("max_qi",  who), who);
  set("qi",query("max_qi",  who), who);
   
   if( query("max_neili", who)<10*who->query_skill("force")){
         addn("max_neili", neili_add, who);
   }
     destruct(me);
}



void invocation()
{
   object me=this_object();
   int i=200+random(200);
   call_out("grow_a", i, me);
}

int grow_a(object me)
{
   int i=400+random(400);
   tell_room(environment(me), me->name()+"慢慢地長出了一個小葉。\n", ({me, me}));
   set_name(RED "一葉瓊草" NOR, ({"qiong cao","cao"}));
   call_out("grow_b", i, me);
   return 1;
}

int grow_b(object me)
{
        int i=600+random(600);
        tell_room(environment(me), me->name()+"慢慢地長出了一個小葉。\n", ({me, me}));
        set_name(RED "二葉瓊草" NOR, ({"qiong cao","cao"}));
        call_out("grow_c", i, me);
        return 1;
}

int grow_c(object me)
{
        int i=800+random(800);
        tell_room(environment(me), me->name()+"慢慢地長出了一個小葉。\n", ({me, me}));
        set_name(RED "三葉瓊草" NOR, ({"qiong cao","cao"}));
        call_out("grow_d", i, me);  
        return 1;
}

int grow_d(object me)
{
        int i=1000+random(1000);
        tell_room(environment(me), me->name()+"慢慢地長出了一個小葉。\n", ({me, me}));
        set_name(RED "四葉瓊草" NOR, ({"qiong cao","cao"}));
        call_out("grow_e", i, me);  
        return 1;
}

int grow_e(object me)
{
        int i=1200+random(1000);
        tell_room(environment(me), me->name()+"慢慢地長出了一個小葉。\n", ({me, me}));
        set_name(RED "五葉瓊草" NOR, ({"qiong cao","cao"}));
        call_out("grow_f", i, me);  
        return 1;
}

int grow_f(object me)
{
        int i=1500+random(1000);
        tell_room(environment(me), me->name()+"慢慢地長出了一個小葉。\n", ({me, me}));
        set_name(RED "六葉瓊草" NOR, ({"qiong cao","cao"}));
        call_out("grow_g", i, me);  
        return 1;
}

int grow_g(object me)
{
        int i=2000+random(1000);
        tell_room(environment(me), me->name()+"慢慢地長出了一個小葉。\n", ({me, me}));
   tell_room(environment(me), me->name()+"周圍漸漸籠起一股紅光。\n", ({me, me}));
        set_name(RED "七葉瓊芝草" NOR, ({"qiong cao","cao"}));
   set("eatable",1);
        return 1;
}
