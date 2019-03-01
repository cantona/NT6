// Room: /d/huangshan/shijian.c
// Last Modified by winder on Sep. 27 2001

inherit ROOM;
void create()
{
        set("short", "試劍石");
        set("long", @LONG
一塊巨大的石頭 （stone），孤處路中，中間一痕，深幾近半，相
傳這是一古代劍師試劍之處，鑄劍千余，最後終于造出一把可以劈開此
石的劍，名為“蒼穹神劍”，可惜劍師因心力憔悴而死。相傳黃山劍廬
主人世代相傳的便是此劍。
LONG
        );
        set("exits", ([ 
                "east" : __DIR__"zuishi",
        ]));
        set("item_desc", ([
                "stone": "一塊巨大的石頭，中間一痕，裂縫深處似乎有一
東西閃閃發光。你似乎也可以在這裡試一試（test）你的武器。\n"
        ]) );
        set("outdoors", "huangshan");
        set("coor/x", -615);
        set("coor/y", -1080);
        set("coor/z", -30);
        setup();
}
void init()
{
        add_action("do_test","test");
}
int do_test(string arg)
{
        object weapon, me = this_player();
        object piece;

        if(!arg ) return notify_fail("你要試一試你身上的哪樣武器？\n");
        if(!(weapon = present(arg,me)))
                return notify_fail("你身上似乎沒有這樣東西！\n");
        if( !query("weapon_prop", weapon) )
                return notify_fail(weapon->name()+"似乎並不是一種武器！\n");
        if( !query("equipped", weapon) )
                return notify_fail("你並沒有將"+weapon->name()+"握在手中。\n");
        message_vision("$N用盡全力，將手中的"+weapon->name()+"猛力向巨石揮去。。。。\n",me);
        weapon->unequip();
        set("weapon_prop", 0, weapon);
        weapon->save();
        me->reset_action();
        message_vision("只聽見”鐺“的一聲，$N手中的"+weapon->name()+"應聲而斷！\n",me);
        seteuid(getuid());
        piece = new("/clone/misc/piece");
        piece->set_name("斷掉的"+query("name", weapon),({query("id", weapon),"piece"}));
        piece->move(this_player());
        destruct(weapon);
        if(random(500))
                tell_object(this_object(),"大石上的裂痕似乎又深了一些！\n");
        else
        {
                tell_object(this_object(),"一塊黑黝黝的東西從石縫中掉了出來！\n");
                weapon = new(__DIR__"obj/banzhi");
                weapon->move(this_object());
        }
        me->start_busy(2);
        return 1;
}