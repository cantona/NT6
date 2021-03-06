//tangfeng@SJ 8/2004

#include <ansi.h>
#include <room.h>
inherit ROOM;
#define QUESTDIR5 "quest/雪山飛狐/寶藏/"

void create()
{
        set("short",YEL"藥庫"NOR);
        set("long", @long
可以看出這本來是一個藥房，經過幾百年，幾乎所有的藥材都已腐爛，但
是整個房間還依然散發出濃郁的古香。這裏看來還是保留了一些名貴中藥。
long);
        set("exits", ([
                "south" : __DIR__"tiantan",
                "west" : __DIR__"midong4",
                "east" : __DIR__"midong4",
                "north" : __DIR__"midong4",
        ]));
        set("quest", 1);
        set("baozang",1);
        setup();
}
void init()
{
        add_action("do_search", "dig");
        add_action("do_search", "xunzhao");
}
int do_search(string arg)
{
        object obj, me;
        int j;
        me = this_player();

        if( ! arg || (arg != "drug"&&arg != "yao cai"&& arg != "yaocai"&& arg != "zhongyao"&& arg != "zhong yao"&& arg != "medicine"))
          return notify_fail("你要找什麼？\n");
	      if( me->is_busy() )
		      return notify_fail("你上一個動作還沒有完成！\n");
	     if( me->is_fighting() )
		      return notify_fail("你還是專心作戰吧！\n");
        if ((int)me->query("jingli") < 500) 
           return notify_fail("你的精力不夠做這件事！\n");  
      	message_vision(HIC"$N蹲在地上，四處尋找。\n"NOR, me);
        if(random(6)!=1||me->query(QUESTDIR5+"yaoku")) 
        {
           me->add("jingli",-200);
           if(!wizardp(me)) me->start_busy(1);
           tell_room(environment(me), me->name() + "找了半天，只弄了一手泥。\n", ({ me }));
           return notify_fail("你找了半天，什麼也沒找到。\n");
        }
        else
        {
          if(random(2)) obj = new("/clone/medicine/neili/puti-zi.c");
          else obj = new("/clone/medicine/neili/qnshouwu.c");
          message_vision(HIB"$N翻開一塊石板，竟然發現一顆"+obj->name()+"。\n"NOR,me);
          //標誌
          me->set(QUESTDIR5+"yaoku",1);
          obj->set("owner",me->query("id"));
          obj->move(me);
          log_file("quest/FEIHU", sprintf("%s(%s)獲得寶藏寶物：%s。經驗%d。\n", me->name(1),me->query("id"),obj->name(1), me->query("combat_exp")) );
          j=me->query_skill("force");
          obj=new("/d/sld/npc/dushe");
          message_vision(HIC"突然，草叢中鑽出一隻"+obj->name()+"。\n"NOR,me);
		      obj->set("combat_exp", me->query("combat_exp"));
		      obj->set("max_qi", me->query("max_qi")*3);
		      obj->set("eff_qi", me->query("max_qi")*3);
		      obj->set("qi", me->query("max_qi")*3);
		      obj->set("max_jing", me->query("max_jing"));
		      obj->set("jing", me->query("max_jing"));
		      obj->set("eff_jing", me->query("eff_jing"));
		      obj->set("eff_jingli", me->query("eff_jingli"));
		      obj->set("max_neili", me->query("max_neili"));
		      obj->set("jing", me->query("max_jing"));
		      obj->set("jingli", me->query("max_jingli"));
		      obj->set("neili", me->query("max_neili")*3/2);
		      obj->set("jiali", 200);
		      obj->set("str", me->query("str")*2);
		      obj->set("con", me->query("con")*2);
		      obj->set("dex", me->query("dex")*2);
		      obj->set("int", me->query("int")/2);
		      obj->set_skill("unarmed",j +random(50));
		      obj->set_skill("force",j + random(50));
		      obj->set_skill("dodge",j + random(50));
		      obj->set_skill("parry",j + random(50));
		      obj->move(environment(me));
		      obj->set_leader(me);
		      message_vision(RED"$N決定和$n一起行動。\n"NOR,obj,me);
		      obj->kill_ob(me);
          return 1;
       }
}
