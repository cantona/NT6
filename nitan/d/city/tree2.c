inherit ROOM;

void create()
{
        set("short", "大榕樹上");
        set("long", @LONG
人説大樹底下好乘涼，沒想到大樹上更涼快。這棵大榕樹真不愧
為千年神木，至今仍綠葉繁茂。當你抬頭往上看的時候似乎有個影在
樹梢之間移動，不過也許是風吹動所造成的錯覺。
LONG
        );

        set("exits", ([
                "down": __DIR__"tree",
                "east"  : "/clone/game/mjroom",
                "west"  : "/clone/game/changan_dufang",
        ]));
        
        set("no_fight", 1);

        setup();
}

void init()
{
        add_action("do_jump","climb");
}

int do_jump(string arg)
{
        object me;
        
        me = this_player();
        if( !arg || arg != "down") 
                return notify_fail("你要往哪個方向爬？\n");

        if( query("gender", me) != "女性" )
                message("vision",
                        me->name() + "氣喘噓噓的抓住樹幹，屁股一扭一扭地往下爬去。\n",
                        environment(me), ({me}) );
        else 
        if( query("age", me)<40 && query("per", me)>24 )
                message("vision",
                        me->name() + "象仙子般繼續向下飄去，轉瞬即逝。\n",
                        environment(me), ({me}) );
        else 
                message("vision",
                        me->name() + "戰戰兢兢的抓住樹幹往下爬去。\n",    environment(me), ({me}) );
        
        me->move(__DIR__"tree");
     
        if( query("gender", me) != "女性" )
                message("vision",
                        me->name() + "氣喘噓噓地從上面爬了下來。\n",
                        environment(me), ({me}) );
        else 
        if( query("age", me)<40 && query("per", me)>24 )
                message("vision","一陣清香飛來，你定眼一看，"+
                        me->name() + "已經婷婷玉立在你眼前。\n",
                        environment(me), ({me}) );   
          
        else 
                message("vision", me->name() + "戰戰兢兢地從上面爬了下來。\n", 
                        environment(me), ({me}) );   
        
        return 1;
}   

int valid_leave(object me, string dir)
{
        if ( dir=="down" && !wizardp(me))
                return notify_fail("這裏沒法直接走，看來你只能爬(climb)下去！\n");

        return 1;
}
