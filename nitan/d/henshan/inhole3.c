#include <ansi.h>
inherit ROOM;

void enter_furong();

void create()
{
        set("short", "水簾洞內");
        set("long", @LONG
這裏陰風瑟瑟，一片漆黑，什麼也看不見，唯有洞口處有一絲光
亮。
LONG );

        set("exits",([                
               "out"   :__DIR__"inhole1",         
        ]));        
                     
        setup();
        
}

void init()
{          
      add_action("do_use","use");        
      add_action("do_zou","zou");        
}


int do_use(string arg)
{ 
    object me;
    me = this_player();

    if (! arg) return 0;
    if (! present("fire", me)) return 0;
    if (arg == "fire" ) 
    {
      write(HIW"\n你點燃了火折，發現洞中似乎有一條路可以順着走(zou)下去。\n\n"NOR);  
      
      delete("long");
      set("long",@LONG
藉着火光你看到洞中怪石嶙峋，前方出現一條路不知通向
何處。
LONG);
              
      set_temp("marks/走1", 1, me);

      return 1;
    }
}

int do_zou(string arg)
{
       object me;
       me = this_player();

       if( query_temp("marks/走1", me) )
       {
                tell_object(me, HIR "\n你拿着火折順着路不停地走...\n\n" NOR);
                  
                call_out("enter_furong", 6);                    
  
                delete_temp("marks/走1", me);

                return 1;
       }
       else 
       {
                write("你想往哪兒走？\n");

                return 1;
       }
}

void enter_furong()
{
        object me = this_player();

        tell_object(me, HIW "這條路彎彎曲曲，你感覺走了很久，道路越來越低，像"
                            "是通往另一個山峯的。\n\n" NOR);                                

        me->move(__DIR__"furong");
}