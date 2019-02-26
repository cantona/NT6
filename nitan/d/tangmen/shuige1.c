//shuige1.c                四川唐門—亭榭水閣

#include <ansi.h>
#include <room.h>
inherit ROOM;

void away(object obj);

void create()
{
        set("short", "亭榭水閣");
        set("long",
"這裏是蓮藕小築的亭榭水閣。這裏與蓮藕小築連為一體，同樣是古玉\n"
"色的建築。水閣四壁上繪着各色的山水魚蟲，從這裏向前通向蓮雲閣，而\n"
"身後一扇大門緊閉着擋住了退路！\n"
);
        set("exits", ([
                "north" : __DIR__"shuige2",
                "south" : "/d/tangmen/qianyuan",
                "east" : __DIR__"chashi",
                "west" : __DIR__"menwei",
        ]));
        set("area", "tangmen");
        setup();
}
void init()
{
        add_action("do_open","open");
}

int do_open(string arg)
{
        object ob, room;
        ob = this_player();

        if ( query("exits/out") )
                return notify_fail("門已經是開着的了。\n");

        if ( !( room = find_object(__DIR__"xiaozhu")) )
                room = load_object(__DIR__"xiaozhu");

        if ( arg && arg=="door" && objectp(room) )
        {
                message_vision(HIC "你用力將大門拉開。\n" NOR, ob);
                set("exits/out", __DIR__"xiaozhu");
                set("exits/enter", __DIR__"shuige1", room);
                remove_call_out("close");
                call_out("close", 60, this_object());
                return 1;
        }
        else
                return 0;
}

void close()
{
        object room;

        if ( !( room = find_object(__DIR__"xiaozhu")) )
                room = load_object(__DIR__"xiaozhu");

        if( this_object() == environment(this_player()) || room == environment(this_player()))
                message("vision",HIR"大門悄無聲息的關了起來。\n"NOR, this_player());
        delete("exits/out");
        if ( objectp(room) )
                delete("exits/enter", room);
}        

int valid_leave(object me, string dir)
{
        object obj, room;

        if ( !( room = find_object(__DIR__"menwei")) )
                room = load_object(__DIR__"menwei");

        if( (dir == "out") && (query("combat_exp", me) <= 200000) && !wizardp(me) && !query("tangmen/xin", me) )
                if ( objectp(present("men wei", environment(me)) ) )
                {
                        obj = present("men wei", environment(me));
                        message_vision("門衞對着$N大聲喊道：“你的武功還不夠高，別出去給唐家丟人了！”\n",me);
                        remove_call_out("away");
                        call_out("away", 60, obj);
                        return notify_fail("\n你忽然想起師傅好像曾經告訴過你，只有功夫厲害了才能被允許出門闖蕩江湖。\n");
                }
                else
                        if ( objectp(room) && objectp(present("men wei", room)) )
                        {
                                obj = present("men wei", room);
                                tell_room(room, "門衞好像聽到了什麼聲響，眉頭一皺自語到：“是誰又想擅自出門！我得去看看!”\n門衞快步向東走去。\n");
                                tell_room(this_object(), "門衞快步從西邊的屋中走過來。\n");
                                obj->move(__DIR__"shuige1");
                                message_vision("門衞對着$N大聲喊道：“你的武功還不夠高，別出去給唐家丟人了！”\n",me);
                                remove_call_out("away");
                                call_out("away", 60, obj);
                                return notify_fail("\n你忽然想起師傅好像曾經告訴過你，只有功夫厲害了才能被允許出門闖蕩江湖。\n");
                        }

        return ::valid_leave(me, dir);
}

void away(object obj)
{
        string name;
        object room;

        if (! objectp(obj)) return;
        if ( !( room = find_object(__DIR__"menwei")) )
                room = load_object(__DIR__"menwei");

        if( living(obj) )
        {
                if (  !obj->busy() && !obj->is_fighting() )
                {
                        message_vision("$N搖了搖頭，笑着説:“現在這些小子真不知天高地厚，可一出去就給唐家丟人。”\n$N向差房走去。\n", obj);
                        tell_room(room, "門衞快步從水閣那邊走過來。\n");
                        obj->move(__DIR__ "menwei");
                }
                else
                {
                        remove_call_out("away");
                        call_out("away", 60, obj);
                }
        }
        return;
}