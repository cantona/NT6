// Room: /d/kunlun/shanbi.c
// Last Modified by winder on Jun. 29 2001

inherit ROOM;

void create()
{
        set("short", "山壁");
        set("long", @LONG
這是一片陡峭的山壁，全為極為堅硬的巖石，滑不溜腳，稍微不小
心就會滑倒。在山壁上劃有六個大字：【張無忌埋經處】。往西而下是
一片洞天，往東而下是一山溝。
LONG        );
        set("outdoors", "hongmei");
        set("exits", ([ /* sizeof() == 2 */
                "westdown" : __DIR__"cuigu",
                "eastdown" : __DIR__"shangou",
        ]));
        set("count" ,1);
        set("no_clean_up", 0);
        set("coor/x", -99000);
        set("coor/y", 20050);
        set("coor/z", 50);
        setup();
}
void init()
{
        add_action("do_dig","dig");
}
int do_dig()
{
        object book1, book2, me = this_player();
        int books=0;
        
        if (query("count") >0 )
        {
                addn("count", -1);
                book1 = new(BOOK_DIR+"medicine6");
                if (book1->violate_unique()) destruct(book1);
                else {
                        books = 1;
                  book1->move(this_object());
                }
                book2 = new(BOOK_DIR+"medicine7");
                if (book2->violate_unique()) destruct(book2);
                else {
                        books ++;
                  book2->move(this_object());
          }
                if ( books > 0 )
                {
                        message_vision("$N挖了一會，挖出了一個油布包，打開包發現......。\n",me);
            return 1;
          }
        }
        message_vision("$N挖了一會，發現好像什麼也沒有，不禁恨恨地吐了口唾沫。\n",me);
        return 1;
}