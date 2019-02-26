// Room: /d/qingcheng/kufang.c

inherit ROOM;
int do_qiao(string arg);

void create()
{
        set("short", "庫房");
        set("long", @LONG
這裏是青城一派的庫房，收藏着各種途徑得來的珍寶。庫房北邊壁
上櫃掛着一些白章虎皮、花格豹皮和其它不知名的皮毛，南邊壁櫃裏擺
放着一些奇石和銅鐵製品，看來還是值點錢的。東壁下是一個大鐵箱，
鎖得甚是嚴實。
LONG );
        set("objects", ([
                __DIR__"obj/xiang" : 1,
        ]));
        set("coor/x", -8069);
        set("coor/y", -840);
        set("coor/z", 90);
        setup();
//        replace_program(ROOM);
}
int do_qiao(string arg)
{
        object me=this_player();
        object room;
        if (arg != "men") return 0;
        if(!( room = find_object(__DIR__"zoulang2")) )
                room = load_object(__DIR__"zoulang2");
        if(objectp(room))
        {
                set("exits/west", __DIR__"zoulang2");
                message_vision("$N費了半天勁，把門撬開了。\n",me);
                set("exits/east", __FILE__, room);
                message("vision","裏面有人把庫門打開了。\n",room);
                remove_call_out("close_gate");
                call_out("close_gate", 10);
        }
        return 1;
}
void init()
{
        add_action("do_qiao","qiao");
}
void close_gate()
{
        object room;

        if(!( room = find_object(__DIR__"zoulang2")) )
                room = load_object(__DIR__"zoulang2");
        if(objectp(room))
        {
                delete("exits/east", room);
                message("vision","只聽乒地一聲，庫門自動關了起來。\n",room);
                message("vision","你腦海中閃過一個念頭：哎喲！又進不去了！\n", room);
                delete("exits/west");
                message("vision","只聽乒地一聲，庫門自動關了起來。\n",this_object());
                message("vision","你腦海中閃過一個念頭：壞了！出不去了！\n" , this_object());
        }
}