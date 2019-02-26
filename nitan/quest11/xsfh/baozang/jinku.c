//tangfeng@SJ 8/2004

#include <ansi.h>
#include <room.h>
inherit ROOM;
#define QUESTDIR5 "quest/雪山飛狐/寶藏/"

void create()
{
        set("short",YEL"金庫"NOR);
        set("long", @long
這裏是金庫，你可以看見偶爾失落的寶玉黃金，只是傳説中的那無數的
寶藏，似乎並沒有發現。這裏明顯有一些打鬥的痕跡，怕是早有人來過。
long);
        set("exits", ([
                "north" : __DIR__"tiantan",
                "south" : __DIR__"midong2",
                "east" : __DIR__"midong2",
                "west" : __DIR__"midong2",
        ]));
        set("quest", 1);
        set("baozang",1);
        setup();
}
void init()
{
  object me;
  if (interactive(me = this_player()) && me->query(QUESTDIR5+"start") && me->query_temp(QUESTDIR5+"search_ok") && !me->query(QUESTDIR5+"jinku"))
  {
       remove_call_out("greeting");
       call_out("greeting", 3, me);
	   me->start_busy(3);
  }       
}
void greeting(object me)
{
	object obj;
	if(!me) return;
	if(!present(me,this_object())) return;
	if(me->query(QUESTDIR5+"jinku")) return;

	me->set(QUESTDIR5+"jinku",1);  //
	obj=new("/clone/money/gold");
	obj->set_amount(300+random(300));
	obj->move(me);
    
	message_vision(WHT"\n$N撿起一些"+obj->query("name")+WHT"！\n"NOR, me);
	obj=new("/d/xingxiu/obj/yuqi");
	obj->move(me);
	message_vision(WHT"$N撿起一塊"+obj->query("name")+WHT"！\n"NOR, me);
	obj=new("/d/hj/obj/tu");
	obj->move(me);
	message_vision(WHT"$N撿起一幅"+obj->query("name")+WHT"！\n"NOR, me);
	obj=new("/d/hj/obj/tu");
	obj->move(me);
	message_vision(WHT"$N撿起一幅"+obj->query("name")+WHT"！\n"NOR, me);
	obj=new("/d/hj/obj/tu");
	obj->move(me);
	message_vision(WHT"$N撿起一幅"+obj->query("name")+WHT"！\n"NOR, me);
	obj=new("/d/hj/obj/shiqi");
	obj->move(me);
	message_vision(WHT"$N撿起一塊"+obj->query("name")+WHT"！\n"NOR, me);
	obj=new("/d/hj/obj/shiqi");
	obj->move(me);
	message_vision(WHT"$N撿起一塊"+obj->query("name")+WHT"！\n"NOR, me);
	obj=new("/d/hj/obj/shiqi");
	obj->move(me);
	message_vision(WHT"$N撿起一塊"+obj->query("name")+WHT"！\n"NOR, me);

	tell_object(me,HIR"\n你四處轉了一圈，果然找到很多玉器黃金，還有一些值錢的名跡，看來這次不虛此行啊。\n"NOR);
	tell_object(me,HIG"突然發現地上一疊不起眼的石板。你伸手撿了起來，竟然是高昌的名物！\n"NOR);
	message("channel:rumor", HIM"【謠言】傳説在闖王寶藏的"+environment(me)->query("short")+HIM"裏，有人找到大量寶物黃金！\n"NOR,users() );
	log_file("quest/FEIHU", sprintf("%s(%s)從寶藏中獲得無數的黃金玉器和名畫。經驗%d。", me->name(1),me->query("id"), me->query("combat_exp")) );
}
