// xiaolu2.c

inherit ROOM;

void create()
{
        set("short", "小山路");
        set("long", @LONG
這裡是華山的一條小山路，地勢較為平緩，不似其它地方那麼險
峻。你走在這裡，四周靜悄悄的，你就象走進了一個世外桃源。東面
好象有一扇竹門(men)。
LONG );
        set("exits", ([ /* sizeof() == 1 */
                "southwest" : __DIR__"xiaolu1",
        ]));
        set("outdoors", "huashan" );

        setup();
}

void init()
{
        add_action("do_knock", "knock");
        add_action("do_push", "push");
        add_action("do_kick", "kick");
}

int close_men()
{
        object room;

        if(!( room = find_object(__DIR__"xiuxishi")) )
                room = load_object(__DIR__"xiuxishi");

        if(objectp(room) && query("exits/east"))
        {
                delete("exits/east");
                message("vision", "門吱吱呀呀地自己合上了。\n", this_object());
                delete("exits/west", room);
                message("vision", "門吱吱呀呀地自己合上了。\n", room);
        }
}

int do_knock(string arg)
{
        object room;

        if (!arg || (arg != "door" && arg != "men"))
                return notify_fail("你要敲什麼？\n");

        if (query("exits/east"))
                return notify_fail("大門已經是開著了。\n");

        if(!( room = find_object(__DIR__"xiuxishi")) )
                room = load_object(__DIR__"xiuxishi");
        
        if(objectp(room))
        {
                if( query_temp("sleeping_person", room)>0 )
                {
                message_vision(
"$N剛輕輕地敲了一下門，就聽見裡面傳出一陣雷鳴般的鼾聲，\n"
"顯然裡面的人睡得跟死豬似的，怎麼敲都沒用了\n",
                        this_player());
                }
                else if( query_temp("person_inside", room)>0 )
                {
                        switch( random(2) )
                        {
                                case 0:
                                message_vision(
"$N輕輕地敲了敲門，只聽見裡面有人很不耐煩地吼到：\n"
"剛躺下就來敲門！我睡著了，聽不見！！！\n",        this_player());
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
                        delete_temp("sleeping_person", room);
                        message_vision("$N輕輕地敲了敲門：咚、咚、咚．．．咚、咚、咚．．．\n",
            this_player());
                }
        }

        if(objectp(room))
                    message("vision",
                            "外面傳來一陣敲門聲，你從門縫往外一瞧，是" +
                        this_player(query("name", ))+"一臉焦急地站在門外，\n"
                            "看樣子也想進來休息。\n", room);
        
        return 1;
}

int do_push(string arg)
{
        object room;

        if (!arg || (arg != "door" && arg != "men"))
                return notify_fail("你要推什麼？\n");

        if (query("exits/east"))
                return notify_fail("門已經是開著了。\n");

        if(!(room = find_object(__DIR__"xiuxishi")))
                room = load_object(__DIR__"xiuxishi");
        
        if(objectp(room))
        {
                if( query_temp("person_inside", room) <= 0 )
                {
                        delete_temp("person_inside", room);
                        set("exits/east", __DIR__"xiuxishi");
                        message_vision("$N輕輕地把門推開。\n", this_player());
                        set("exits/west", __FILE__, room);
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

int do_kick(string arg)
{
        object me;
        object room;

        if (!arg || (arg != "door" && arg != "men"))
                return notify_fail("你要踢什麼？\n");

        if (query("exits/east"))
                return notify_fail("大門開著，你踢它幹嗎？。\n");

        if(!( room = find_object(__DIR__"xiuxishi")) )
                room = load_object(__DIR__"xiuxishi");

        me = this_player();
        if(objectp(room))
        {
                if( query("qi", me)<40 )
                {
                        message_vision("$N飛起一腳，狠狠的踢中大門，然而大門紋絲不動。\n", me);
                        message("vision", "就聽“砰”的一聲巨響，外面似乎有人發火踢門了。\n", room);
                        tell_object(me, "你覺得腳趾幾乎都要斷了！\n");
                        me->unconcious();
                } else
                if( query("qi", me)<100 )
                {
                        message_vision("$N飛起一腳，狠狠的踢中大門，然而大門只是晃了一下。\n", me);
                        message("vision", "就聽“砰”的一聲巨響，外面似乎有人發火踢門了。\n", room);
                        tell_object(me, "你覺得腳非常的痛！\n");
                        set("qi", 20, me);
                        me->receive_wound("qi", 20);
                } else
                {
                        message_vision("$N飛起一腳，狠狠將大門踹開。\n", me);
                        message("vision", "就聽“砰”的一聲巨響，門忽的一下子就開了，嚇了"
                                          "你一跳。仔細一看，原來是" + me->name() +
                                          "氣勢洶洶的站在門口。\n", room);
                        me->receive_damage("qi", 100);
                        delete_temp("person_inside", room);
                        set("exits/east", __DIR__"xiuxishi");
                        set("exits/west", __FILE__, room);
                        remove_call_out("close_men");
                        call_out("close_men", 10);
                }
        }

        return 1;
}

string look_men()
{
        object room;

        if (query("exits/east"))
                return ("門上掛了個牌子：華山小築\n");

        if(!( room = find_object(__DIR__"xiuxishi")) )
                room = load_object(__DIR__"xiuxishi");

        if( objectp(room) )
        if( query_temp("person_inside", room)>0 )
        {
                return ("門上掛了個牌子：打擾一次、罰跪三天!\n");
        } 
    
        return ("門上掛了個牌子：華山派休息室\n");
}

int valid_leave(object me, string dir)
{
        object room;
            
        if(!( room = find_object(__DIR__"xiuxishi")) )
                room = load_object(__DIR__"xiuxishi");

        if(objectp(room) && dir == "east")
        {
                addn_temp("person_inside", 1, room);
                // will open the door if ppl inside stay too long 
                remove_call_out("force_open");
                call_out("force_open", 300, room);
        }                

        return ::valid_leave(me, dir);
}

int force_open(object room)
{
        if(!objectp(room))
                return 0;

        if( query_temp("person_inside", room) <= 0 )
                return 0;
    
        delete_temp("person_inside", room);
        set("exits/east", __DIR__"xiuxishi");
        set("exits/west", __FILE__, room);
        message("vision", "外面突然響起粗重的腳步聲，由遠而近，到門前停了下來．．．\n"
                              "陸大有啪地把門打開，伸個頭進來，一臉狐疑：呆大半天了還不出"
                          "去，搞什麼鬼？\n", room);
        remove_call_out("close_men");
        call_out("close_men", 10);
}