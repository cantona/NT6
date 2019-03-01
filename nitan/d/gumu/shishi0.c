// Room: /d/gumu/shishi0.c
// Last Modifyed by Winder on Jan. 14 2002
 
#include <ansi.h>
inherit ROOM;

void create()
{ 
        set("short",HIB"石室"NOR);
        set("long", @LONG
頭頂的石壁 (shibi)又恢復了原狀，你發現自己置身于一間陰沉的
石室中，空盪盪的感覺使你心中只有恐懼，甚至忘記孤獨。你不知身處
何地，四周如此漆黑一片，只能靠摸索前行。
LONG        );
        set("item_desc", ([
                "shibi": "石壁恢復了原狀，與周圍吻合地天衣無縫，你不由感嘆其高超造詣。\n"NOR,
        ]));
        set("exits", ([
                "out" : __DIR__"shishi1",
        ]));
        set("no_clean_up", 0);
        set("coor/x", -3220);
        set("coor/y", -40);
        set("coor/z", 80);
        setup();
}

void init()
{
        add_action("do_tui", "tui");
}

int do_tui(string arg)
{
        object me = this_player();

        if (me->is_busy() || me->is_fighting())
                return notify_fail("你正忙著哪！\n");
        if (arg =="shibi")
        {
                message_vision(YEL "$N雙手把石壁用力向上推去，咯吱吱一聲，石壁緩緩移開。\n"NOR,me);
                set("exits/up", __DIR__"woshi");
                remove_call_out("close");
                call_out("close", 5, this_object());
                return 1;
        }
        return notify_fail("你要推什麼？\n");
}

void close(object room)
{
        message("vision",HIY"石壁慢慢移了回來，恢復了原狀。\n"NOR, room);
        delete("exits/up", room);
}