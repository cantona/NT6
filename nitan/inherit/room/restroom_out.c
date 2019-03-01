inherit ROOM;

void init()
{
        add_action("do_knock", "knock");
        add_action("do_push",  "push");
}
int is_open() {return stringp(query("exits/"+query("door_dir")));}
varargs void open_door(object ob)
{
        if (objectp(ob))
                set("exits/"+query("door_dir"),ob);
        else
          set("exits/"+query("door_dir"),query("restroom"));
}
void close_door(){        delete("exits/"+query("door_dir"));}

int close_men()
{
        object room;

        room = find_object(query("restroom"));
        if(!objectp(room)) room = load_object(query("restroom"));
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
        else message("vision", "發現錯誤，請通知巫師解決。.\n", room);
}

int do_knock(string arg)
{
        object room;

        if (is_open())
        return notify_fail(query("door_name")+"已經是開著了。\n");

        if (!arg || (arg != "door" && arg != "men"))
        return notify_fail("你要敲什麼？\n");

        room = find_object(query("restroom"));
        if(! objectp(room) )
        room = load_object(query("restroom"));        

        if(objectp(room))
        {
                message("vision","外面傳來一陣敲門聲，你從門縫往外一瞧，是"+query("name", this_player())+"一臉焦急地站在門外，\n看樣子也想進來休息。\n",room);
                if (room->query_sleeping_person() > 0)
                {
                message_vision(
"$N剛輕輕地敲了一下門，就聽見裡面傳出一陣雷鳴般的鼾聲，\n"
"顯然裡面的人睡得跟死豬似的，怎麼敲都沒用了。\n",
                        this_player());
                }
                else if (room->query_inside_person() > 0)
                {
                        switch( random(2) )
                        {
                                case 0:
                                message_vision(
"$N輕輕地敲了敲門，只聽見裡面有人很不耐煩地吼到：\n"
"“剛躺下就來敲門！我睡著了，聽不見！！！”\n",        this_player());
                                        break;
                                case 1: 
                                        message_vision(
"$N輕輕地敲了敲門，只聽見裡面有些響動，\n"
"好象有人在踱來踱去，拿不定主意是否開門。\n", this_player());
                                        break;
                        }                   
                }
                else
                {
                message_vision("$N輕輕地敲了敲門：咚、咚、咚．．．咚、咚、咚．．．\n",this_player());
                }
        }
        return 1;
}

int do_push(string arg)
{
        object room;

        if (is_open())
        return notify_fail("門已經是開著了。\n");

        if (!arg || (arg != "door" && arg != "men"))
        return notify_fail("你要推什麼？\n");

        room = find_object(query("restroom"));
        if(! objectp(room) )
        room = load_object(query("restroom"));        
        
        if(objectp(room))
        {
                if( room->query_inside_person()<=0 )
                {
                        open_door();
                        message_vision("$N輕輕地把門推開。\n", this_player());
                        room->open_door(__FILE__);
                        remove_call_out("close_men");
                        call_out("close_men", 10);
                }
                else 
                {
                        message_vision("$N想把門推開，卻發覺門被人從裡面閂上了。\n",this_player());
                }
        }

        return 1;
}

string look_men()
{
        object room;

        if (is_open()) return (query("open_door_msg"));

        if(!objectp( room = find_object(query("restroom"))) )
        room = load_object(query("restroom"));

        if( objectp(room) && room->query_person_inside() > 0 )
                return (query("inside_msg"));
        return (query("no_one_msg"));
}

