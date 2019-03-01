// weapon: /d/zhongnan/obj/yaochu.c 
// sdong 08/06/98 
        
#include <weapon.h> 
        
inherit HAMMER; 
        
void create() 
{ 
        set_name("藥鋤", ({ "yao chu", "chu" }) ); 
        set_weight(1000); 
        if( clonep() ) 
                set_default_object(__FILE__); 
        else { 
                set("unit", "把"); 
                set("long", sort_msg("這是一把全真教道長們用來專門採藥用的藥鋤。經過了多人的"
                        "使用雖然鋤身已經鏽跡斑斑了，但是鋤口還是那樣的鋒利。稍不小心就有可"
                        "能把藥草挖斷。你可以在來全真路上的樹林中來採集所需要的藥材。\n"));            
                set("value", 50); 
                set("material", "iron"); 
                set("wield_msg", "$N拿出一把$n，握在手中。\n"); 
                set("unwield_msg", "$N放下手中的$n。\n"); 
        } 
       
        init_hammer(5); 
        setup(); 
}        

void init() 
{ 
        object me = this_player(); 
        if( query("id", me) != "qiu chuji" && !wizardp(me) )
        { 
                set("no_drop",  "這麼有用的東西怎麼能扔了呢。\n"); 
                set("no_steal", "這個東西你偷不到。\n"); 
                set("no_get", "這個東西你不能拿。\n"); 
        } 
} 

