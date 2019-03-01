// Room: /guiyun/qianyuan.c
// Date: Nov.18 1998 by Winder
#include <ansi.h>;
inherit ROOM;

void create()
{
        set("short", "大院");
        set("long", @LONG
這裡是歸雲莊的大院，整個院子相當寬敞。左右靠牆各建有幾間低
矮的平房，像是家人的住處。正前方幾棵樹木，湖中清風吹來，落葉蕭
蕭而下。樹木再往後是一間大廳。
LONG );
        set("outdoors", "guiyun");
        set("no_clean_up", 0);
        set("valid_startroom", 1);
/*
右首有一對白雕(diao)。原來這裡是桃花島為方便弟子回島的。
        set("item_desc", ([
                "diao" : "一對白雕正展翅欲飛。如果是桃花島的弟子，\n"
                "騎上(ride)就可以飛回桃花島。\n",
        ]));
*/
        set("exits", ([
                "out"   : __DIR__"damen",
                "west"  : __DIR__"qianting",
        ]));
        set("coor/x", 280);
        set("coor/y", -830);
        set("coor/z", 0);
        setup();
        "/clone/board/guiyun_b"->foo();
}

void init()
{
//        add_action("do_ride", "ride");
}
int do_ride ( )
{
        mapping myfam;
        object room;
        object ob = this_player () ;
        myfam=query("family", ob);
        if(!myfam || myfam["family_name"] != "桃花島")
        {
                message_vision("$N一躍身跨上了白雕。只見白雕仰天長唳，突然猛然一顛......\n"
                HIR "結果$N摔了個鼻青臉腫！\n" NOR
                "看來白雕對$N並不感興趣，它只認識桃花島的弟子。\n" , ob ) ;
                ob -> receive_damage ("qi",50) ;
                ob -> receive_wound  ("qi",50) ;
                return 1;
        }
        if( !(room = find_object("/d/taohua/lantian")) )
                room = load_object("/d/taohua/lantian");
        if( room = find_object("/d/taohua/lantian") ) 
        if( query_temp("tian_trigger", room) == 1 )
        {
                message_vision("現在白雕正忙著,請過一會再乘坐!\n" , ob) ;
                return 1 ;
        }
        set_temp("tian_trigger", 1, room);
        message_vision("$N一躍身跨上了白雕。只見白雕仰天長唳，突然展翅高飛。\n\n"
                "但看一雕一人身形漸漸縮小，終至不見。\n" , ob );
        ob->move(room) ;
        tell_object(ob, CYN  "\n你不斷地飛呀飛，萬水千山身下飄過 ......\n\n" NOR ) ;
        call_out("taohua", 3 , ob );
        delete_temp("tian_trigger", room);
        return 1 ;
}
void taohua( object ob )
{
        tell_object(ob, "你終于飛到了桃花山莊，白雕落了下來。\n\n"  ) ;
        ob -> move ("/d/taohua/damen") ; 
}
void reset()
{
        object room;

        ::reset();
        if( room = find_object("/d/taohua/lantian") )
                delete("tian_trigger", room);
}