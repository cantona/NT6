#include <ansi.h>

inherit ROOM;

void create()
{
        set("short", "聽雨居");
        set("long", @LONG
這個小居建在湖上，看上去沒有什麼特別之處。四面為水，湖上
煙波盡收眼底。唯一奇怪的是這兒放著一具瑤琴(qin)。
LONG );
        set("item_desc", ([
            "qin" :  "這琴比之尋常七弦琴短了尺許，卻有九根琴弦。\n"
                     "不知是該去彈一彈(tan)還是將它擊開(break)。\n",
        ]));
        set("exits", ([
            "south" : __DIR__"xiaoqiao",
        ]));
        setup();
}


void init()
{
    add_action("do_tan", "tan");
    add_action("do_tan","play");
    add_action("do_break","break");
}

int do_tan (string arg)
{
    object room;
    object ob = this_player();
    if (! arg || arg != "qin")
                return notify_fail("你要彈什麼？\n");

    message_vision("$N輕輕的在琴上一撥，鐺的一聲，聲音頗為宏亮。\n\n" +
                   "似乎這琴有點古怪.....\n" +
                   "$N正納悶間，忽覺腳底一虛，身子往下直沉.....\n", ob);
    tell_object(ob, "\n你忍不住啊喲一聲，便掉入了一個軟綿綿的所在！原來是"
                "一艘小船。\n\n" ) ;
    room = load_object("d/yanziwu/hu");
    ob->move(room) ;

    call_out("mantuo", 10, ob);
    return 1;
}

int do_break(string arg)
{
        if (! arg || arg != "qin")
                return notify_fail("你要擊開什麼？\n");

        message_vision("\n$N一掌擊開瑤琴，只聽“唰”的一聲，突然銀光一閃，\n"+
                "一枚梅花鏢倏的射出,“噗”的一聲射入了$N的人中穴。\n",
                this_player());

        if( query("qi", this_player())<200 )
                this_player()->die();
        else
                this_player()->unconcious();
        return 1;
}

void mantuo(object ob)
{
        if (! objectp(ob))
                return;

        if (base_name(environment(ob)) != "/d/yanziwu/hu") 
                return;
        tell_object(ob, "船來到了一個不知名的地方，你下得船來，"
                    "茫然的看看四周，不知所處。\n");
        ob->move(__DIR__"hupan");
        return;
}
