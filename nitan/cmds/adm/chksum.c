 // chksum.c
 // By Plzw 
 // 2004-5-25 
  
#include <ansi.h>  
#include <command.h>  
  
inherit F_CLEAN_UP;  
  
int main(object me, string str)  
{ 
        object ob;  
        string file;  
        mapping ol; 
        string item; 
        string *items; 
        string nitem; 
        string msg; 

        if (! SECURITY_D->valid_grant(me, "(admin)")) 
                return 0;
        
        if (! str)   
                ob = me;   
        else   
        {   
                ob = present(str, environment(me));   
                if (! ob) ob = find_player(str);   
                if (! ob) ob = find_living(str);   
                if (! ob) return notify_fail("你要查看誰的召喚列表？\n");   
        }  
        
        // 獲取可召喚物品列表 
        
        if( !mapp(ol=query("can_summon", ob)) || sizeof(ol)<1 )
                return notify_fail("你現在還沒有可以召喚的物品。\n"); 
 
        msg=query("name", ob)+"("+query("id", ob)+")可以召喚的物品有：\n\n";
        items = keys(ol); 
        foreach (item in items) 
        { 
                file = (string) ol[item]; 
                if (file_size(file + ".c") < 0 && file_size(file) < 0) 
                        nitem = HIR"<不存在的武器ID，請與巫師聯系>"NOR; 
                else 
                { 
                        call_other(file, "???"); 
                        if (objectp(ob = find_object(file))) 
                                nitem = ob->name(); 
                } 
                msg += sprintf(WHT "%-14s  %-14s\n", item, nitem); 
        } 
        write(msg); 
        return 1; 
}