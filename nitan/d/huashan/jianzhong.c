// Room: jianzhong 劍塚
// Modify by Rcwiz for hero.cd
// 獲得玄鐵重劍、無名劍

#include <ansi.h>

inherit ROOM;

string look_fen();
string look_stone();
string look_sword2();
string look_sword3();

#define XUANTIE "/clone/lonely/xuantiejian"
#define NONAME "/clone/lonely/noname"

void create()
{
        set("short", "劍塚");
        set("long", @LONG
只見許多石塊堆著一個大墳。這墳（fen）背向山谷，俯仰空闊。
 墳旁立有一大石（stone），上刻：「劍塚」二字。站在此處， 山風
刺骨，俯瞰蓮花峰（lianhua）下景色壯麗無比。
LONG );
        set("outdoors", "huashan");

        set("objects", ([ 
                CLASS_D("misc/shendiao")  :  1, 
        ]));

        set("item_desc", ([
                "stone"          : (: look_stone :),
                "fen"            : (: look_fen :),
                "fir sword"      : NOR + GRN "你拿起這柄劍，只覺著手輕飄飄的渾似無物，原來是柄竹劍。但見劍下的石刻道：\n"
                                   HIM "「四十歲後，不滯於物，草木竹石均可為劍。自此精修，漸進於無劍勝有劍之境。 」 \n" NOR,
                "sec sword"      : (: look_sword2 :),
                "thi sword"      : (: look_sword3 :), 
                "piece"          : HIW "你拿起長條石片 ，見石片下的青石上也刻有兩行小字：\n"
                                   HIM "「紫薇軟劍，三十歲前所用，誤傷義不祥，乃棄之深谷。」 \n" NOR,
                "sec piece"      : HIW "細看石刻，見兩行小字道：「重劍無鋒，大巧不工。四十歲前恃之橫行天下。」 \n" NOR,
                "thi piece"      : HIW "石上刻有兩行小字：「凌厲剛猛，無堅不摧，弱冠前以之與河朔群雄爭鋒。」 \n" NOR,
                "big stone"      : NOR + WHT "一堆石頭，似乎獨孤求敗所遺留之劍就在下面。\n" NOR,
                "lianhua"        : HIG "景色壯麗無比，可以從這裡（jump lianhua）到蓮花峰。\n" NOR,
 
        ]));

        setup();
}

void init()
{
        MYGIFT_D->check_mygift(this_player(), "newbie_mygift/shendiao"); 
        add_action("do_move", "move");
        add_action("do_pick", "pick");
        add_action("do_jump", "jump");
}

string look_stone()
{
        string msg;

        msg = NOR + WHT "只見大石上「劍塚」兩個大字之旁，尚有兩行字體較小的石刻：\n"
              HIR "「劍魔獨孤求敗既無敵於天下，乃埋劍於斯。嗚呼！群雄束手，長劍空"
              "利，不亦悲夫！」 \n" NOR;

        return msg;
}

string look_fen()
{
        object me = this_player();
        object ob, noname, xuantie;
        string msg;
        
        if (! ob = find_object(__FILE__));
                 ob = load_object(__FILE__);
        
        if( !query_temp("moved", ob) )
                 return NOR + WHT "想必這就是劍魔獨孤求敗埋劍的地方，上面堆滿了大石（big stone）。\n" NOR;
        
        if (! noname = find_object(NONAME));
                 noname = load_object(NONAME);

        if (! xuantie = find_object(XUANTIE));
                 xuantie = load_object(XUANTIE);
        
        // 第一（fir sword）是竹劍，第二是玄鐵劍，最右是無名劍
        if (! environment(noname) && ! environment(xuantie))
                 msg = NOR + WHT "劍塚下露出並列著的三柄長劍。\n在第一（fir sword）、第二（sec sword）把劍之"
                       "間，另有一塊長條石片（piece）。\n三柄劍和石片並列於一塊大青石之上。\n" NOR;

        else if (! environment(noname) && environment(xuantie))
                 msg = NOR + WHT "劍塚下露出並列著的兩柄長劍，在第一（fir sword）的右邊"
                       "另有一塊長條石片（piece）。\n而第二把劍已不知去向，只留下石片（se"
                       "c piece）上所刻的小字。\n兩柄劍和石片並列於一塊大青石之上。 \n" NOR;

        else if (environment(noname) && ! environment(xuantie))
                 msg = NOR + WHT "劍塚下露出並列著的兩柄長劍。\n在第一（fir sword）、第二（sec sword）把劍之"
                       "間，另有一塊長條石片（piece）。\n而最右首的劍已不知去向，只留下"
                       "石片（thi piece）上所刻的小字。\n兩柄劍和石片並列於一塊大青石之上。 \n" NOR;

        else     msg = NOR + WHT "劍塚下露出並列著的一柄長劍，在第一（fir sword）的右邊"
                       "另有一塊長條石片（piece）。\n其余的兩把劍已不知去向，只留下"
                       "石片（sec piece、thi piece）上所刻的小字。\n這柄劍和石片並列"
                       "於一塊大青石之上。 \n" NOR;

        return msg;
}

