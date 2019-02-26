// counter.c
//wsw於2004年2月20日
//玩家櫃枱
//玩家有此櫃枱後，可把物品擺在櫃枱上出售，重啟後保留。
//如果是隨機屬性物品，物品->set("changed",1)

#include "counter.h"   

void create()
{        
        seteuid(0);
        set_name(HIC"櫃枱"NOR,({"counter" }) );   
        set_weight(50000);   
        if( clonep() )   
                set_default_object(__FILE__); 
        else {   
        set("value", 2000000);   
   
                set("unit","個");   
                set("capacity",10);  //容量 
                set("no_put",1);   
                set("no_sell",1);   
                set("no_get",1);   
                set("no_give",1);   
                set("no_drop",1);   
                set("long",HIB"玩家之城的櫃枱。\n"NOR);   
        }   
        setup();     
}   
