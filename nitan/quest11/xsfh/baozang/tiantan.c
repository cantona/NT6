//tangfeng@SJ 8/2004

inherit ROOM;
#include <ansi.h>
#define QUESTDIR5 "quest/雪山飛狐/寶藏/"

void create()
{
            set("short",HIW"大廳"NOR);
            set("long",@LONG
這裡是寶藏圖標志的天壇，巨大的廣場難以想象當初如何建造。中間堆落
著一個巨大的天壇，看來是祭祀所用，可能因為年代的久遠，已經有些塌陷。
但不影響其宏大的氣勢。
LONG
       );
        set("exits", ([
                "east" : __DIR__"midong1",
                "south" : __DIR__"midong2",
                "west" : __DIR__"midong3",
                "north" : __DIR__"midong4",
        ]));
            set("valid_startroom", 1);
            set("quest", 1);
            set("no_fight", 1);
            set("no_get", 1);
            set("baozang",1);
            setup();
}

void init()
{
int i;
  object me,ob,*obj;
  ob = this_object();
  me = this_player();
  obj = deep_inventory(me);
   i = sizeof(obj);
  while (i--)
  if (obj[i]->is_character())
      me->set_temp("out",1);
  if (me->query_temp("out")||!me->query(QUESTDIR5+"start")||!me->query_temp(QUESTDIR5+"search_ok")
        ||!me->query_temp(QUESTDIR5+"map_where")||me->query_condition("killer"))
  {
     me->delete_temp("out");
     me->delete_temp(QUESTDIR5+"search_ok");
     me->delete_temp(QUESTDIR5+"search");
          message_vision(YEL"突然$N聽到一個聲音道：“這裡不歡迎$N！”\n"NOR,me);
    if(!wizardp(me)) 
      {
             me->move("/d/xiangyang/damen");  
           tell_object(me,YEL"你抬眼一看，這裡竟然是武館大門，剛才的一切像夢一樣虛幻。\n"NOR); 
    }
    else 
     {
          if(random(2)) message_vision(YEL"$N似乎有些氣憤，張口罵道：“沒看出我是誰啊？我是巫師"+me->query("name")+"”\n\n"NOR,me);
          else message_vision(YEL"$N哼了一聲，突然渾身散發出神才有的氣勢，額頭隱隱約約顯出幾個金字："NOR+HIY+me->query("name")+NOR+YEL"！\n\n"NOR,me);
          message_vision(YEL"剛才鳥叫的聲音好像也似乎因為$N的氣勢萎了回去。$N不由地得意地一笑。\n"NOR,me);
          message_vision(YEL"突然一個角落裡飛出一只鞋子，砰的一聲砸到$N頭上，接著一個聲音道：“管你是誰，TMD”\n"NOR ,me);
          me->unconcious();
    }
     return;   
  }
   if(ob->query("busy")&&ob->query("busy")!=me->query("id"))
  {
     tell_object(me,YEL"突然你聽到一個聲音道：“寶藏已經被人搶先一步了！”\n"NOR); 
     me->move("/d/xiangyang/damen");  
     me->delete_temp(QUESTDIR5+"search_ok");
      me->delete_temp(QUESTDIR5+"search");
     tell_object(me,YEL"你抬眼一看，這裡竟然是武館大門，剛才的一切像夢一樣虛幻。\n"NOR); 
     return;   
   }
  ob->set("exits/up",me->query_temp(QUESTDIR5+"map_where"));
  ob->set("busy",me->query("id"));//其他玩家無法進入
  remove_call_out("check");
  call_out("check",1,me);
}
int valid_leave(object me, string dir)
{
        if ( dir == "up" && userp(me) && me->query(QUESTDIR5+"start")) this_object()->delete("busy");
        return ::valid_leave(me,dir);
}
void check(object me)
{
	object obj;
	remove_call_out("check");
	if(!me||!living(me) || !environment(me)->query("baozang"))
	{
		this_object()->delete("exits/up");
		this_object()->delete("busy");
		return;
	}
        if((obj=present("baozang tu",me))) 
        {
                            tell_object(me,YEL"你順手丟掉"+obj->query("name")+YEL"。\n"NOR); 
              message_vision(HIC"$N丟下一張"+obj->query("name")+HIC"！\n" NOR,me);
              message_vision(obj->query("name")+HIC"落地時一閃，竟然失去了蹤影！\n" NOR,me);
                    destruct(obj);
       }
  call_out("check",1,me);
}
