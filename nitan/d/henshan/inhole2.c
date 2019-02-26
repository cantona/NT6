#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", "水簾洞內");
        set("long", @LONG
這裏陰風瑟瑟，一片漆黑，什麼也看不見。唯有洞外有一絲光亮。
LONG );

        set("exits",([                
               "out"   :__DIR__"inhole1",              
        ]));        
                     
       setup();
}

void init()
{
        add_action("do_use","use");
}

int do_use(string arg)
{
    object me,ob;
    me = this_player();

    if (! ob = find_object(__DIR__"inhole2"))
                ob=load_object(__DIR__"inhole2");        

    if (! arg || arg != "fire" ) return 0;
    if (! present("fire", me)) return 0;
   
        write(HIG"\n你點燃了火折，發現這裏有出口。\n\n"); 
        set_temp("marks/走1", 1, me);

        delete("long");
        set("long",@LONG
藉着火光你發現這裏有一些出口，但不知道通往何處。
LONG);  
            
        set("exits/west"  ,__DIR__"zigai1");
        set("exits/north" ,__DIR__"zigai2");
                         
        return 1;
}

void reset()

{
         ::reset();

         delete("exits/west");
         delete("exits/north");

}