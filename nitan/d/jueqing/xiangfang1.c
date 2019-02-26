#include <ansi.h>

inherit ROOM;

int tell_player();

void create()
{
        set("short", "廂房");
        set("long", @LONG
這是絕情谷主的廂房，平時除了谷主本人外未經允許任何
人都不能入內。但見廂房佈置簡陋，但四周陳設整齊，靠牀的
衣櫃上擺着一個外形奇怪的花盆(pen)。
LONG);
        set("item_desc",([
               "pen" : HIC "這個花盆看上去很奇怪，似乎連接着什麼機關。\n" NOR,
        ]));

        set("exits", ([
               "east"    : __DIR__"changlang3",
        ]));

        set("no_clean_up", 0);

        setup();
}

void init()
{       
        add_action("do_turn", ({ "turn", "zhuan" }));
        add_action("do_jump", ({ "tiao", "jump" }));
}

int do_turn(string arg)
{
        object me = this_player();
        object ob;

        if (! arg || arg != "pen")
                return notify_fail("你要做什麼？\n");

        if (! ob = find_object(__DIR__"xiangfang1"))
                ob = load_object(__DIR__"xiangfang1");

        if (me->is_busy())
                return notify_fail("你現在正忙着呢！\n");

        if (me->is_fighting())
                return notify_fail("你還是先把你面前這個傢伙解決了再説。\n");

        // 機關已經打開，再次轉動則關閉
        if( query_temp("marks/轉", ob) )
        {
                 message_sort(HIG "\n$N輕輕地轉動花盆，一陣巨響從牀頭傳"
                              "出，原來露出的洞口已被完全封住，已經也看"
                              "不出來這下面隱藏的暗道。\n" NOR, me);   

                 set("long",@LONG
這是絕情谷主的廂房，平時除了谷主本人外未經允許任何
人都不能入內。但見廂房佈置簡陋，但四周陳設整齊，靠牀的
衣櫃上擺着一個外形奇怪的花盆(pen)。
LONG);

                 delete_temp("marks/轉", ob);

                 return 1; 
        }
        // 機關未打開，打開機關
        message_sort(HIY "\n$N輕輕地轉動花盆，一陣巨響從牀頭傳出，定睛"
                           "一看，只見牀頭處露出一個洞口(dong)來，原來"
                           "這裏竟隱藏着暗道。\n" NOR, me);

       set_temp("marks/轉", 1, ob);

       set("long",@LONG
這是絕情谷主的廂房，平時除了谷主本人外未經允許任何
人都不能入內。但見廂房佈置簡陋，但四周陳設整齊，牀頭處
卻露出一個洞(dong)來，不知道通往何處。 
LONG);

       return 1;
}

int do_jump(string arg)
{
        object me = this_player();
        object ob;

        if (! arg || (arg != "dong" && arg != "hole"))
                return notify_fail("你要做什麼？\n");

        if (! ob = find_object(__DIR__"xiangfang1"))
                ob = load_object(__DIR__"xiangfang1");

        if (me->is_busy())
                return notify_fail("你現在正忙着呢！\n");

        if (me->is_fighting())
                return notify_fail("你還是先把你面前這個傢伙解決了再説。\n");
        
        if( !query_temp("marks/轉", ob) )
                return notify_fail("你亂跳什麼？");  

        tell_room(ob, me->name() + HIW "縱身一躍，跳進牀頭的洞口…\n" NOR, me);

        tell_object(me, HIC "\n你縱身一躍，進入洞中，耳邊寒風颼颼，此洞深不見底，但覺\n"
                            "足底空虛，竟似直墮了數十丈尚未著地…\n" NOR);

        remove_call_out("tell_player");
        call_out("tell_player", random(4) + 3);

        return 1;
}

int tell_player()
{
       object ob1, ob2;
       object me = this_player();
     
       // ob1 鄂魚潭岸上
       if (! ob1 = find_object(__DIR__"eyutan1"))
               ob1 = load_object(__DIR__"eyutan1");

       // ob2 鄂魚潭水中
       if (! ob2 = find_object(__DIR__"eyutan2"))
               ob2 = load_object(__DIR__"eyutan2");

       tell_object(me, HIG "思念未定，撲通一聲，你已摔入水中，往下急沉。\n" NOR);

       tell_room(ob1, me->name()+ HIW "\n從上面跳下，墜入潭中。\n" NOR, me);

       me->move(ob2);

       return 1;
}
