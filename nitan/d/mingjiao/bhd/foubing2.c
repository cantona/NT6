// foubing2.c 冰山
// Modify By River@SJ 99.06
#include <ansi.h>
inherit ROOM;
void create()
{
	set("short",HIW"冰山"NOR);
        set("long", @LONG
這是一塊很大浮動冰山，是由萬年玄冰組成。由于前面的冰山受
到火山之熱，不斷的熔化，這時反而隨著冰山熔化成暖水一沖又向南
飄，這時你看到不遠之處有一塊小基塊(bing)，可能可以當船用，向
島劃動。
LONG );
        set("no_fight", 1);
        set("no_get_from", 1); 
        set("no_sleep_room", 1); 
        set("outdoors","極北");
	setup();
}

void init()
{
    if(interactive(this_player())){
         remove_call_out("run");
         call_out("run", 20+random(30));
    }
    add_action("do_jump","jump");
}

int do_jump(string arg)
{
	object me=this_player();
	if (!arg) return 0;
	if (arg=="bing" || arg== "小冰塊"){
            message("vision", me->name() + "張手抱向小冰塊， 撲通一聲跳入海中。\n",environment(me), ({me}) );
       	    me->move(__DIR__"xbkai");
            message("vision", me->name() + "狼狼狽狽的跳了過來，雙手抱向小冰塊。\n",environment(me), ({me}) );
            return 1;
        }
        return 0;
}

void run()
{
     object *obj;
     int i;
     obj = all_inventory(this_object());
     for(i=0; i<sizeof(obj); i++){ 
        tell_object(obj[i],HIW"\n冰山隨著海水暖流向南飄離。\n\n"NOR);
       	obj[i]->move(__DIR__"dbshan");
     }
}
