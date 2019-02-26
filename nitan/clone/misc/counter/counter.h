// counter.h
//wsw於2004年2月20日
//玩家櫃枱
//玩家有此櫃枱後，可把物品擺在櫃枱上出售，重啟後保留。
//如果是隨機屬性物品，物品->set("changed",1)

#include <ansi.h>   
inherit F_SAVE;   
inherit ITEM;

void init () ;
void setup();
string query_save_file();
int save();
int do_sell(string arg);
int do_buy(string arg) ;
int do_look(string arg);
int do_qu(string arg);
object get_item(object ob,int place);
  
void init ()   
{   
  add_action ("do_sell","sell");   
  add_action ("do_buy","buy"); 
  add_action ("do_look","look"); 
  add_action ("do_qu","qu"); 

}

void setup()
{
        ::setup();
        restore();
}   
string query_save_file()  
{  
   string id;  

   id=file_name(this_object());
   id = id[strsrch(id,"/",-1)+1..strsrch(id,"#",1)-1] ;
   if( !id ) return 0;  
   return sprintf("/data/playercity/obj/counter/%s", id);  
}  
  
int save()  
{  
   return ::save();  
}  

int do_sell(string arg)  
{  
        object obj,newobj;  
        object me= this_player();  
        object ob= this_object();  
        string thing,str;  
        int place,price,j;  

        if(!arg)  
                return notify_fail("你準備賣什麼東西？<指令>:sell <物品ID> at <位置號> for <單價>\n");  

        if(ob->query("owner_id")!=me->query("id")) 
                return notify_fail("這不是你的櫃枱。\n");

        if(me->is_busy()) 
                return notify_fail("你正忙着呢！\n");  

        if (sscanf(arg,"%s at %d for %d",thing,place,price)!=3)     
                return notify_fail("你要把什麼物品放在櫃枱的哪個位置？<指令>:sell <物品ID> at <位置號> for <單價>\n");    
              
        if (price<=0) return notify_fail("象你這樣的好心人，現在不多了！\n");

        if (!( obj=present (thing,me)))   
                return notify_fail("你身上沒有這個物品。\n");   

        if (obj->is_character()
             || obj->query_max_encumbrance()  
            || obj->query("liquid")  
                || obj->query_unique())  
                return notify_fail("這樣東西可不能賣。\n");  
                
        if (obj->query("equipped")) 
                return notify_fail("你先脱下來吧。\n");  

        if (place <1 || place >ob->query("capacity"))  
                return notify_fail("這個櫃枱只能擺"+ob->query("capacity")+"件物品。\n");  

        if (ob->query("place_"+place+"/have")=="have")  
                return notify_fail("櫃枱第"+place+"個位置已經有物品了。\n");  

        ob->set("place_"+place+"/have","have");
        ob->set("place_"+place+"/file_name",base_name(obj));
        if (obj->query_amount()) ob->set("place_"+place+"/amount",obj->query_amount());
        else ob->set("place_"+place+"/amount",1);
        ob->set("place_"+place+"/price",price);
        ob->set("place_"+place+"/attribute",obj->query_entire_dbase());

        ob->save();  
        message_vision("$N把一"+obj->query("unit")+obj->name()+NOR+"擺進櫃枱。\n",me);
        obj->move(VOID_OB);  
        destruct(obj);  
        me->start_busy(2); 
        return 1;
}     
 
int do_buy(string arg)  
{ 
        object newobj;  
        object me= this_player();  
        object ob= this_object(); 
        mapping attribute;  
        int place,afford,price;  
        if(!arg)  
                return notify_fail("你要買什麼？<指令>:buy <序號> from counter\n");  

        if(me->is_busy()) 
                return notify_fail("你正忙着呢！n");    

        if (sscanf(arg,"%d from counter",place)!=1)     
                return notify_fail("你要買什麼位置的物品？<指令>:na xxx from bag\n"); 

        if (place <1 || place >ob->query("capacity"))  
                return notify_fail("櫃枱只有"+ob->query("capacity")+"個空間。\n");  

        if (ob->query("place_"+place+"/have")!="have")  
                return notify_fail("櫃枱第"+place+"個空間是空的。\n");  
         
       price=ob->query("place_"+place+"/price");
       if (me->query("stocks/balance") < price && ob->query("owner_id") != me->query("id")) 
                return notify_fail("你的YSG不夠。\n");
       newobj=get_item(ob,place);
       if(newobj && newobj->move(me)) 
       {             
          if(ob->query("owner_id") != me->query("id")) {
                  me->add("stocks/balance",-1*price);
                  ob->add("payment",price);
          }
          ob->add("place_"+place+"/amount",-1);
          if (ob->query("place_"+place+"/amount")<=0)
              ob->delete("place_"+place);
                  if(ob->query("owner_id") != me->query("id"))
                  message_vision("$N買下了一"+newobj->query("unit")+newobj->name()+NOR+"。\n",me); 
          else message_vision("$N從櫃枱上撤下了一"+newobj->query("unit")+newobj->name()+NOR+"。\n",me); 
          ob->save();
          me->save();
          me->start_busy(2);
                 return 1;
        }else{
                destruct(newobj);
                return notify_fail("買物品失敗。\n");
        }
}

