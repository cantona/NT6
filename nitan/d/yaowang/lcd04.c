inherit ROOM;

protected string p = "";

void create()
{
        set("short", "泥濘小路");
        set("long", @LONG
這是一條的小岔路，地上總是像剛下過雨一樣泥濘不堪，和
着一些腐爛的枯枝敗葉，臭氣熏天。正前方是塊大石頭，石頭上
滿是青苔和爛藤，擋住了西方的道路，不知道能否推開(push)石頭，
但實在又不知道往哪個方向推。
LONG
        );
        set("exits", ([ /* sizeof() == 1 */
  "northeast" : __DIR__"lcd03",
]));

        set("outdoors", "yaowang");
        setup();
}

void init()
{
        add_action("do_push", "push");
}

int do_push(string arg)
{
        object me = this_player();

        if( query("exits/west") )
        {
                tell_object(me, "石頭已經移開了。\n");
                return 1;
        }

        if(sizeof(p) > 10)
                p = "";

        switch (arg)
        {
                case "left":
                        p = "l";
                        tell_object(me, "你向左面使勁推了一下石頭，沾了一手泥。\n");
                        return 1;
                case "right":
                        p += "r";
                        tell_object(me, "你向右面使勁推了一下石頭，沾了一手泥。\n");
                        if( (sizeof(p) > 5) && (p[<6..] == "lrrrrr") )
                        {
                                p = "";
                                if(!query("exits/west"))
                                {
                                        set("exits/west", __DIR__"lcd05");
                                        call_out("remove_west", 5);
                                        tell_room(__FILE__, "石頭向右面一動，露出了一個縫隙。\n");
                                        return 1;
                                }
                                return 1;
                        }
                        return 1;
                default:
                        tell_object(me, "你要往哪個方向推？\n");
                        return 1;
        }
}

protected void remove_west()
{
        if("exits/west")
        {
                delete("exits/west");
                p = "";
        }
}
