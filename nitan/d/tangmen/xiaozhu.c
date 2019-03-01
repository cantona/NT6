//xiaozhu.c                四川唐門─蓮藕小築

#include <ansi.h>
#include <room.h>
inherit ROOM;

void create()
{
        set("short", "蓮藕小築");
        set("long",
"這裡是距蜀中唐門不遠的蓮藕小築。蓮藕小築是棟古玉色的建築看來\n"
"雅致簡樸，但有多少江湖高手為了越此一步，都屍橫遍地不可得呢！一扇\n"
"厚重的大門(door)緊緊的閉著。\n"
);
        set("item_desc", ([
                "door" : "這是一扇極其厚重的大門，兩個紫銅門環便足有碗口大小。\n"NOR,
        ]));
        set("area", "tangmen");
        setup();
}

void init()
{
        add_action("do_knock","knock");
        add_action("do_open","open");
}

int do_open(string arg)
{
        object ob;
        ob = this_player();

        if ( arg && arg=="door" )
        {
                message_vision(HIC "$N雙手用力想推開大門，但大門顯然從裡面鎖住了。\n" NOR, ob);
                return 1;
        }
}

int do_knock(string arg)
{
        object ob, room;

        ob = this_player();

        if ( query("exits/enter") )
                return notify_fail("門已經是開著的了。\n");

        if ( !( room = find_object(__DIR__"shuige1")) )
                room = load_object(__DIR__"shuige1");

        if ( arg && arg=="door" && objectp(room) )
        {
//                message_vision(HIC "$N伸手小心翼翼的扣動門環。\n忽聽一人怩聲怩氣的道：“何必為難呢？有膽就進小築裡來吧，我正恭候光臨哩！。\n大門悄無聲息的打開了。\n" NOR, ob);
                message_vision(HIC "$N用力扣動門環，大門悄無聲息的打開了。\n" NOR, ob);
                set("exits/enter", __DIR__"shuige1");
                set("exits/out", __DIR__"xiaozhu", room);
                remove_call_out("close");
                call_out("close", 5, this_object());
                return 1;
        }
        else
                return 0;
}

//void close(object room)
void close()
{
        object room;

        if ( !( room = find_object(__DIR__"shuige1")) )
                room = load_object(__DIR__"shuige1");

        if( this_object() == environment(this_player()) || room == environment(this_player()))
                message("vision",HIR"大門悄無聲息的關了起來。\n"NOR, this_player());
        
        delete("exits/enter");
        if ( objectp(room) )
                delete("exits/out", room);
}        