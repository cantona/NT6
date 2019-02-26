//ROOM: /d/yanziwu/huanshi.c

inherit ROOM;
#include <ansi.h>

// 演練參合指必須的三種少林指法
#define BOOK1 "/clone/lonely/book/tianzhuzhi"
#define BOOK2 "/clone/lonely/book/duoluoyezhi"
#define BOOK3 "/clone/lonely/book/xiuluozhi"

string* books = ({ BOOK1, BOOK2, BOOK3 });

int can_creat_book = 0, ran;

void create()
{
        set("short", "還施水閣");
        set("long", @LONG
閣中滿是書架(jia)， 架上擺着許多頗古舊的書籍，架上均貼有
標籤(sign)。這就是慕容世家歷經數代才收集積累而成的武學寶庫。
LONG );
        set("exits", ([
            "out": __DIR__"lanyue",
        ]));
        set("objects", ([
            "/clone/book/book-bamboo": random(2),
            "/clone/book/book-iron": random(2),
            "/clone/book/book-paper": random(2),
            "/clone/book/book-silk": random(2),
            "/clone/book/book-stone": random(2),
        ]));
        
        set("item_desc",([
            "sign" : HIR "缺大理段氏六脈神劍，丐幫降龍十八掌、打狗棍法…\n" NOR,
              "jia"  : HIC "上面放着各種武學書籍，卻發現沒什麼有價值的祕籍。\n" NOR,
        ]));
        
        // 每次更新時隨機選出一種可以產生的祕籍，並等待判斷 ...
        ran = random(sizeof(books));

        // 每次更新有1/5的機率可以隨機產生出一種祕籍，
        // 則產生特定祕籍的機率為1/15，並等待判斷 ...
        if (random(5) == 0)can_creat_book = 1;

        setup();

}

void init()
{
        add_action("do_move", "move");      
}

int do_move(string arg)
{       
        object me, book, here;

        me = this_player();
        
        if (! arg || arg != "jia")
                 return notify_fail("你要幹什麼？\n");
     
        if (! book = find_object(books[ran]))
                  book = load_object(books[ran]);

        if (! here = find_object(__FILE__))
                  here = load_object(__FILE__);

        // 更新前已有人取得過祕籍，只有更新後才可能第二次產生祕籍
        if( query("marks/move", here) || !can_creat_book )
                  return notify_fail(HIC "你輕輕地將書架推了開，但什麼也沒發現。\n" NOR);

        message_vision(HIC "$N" HIC "輕輕地將書架推了開…\n" NOR, me);

        if (! environment(book))
        {     
                  tell_object(me, HIY "啪~~地一聲，一本書掉在了地上，你趕緊將它收了"
                              "起來。\n" NOR);
     
                  book->move(me);
     
                  set("marks/move", 1, here);
        }
        else return notify_fail(HIG "結果你什麼都沒發現！\n");

        return 1;
}

// 保證只有每次更新後才會有機會出現祕籍
void reset()
{
       object here;

       ::reset();

       if (! here = find_object(__FILE__))
                 here = load_object(__FILE__);       

       if( query("marks/move", here) )
                 delete("marks/move", here);

}
