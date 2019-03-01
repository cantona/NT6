// foubing1.c 冰山
// Modify By River@SJ 99.06
#include <ansi.h>
inherit ROOM;
void create()
{
	set("short",HIW"冰山"NOR);
        set("long", @LONG
這是一塊很大浮動冰山，是由萬年玄冰組成。由于前面的冰山受
到火山之熱，不斷的熔化，而產生吸力，把許多浮基不斷的吸進，所
以冰山是不斷的靠近火山。
LONG );
        set("no_fight", 1);
        set("no_get_from", 1); 
        set("no_sleep_room", 1); 
	set("outdoors","極北");
	setup();
}

void run(object ob)
{
       if(objectp(present(ob, this_object()))){
  	  write(HIW"\n冰山緩緩的向北飄去。\n\n"NOR);
       	  ob->move(__DIR__"foubing2");
       }
}

void init()
{
    if(interactive(this_player())){
          remove_call_out("run");
          call_out("run", 20+random(30), this_player());
    }
}
