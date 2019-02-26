#include <ansi.h>
inherit ROOM;

int do_knock(string arg);

void create()
{
        set("short", "劉府大門");
        set("long",
"這裏是劉府大門。劉府的主人，就是衡山派中的僅次於掌\n門人莫大先生"
"的第二號人物劉正風劉老爺子。今天興許劉府有\n事吧，大門(gate)緊閉，管"
"家家丁也異樣緊張，莫非今天出了\n什麼事情。\n\n" HIR
"     ||                                        ||\n"
"  ┏≡≡┓" HIW "   ※※※※※※※※※※※※※※" HIR "   ┏≡≡┓\n"
"  {------}" HIW "   ※                        ※" HIR "   {------}\n"
"  ┗≡≡┛" HIW "   ※       " HIY "劉      府" HIW "       ※" HIR "   ┗≡≡┛\n"
"   │││" HIW "    ※                        ※" HIR "    │││\n"
"   │││" HIW "    ※※※※※※※※※※※※※※" HIR "    │││\n"
"   │││                                    │││\n\n"

); 

        set("exits", ([
                "south"  : __DIR__"hengyang1",
        ]));

        set("item_desc", ([
                "gate" : HIR "\n硃紅的大門緊閉着，敲敲(knock)看吧。\n\n" NOR,
        ]));

        set("objects", ([
                __DIR__"npc/haoke"    : 4,
                __DIR__"npc/jian-ke" : 2,
        ]));  

	set("coor/x", -6900);
	set("coor/y", -5690);
	set("coor/z", 0);
	setup();
}
void init()
{
        add_action("do_knock", "knock");
        add_action("do_push", "push");
        add_action("do_push", "open");
}

int do_knock(string arg)
{
        object me;

        me = this_player();
              message_vision(HIW "\n$N“咚，咚，咚……。”地敲着門，可裏面"
                             "卻一點動靜都沒有。\n\n" NOR, me);

        set_temp("marks/liufu", 1, me);

        return 1;
}

int do_push(string arg)
{
    int n;
    object weapon,me = this_player();
    mapping fam;

    if( !query_temp("marks", me) )
              return notify_fail("門關得牢牢的，急切打不開！\n");

    if ( !arg || arg != "gate" ) 
              return notify_fail("這是幹嘛？\n");

    message_vision(HIY "$N走到門前，把門隨便一推，居然就推開了大門！\n\n"NOR,me);

    set("exits/enter",__DIR__"liufudayuan");

    remove_call_out("close");
    call_out("close", 5, this_object());

    return 1;
}
void close_out()
{
    if (query("exits/enter")) 
              delete("exits/enter");
}

void close(object room)
{
    message("vision",HIC"\n一陣咿咿呀呀門響，裏面有人把大門給關上了。\n"NOR, room);

    delete("exits/enter", room);
}