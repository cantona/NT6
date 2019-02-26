inherit ROOM; 
#include <ansi.h> 
void create ()
{
  set ("short", "休息室");
  set ("long", HIG @LONG
這裏看上去象是一間休息室，屋子中央擺着幾張桌子，上面有
一些小菜，屋角有一個櫃子(closet)，從裏面傳出撲鼻的香氣，令
人垂涎。靠窗有取暖裝置，屋裏温暖如春。
LONG);

  set("item_desc", ([
     "closet" : "一個竹製的櫃子，裏面放着煙(cigarette)，酒(wine)和糖果(sugar)，可以拿(take)出來吃哦。\n",
   ]));
  set("exits", ([
        "north"    : __DIR__"spirit5",
        "east"    : __DIR__"spirit4",
        "west"    : __DIR__"liechang",
      ])); 
  set("objects", ([ 
      ]));
        set("no_fight", 1);
        set("sleep_room",1);

  set("no_magic", 1);
        setup();
}

void init()
{
        add_action("do_take", "take");
}

int do_take(string arg)
{
        object me=this_player();
        object ob;
        if(!arg) return notify_fail("你要拿什麼？\n"); 
        if(arg=="wine"){
       ob = new ("/quest/tulong/obj/wine");   
       ob->move(me); 
  message_vision ("$N從櫃子拿出$n。\n",me,ob);   
        return 1;
        }
        if(arg=="sugar"){
       ob = new ("/quest/tulong/obj/sugar");   
       ob->move(me); 
  message_vision ("$N從櫃子拿出$n。\n",me,ob);   
        return 1;
        }
        if(arg=="cigarette"){
       ob = new ("/quest/tulong/obj/cigarette");   
       ob->move(me); 
  message_vision ("$N從櫃子拿出$n。\n",me,ob);   
        return 1;
        }
        else
        write("那裏面沒有這樣東西！\n");
        return 1;  
}
int valid_leave()
{
        if((present("wine", this_player())))
            return notify_fail("請不要帶走這裏的東西。\n"); 
        if((present("sugar", this_player())))
            return notify_fail("請不要帶走這裏的東西。\n"); 
        if((present("cigarette", this_player())))
            return notify_fail("請不要帶走這裏的東西。\n"); 
        if((present("budai", this_player())))
            return notify_fail("請放下布袋，這裏的東西不能帶出去，謝謝。\n");

    return ::valid_leave();
}
