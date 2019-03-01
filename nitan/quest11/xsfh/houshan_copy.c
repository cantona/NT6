//wrong
//tanfeng@SJ 8/2004

#include <ansi.h>
inherit ROOM;
#define QUESTDIR2 "quest/雪山飛狐/復仇篇/"

void create()
{
        set("short","後山");
        set("long", @LONG
古樹參天，荊棘密布，一不小心就會被掛到了手腳。濃密寬厚的樹葉遮蔽
了日月星辰，地上零星散落著捕蛇人踩過的腳印，四周死一般的寂靜，只有風
吹過樹梢的沙沙之聲。遍地爬滿了各種毒蟲，你不禁產生了退縮之心。
LONG
        );

   set("quest",1);
        set("exits", ([
                "southeast" : __DIR__"shanlu",
        ]));
        set("outdoors", "苗疆");
        setup();
}
void init()
{
  object me = this_player();
  if(me->query(QUESTDIR2+"start"))
  {
  	call_out("greeting",3,me);
  }
}
void greeting(object me)
{
	int j;
	object obj;
	if(!me) return;
	if(!present(me,this_object())) return;
	tell_object(me,HIG"你看了看四周，發現這裡根本沒有人行的痕跡，或許是路走錯了。\n"NOR);
	if(random(2))
	{
		      j=me->query_skill("force");
          obj=new("/d/sld/npc/dushe");
          message_vision(HIC"突然，草叢中鑽出一只"+obj->name()+"。\n"NOR,me);
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
	}
}
