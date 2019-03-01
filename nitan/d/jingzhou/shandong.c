//Edited by fandog, 02/18/2000
#include <ansi.h>;
inherit ROOM;
void create()
{
        set("short", "山洞");
        set("long", @LONG
洞中有戚芳用黏土捏的泥人，狄雲用來彈鳥的彈弓，捉山兔的扳機，
戚芳放牛時吹的短笛，放在洞裡的石上。那邊是戚芳的針線籃。籃中的
剪刀已生滿了黃鏽。針線籃中還有一本舊書，那是戚芳用來夾鞋樣、繡
花樣的。
LONG );
        set("exits", ([
                "out"  : __DIR__"dashandong",
        ]));
        set("book_count", 1);
        set("no_clean_up", 0);
        set("coor/x", -1640);
        set("coor/y", -2210);
        set("coor/z", 0);
        setup();
}
void init()
{
        add_action("do_pick","pick");
}

int do_pick(string arg)
{
        object obj, me = this_player();
        if( !arg || arg!="book" ) return notify_fail("你要拿什麼?\n");
        if( query("book_count") )
        {
                obj = new (__DIR__"obj/tangshi");
                obj->move(me);
                addn("book_count", -1);
                message_vision("$N隨手從針線籃中拿起一本舊書，書的封面上寫著“唐詩選輯”四個字。\n",me );
message("channel:rumor",MAG"【謠言】某人："+query("name", me)+"拿到唐詩選輯啦。\n"NOR,users());
        }
        else
                return notify_fail("你要拿起那本書，卻發現你看花了眼，其實那裡什麼都沒有。\n");
        return 1;
}