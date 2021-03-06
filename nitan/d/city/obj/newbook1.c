// Copyright (C) 2003, by Lonely. All rights reserved.
// This software can not be used, copied, or modified 
// in any form without the written permission from authors.

#include <ansi.h>
inherit ITEM;


int start_book_title(object me);
void get_book_title(string book_title, object ob);
int start_book_text(object me, int p_no);
void get_book_text(string str, int p_no);
int help(object me);

mapping new_book = ([]);
mapping text = ([]);
// text = allocate( string 20 );

void create()
{
        set_name("紙稿", ({"book"}));
        set_weight(10);
        set_weight(1);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", "一本空白的書，你可以在上面寫字。(write)\n");
                set("unit", "本");
                set("material", "paper");
                set("value", 100000);
        }
}
int init()
{
        add_action("do_title","title");
        add_action("do_write", "write");
        add_action("do_read", "read");   
}

int do_title(string arg)
{
          object me;
          object this_book;

          me = this_player();
                  this_book = this_object();

          if (arg != "book") 
              return  notify_fail("你要寫什麼？\n");

          if( !query("titled", this_book) )
                   {
              start_book_title(me);
                  }
                  else {
              message_vision("$N左想右想，又決定要把書名改一改。\n"NOR,me);
                          start_book_title(me);
                  }

                  return 1;

}

int start_book_title(object me)
{
    tell_object(me,"【書名】:");
    input_to( (: get_book_title :), me );
        return 1;
}

void get_book_title(string book_title, object ob)
{
        object me, this_book;

        me=ob;
                this_book = this_object();

        if( !book_title || (strlen(book_title)<2) ) {
              write("請先寫書名。\n");
              tell_object(this_player(),"【書名】:");
              input_to( (: get_book_title :),  me);
              return;
        }

        message_vision("$N想了半天，終於在封皮上題了一個書名。\n"NOR,me);

                new_book["title"] = book_title;
        new_book["arthur"]=me->name(1)+"("+query("id", me)+")";
        new_book["arthur_id"]=query("id", me);
 
        set("titled", 1, this_book);
        this_book->set_name(book_title, ({"book"}));
                set("long", "一本未寫完的書，你可以在上面接着寫。(writebook)\n", this_book);
        set("book_content", new_book, this_book);

        return;        
}

int do_write(string arg)
{
          string msg;
          object me;
          object this_book;
                  int page_no;

          me = this_player();
                  this_book = this_object();

              if( !arg || sscanf(arg, "%s %d", msg, page_no)!=2 ) return help(me);

          if (msg != "page") 
              return  notify_fail("寫書用 (write page #) 。\n");
                  if (page_no > 20 || page_no < 1) 
              return  notify_fail("寫書在 1 到 20 頁之間。\n");
          if( !query("titled", this_book) )
                      return  notify_fail("你還沒有給書題名呢，先想個書名再説把 (title book)。\n");
                  else 
                  {
              message_vision("$N拿出一支筆，鋪開書本，開始寫作.....\n"NOR,me);
                          start_book_text(me, page_no);
                  }
          return 1;

}


int start_book_text(object me, int p_no)
{
        write("【書本內容】:\n");
        me->edit( (: get_book_text, p_no :) );
        return 1;
}

void get_book_text(int p_no, string str)
{

        message_vision("$N寫完一段，放下手中的筆。\n"NOR,this_player());
                   text[p_no] = str;
        new_book["text"] = text;


        set("book_content", new_book, this_object());
        set("text_written", 1, this_object());
        set("publishable", 1, this_object());
        return;
        
}

int do_read(string arg)
{
        string msg, this_page;
                int page_no;
                object me, this_book;

        me = this_player();
                this_book = this_object();

        if( !arg || sscanf(arg, "%s %d", msg, page_no)!=2 ) return help(me);

        if (msg != "page") 
             return  notify_fail("讀書用 (read page #) 。\n");
            if (page_no > 20) 
              return  notify_fail("書不超過 20 頁。\n");

        if( !query("text_written", this_book) )
             return  notify_fail("這本書還沒寫，怎麼讀？\n");

        if(!(this_page = new_book["text"][page_no]))
             return  notify_fail("這一頁還沒寫，怎麼讀？\n");;

        printf("【%s】：\n【作者】：%s\n\n",
                new_book["title"],new_book["arthur"]);
                this_player()->start_more(this_page);

        
        return 1;
}

int help(object me)
{
        write("指令格式：\n
        寫書用 (write page #) 。\n
        讀書用 (read page #) 。\n");
        return 1;
}