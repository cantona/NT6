// fangjian2.c
// Modified by Winder June.25 2000

inherit ROOM;

void create()
{
        set("short", "房間");
        set("long", @LONG
這是一間佈置成卧室模樣的小房間，有張石牀，牀上擺着個小小的
木頭製成的搖籃，牆壁上懸着一個七絃琴，絃線都已經斷了。
LONG );
       set("exits", ([
               "south" : __DIR__"shiji2",
       ]));
       set("no_clean_up", 0);
        set("coor/x", -50010);
        set("coor/y", -21030);
        set("coor/z", -40);
        setup();
}

void init()
{
        add_action("do_shout", "shout");
}

int do_shout(string arg)
{
        object me;
        me = this_player();

        if( !arg || arg=="" ) return 0;

        if( arg=="芝麻開門") 
        {
                tell_object(me,"你氣運丹田，對着牆壁大喝一聲：“芝麻開門！”\n");
                if( random(100)>50 || ((query("family", me)) && query("family", me)["master_name"] == "逍遙子") )
                {
                message("vision", "過了一會兒，你只聽到一陣轟隆隆的響聲，出現了一道暗門。\n", me);
                set("exits/down", __DIR__"shishi4");
                remove_call_out("close");
                call_out("close", 5, this_object());
                }
        else
                {
                message("vision", "房間裏到處迴盪着你的聲音，震得你的耳朵翁翁作響。\n", me);
                me->receive_wound("qi",20);
                me->unconcious();
                }
                return 1;
        }
}

void close(object room)
{
        message("vision","一陣轟隆隆的響聲過後，石門又緩緩地關上了。\n", room);
        delete("exits/down", room);
}