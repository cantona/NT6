// 該物件用于記錄A-F房間開鎖狀態和隨機分配房間參數
// 該文件常駐內存直到系統關閉

inherit ITEM;
#include <ansi.h>

public string openlock(string lock); // 外部調用開鎖函數
public void init_data(string arg); // 初始化物件數據
private string get_result(string str1, string str2);

mapping unlock = ([
// 對應房間可開啟鎖的序列

        "A" : "1345",
        "B" : "236",
        "C" : "1456", 
        "D" : "136", 
        "E" : "256", 
        "F" : "246", 
]);

void create()
{
        set_name("獨孤九劍解迷管理物件", ({ "tsr_dugu-jiujian" }) );
        set_weight(1);
        set("no_clean_up", 1);
        
        if (clonep())
                set_default_object(__FILE__);
        else
                init_data("");

        setup();
}

public void init_data(string arg)
{
         string* rn = ({ "A", "B", "C", "D", "E", "F" });
         int ran_num;
         object s;

         // 隨機分配房間參數，每次reboot後順序都不一樣
         // 初試化個房間數據，各個房間數據統一交該物件管理，便于統一
         // 增加了解迷的難度
         ran_num = random(6);
         set("number/lockroom1", rn[ran_num]);
 
         rn -= ({ rn[ran_num] });
         ran_num = random(5); 
         set("number/lockroom2", rn[ran_num]);

         rn -= ({ rn[ran_num] });
         ran_num = random(4); 
         set("number/lockroom3", rn[ran_num]);

         rn -= ({ rn[ran_num] });
         ran_num = random(3); 
         set("number/lockroom4", rn[ran_num]);

         rn -= ({ rn[ran_num] });
         ran_num = random(2); 
         set("number/lockroom5", rn[ran_num]);

         rn -= ({ rn[ran_num] });
         set("number/lockroom6", rn[0]);
            
         set("lock/unlocked", 0); // 所有鎖是否解開
         set("lock/opened", ""); // 已經打開的鎖序列
  
         if (arg == "enter")
         {
                 if (! s = find_object("/d/huashan/s"))
                           s = load_object("/d/huashan/s");

                 tell_room(s, HIG "只聽得轟隆隆幾聲，石門升起將山洞封住了。\n" NOR);
                 delete("exits/enter", s);
         }

         return;

}

// 外部調用此函數傳遞參數lock為: "A"-"F"    
public string openlock(string lock)
{       
        string opened, str_want_open;
        mixed result;
        int i;
        object s;

        if (! stringp(query("lock/opened")) ||
            query("lock/opened") == "")
        {
              
              set("lock/opened", unlock[lock]);
              return unlock[lock];
        }
        str_want_open = unlock[lock];
        opened = query("lock/opened");
        
        if (! stringp(opened))
              return "erros: opened is not a string.\n";
 
        result = get_result(opened, str_want_open);
        //if (sizeof(result) == 6 && result == "413256")
        if (sizeof(result) == 6)
        { 
             set("lock/unlocked", 1);
             set("lock/opened", result);
             if (! s = find_object("/d/huashan/s"))
                       s = load_object("/d/huashan/s");

             set("exits/enter", __DIR__"x", s);

             tell_room(s, HIG "只聽得轟隆隆幾聲，石門已陷入地下，露出了山洞的入口。\n" NOR);
             call_out("init_data", 180 + random(10), "enter"); // 二分鐘後重新初始化所有數據
             return "UNLOCKED";
        }
        set("lock/opened", result);

        remove_call_out("init_data");

        return query("lock/opened");

}

private string get_result(string str1, string str2)
{
        int n1, n2;
        string temp;

        if (! strcmp(str1, str2))return "";

        temp = "";        

        for (n1 = 0; n1 < sizeof(str1); n1 ++)
        {
                for (n2 = 0; n2 < sizeof(str2); n2++)
                {
                      if (str2[n2..n2] == str1[n1..n1])
                      {
                              temp += str2[n2..n2];
                      }
                }
       }
       if (temp == "")return str1 + str2;

       for (n1 = 0; n1 < sizeof(temp); n1 ++)
       {
                str1 = replace_string(str1, temp[n1..n1], "");
                str2 = replace_string(str2, temp[n1..n1], "");
       }
       return str1 + str2;
}