string look_sword2()
{
        object ob, xuantie;
        string msg;
        
        if (! ob = find_object(__FILE__));
                 ob = load_object(__FILE__);
        
        if( !query_temp("moved", ob) )
                 return "你要看什麼？\n";
        
        if (! xuantie = find_object(XUANTIE));
                 xuantie = load_object(XUANTIE);

        if (environment(xuantie))
                 return "你要看什麼？\n";

        msg = NOR + WHT "一把黑黝黝的鐵劍，下面有一個石片（sec piece）。\n" NOR;

        if (objectp(xuantie))destruct(xuantie);
      
        return msg;
               
}

string look_sword3()
{
        object ob, noname;
        string msg;
        
        if (! ob = find_object(__FILE__));
                 ob = load_object(__FILE__);
        
        if( !query_temp("moved", ob) )
                 return "你要看什麼？\n";
        
        if (! noname = find_object(NONAME));
                 noname = load_object(NONAME);

        if (environment(noname))
                 return "你要看什麼？\n";

        msg = HIC "只見此劍長約四尺，青光閃閃，似是利器。下面有一個石片（thi piece）。\n" NOR;

        if (objectp(noname))destruct(noname);
      
        return msg;
               
}

int do_move(string arg)
{
        object me = this_player();
        object ob;

        if (me->is_busy() || me->is_fighting())
              return notify_fail("你忙完了再說吧！\n");

        if (! arg || arg != "big stone")
              return notify_fail("你要幹什麼？\n");
        
        if (! ob = find_object(__FILE__));
                 ob = load_object(__FILE__);

        if( query_temp("moved", ob) )
                 return notify_fail("上面的石頭已經被移開了！\n");
 
                
        message_vision(HIG "$N" HIG "用力將劍塚上面的石頭一塊塊地移開 ……\n", me);

        set_temp("moved", 1, ob);
 
        me->start_busy(1);
      
        return 1;
}

int do_pick(string arg)
{
        object me = this_player();
        object ob, noname, xuantie;

        if (me->is_busy() || me->is_fighting())
              return notify_fail("你忙完了再說吧！\n");

        if (! arg || 
            arg != "fir sword" &&
            arg != "sec sword" &&
            arg != "thi sword")
              return notify_fail("你要取什麼？\n");
        
        if (! ob = find_object(__FILE__));
                 ob = load_object(__FILE__);

        if (! noname = find_object(NONAME));
                 noname = load_object(NONAME);

        if (! xuantie = find_object(XUANTIE));
                 xuantie = load_object(XUANTIE);

        if( !query_temp("moved", ob) )
                 return notify_fail("你要幹什麼？\n");

        switch(arg)
        {
              case "fir sword" : 
                     return notify_fail(HIC "你將竹劍拿起來看了看，覺得普通之極，便又放了回去。\n" NOR);

              case "sec sword":
                     if (environment(xuantie))
                           return notify_fail("上面的東西已被人拿走了！\n");

                     if( query("str", me)<34 )
                           return notify_fail("你將鐵劍只提起數尺，嗆的一聲，竟然脫手掉下"
                                              "，在石上一碰，火花四濺，不禁嚇了一跳。\n");

                     message_vision(HIM "$N" HIM "將玄鐵重劍提了起來。\n" NOR, me);

                     xuantie->move(me);

                     return 1;

              case "thi sword":
                     if (environment(noname))
                           return notify_fail("上面的東西已被人拿走了！\n");
              
                     message_vision(HIM "$N" HIM "將無名劍提了起來。\n" NOR, me);

                     noname->move(me);

                     return 1;
        }
         
        me->start_busy(1);
      
        return 1;
}

int do_jump(string arg)
{
        object me = this_player();

        if (! arg || arg != "lianhua")
             return notify_fail("你要往哪兒跳？\n");

        if( query("qi", me)<300 )
             return notify_fail("你力氣不加。\n");

        if (me->is_busy() || me->is_fighting())
             return notify_fail("等你忙完了再說。\n");

        me->start_busy(1 + random(3));

        message_sort(HIG "\n$N" HIG "縱身跳下 ……\n" NOR, me);

       me->move(__DIR__"lianhua");
      
       return 1;
}
