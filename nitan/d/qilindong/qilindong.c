inherit ROOM;
#include <ansi.h> 
void create()
{
        set("short", "麒麟洞");
        set("long",
"這裡就是麒麟洞，一只火麒麟盤踞在這裡，看見有人進來，發出\n"
"一聲震天巨吼，然後便發起了攻擊。聽說它守護著雄霸留下來的寶藏。\n"
"有空的話，搜索(search)一下或許會有收獲。\n"
);
        set("exits", ([ 
              "south" : __DIR__"dong5", 
           ]));
        set("objects", ([ 
             __DIR__"npc/huoqilin" : 1,
          ]));        
        setup();
} 

void init()
{
     add_action ("do_search","search"); 
     add_action ("do_train","train");
}

int do_train(string arg)
{
    write("麒麟洞裡的都是神獸，這你也想馴服？！\n");
    return 1;
} 

int do_search (string arg)
{
    object who = this_player();   
    object tu;  
 
   
   if ( who->query("reborn_start/qilindong/tu") )
   {
         write("你已經找到過圖樣了!\n");
         return 1;
   }

   if (random(10))
   {
      message_vision ("$N四處搜索了一番，什麼也沒有找到。\n",who);
      write("看來還得再仔細找找!\n");  
      who->start_busy(2 + random(2));
   }
   else
   {
      tu = new(__DIR__"npc/obj/tu");
      message_vision ("\n突然只見$N竟從枯樹葉間找出一張"+YEL"殘破的圖樣"NOR+"！\n",who);
     
      tu->move(who);  
      who->set("reborn_start/qilindong/tu",1);
      message("vision", HIW"【轉世傳聞】：據說"+ who->query("name") +
                       "在麒麟洞內找到了一張殘破的圖樣。\n"NOR, users());
      
  }
  return 1;
}


