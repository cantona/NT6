// jingxiu.c 靜修室

inherit ROOM;

void init();
int close_men();
int force_open(object room);
int do_push(string arg);
int do_knock(string arg);
int valid_leave(object me, string dir);
string look_men();

void create()
{
        set("short", "靜修室");
        set("long", @LONG
這裏是靜修室，屋中有一些胡家弟子在這裏打坐練功。南面有一
扇小門(men)，裏面隱隱傳來了鼾聲。
LONG );
        set("exits", ([
                "east" : __DIR__"houyuan",
        ]));

        set("item_desc",([
                "men"  : (: look_men :),
        ]));

        set("objects", ([
                "/clone/weapon/mudao" : 3,
        ]));

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

        if (!( room = find_object(__DIR__"xiuxishi")) )
                room = load_object(__DIR__"xiuxishi");

        if (objectp(room))
        {
                delete("exits/south");
                message("vision", "門吱吱呀呀地自己合上了。\n", this_object());
                delete("exits/north", room);
                message("vision", "門吱吱呀呀地自己合上了。\n", room);
        } else message("vision", "ERROR: men not found(close).\n", room);

        return 1;
}

int do_knock(string arg)
{
        object room;

        if (!arg || (arg != "door" && arg != "men"))
                return notify_fail("你要敲什麼？\n");

        if (query("exits/south"))
                return notify_fail("大門已經是開着了。\n");

        if (!( room = find_object(__DIR__"xiuxishi")) )
                room = load_object(__DIR__"xiuxishi");

        if(objectp(room))
        {
                if( query_temp("sleeping_person", room)>0 )
                {
                        message_vision("$N剛輕輕地敲了一下門，就聽見裏面傳出一陣雷鳴般的鼾聲，\n"
                                       "顯然裏面的人睡得跟死豬似的，怎麼敲都沒用了\n",
                                       this_player());
                } else
                if( query_temp("person_inside", room)>0 )
                {
                        switch (random(2))
                        {
                        case 0:
                                message_vision("$N輕輕地敲了敲門，只聽見裏面有人很不耐煩地吼到：\n"
                                               "剛躺下就來敲門！我睡着了，聽不見！！！\n",
                                               this_player());
                                break;
                        case 1:
                                message_vision("$N輕輕地敲了敲門，只聽見裏面有些響動，\n"
                                               "好像有人在踱來踱去，拿不定主意是否開門。\n",
                                               this_player());
                                break;
                        }
                } else
                {
                        delete_temp("sleeping_person", room);
                        message_vision("$N輕輕地敲了敲門：咚、咚、咚．．．咚、咚、咚．．．\n",
                                       this_player());
                }
        }

        if (objectp(room))
                message("vision",  "外面傳來一陣敲門聲，你從門縫往外一瞧，是" +
                        this_player()->name() + "一臉焦急地站在門外，\n"
                        "看樣子也想進來休息。\n", room);
        return 1;
}

int do_kick(string arg)
{
        object me;
        object room;

        if (!arg || (arg != "door" && arg != "men"))
                return notify_fail("你要踢什麼？\n");

        if (query("exits/south"))
                return notify_fail("大門開着，你踢它幹嗎？。\n");

        if (!( room = find_object(__DIR__"xiuxishi")) )
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
                        set("exits/south", __DIR__"xiuxishi");
                        set("exits/north", __FILE__, room);
                        remove_call_out("close_men");
                        call_out("close_men", 10);
                }
        }

        return 1;
}

int do_push(string arg)
{
        object room;

        if (query("exits/south"))
                return notify_fail("門已經是開着了。\n");

        if (!arg || (arg != "door" && arg != "men"))
                return notify_fail("你要推什麼？\n");

        if (!(room = find_object(__DIR__"xiuxishi")))
                room = load_object(__DIR__"xiuxishi");

        if (objectp(room))
        {
                    if( query_temp("person_inside", room) <= 0 )
                    {
                        delete_temp("person_inside", room);
                        set("exits/south", __DIR__"xiuxishi");
                        message_vision("$N輕輕地把門推開。\n", this_player());
                        set("exits/north", __FILE__, room);
                        message("vision", "有人從外面把門推開了。\n", room);
                        remove_call_out("close_men");
                        call_out("close_men", 10);
                } else
                {
                        message_vision("$N想把門推開，卻發覺門被人從裏面閂上了。\n",
                                       this_player());
                }
        }

        return 1;
}

string look_men()
{
        object room;

        if (!( room = find_object(__DIR__"xiuxishi")))
                room = load_object(__DIR__"xiuxishi");

        if( objectp(room) && query_temp("person_inside", room)>0 )
                return "門上掛了個牌子：休息中、請毋打擾\n";

        return "門上掛了個牌子：休息室\n";
}

int valid_leave(object me, string dir)
{

        object room;

        if (!( room = find_object(__DIR__"xiuxishi")) )
                room = load_object(__DIR__"xiuxishi");

        if (objectp(room) && dir == "south")
        {
                addn_temp("person_inside", 1, room);
                // will open the door if ppl inside stay too long
                remove_call_out("force_open");
                call_out("force_open", 599, room);
        }

        return ::valid_leave(me, dir);
}

int force_open(object room)
{
        if (! objectp(room)) return 0;
            if( query_temp("person_inside", room) <= 0)return 0;

        delete_temp("person_inside", room);
            set("exits/north", __DIR__"xiuxishi");
            set("exits/south", __FILE__, room);
            message("vision", "外面突然響起粗重的腳步聲，由遠而近，到門前停了下來．．．\n"
                          "幾個弟子一下子把門打開，伸個頭進來，罵罵咧咧道：什麼鳥人\n"
                          "在裏面磨磨蹭蹭的？\n", room);
            remove_call_out("close_men");
            call_out("close_men", 10);

            return 1;
}