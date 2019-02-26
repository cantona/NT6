inherit COMBINED_ITEM;
#include <ansi.h>                                                                                                                                     
string query_autoload()
{                                     
        return query_amount() + "";
}
                                                                                         
void create()                                                                            
{                                                                                        
        set_name(HIY "陰虛丹" NOR, ({ "yinxu dan" }));              
        if (clonep())                                                                    
                set_default_object(__FILE__);                                            
        else {                                                                           
                set("long", YEL "此丹吃下後可以消除一次臂力類吃丹失敗記錄。\n" NOR);   
                set("base_unit", "顆");                                       
                set("base_value", 400000);                                               
                set("base_weight", 50);                                                  
                set("only_do_effect", 1);                                                                                                                                       
                set("gift_msg", HIM "突然間你覺得自己身上好像少了點什麼。\n" NOR);
        }                                                                                
        setup();                                                                         
}               

int do_effect(object me)
{
                                                               
        message_vision(WHT "$N" WHT "一仰脖，吞下了一" +                                                                      
                       query("base_unit") + name() + WHT
                       "。\n" NOR, me);    
                       
        if( query("gift/clearcount", me) >= 3 )
        {                                                           
                tell_object(me, "你覺得這藥好像沒什麼效果。\n");
        }
        else
        {                                                           
                if( query("gift/str/fail", me) )
                {
                       addn("gift/str/fail", -1, me);
                       addn("gift/str/all", -1, me);
                       addn("gift/clearcount", 1, me);
                       tell_object(me, query("gift_msg"));
                       tell_object(me, HIC "OK.\n" NOR);
                }
                else 
                {
                        tell_object(me, HIC "你覺得這藥好像沒什麼效果。\n" NOR);
                }
                
        }             
        add_amount(-1);                    
        if (query_amount() < 1)
                destruct(this_object());
        
        return 1;
}

void autoload(string param)
{                                                                         
        int amt;

        if (sscanf(param, "%d", amt) == 1)    
                set_amount(amt);
}                                             
                                              
void setup()
{                                             
        set_amount(1);
        ::setup();
}
                               
                               