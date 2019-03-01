// Room: /d/gaochang/zoulange.c
// Last Modified by Winder on Jul. 15 2000


inherit ROOM;
string look_writing();


void create()
{
        set("short", "走廊");
        set("long", @LONG
這裡是後殿走廊。房頂一側支在南面的高牆上，另一側則與北邊般
若堂的屋頂相連。彩樑畫棟，抬眼望去，連頂棚也用彩漆繪滿了各種飛
天的圖形，每幅畫似乎都在訴說一個娓娓動人的佛經故事。南邊牆上題
著一個字(writing)。
LONG
        );

        set("exits", ([
                "northwest" : __DIR__"zoulangc",
                "southwest" : __DIR__"eroom3",
        ]));
        set("item_desc",([
                "writing" : (: look_writing :),
        ]));
        set("no_clean_up", 0);
        setup();
}

string look_writing()
{
        return
        "\n"
"       風風風風風風風風風風風風風風風風風風風風\n"
"       風風風風風                  風風風風風風\n"
"       風風風風風  風風風風風風風  風風風風風風\n"
"       風風風風風  風  風風風  風  風風風風風風\n"
"       風風風風風  風風  風  風風  風風風風風風\n"
"       風風風風風  風風風  風風風  風風風風風風\n"
"       風風風風風  風風  風  風風  風風風風風風\n"
"       風風風風風  風  風風風  風  風風風風風風\n"
"       風風風風風  風風風風風風風  風風風風風風\n"
"       風風風風  風風風風風風風風風  風  風風風\n"
"       風風風  風風風風風風風風風風風  風風風風\n"
"       風風風風風風風風風風風風風風風風風風風風\n"
"       風風風風風風風風風風風風風風風風風風風風\n";

}

void init()
{
        add_action("do_study", "yanxi");
}


int do_study(string arg)
{
        object me = this_player();
        int cost=10;

        if ( !arg && ( arg != "qiang" ) && ( arg != "qiangbi" ) )
                return notify_fail("什麼？\n");

        if ( (int)me->query_skill("literate", 1) < 1)
                return notify_fail("你是個文盲，先學點文化(literate)吧。\n");

        if( query("jing", me)<30 )
                return notify_fail("你現在精神無法集中！\n");

        me->receive_damage("jing", 10);

        message_vision("$N正專心研讀牆壁上的古怪圖形。\n", me);

        if ( (int)me->query_skill("dodge", 1) < 100)
        {
            if( query("jing", me)>cost )
              {
                 me->improve_skill("dodge",(query("int", me)/4));
                 write("你對著牆壁琢磨了一回兒，似乎對基本輕功有點心得。\n");
                 set_temp("stone_learned", 1, me);
                 return 1;
                }
            else
               {
                cost=query("jing", me);
                write("你現在過于疲倦，無法專心下來研讀基本輕功。\n");
               } 
                            
        }

        if( !query_temp("stone_learned", me) )
        {
                write("你對著牆壁琢磨了一回兒，發現上面所說的太過淺顯，對你來說已毫無意義了。\n");
        }
        return 1;
}
