// Feb. 6, 1999 by Winder
inherit ROOM;
void init();
void close_door();
int do_open(string arg);
int do_close(string arg);
void create()
{
        set("short", "暗道盡頭");
        set("long",@LONG
這裏是暗道的盡頭，有扇鐵門(door)看起來很陳舊，不知道通往
哪裏。
LONG                
        );
        set("no_clean_up", 0);
        set("exits", ([
                "south" : __DIR__"andao2",
        ]));
        set("item_desc",([
                "door"        : "這是一扇破舊的鐵門。\n"
        ]));
        set("coor/x", 1620);
        set("coor/y", -1750);
        set("coor/z", -10);
        setup();
}
void init()
{
        add_action("do_open", "open");
        add_action("do_close", "close");
}
void close_door()
{
        object room;
        if(!( room = find_object("/d/shiliang/tingzi")) )
                room = load_object("/d/shiliang/tingzi");
        if(objectp(room))
        {
                delete("exits/east");
                        message("vision", "忽然間，水流翻湧，又把門合上了。\n", this_object());
                delete("exits/west", room);
                message("vision", "水流又悠然合上了。\n", room);
        }
}
int do_close(string arg)
{
        if (!query("exits/east"))
                return notify_fail("已經沒有出路了！\n");
        if (!arg || (arg != "door" && arg != "east"))
                return notify_fail("你要關什麼？\n");
        message_vision("$N點了點頭。\n", this_player());
        remove_call_out("close_door");
        call_out("close_door", 2);
        return 1;
}
int do_open(string arg)
{
        object room;
        if (query("exits/east"))
                return notify_fail("已經有出路了！\n");
        if (!arg || (arg != "door" && arg != "east"))
                return notify_fail("你要開什麼？\n");
        if(!( room = find_object(__DIR__"tingzi")) )
                room = load_object(__DIR__"tingzi");
        if(objectp(room))
        {
                set("exits/east",__DIR__"tingzi");
                message_vision("$N用力把破鐵門打了開來。\n", this_player());
                set("exits/west", __FILE__, room);
                message("vision", "忽然間，水流分開，露出一條出路。\n", this_object());
                remove_call_out("close_door");
                call_out("close_door", 2);
        }
        return 1;
}