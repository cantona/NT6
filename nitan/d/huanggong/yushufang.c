// Room: /d/huanggong/yushufang.c
#include <room.h>
inherit ROOM;

void close_gate();
int do_open(string arg);
void create()
{
        set("short", "御書房");
        set("long", @LONG
皇上用功讀書的御書房，又叫上書房、南書房。也是皇子皇孫們讀
書的地方。北面是聖祖御筆的牌匾(bian)，兩側是世宗御筆楹聯(lian)。
四下齊整地排著幾張書架，上面看來都是些名典巨著。你暗自想，原來
皇帝也讀這麼多的書啊。書房正中有張精雕的檀香木書桌，桌上擺著幾
本封面精美的書。
LONG         );
         set("item_desc", ([ 
                "bian" : "\n養正毓德\n\n",
                "lian" : "
立身以至誠為本
讀書以明理為先\n\n",
         ]));
        set("objects", ([
                __DIR__"npc/kangxi" : 1,
                "/d/beijing/obj/book14_2" : 1,
        ]));
        set("exits", ([
                "northwest" : __DIR__"qianqinggong",
        ]));

	set("coor/x", -2800);
	set("coor/y", 7741);
	set("coor/z", 0);
	setup();
}

void init()
{
        add_action("do_open", "open");
}

int close_gate()
{
        object room;

        if(!( room = find_object(__DIR__"mishi")) )
        room = load_object(__DIR__"mishi");
        if(objectp(room))
        {
                delete("exits/north");
                message("vision","只聽乒地一聲，暗門自動關上了。\n", this_object());
                message("vision","你腦海中閃過一個念頭：哎喲！又進不去了！\n", this_object());
                delete("exits/south", room);
                message("vision","只聽乒地一聲，暗門自動關了起來。\n", room);
                message("vision","你腦海中閃過一個念頭：壞了！出不去了！\n", room );
        }
}


int do_open(string arg)
{
        object ob,room;
        if (query("exits/north"))
                return notify_fail("暗門已經是打開的。\n");
        if (!arg || (arg != "bian"))
                return notify_fail("你要打開什麼？\n");
        set("exits/north", __DIR__"mishi");
        if(!( room = find_object(__DIR__"mishi")) )
                room = load_object(__DIR__"mishi");
        if(objectp(room))
        {
                set("exits/north", __DIR__"mishi");
                message_vision("$N輕輕地推了推牌匾，只聽吱地一聲，一個暗門開了。\n",this_player());
                set("exits/south", __FILE__, room);
                message("vision","只聽吱地一聲，暗門從外面打開了。\n", room);
                remove_call_out("close_gate");
                call_out("close_gate", 10);
        }
        return 1;
}