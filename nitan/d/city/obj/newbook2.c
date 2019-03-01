// Modified by Lonely Nitan@Mud
#include <ansi.h>
inherit ITEM;

int help(object me);

void create()
{
        set_name("空白的書", ({"book"}));
        set_weight(10);
        set_weight(1);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", "一本已經寫好的書，你可用讀(read)來看它的內容。\n");
                set("unit", "本");
                set("material", "paper");
                set("value", 2000);
                set("no_sell", 1);
        }
}

int init()
{
    add_action("do_read", "read");   
}

int do_read(string arg)
{
        string msg, this_page;
                int page_no;
                object me, this_book;
        mapping new_book;

        me = this_player();
                this_book = this_object();

        if( !arg || sscanf(arg, "%s %d", msg, page_no)!=2 ) return help(me);

        if (msg != "page") 
             return  notify_fail("讀書用 (read page #) 。\n");
            if (page_no > 20 || page_no < 1) 
              return  notify_fail("書在 1 到 20 頁之間。\n");

                new_book=query("new_book", this_book);

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
        讀書用 (read page #) 。\n");
        return 1;
}