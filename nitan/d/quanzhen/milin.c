// Code of ShenZhou
// road: /zhongnan/milin4.c

inherit ROOM;

void create()
{

        set("short","樹林");

        set("long", @LONG
走在林中，你只聞錚錚琴聲，一股淡淡白煙，帶著極甜的花香，
自密林深處傳出。一群乳白色的蜜蜂在你身旁飛來飛去。不論往哪ㄦ
走盡是茂密的樹林。附近有一團花叢(flowers)。
LONG );

        set("item_desc",([
                "flowers" : "這花叢既深且密，你向後看去幾忽看不到底，花間有些孔隙，似乎經常有些動物在叢中鑽來鑽去。\n",
        ]));

        set("exits",([ 
                "north" : __DIR__"shulin6",
        ]));

        set("cost",2);
        set("outdoors", "quanzhen");
        setup();

}

void init()
{               
        add_action("do_push", "push");
        add_action("do_push", "tui");
        add_action("do_push", "zuan");
}

int do_push(){

        object room;
        object me=this_player();
        
        if (me->is_busy())
                return notify_fail("你現在正忙著哪！\n");

        if( query("hide_person", this_object()) )
                return notify_fail("你看見裡面有影子晃動，還是不鑽的好，別有什麼猛獸。\n");

        tell_object(me, "你輕輕地推開花木，向裡鑽了進去。\n");
        
        room = load_object("/d/quanzhen/flowers");
        
        set("hide_person", 1, this_object());
        
        me->move(room);
        return 1;

}