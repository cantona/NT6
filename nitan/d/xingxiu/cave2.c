// Room: /d/xingxiu/cave2.c
// Last Modified by Winder on Apr. 25 2001

inherit ROOM;

int do_use(string arg);
int do_zuan(string arg);

void create()
{
        set("short", "山洞");
        set("long", @LONG
本來是黑黝黝的山洞裡，伸手不見五指。只有一絲微光從洞頂的裂縫
透進來，可以勉強看見正中央有一個石棺，散發著濃厚的腐屍氣味，微光
下更顯得洞內陰森可怕。一個鬼一般的人影坐在石壁邊，兩只閃著藍光的
眼睛正盯著你看，山壁上有人工修繕之處。
LONG);
        set("objects", ([
                CLASS_D("xingxiu")+"/piaoran" : 1, 
                __DIR__"obj/shiguan" : 1,  
                __DIR__"obj/muding" : 1,  
                __DIR__"obj/lanyubo" : 1,  
        ]));
        set("coor/x", -50500);
        set("coor/y", 20400);
        set("coor/z", 200);
        setup();
}

void init()
{
        add_action("do_use", "use");
        add_action("do_zuan", "zuan");
}

int do_use(string arg)
{
        object me = this_player();

        if( !arg || arg=="" ) return 0;
        if (!present("fire", me))  return 0;
        if(arg=="fire")
        {
                write("你點燃了火折，發現東面石壁上的一道裂縫可以鑽(zuan)出去。\n");
                set_temp("marks/鑽", 1, me);
                me->start_busy(2);
                return 1;
        }
}

int do_zuan(string arg)
{
        object me = this_player();

        if( query_temp("marks/鑽", me) )
        {
                message("vision", me->name() + "滋溜一下不知從什麼地方鑽出去了。\n", environment(me), ({me}) );
                me->move(__DIR__"cave");
                message("vision", me->name() + "不知從什麼地方鑽了出來。\n", environment(me), ({me}) );
                set_temp("marks/鑽", 0, me);
                return 1;
        }
        else
        {
                write("你想往哪兒鑽?!\n");
                return 1;
        }
}