
#include <ansi.h>
#include <room.h>
inherit ROOM;
#define QUESTDIR5 "quest/雪山飛狐/寶藏/"
#define JADE    "/d/zhiye/obj/othermaterial" //玉

void create()
{
        set("short",YEL"兵器庫"NOR);
        set("long", @long
這裡應該是一個練武場或者兵器室，地上散滿了亂七八糟的兵器，十之八
九都是古劍，或長逾七尺，或短僅數寸，只是大多鐵口斑駁。
long);
        set("exits", ([
                "east" : __DIR__"tiantan",
                "south" : __DIR__"midong3",
                "west" : __DIR__"midong3",
                "north" : __DIR__"midong3",
        ]));
        set("quest", 1);
        set("baozang",1);
        setup();
}
void init()
{
        add_action("do_search", "search"); 
        add_action("do_search", "xunzhao"); 
        add_action("do_search", "dig"); 
}
int do_search(string arg)
{
	object me,obj;
  me = this_player();
	if (me->is_busy() || me->is_fighting())
		      return notify_fail("你正忙著哪！\n");
  message_vision(HIY"$N蹲在地上，四處尋找。\n"NOR, me);
  if(!wizardp(me)) me->start_busy(1);
  if(me->query(QUESTDIR5+"bingqiku")>=2||random(2))
  {
         tell_room(environment(me), me->name() + "找了半天，一不小心踩到了一坨蝙蝠糞便，摔了個仰八叉。\n", ({ me }));
       return notify_fail("你找了半天，什麼也沒找到。\n");
  }
    me->add(QUESTDIR5+"bingqiku",1);
  obj = new(JADE);
  obj->set_level(3+random(3));
        obj->move(me);
        message_vision(WHT"$N發現一塊"+obj->name()+WHT"。\n"NOR, me);
  log_file("quest/FEIHU", sprintf("%s(%s)找到兵器庫的寶物%s。經驗%d。\n", me->name(1),me->query("id"),obj->query("name"), me->query("combat_exp")) );
  me->start_busy(2);
	return 1;
}
