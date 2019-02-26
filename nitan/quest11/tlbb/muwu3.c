// cool 980725
// Modify By River 98/12
//COOL@SJ,9908
//tangfeng@SJ,2004

#include <ansi.h>
#include <room.h>
inherit ROOM;
#define QUESTDIR1 "quest/天龍八部/凌波微步篇/"
void create()
{
        set("short", "石屋裏");
        set("long", @LONG
這裏是石屋裏了，裏面黑漆漆的，什麼也看不清楚，陽光都被門口的一塊
大巖石擋住了，只能透過幾縷石縫中透過來的陽光，你打量着這間屋子。
LONG
        );

        set("item_desc", ([
              "yan" : "一塊大巖石，可以試着推開!。\n",
        ]));
        setup();
}

void init()
{   
       object ob,obj;
       ob=this_player();

       if (interactive(ob)
        && !present("qingnian nanzi", this_object())
        && !present("duan yu",this_object())
        && ob->query_temp(QUESTDIR1+"kill_duan")
        && ob->query(QUESTDIR1+"pass_shanlu")
        && !ob->query(QUESTDIR1+"over")){
		     obj=new(__DIR__"npc/dy");
         obj->move(this_object());
       }
       if (userp(ob)) {
	        remove_call_out("close");
          call_out("close", 2, this_object());
          }
	  add_action("do_tui", "tui");
    add_action("do_tui", "push");
}

int do_tui(string arg)
{
       int i;
        i = this_player()->query("neili");
       if( !arg || arg!="yan" ) 
         return notify_fail("你要推什麼？\n");
        message_vision(HIY"$N站在門後，把雙掌放在巖上，深深的吸了一口氣，雙臂一發勁，大喝一聲“開”。\n"NOR, this_player());
       if ( i >=800 ){
        message_vision(RED"$N只聽一陣轟響，大石緩緩的移開了！\n"NOR, this_player());
        set("exits/out", __DIR__"muwu2");
        this_player()->add("neili",-800);
        remove_call_out("close");
        call_out("close", 5, this_object());
        }
       else {
        message_vision("$N卻見大石紋絲不動，看來$N的內力還不夠。\n", this_player());
        this_player()->set("neili",0);
        }
    return 1;
}

void close(object room)
{
      message("vision",YEL"大石緩緩移動，把石屋再次封住了。\n"NOR, room);
      room->delete("exits/out");
}
