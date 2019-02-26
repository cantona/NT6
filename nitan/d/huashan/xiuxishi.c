// Room: xiuxishi.c

inherit ROOM;

void init();
void close_men();
int do_open(string);
int do_close(string);

void create()
{
        set("short", "華山小築");
        set("long", @LONG
這是間整潔的廂房，因門窗常閉着，光線很昏暗。房裏別無他物，
只有中間放着一張收拾得舒舒服服的大牀，看着就讓人想睡覺。
LONG );

        set("sleep_room", 1);
        set("no_fight", 1);

        setup();
}

void init()
{
        object me = this_player();
        add_action("do_open", "open");
        add_action("do_close", "close");

        if( query_temp("xunshan", me))set_temp("xunshan/yunu", 1, me);
}

void close_men()
{
        object room;

        if(!( room = find_object(__DIR__"xiaolu2")) )
                room = load_object(__DIR__"xiaolu2");

        if(objectp(room) && query("exits/west"))
        {
                delete("exits/west");
                message("vision", "門咿咿呀呀地自己合上了。\n", this_object());
                delete("exits/east", room);
                message("vision", "門咿咿呀呀地自己合上了。\n", room);
        }
}

int do_close(string arg)
{
        object room;

        if (!arg || (arg != "men" && arg != "door"))
                return notify_fail("你要關什麼？\n");

        if (!query("exits/west"))
                return notify_fail("門已經是關着的了。\n");

        message_vision("$N一伸手，把門關上了。\n", this_player());

        if(!( room = find_object(__DIR__"xiaolu2")) )
                room = load_object(__DIR__"xiaolu2");

        if(objectp(room))
        {
                message("vision", "門被人從裏面關上了。\n", room);
                delete("exits/west");
                delete("exits/east", room);
        }

        return 1;
}

int do_open(string arg)
{
        object room;
        object me = this_player();

        if (!arg || (arg != "men" && arg != "door" && arg != "west"))
                return notify_fail("你要開什麼？\n");

        if (query("exits/west"))
                return notify_fail("大門已經是開着了。\n");

        if(!( room = find_object(__DIR__"xiaolu2")) )
                room = load_object(__DIR__"xiaolu2");
        if(objectp(room))
        {
                set("exits/west", __DIR__"xiaolu2");
                message_vision("$N輕手輕腳地把門打開。\n", this_player());
                set("exits/east", __FILE__, room);
                
                if( query_temp("sleeped", me) )
                {
                message("vision","吱地一聲，"+query("name", me)+
                                  "精神煥發地從裏面把門打開了。\n",
                room);
                } else 
                {
                message("vision","梆地一聲，"+query("name", me)+
                                  "從裏面把門打開，一臉的不耐煩。\n",
                         room);
                }        
                
                remove_call_out("close_men");
                call_out("close_men", 10);
        }

        return 1;
}


int valid_leave(object me, string dir)
{
        object room;

        if ( !::valid_leave(me, dir) ) 
                return 0;
        
        addn_temp("person_inside", -1);        
        if ((int)query_temp("person_inside") <= 0)
                delete_temp("person_inside");        
        
        return 1;
}