int do_look(string arg)
{
    string str;
    object obj,ob;
    int place,j;
    
    ob=this_object();
    
    if (!arg) return 0;
    if (arg == "counter") {
            str=HIB"玩家之城的櫃枱。\n"NOR;
            str+="查看物品詳細資料：look <序號> in counter 。\n";
            str+="擺上物品準備出售：sell <物品ID> at <序號> for <單價>\n";
            str+="賣下櫃枱裏的物品：buy <序號> from counter\n";
            str+="取出櫃枱裏的貨款：qu <數量> from counter\n";
            str+="┌——————————————————————————————————————┐\n";
            str+=   "│序號   物品名稱     ID                 數量        單價\n";  
            str+="├——————————————————————————————————————┤\n";
            for (j = 1; j<ob->query("capacity")+1; j++) { 
            if (ob->query("place_"+j+"/have")=="have")
                    str+=sprintf("│%2d：%16' 's\t%16' 's\t%d\t%d\t\t\t│\n",j,ob->query("place_"+j+"/attribute/name"),
                    ob->query("place_"+j+"/attribute/id"),ob->query("place_"+j+"/amount"),
                    ob->query("place_"+j+"/price"));
            else  str+=sprintf("│%2d： <空>\t\t\t\t\t\t\t\t│\n",j);
       }
        str+="└——————————————————————————————————————┘\n";  
        str+="當前貨款："+ob->query("payment")+"。\n"; 
        write(str);
        return 1;
    }
    
    if (sscanf(arg,"%d in %s",place,str)==2) {
            if (str!="counter") return 0;
            if (ob->query("place_"+place+"/have")=="have") {
                    obj=get_item(ob,place);
                    if (objectp(obj)) {
                            if (obj->query("changed")) 
                                    "/cmds/std/ll.c"->look_item(0,obj);
                            else "cmds/std/look.c"->look_item(this_player(),obj);
                            destruct(obj);
                            return 1;
                    }
            }else write("這個位置是空的。\n");
            return 1;        
    } 
    return 0;
}

int do_qu(string arg)  
{  
        object obj,newobj;  
        object me= this_player();  
        object ob= this_object();  
        string thing,str;  
        int place,price,j; 
         
        if(ob->query("owner_id")!=me->query("id")) 
                return notify_fail("你想當小偷？？\n");        
        if(!arg)  
                return notify_fail("你要取多少錢？<指令>:qu <數量> from counter\n");  
        if(me->is_busy()) 
                return notify_fail("你正忙着呢！\n");  
        if (sscanf(arg,"%d from counter",price)!=1)     
                return notify_fail("你要取多少錢？<指令>:qu <數量> from counter\n");
                  
        if (price <= 0) return notify_fail("你想幹嘛呢？\n");

        if (ob->query("payment") < price) return notify_fail("櫃枱裏沒有這麼多貨款。\n");

        ob->add("payment",-1 * price);
        me->add("stocks/balance", price);
        me->start_busy(2);
        message_vision("$N從櫃枱上取出"+ price +" YSG的貨款並存入了股市。\n",me); 
        
        ob->save();
        me->save();
        return 1;
        
}

object get_item(object ob,int place)
{
    object obj;
    mapping attribute;
    string *key;
    int j;
    
    obj=new(ob->query("place_"+place+"/file_name"));  
    if(!obj)  return 0; 
    attribute=ob->query("place_"+place+"/attribute");
    if (mapp(attribute)) {
             key=keys(attribute);
               key = sort_array(key, 0);
            for(j=0; j<sizeof(key); j++) {
                obj->set(key[j], attribute[key[j]]); 
            }                
    }
    return obj;        
        
}
