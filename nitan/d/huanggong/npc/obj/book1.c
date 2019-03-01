// book1.c
inherit ITEM;

int do_move(string arg);

void init()
{
        add_action("do_move", "move");
}

void create()
{
        set_name("帛書", ({"book"}));
        set_weight(500);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("long", "\n一封精裝的<<論語>>\n");
                set("unit", "幅");
                set("material", "paper");
                set("no_get", "\n住手,你豈可在此胡鬧!下去!\n");
        }
        setup();
}

int do_move(string arg)
{
        object me;
        object door;
        string dir;
        me = this_player();
        if (!arg||arg=="") return 0;
        if( arg=="book" ) {
                if( !query_temp("doorisok", me) )
                {
                        set_temp("doorisok", 1, me);
                        message_vision(
"\n$N試著移動畫卷，發現它可以左右推動...\n", this_player());
                }
                if(!objectp(present("door", environment(me))))
                {
                        message_vision(
"$N輕輕地挪動畫頁，突然一扇暗門出現在$N眼前。\n", this_player());
                        door = new("/d/beijing/obj/door");
                        door->move("/d/huanggong/shufang");
                }
        }
        if( sscanf(arg, "book %s", dir)==1 )
        {
                if( dir=="left" )
                {
                        message_vision(
"$N將畫卷往左移，只聽軋軋幾聲，畫卷又移回原位。\n", this_player());
                        if( !query_temp("pushdoor", me) )
                                set_temp("pushdoor", 1, me);
                        else
                                set_temp("pushdoor", 0, me);
                        return 1;
                }
                if( dir=="right" )
                {
                        message_vision(
"$N將畫卷往右移，只聽軋軋幾聲，畫卷又移回原位。\n", this_player());
                        if( query_temp("pushdoor", me) )
                        {
                                set_temp("doorisok", 1, me);
                                delete_temp("pushdoor", me);
                        }
                return 1;
                }
                else {
                        write("你要將畫卷移向那個方向？\n");
                        return 1;
                }
        }
        return 1;
}

