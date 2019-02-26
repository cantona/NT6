#include <ansi.h>
inherit ITEM;
#define QUESTDIR5 "quest/雪山飛狐/寶藏/"
string* map_where = ({"/d/hj/caoyuan1","/d/fairyland/shanxi","/d/lanzhou/qingcheng",
                      "/d/lanzhou/tumenzi","/d/lanzhou/gccheng","/d/lanzhou/wufosi",});
string* map_name = ({"草海","崑崙小溪","青城","蘭州土門子","古長城","五佛寺",});

void create()
{
        set_name(HIB"寶藏圖"NOR, ({ "baozang tu","tu"}));
        set_weight(1000);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "張");
                set("long","一個羊皮紙上似乎是隨意記錄一些山脈、河流和城鎮的地圖。\n"+
                           "你可以按地圖上的樣子對照（duizhao）你的方位。\n");
                set("value",1);
                 set("unique", 1);
                set("no_get",1);
                set("no_give",1);
                set("no_drop",1);
        }
        setup();
}

void init()
{
	if (environment()==this_player()&&!this_player()->query_condition("killer"))
	{
        add_action("do_duizhao","duizhao");
  }
}

int do_duizhao(string arg)
{
     	object me, obj,room;
     	int i;
     	string where,name;
     	me = this_player();
     	obj= this_object();
     	if(me->is_busy()) return 0;
     	if(me->is_fighting()) return 0;
     	if(!me->query(QUESTDIR5+"start")) return 0;
     	if(!present("lengyue dao",me))
     	    return notify_fail(HIY"單純的地圖無法提供足夠的信息，你需要其他線索！\n"NOR);
        if( ! arg || (arg != "lengyue baodao"&& arg != "baodao"&& arg != "lengyue"))
                 return notify_fail("你對照的東西無法比較出什麼結果。\n");
      if(!me->query_temp(QUESTDIR5+"yanjiu_ok"))
     		  return notify_fail(HIY"單純的地圖無法提供足夠的信息，你需要其他線索！\n"NOR);
      if(!me->query_temp(QUESTDIR5+"guanzhu_ok"))
      {
           message_vision(HIC"$N將"+obj->name()+HIC"對比着冷月寶刀，翻來覆去地研究着！\n"NOR, me);
     	   me->add("neili", -150);
     	   return notify_fail(HIY"很遺憾的是，寶刀上的提示似乎還不夠清晰！\n"NOR);
     	}
      if(me->query_temp(QUESTDIR5+"search_ok"))
     	   return notify_fail(HIY"地圖已經什麼都看不出來了！\n"NOR);
      if(me->query_temp(QUESTDIR5+"map_where"))
     	   return notify_fail(HIY"地圖漸漸變得模糊，什麼也看不清楚了！\n"NOR);
      i=random(sizeof(map_where));
      where=map_where[i];
      name=map_name[i];
      if(!room=find_object(where))
        room=load_object(where);
      if(!room)  return notify_fail(HIY"地圖漸漸變得模糊，可能是巫師做的手腳！\n"NOR);
     	message_vision(HIC"$N將"+obj->name()+"對比着冷月寶刀，翻來覆去地研究着！\n"NOR, me);
     	tell_object(me,YEL"你發現刀身上的數條脈路，似乎和藏寶圖可以對照。\n"NOR);
     	tell_object(me,YEL"你突然發現兩者結合最終的標誌竟然落在一個你曾經熟悉的地方——"+name+"。\n"NOR);
      me->set_temp(QUESTDIR5+"map_where",where);
      me->start_busy(1);
     	return 1;
}
