// Feb. 6, 1999 by Winder
inherit ROOM;
void init();
void close_gate();
int do_open(string arg);
int do_close(string arg);
string look_gate();
void create()
{
        set("short", "大院");
        set("long", @LONG
這裏就是温宅進門的一個大庭院，地上鋪着一塊塊平整的
大理石，光可鑑人。院子的面積很大，看得出來這家主人家資
豐厚。南面的大門(gate)緊鎖着。
LONG
        );
        set("no_clean_up", 0);
        set("outdoors","shiliang");
        set("exits", ([ 
            "west" : __DIR__"xixiangfang",
            "east" : __DIR__"dongxiangfang",
            "north" : __DIR__"dating",
        ]));
        set("item_desc",([
                "gate"                :        (: look_gate :),
        ]));
        set("coor/x", 1610);
        set("coor/y", -1960);
        set("coor/z", 0);
        setup();
}
void init()
{
        add_action("do_open", "open");
        add_action("do_close", "close");
}
void close_gate()
{
        object room;
        if(!( room = find_object(__DIR__"gate")) )
                room = load_object(__DIR__"gate");
        if(objectp(room))
        {
                delete("exits/south");
                        message("vision", "有人走上前來把門關上了。\n", this_object());
                delete("exits/north", room);
                message("vision", "乒地一聲，裏面有人把大門關上了。\n", room);
        }
}
int do_close(string arg)
{
        if (!query("exits/south"))
                return notify_fail("大門已經是關着的了。\n");
        if (!arg || (arg != "gate" && arg != "south"))
                return notify_fail("你要關什麼？\n");
        message_vision("$N點了點頭。\n", this_player());
        remove_call_out("close_gate");
        call_out("close_gate", 2);
        return 1;
}
int do_open(string arg)
{
        object room;
        if (query("exits/south"))
                return notify_fail("大門已經是開着了。\n");
        if (!arg || (arg != "gate" && arg != "south"))
                return notify_fail("你要開什麼？\n");
        if(!( room = find_object(__DIR__"gate")) )
                room = load_object(__DIR__"gate");
        if(objectp(room))
        {
                set("exits/south", __DIR__"gate");
                message_vision("$N用力把大門打了開來。\n", this_player());
                set("exits/north", __FILE__, room);
                message("vision", "吱地一聲，裏面有人把大門打開了。\n", room);
                remove_call_out("close_gate");
                call_out("close_gate", 10);
        }
        return 1;
}
string look_gate()
{
        return "一道三丈來高的硃紅杉木包銅大門。\n";
}
int valid_leave(object me, string dir)
{
        if( query("id", me) == "sengbing" && dir == "south")return 0;
        return ::valid_leave(me, dir);
}