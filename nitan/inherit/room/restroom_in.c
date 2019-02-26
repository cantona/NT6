inherit ROOM;

void init()
{
        add_action("do_open", "open");
        add_action("do_close", "close");
        remove_call_out("force_open");
        call_out("force_open",300);
}

int is_open() {return stringp(query("exits/"+query("door_dir")));}
varargs void open_door(object ob)
{
        if (objectp(ob))
                set("exits/"+query("door_dir"),ob);
        else
          set("exits/"+query("door_dir"),query("outroom"));
}
void close_door(){        delete("exits/"+query("door_dir"));}
int query_inside_person()
{
        object *inv;
        int i,count;
        
        inv = all_inventory();
        count = 0;
        for (i=0;i<sizeof(inv);i++)
                if (userp(inv[i])) count++;
        
        return count;
}
int query_sleeping_person()
{
        object *inv;
        int i,count;
        
        inv = all_inventory();
        count = 0;
        for (i=0;i<sizeof(inv);i++)
                if( userp(inv[i]) && query_temp("noliving/sleeped", inv[i]))count++;
        
        return count;
}

void close_men()
{
        object room;

        if(!objectp( room = find_object(query("outroom")) ))
                room = load_object(query("outroom"));
        if(objectp(room))
        {
                if (  is_open() ) 
                {
                        close_door();
                        message("vision", query("door_name")+"吱吱呀呀地自己合上了。\n", this_object());
                        room->close_door();
                        message("vision", query("door_name")+"吱吱呀呀地自己合上了。\n", room);
                }
        }
}

int do_close(string arg)
{
        if ( !is_open() )
                return notify_fail("門已經是關着的了。\n");

        if (!arg || (arg != "men" && arg != "door"))
                return notify_fail("你要關什麼？\n");

        message_vision("$N想把門關上。\n", this_player());

        remove_call_out("close_men");
        call_out("close_men", 0);

        return 1;
}

int do_open(string arg)
{
        object room;
        object me = this_player();

        if (is_open())
                return notify_fail("大門已經是開着了。\n");

        if (!arg || (arg != "men" && arg != "door" && arg != query("door_dir")))
                return notify_fail("你要開什麼？\n");

        if(!objectp( room = find_object(query("outroom"))) )
                room = load_object(query("outroom"));
        if(objectp(room))
        {
                open_door();
                message_vision("$N輕手輕腳地把門打開。\n", this_player());
                room->open_door(__FILE__);
                
                if( query_temp("sleeped", me) )
                message("vision","吱地一聲，"+query("name", me)+"精神煥發地從裏面把門打開了。\n",room);
                else
                message("vision","梆地一聲，"+query("name", me)+"從裏面把門打開，一臉的不耐煩。\n",room);
                
                remove_call_out("close_men");
                call_out("close_men", 10);
        }

        return 1;
}

int force_open()
{
        object room;
        if(!objectp( room = find_object(query("outroom"))) )
                room = load_object(query("outroom"));
        if( !objectp(room) )        return 0;
        if( query_inside_person() <= 0 )        return 0;
        
        open_door();
        room->open_door(__FILE__);
        message("vision","外面突然響起粗重的腳步聲，由遠而近，到門前停了下來．．．\n"+query("force_name")+"啪地把門打開，伸個頭進來，一臉狐疑：呆大半天了還不出去，搞什麼鬼？\n", room);
        remove_call_out("close_men");
        call_out("close_men", 10);
}