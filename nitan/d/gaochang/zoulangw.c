// Room: /d/gaochang/zoulangw.c
// Last Modified by Winder on Jul. 15 2000

inherit ROOM;
string look_writing();

void create()
{
        set("short", "走廊");
        set("long", @LONG
這裏是殿堂走廊。房頂一側支在南面的高牆上，另一側則與北邊殿
堂的屋頂相連。彩樑畫棟，抬眼望去，連頂棚也用彩漆繪滿了各種飛天
的圖形，每幅畫似乎都在訴説一個娓娓動人的佛經故事。南邊牆上題着
一個字(writing)。
LONG
        );

        set("exits", ([
                "southeast" : __DIR__"wroom3",
                "northeast" : __DIR__"zoulangc",
        ]));
        set("item_desc",([
                "writing"                :        (: look_writing :),
        ]));
        set("no_clean_up", 0);
        setup();
}

string look_writing()
{
        return
        "\n"
"              仙仙仙仙仙仙仙仙仙仙仙仙仙仙仙仙仙\n"
"              仙仙仙仙  仙仙仙仙仙    仙仙仙仙仙\n"
"              仙仙仙仙  仙仙仙仙仙  仙仙仙仙仙仙\n"
"              仙仙仙    仙仙仙仙仙  仙仙仙仙仙仙\n"
"              仙仙    仙仙仙仙仙仙  仙仙仙仙仙仙\n"
"              仙    仙  仙仙仙仙仙  仙仙仙仙仙仙\n"
"              仙仙仙仙  仙仙  仙仙  仙仙仙  仙仙\n"
"              仙仙仙仙  仙仙  仙仙  仙仙仙  仙仙\n"
"              仙仙仙仙  仙仙  仙仙  仙仙仙  仙仙\n"
"              仙仙仙仙  仙仙  仙仙  仙仙仙  仙仙\n"
"              仙仙仙仙  仙仙                仙仙\n"
"              仙仙仙    仙仙  仙仙仙仙仙仙  仙仙\n"
"              仙仙仙仙仙仙仙仙仙仙仙仙仙仙仙仙仙\n"
"              仙仙仙仙仙仙仙仙仙仙仙仙仙仙仙仙仙\n";
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

        if ( (int)me->query_skill("medicine", 1) < 100)
        {
              if( query("jing", me)>cost )
                {me->improve_skill("medicine",(query("int", me)/4));
                 write("你對着牆壁琢磨了一回兒，似乎對濟世之術有點心得。\n");
                 set_temp("stone_learned", 1, me);
                 return 1;
                }
                else
             {
                cost=query("jing", me);
                write("你現在過於疲倦，無法專心下來研讀濟世之術。\n");
             } 
                 
        }

        if( !query_temp("stone_learned", me) )
        {
                write("你對着牆壁琢磨了一回兒，發現上面所説的太過淺顯，對你來説已毫無意義了。\n");
        }
        return 1;
}
