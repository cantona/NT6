
inherit ROOM;

void check_trigger();
void on_board();
void arrive();
void close_passage();

void setup()
{
        object room;

        ::setup();

        if (room = find_object(query("boat")))
                delete("yell_trigger", room);
}

void init()
{
        add_action("do_yell", "yell");
}

int do_yell(string arg)
{
        string dir;

        if (! arg || arg == "") return 0;

        if (arg == "boat") arg = "船家";

        if( query("age", this_player())<14 )
                message_vision("$N使出吃奶的力氣喊了一聲：“" + 
                               arg + "”\n", this_player());
        else if( query("neili", this_player())>200 )
                message_vision("$N吸了口氣，一聲“" + arg + 
                               "”，聲音中正平和地遠遠傳"
                               "了出去。\n", this_player());
        else    message_vision("$N鼓足中氣，長嘯一聲：“" + arg + 
                               "！”\n", this_player());

        if (arg == "船家") 
        {
                check_trigger();
                return 1;
        }else message_vision(query("name", this_object())+"面上遠遠傳來一陣回聲：“"+arg+
                               "～～～”\n", this_player());

        return 1;
}

void check_trigger()
{
        object room;
        string myboat;

        if( query("exits/enter", this_object()) )
        {
                message("vision", "岸邊一隻渡船上的老艄公説道：正等着你呢，上來吧。\n",
                        this_object());
                return;
        }

        if( !(room=find_object(myboat=query("boat", this_object()))) )
                room = load_object(myboat);

        if (! (room = find_object(myboat))) 
        {
                message("vision", "ERROR: boat not found\n", this_object());
                return;
        }

        if( query("yell_trigger", room) )
        {
                message("vision","只聽得"+query("name", this_object())+"面上隱隱傳來：“別急嘛，"
                        "這兒正忙着吶……”\n", this_object() );
                return;
        }

        set("yell_trigger", 1, room);
        set("exits/enter", myboat, this_object());
        set("exits/out", base_name(this_object()), room);

        message("vision", "一葉扁舟緩緩地駛了過來，艄公將一塊踏腳"
                "板搭上堤岸，以便乘客\n上下。\n", this_object());
        message("vision", "艄公將一塊踏腳板搭上堤岸，形成一個向上"
                "的階梯。\n", room);

        remove_call_out("on_board");
        call_out("on_board", 15);
}

void on_board()
{
        object room;

        if( !query("exits/enter", this_object()) )
                return;

        message("vision","艄公把踏腳板收了起來，竹篙一點，扁舟向"+query("name", this_object())+"心駛去。\n",
                this_object());

        if (room = find_object(query("boat"))) 
        {
                delete("exits/out", room);
                message("vision", "艄公把踏腳板收起來，説了一聲“坐穩嘍”，"
                        "竹篙一點，扁舟向\n"+query("name", this_object())+"心駛去。\n",
                        room);
        }

        delete("exits/enter", this_object());

        remove_call_out("arrive");
        call_out("arrive", 20);
}

void arrive()
{
        object room;
        string myboat = query("boat");
        string myopp = query("opposite");

        if (room = find_object(myboat)) 
        {
                set("exits/out", myopp, room);
                message("vision", "艄公説“到啦，上岸吧”，隨即把一塊踏腳板"
                        "搭上堤岸。\n", 
                        room );
        }

        /*
        if( !(room = find_object(myopp)) )
                room = load_object(myopp);

        if( room = find_object(myopp) ) {
                set("exits/enter", myboat, room);
                message("vision", "一葉扁舟緩緩地駛了過來，艄公將一塊踏腳"
                        "板搭上堤岸，以便乘客\n上下。\n", 
                        room);
        }
        */       

        remove_call_out("close_passage");
        call_out("close_passage", 20);
}

void close_passage()
{
        object room;

        if (room = find_object(query("boat"))) 
        {
                delete("exits/out", room);
                message("vision","艄公把踏腳板收起來，把扁舟駛向"+query("name", this_object())+"心。\n",
                room);
                delete("yell_trigger", room);
        }

        /*
        if( room=query("opposite", find_object(this_object()))){
                delete("exits/enter", room);
                message("vision","艄公把踏腳板收了起來，竹篙一點，扁舟向"+query("name", this_object())+"心駛去。\n",
                        room);
        }
        */
}
