// This is a room made by wsl.
inherit ROOM;
int do_zuan(string arg);
void create()
{
    set("short", "石道");
        set("long", @LONG
此路又是另一番景象，兩旁松柏相掩，四對石翁仲背靠松林，想
不到在着地下洞穴中也有如此浩大的松林，要不是光線暗了點，根本
看不出和地面有什麼區別。
LONG );
    set("exits", ([
       "south" :__DIR__"shidao",
]));
    setup();
}
void init()
{
        add_action("do_zuan", "zuan");
}
int do_zuan(string arg)
{
        object ob,room;
        ob = this_player();
        room=load_object("/d/changan/qinhuang/songlin.c");
        if( !arg || arg=="" ) return 0;
        if( arg=="松林" ) {
                message_vision("$N壯了壯膽，一頭鑽進了松林裏。\n", ob);
        ob->move(room);
        write("你回頭看了看，已經沒有退路了。\n");
        tell_object(ob, "你在松林裏走了很久很久.......\n") ;
        call_out("songlin", 20 , ob );
        return 1;
        }
}
void songlin(object ob)
{
        if(!ob) return;
        tell_object(ob, "你累了個半死，終於走出了這片松林。\n");
        ob->move("/d/changan/qinhuang/dadian.c");
        set("food", 1, ob);
        set("water", 1, ob);
}