// Room: xiuxishi.c 休息室
// By Marz

inherit ROOM;

void init();
void close_men();
int do_open(string arg);
int do_close(string arg);
int valid_leave(object me, string dir);

void create()
{
        set("short", "休息室");
        set("long", @LONG
這是間整潔的廂房，因門窗常閉著，光線很昏暗。房裡別無他物，
只有中間放著一張收拾得舒舒服服的大床，看著就讓人想睡覺。
LONG );
        set("no_clean_up", 0);
        set("sleep_room", 1);
        set("no_fight", 1);
        setup();
}

void init()
{
        add_action("do_open", "open");
        add_action("do_close", "close");
}

void close_men()
{
        object room;

        if(!( room = find_object(__DIR__"jingxiu")) )
                room = load_object(__DIR__"jingxiu");
        if(objectp(room))
        {
                delete("exits/north");
                        message("vision", "門吱吱呀呀地自己合上了。\n", this_object());
                delete("exits/south", room);
                message("vision", "門吱吱呀呀地自己合上了。\n", room);
        }
}

int do_close(string arg)
{
        object room;

        if(!( room = find_object(__DIR__"jingxiu")) )
                room = load_object(__DIR__"jingxiu");

        if (!arg || (arg != "men" && arg != "door"))
                return notify_fail("你要關什麼？\n");

        if (!query("exits/north"))
                return notify_fail("門已經是關著的了。\n");

        message_vision("$N輕手輕腳的把門關上了。\n", this_player());
        delete("exits/north");

        if(objectp(room))
        {
                delete("exits/south", room);
                message("vision", "門被人從裡面關上了了。\n", room);
        }

        return 1;
}

int do_open(string arg)
{
        object room;
        object me = this_player();

        if (!arg || (arg != "men" && arg != "door" && arg != "south"))
                return notify_fail("你要開什麼？\n");

        if (query("exits/north"))
                return notify_fail("大門已經是開著了。\n");

        if(!( room = find_object(__DIR__"jingxiu")) )
                room = load_object(__DIR__"jingxiu");

        if(objectp(room))
        {
                set("exits/north", __DIR__"jingxiu");
                message_vision("$N輕手輕腳地把門打開。\n", this_player());
                set("exits/south", __FILE__, room);

                if( query_temp("sleeped", me) )
                {
                message("vision","吱地一聲，"+query("name", me)+"精神煥發地從裡
面把門打開了。\n",
                room);
                } else
                {
                message("vision","梆地一聲，"+query("name", me)+"從裡面把門打開
，一臉的不耐煩。\n",
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
        if (query_temp("person_inside") <= 0)
                delete_temp("person_inside");

        return 1;
}