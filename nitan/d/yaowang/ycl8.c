inherit ROOM;
string p = "";
void create()
{
        set("short", "羊腸小路");
        set("long", @LONG
這是一條蜿蜒曲折的小路，右面是一小片低矮的樹林，左面
是陡峭的山壁。地上滿是亂石子，有的還很尖利，看樣子這裡很
少有人來。正前方是一堆粗大的原木擋住了去路。
LONG
        );
        set("exits", ([ /* sizeof() == 1 */
  "south" : __DIR__"ycl7",
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
                tell_object(me, "原木已經移開了。\n");
                return 1;
        }

        if(sizeof(p) > 10)
                p = "";

        switch (arg)
        {
                case "left":
                        p = "l";
                        tell_object(me, "你向左面使勁推了一下原木。\n");
                        return 1;
                case "right":
                        p += "r";
                        tell_object(me, "你向右面使勁推了一下原木。\n");
                        if( (sizeof(p)>5) && (p[<6..] == "lrrrrr") && (query_temp("murong_ask", me) || query("family/master_name",me) == "石萬嗔") )
                        {
                                p = "";
                                if(!query("exits/north"))
                                {
                                        set("exits/north", __DIR__"ycl9");
                                        call_out("remove_north", 5);
                                        tell_room(__FILE__, "原木向左面一動，露出了一個縫隙。\n");
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

void remove_north()
{
        if("exits/north")
        {
                delete("exits/north");
                p = "";
        }
}
