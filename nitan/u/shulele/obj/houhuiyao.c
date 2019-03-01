//後悔藥                                               
                                                                                            
inherit ITEM; 
#include <ansi.h>                                                                              
                                                                                            
int do_eat(string);                                                                         
void init();                                                                                
                                                                                            
void init()                                                                                 
{                                                                                           
  if (!wizardp(this_player())) {                                                            
    set("no_get","你手裡一鬆，後悔藥從指間滑落！\n");                                       
    set("no_give","這麼珍貴的藥，哪能隨便給人？\n");                                        
    set("no_drop","這麼寶貴的藥，扔了多可惜呀！\n");                                        
    set("no_sell","凡人哪裡知道"+this_object()->query("name")+"的價值？還是自己留著吧。\n");
  }                                                                                         
  add_action("do_eat", "eat");                                                              
}                                                                                           
                                                                                            
void create()                                                                               
{                                                                                           
  set_name( HIM "後悔藥" NOR , ({"houhui yao", "yao"}));                                    
  set_weight(90);                                                                           
  if (clonep())                                                                             
    set_default_object(__FILE__);                                                           
  else {                                                                                    
    set("unit", "包");                                                                      
    set("long", "一包顏色怪怪的藥，味道一定不怎麼樣。\n");                                  
    set("value", 0);                                                                        
    set("drug_type", "補品");                                                               
  }                                                                                         
  set("is_monitored",1);                                                                    
  setup();                                                                                  
}                                                                                           
                                                                                            
int do_eat(string arg)                                                                      
{                                                                                           
  object me = this_player();                                                                
  if (arg!="yao" && arg!="houhui yao")   return 0;                                          
                                                                                            
  me->set("eff_sen", (int)me->query("max_sen"));                                            
  me->set("sen", (int)me->query("max_sen"));                                                
  me->set("eff_gin", (int)me->query("max_gin"));                                            
  me->set("gin", (int)me->query("max_gin"));                                                
  me->set("eff_kee", (int)me->query("max_kee"));                                            
   me->delete("mieyao_mudage"); 
   me->delete("secmieyao_mudage");                                                            
   me->delete("bad_mudage");                                                                
  me->set("kee", (int)me->query("max_kee"));                                                
  me->set("mana", (int)me->query("max_mana"));                                              
  me->set("force", (int)me->query("max_force"));                                            
   message_vision(HIM "$N把後悔藥往嘴裡一放，苦的眼淚鼻涕一起流了下來。                     
\n" NOR, me);                                                                               
  destruct(this_object());                                                                  
  return 1;                                                                                 
}                                                                                           