//tangfeng@SJ 8/2004

#include <ansi.h>
#include <room.h>
inherit ROOM;
#define QUESTDIR5 "quest/雪山飛狐/寶藏/"
#define QUESTDIR4 "quest/雪山飛狐/武功/"

void create()
{
        set("short",BLU"書房"NOR);
        set("long", @long
你打量四周，看來似乎是個書房，但是架子上一本書也沒有，好像連腐爛
的痕跡都沒有。架子旁邊是個桌子，中間早已裂開；旁邊應該是幾個花盆。
long);
        set("exits", ([
                "west" : __DIR__"tiantan",
                "south" : __DIR__"midong1",
                "east" : __DIR__"midong1",
                "north" : __DIR__"midong1",
        ]));
        set("quest", 1);
        set("baozang",1);
        setup();
}
void init()
{
        add_action("do_search", "xunzhao");
        add_action("do_search", "dig");
        add_action("do_search", "search");
        add_action("do_move", "move");
        add_action("do_push", "push");
        add_action("do_push", "tui");
        add_action("do_bang", "bang");
        add_action("do_move", "zhuan");
}
int do_search(string arg)
{
     object me,obj;
     me = this_player();
     if (me->is_busy() || me->is_fighting())
                   return notify_fail("你正忙着哪！\n");
      message_vision(HIY"$N蹲在地上，四處尋找。\n"NOR, me);
      if(!wizardp(me)) me->start_busy(1);
      if(me->query(QUESTDIR5+"yupei")||!me->query(QUESTDIR4+"lengquanshengong")||me->query(QUESTDIR4+"lengquanshengong_teach"))
      {
         tell_room(environment(me), me->name() + "找了半天，只弄了一手泥。\n", ({ me }));
         return notify_fail("你找了半天，什麼也沒找到。\n");
      }
      obj = new("/d/xingxiu/baozang/obj/yuqi");
      obj->set("owner",me->query("id"));
      obj->set("quest",1);
      obj->set("long", HIC"這是東漢玉石飾品中的一個，出自陝西，山東，河南一帶。\n"
                      +"下面刻着一個“苗”字。\n"NOR);
      obj->move(me);
      message_vision(WHT"$N按照紙團提示的方位，並沒有發現祕籍，但卻發現一塊"+obj->name()+WHT"。\n"NOR, me);
      log_file("quest/FEIHU", sprintf("%s(%s)找到苗家玉佩，解開冷泉神功。經驗%d。\n", me->name(1),me->query("id"),me->query("combat_exp")) );
      me->set(QUESTDIR5+"yupei",1);
      me->start_busy(2);
      return 1;
 }

int do_push(string arg)
{
	object me,*ob;
  int i;
  me = this_player();
	if (me->is_busy() || me->is_fighting())
		      return notify_fail("你正忙着哪！\n");
	if ( !arg || (arg != "zhuo zi" &&arg != "zhuozi" &&arg != "anmen" && arg != "wall"))
       		return notify_fail("你要推動什麼？\n");
  ob = deep_inventory(me);
  i = sizeof(ob);
  while (i--)
  if (ob[i]->is_character())
       		return notify_fail("你揹負一人，無法推動。\n");
  if(arg=="zhuo zi"||arg=="zhuozi")
  {
    if(!me->query_temp(QUESTDIR5+"bang_zhuozi"))
       		return notify_fail("桌子太零散，無法推開。\n");
    if(me->query_temp(QUESTDIR5+"move_zhuozi"))
    {
    		message_vision(HIY"$N把桌子又推回原來的位置。\n"NOR, me);
	      me->delete_temp(QUESTDIR5+"move_zhuozi");
        me->start_busy(1);
  	    return 1;
    }
	  message_vision(HIG"$N用力將綁好的桌子全部推到角落的一邊。\n"NOR, me);
	  me->set_temp(QUESTDIR5+"move_zhuozi",1);
    me->start_busy(1);
  	return 1;
  }
  if(!me->query_temp(QUESTDIR5+"move_huapen"))
       		return notify_fail("暗門的機關沒有打開，無法推開。\n");
  if(!me->query_temp(QUESTDIR5+"move_zhuozi"))
       		return notify_fail("有桌子阻擋，無法推開。\n");

	message_vision(HIG"$N用力推開活動的暗門，奮力從門縫擠了進去。\n"NOR, me);
	me->move(__DIR__"mishi");
	me->delete_temp(QUESTDIR5+"move_zhuozi");
	me->delete_temp(QUESTDIR5+"move_huapen");
	me->delete_temp(QUESTDIR5+"bang_zhuozi");
  me->start_busy(1);
	tell_room(environment(me), me->name() + "從外面擠了進來。\n", ({ me }));
	return 1;
}
int do_move(string arg)
{
	object me;
  me = this_player();
	if (me->is_busy() || me->is_fighting())
		return notify_fail("你正忙着哪！\n");
	if ( !arg || (arg != "huapen" && arg != "hua pen"))
       		return notify_fail("你要轉動什麼？\n");
  if(me->query_temp(QUESTDIR5+"move_huapen"))
  {
  	message_vision(HIG"$N把地上的花盆轉回原位。\n"NOR, me);
	  me->delete_temp(QUESTDIR5+"move_huapen");
    me->start_busy(1);
    return 1;
  }
	message_vision(HIG"$N轉了轉地上的花盆。\n"NOR, me);
	me->set_temp(QUESTDIR5+"move_huapen",1);
  me->start_busy(1);
	tell_room(me,"你突然發現桌子後邊似乎有道暗門。\n");
	return 1;
}
int do_bang(string arg)
{
	object me,ob;
  me = this_player();
	if (me->is_busy() || me->is_fighting())
		return notify_fail("你正忙着哪！\n");
	if ( !arg || (arg != "zhuo zi" && arg != "zhuozi"))
       		return notify_fail("你要綁什麼？\n");
  if(me->query_temp(QUESTDIR5+"bang_zhuozi"))
       		return notify_fail("你已經綁好了。\n");
  if(!(ob=present("sheng zi",me))) 
       		return notify_fail("你沒有繩子，拿什麼綁？\n");
       		
	message_vision(HIG"$N將快要零散的桌子，用繩子綁在一起。\n"NOR, me);
	me->set_temp(QUESTDIR5+"bang_zhuozi",1);
  me->start_busy(1);
	return 1;
}
