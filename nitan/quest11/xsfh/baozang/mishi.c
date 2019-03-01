inherit ROOM;
#include <ansi.h>
#define QUESTDIR5 "quest/雪山飛狐/寶藏/"
#define QUESTDIR4 "quest/雪山飛狐/武功/"
void create()
{
          set("short",HIC"密室"NOR);
	  set("long",@LONG
明顯這是一個密室，狹小的空間很難確定當年這裡的用途。
LONG
           );

	  set("exits",([
              "out": __DIR__"shuku",
          ]));
    set("quest",1);
    set("baozang",1);
	  setup();
}
void init()
{
        add_action("do_search", "search"); 
        add_action("do_search", "xunzhao"); 
        add_action("do_search", "dig"); 
}
int valid_leave(object me, string dir)
{
      if((present("zhi tuan",me))||(present("tishi ka",me)))  return notify_fail(HIR"你攜帶了不允許攜帶出去的物品，請丟棄之後再嘗試離開。\n"NOR);
       return ::valid_leave(me, dir);
}
int do_search(string arg)
{
  object me,obj;
  me = this_player();
  if (me->is_busy() || me->is_fighting())
		      return notify_fail("你正忙著哪！\n");
  message_vision(HIY"$N蹲在地上，四處尋找。\n"NOR, me);
  if(!wizardp(me)) me->start_busy(1);
  if(me->query(QUESTDIR5+"shuku")>=4||random(2)||present("zhi tuan",me))
  {
       tell_room(environment(me), me->name() + "找了半天，只弄了一手泥。\n", ({ me }));
       return notify_fail("你找了半天，什麼也沒找到。\n");
  }
  me->add(QUESTDIR5+"shuku",1);
  obj=new("/cmds/leitai/bwdh/obj/danwan");
  obj->set("owner",me->query("id"));
  if(me->query(QUESTDIR5+"shuku")==1) obj->set("secret_obj",1);
  obj->set("bonus","combat_exp");
  obj->move(me);
  message_vision(WHT"$N發現一顆"+obj->name()+WHT"。\n"NOR, me);
  log_file("quest/FEIHU", sprintf("%s(%s)找到密室的寶物%s。經驗%d。\n"NOR, me->name(1),me->query("id"),obj->query("name"), me->query("combat_exp")) );
  me->start_busy(2);
   if(!me->query(QUESTDIR4+"lengquanshengong")&&((me->query(QUESTDIR5+"shuku")>=4 && me->query("registered")>=3)||(me->query(QUESTDIR5+"shuku")==3)))
{
	  message_vision(HIG"$N打開"+obj->name()+HIG"竟然發現裡面有一張紙團。\n"NOR, me);
	  tell_object(me,HIY"你展開紙團，仔細看了看似乎是武功秘籍之類的介紹。\n"NOR);
	  destruct(obj);
	  obj=unew("/d/xingxiu/baozang/obj/zhituan");
	  if(!clonep(obj)){
		  tell_room(environment(me), me->name() + "順手把紙團丟了。\n", ({ me }));
		  log_file("quest/FEIHU", sprintf(HIR"%s(%s)隨手丟棄紙團。注意可能有BUG。\n"NOR, me->name(1),me->query("id")) );
		  return notify_fail(HIY"你看了看什麼也沒看懂，你順手把紙團丟了。\n"NOR);
	  }
	  obj->set("owner",me->query("id"));
	  obj->move(me);
	  me->add_busy(1);
	  log_file("quest/FEIHU", sprintf(HIR"%s(%s)找到冷泉神功提示紙團。經驗%d。\n"NOR, me->name(1),me->query("id"),me->query("combat_exp")) );
	  return 1;
  }
  return 1;
}
