// room: /d/baituo/barn
// Jay 10/8/96

inherit ROOM;

void create()
{
        set("short", "蛇舍");
        set("long", @LONG
這是歐陽世家的蛇舍，屋裡到處都是毒蛇，牆上有一張「蛇經」
(shejing)，角落擺了一堆捕蛇用的竹簍(zhulou)。
LONG );
        set("exits", ([ 
                "north" : __DIR__"road2",
                "south" : __DIR__"road1",
        ]));
        set("item_desc", ([
                "shejing" : 
                "歐陽世家訓蛇密法：當馭獸術達到三十級以上，可嘗試將毒蛇變(bian)成蛇杖，\n"
                "蛇杖乃是歐陽世家的獨門兵器。也可以把蛇杖變回毒蛇，驅使害人。\n",
                "zhulou" : "一堆捕蛇用的竹簍，歐陽世家的人想要捕蛇時，可以來這裡拿(take)。\n",
        ]));
        set("objects", ([ 
                __DIR__"npc/snake" : 3,
         ]) );

        set("coor/x", -49970);
        set("coor/y", 20090);
        set("coor/z", 30);
        setup();
}


void init()
{
        add_action("do_lingwu","lingwu");
        add_action("do_take","take");
}

int do_lingwu(string arg)
{
        object me = this_player();
        int level, check;

        level = (int)me->query_skill("poison",1);
        check = level*level*level;

        if (!arg || arg!="shejing") 
                return notify_fail("你要領悟什麼？\n");
        
        if( !query("family", me) || query("family/family_name", me) != "歐陽世家" )
                return notify_fail("你是未入白駝，難悟白駝蛇經。\n");

        if ( level < 30) 
                return notify_fail("經中所言對你過于高深，你無法領悟。\n");

        if ( level > 100) 
                return notify_fail("經中所言對你太淺，沒有任何幫助。\n");

        if( check>query("combat_exp", me)*10 )
                return notify_fail("你實戰經驗不足，無法領悟。\n");

        if( query("jing", me)<30 )
                return notify_fail("你精神無法集中。\n");

        me->receive_damage("jing", 20);
        me->improve_skill("poison",query("int", me));
        write("你鑽研蛇經，領悟了施毒的法門。\n");
        return 1;
}

int do_take(string arg)
{
        object me = this_player(), obj, fire;

      if( query("family/family_name", me) != "歐陽世家")return notify_fail("你不是歐陽世家的亂拿什麼？\n");

        if (!arg && arg != "zhulou" && arg != "basket" ) 
                return notify_fail("你要拿什麼？\n");

        if( time()-query_temp("zhulou_last_taked", me)<180 )
            return notify_fail("你已經拿過個竹簍了，等會再來拿吧。\n");

        obj = new(__DIR__"obj/zhulou");
        obj->move(me);
        set("keeper",query("id",  me), obj);
        obj->set("long",
                "一個竹條編成的簍子，是歐陽世家的人專門用來捕(catch)蛇的。\n"
                "簍子外邊貼了一張小紙片，上面寫著□"+me->name()+"□。\n"
        );
        message_vision("$N在蛇舍角落找出了一個竹簍。\n", me );
        set_temp("zhulou_last_taked", time(), me);
        fire = new("/d/xingxiu/obj/fire");
        fire->move(obj);

        return 1;
}