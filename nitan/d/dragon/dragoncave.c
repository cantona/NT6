inherit ROOM;
#include <ansi.h> 
void create()
{
        set("short", "龍潭");
        set("long",
"[1;31m這裡就是龍潭，一只巨龍盤踞在這裡，看見有人進來，發出\n"
"一聲震天巨吼，然後便發起了攻擊。聽說它守護著精靈王留下來的寶藏。\n"
"有空的話，搜索(search)一下或許會有收獲。\n"
);
        set("exits", ([ 
              // "south" : __DIR__"spirit6", 
           ]));
        set("objects", ([ 
             "/quest/tulong/npc/dragon" : 1,
          ]));
        set("book_count", 7);

        set("no_magic", 1);
        setup();
} 

void init()
{
  add_action ("do_search","search"); 
  add_action ("do_quit","train");}

int do_quit(string arg){
        write(query("name", this_player())+"，龍也是可以馴的麼？！\n");
        return 1;
} 
int do_search (string arg)
{
  object who = this_player ();
  object where = this_object ();
  object book;

 if (query("book_count") < 1) 
  {
    message_vision ("$N四處搜索了一番，什麼也沒有找到。\n",who);  
    message_vision ("也許是被拿光了。\n",who);  
    return 1;
  }
        if (  present("night's diary", who) ) {
                return notify_fail("你都有這本書了，還要找什麼。\n");
          }
 if( query_temp("mark/diary", who) )
   {
    message_vision ("$N四處搜索了一番，什麼也沒有找到。\n",who);  
    message_vision ("看樣子是不能多拿的。\n",who);  
    return 1;
  }

  if (random(10))
  {
    message_vision ("$N四處搜索了一番，什麼也沒有找到。\n",who);  
  }
  else
  {
    book = new ("/quest/tulong/obj/diary");
    message_vision ("$N竟從枯樹葉間找出一本"+YEL"夜辰日記"NOR+"！\n",who,book);
     set_temp("mark/diary", 1, who);
    book->move(who);  
message("channel:rumor",HIR"【精靈神界】某人："+query("name", this_player())+"找到夜辰日記啦。\n"NOR,users());
   addn("book_count", -1);
  }
  return 1;
}

void reset()
{
        ::reset();
        delete("exits/north");
}