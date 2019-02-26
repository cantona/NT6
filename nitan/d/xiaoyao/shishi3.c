// shishi3.c
// Modified by Winder June.25 2000

inherit ROOM;
#include <ansi.h>;
void create()
{
        set("short", "石室");
        set("long", @LONG
這裏是一個極大的石室，比之外面的任何一個都大了數倍，室中一
排排地列滿了木製成的書架(shelf),可是書架上卻空蕩蕩地連一本書也
沒有，走近看時，只見書架上貼滿了“崑崙派”，“少林派”，“青城
派”之類的條目，想象當年所列，皆是各門各派的武功祕籍。室中還有
一張小牀(bed)。
LONG );
        set("exits", ([
                "south" : __DIR__"shidong",
        ]));
        set("objects", ([
                CLASS_D("xiaoyao")+"/xiaoyaozi" : 1,
        ]));
        set("item_desc", ([
                "bed"   : "一張很簡陋的小牀。\n",
                "shelf" : "書架上貼着一張小貼：“乘天地之正，御六氣之辯，以遊於無窮，是為逍遙。”\n",
        ]));
        set("book1_count",1);
        set("no_clean_up", 0);
        set("coor/x", -50020);
        set("coor/y", -21030);
        set("coor/z", -40);
        setup();
}

void init()
{
        add_action("do_strike","strike");
        add_action("do_move","move");
}

int do_strike(string arg)
{
        object me;

        me=this_player();
        if(!arg || arg!="shelf") return 0;
        message_vision("$N看着看着，忽然猛的一掌向書架打去！震得書架“克拉，克拉”的響了幾聲。\n",me);
        if ( random(100) > 94)
        {
message_vision("忽然，$N聽到一個聲音嘿嘿地奸笑起來：“你上當啦！”\n",me);
message_vision("接着，不知道哪裏射出一支毒箭，射中了$N！\n",me);
                me->die();
        }
        if (random(100)==50 && !present("miji1",me) && query("book1_count")>=1)
        {
                     addn("book1_count", -1);
                me=new("/clone/book/strike_book");
                me->move(__DIR__"shishi3");
                message("channel:rumor",MAG"【謠言】某人："+query("name", this_player())+"得到了掌法總譜啦。\n"NOR,users());
                tell_object(me, "突然啪地一聲，有一件東西從書架上掉了下來！\n");
        }
        return 1; 
}

int do_move(string arg)
{
        object me = this_player();

        if(!arg || arg!="bed") return 0;
        if(me->query_skill("construction", 1) < 10)
                return notify_fail("你的土木機關還不夠精熟，沒法打開小牀機關。\n");
        message_vision("$N用力把小牀移開，發現裏面竟然有一條祕密通道！\n",me);
        me->move(__DIR__"midao1");
        tell_object(me,"接着是一陣轟隆隆的響聲，你定神一看，自己已經處身在祕密通道中了。\n");
        return 1; 
}