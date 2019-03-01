//Cracked by Kafei
// door1.c 華山後山小路密室石門前
// qfy 8/11/97

inherit ROOM;

void create()
{
        set("short", "石門前");
        set("long",
"石門(door)緊閉著，看起來似乎相當的厚。門上有兩個大石環，各自\n"
"嵌在兩個精雕的龍頭嘴裡。\n"
);

        set("exits", ([ /* sizeof() == 1 */
                "up" : __DIR__"stair",
        ]));

        set("item_desc",([
            "石門" : "石門上刻著「仗義江湖」四個古篆大字，四周皆是精致的浮雕。\n",
            "door" : "石門上刻著「仗義江湖」四個古篆大字，四周皆是精致的浮雕。\n",
        ]));

        set("cost", 0);
        setup();
}

void init()
{
        add_action("do_open", "open");
        add_action("do_close", "close");
}

int do_open()
{
        object me=this_player();

        if ( query_temp("open") ) {
                write("石門已經是開著的了！\n");
                return 1;
        }

        message_vision("$N運起內功，雙掌按在石門上，緩緩往後推去。\n", me);
        message_vision("石門在一陣轟響之後，慢慢地開啟了。\n", me);

        set("exits/enter", __DIR__"mishi");
        set("long", "石門敞開著，看起來約有一尺來厚。\n");
        set_temp("open", 1);
        remove_call_out("auto_close");
        call_out("auto_close", 5, this_object());

        return 1;
}

int do_close()
{
        object me=this_player();

        if ( !query_temp("open") ) {
                write("石門已經是關著的了！\n");
                return 1;
        }

        message_vision("$N運起內功，雙手抓在石門門環上，緩緩地往前拉。\n", me);
        message_vision("石門在一陣轟響之後，慢慢地關閉了。\n", me);

        set("long", "石門(door)緊閉著，看起來似乎相當的厚。門上有兩個大石環，各自\n嵌在兩個精雕的龍頭嘴裡。\n");
        delete("exits/enter");
        delete_temp("open");
        remove_call_out("auto_close");

        return 1;
}

void auto_close(object room)
{
        if( query_temp("open", room)){
                message("vision","石門突然發出一陣轟響，自動關閉起來。\n", room);
                set("long", "石門(door)緊閉著，看起來似乎相當的厚。門上有兩個大石環，各自\n嵌在兩個精雕的龍頭嘴裡。\n");
                delete("exits/enter", room);
                delete_temp("open", room);
        }
}       
