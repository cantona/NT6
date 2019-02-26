// Room: /d/xingxiu/yueerquan.c
// Last Modified by winder on Feb. 28 2001

inherit ROOM;

void create()
{
        set("short", "月兒泉");
        set("long", @LONG
出乎你的意料之外，在浩瀚沙漠中竟然有的泉水，一泓清澈的泉水
形成一個月牙的形狀，因而得名月兒泉。漣漪縈迴，水草叢生，清澈見
底。這裏出產鐵背魚、七星草，但不常見。此泉雖在流沙山羣中，風起
沙飛，均繞泉而過，從不落入泉內。北面是一片峭壁(cliff) ，東邊傳
來嗡嗡的聲響。
LONG );
        set("outdoors", "qilian");
        set("resource/water", 1);
        set("exits", ([
                "southup" : __DIR__"shashan",
                "east"    : "/d/qilian/loulan",
        ]));
        set("item_desc", ([
                "cliff" : "峭壁上似乎有一個洞(hole)。\n"
        ]) );
        set("no_clean_up", 0);
        set("coor/x", -20310);
        set("coor/y", 200);
        set("coor/z", 0);
        setup();
}

void init()
{
        add_action("do_enter", "enter");
}
int do_enter(string arg)
{
        object me;
        me = this_player();

        if( !arg || arg=="" ) return 0;
        if( arg=="hole" )
        {
                if(me->query_encumbrance()*100/me->query_max_encumbrance()< 20)
                {
                        message("vision", me->name() + "一縱身躍進了洞裏。\n", environment(me), ({me}) );
                        me->move("/d/xingxiu/mogaoku");
                        message("vision", me->name() + "從洞外跳了進來。\n", environment(me), ({me}) );
                        return 1;
                }
                else
                {
                        write("你身上背的東西太重，洞口又太高，你夠不着。\n");
                        return 1;
                }
        }
}