inherit ITEM;


void create()
{
        set_name("石刻棋盤", ({ "qi pan", "pan" }));
        set("long","這是一塊刻在巨石上的棋盤，上面放着一些棋子。\n");
        set_weight(1000);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "塊");
                set("value", 1000);              
                set("no_get","這塊棋盤是直接刻在巖石上的，無法拿取。\n");
                set("qizi",2);
        }
}

void init()
{
        add_action("do_get","get");
}

int do_get(string arg)
{
        object ob;
        string qizi,qipan;
        ob = this_player();
        if(arg == "qi pan" || arg == "pan" )
        {
                tell_object(ob,"這塊棋盤是直接刻在巖石上的，無法拿取。\n");
                return 1;
        }
        if(sscanf( arg, "%s from %s", qizi, qipan)!=2)return 0;
        if((qizi !="qi zi" && qizi !="zi")
        ||(qipan!="qi pan" && qipan != "pan") )return 0;
        if(present("yi zhe",environment(this_object()) ) )
        {
                tell_object(ob,"別人正在下棋，怎麼能把棋子拿走呢？\n");
                return 1;
        }
        if(query("qizi") <= 0 )
        {
                tell_object(ob,"棋子已經被別人拿光了。\n");
                return 1;
        }
        message_vision("$N從棋盤上拿下一把棋子。\n",ob);
        add("qizi",-1);
        new(__DIR__"qizi")->move(ob);
        return 1;
}
