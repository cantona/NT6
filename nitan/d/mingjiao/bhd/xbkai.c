// xbkai.c 冰山
// Modify By River@SJ 99.06
#include <ansi.h>
inherit ROOM;
void create()
{
	set("short", HIW"小冰塊"NOR);
        set("long", @LONG
這是一塊小浮基，能用手劃(hua)動它，不遠之處就是一塊巖石(
yanshi)，從那裡可以登上陸地。
LONG );
        set("no_fight", 1);
        set("no_get_from", 1); 
        set("no_sleep_room", 1); 
	set("outdoors","極北");
	setup();
}

void init()
{
        object me, ob, *obj;
        int i;
        me = this_player();
        ob = this_object();
        obj = all_inventory(ob);
        if(!this_player()->query_condition("cold_wind") && !wizardp(me))
        this_player()->apply_condition("cold_wind", 1);
        for(i= 0;i< sizeof(obj);i++){
             if(obj[i]==me ) continue;
             if(obj[i]->is_character()){
                 message_vision(HIR"只見小冰塊猛得一震，沉下海去！\n"NOR, ob);
                 obj[i]->unconcious();
                 obj[i]->move(__DIR__"dbshan");
                 me->unconcious();
                 me->move(__DIR__"dbshan");
                 message("vision", "一個昏迷不醒的人被海水沖了上來。\n",environment(me), ({me}) );
             }
        }
        delete("hua_trigger");
	add_action("do_pa","pa");
	add_action("do_hua","hua");
}

int do_hua()
{
      object ob=this_player();
      if(ob->is_busy()) return notify_fail("你正忙著呢。\n");
      if(ob->query_temp("marks/劃1")) return notify_fail("你已經劃到巖石邊了。\n");
      message_vision("$N手腳劃動，吃力的向北邊的巖石劃去。\n",ob);
      ob->start_busy(1);      
      if((int)query("hua_trigger")>=7){
            message_vision("浮冰終于被$N劃到達巖石的旁邊。\n", ob);
	    delete("hua_trigger");
	    ob->set_temp("marks/劃1",1);
            }
      else add("hua_trigger", 1);
      return 1;
}

int do_pa(string arg)
{
	object ob;
	ob=this_player();	
	if (!ob->query_temp("marks/劃1"))
		return notify_fail("你現在離巖石還很遠呢。\n");
        if (!arg  || arg !="yanshi")
		return notify_fail("你要爬到那裡？\n");
	message("vision", ob->name() + "堅難的爬上了巖石。\n", environment(ob), ({ob}));
        ob->move(__DIR__"yanshi");
        message("vision", ob->name() + "從浮冰上爬了上來，渾身上水。\n",environment(ob), ({ob}) );
        EMOTE_D->do_emote(ob,"cold", ob->query("id"));
        EMOTE_D->do_emote(ob,"cold");
        ob->delete_temp("marks/劃1");
        ob->start_busy(2);
        return 1;
}
