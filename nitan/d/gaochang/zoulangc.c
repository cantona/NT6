// Room: /d/gaochang/zoulangc.c
// Last Modified by Winder on Jul. 15 2000

inherit ROOM;
string look_writing();

void create()
{
        set("short", "走廊");
        set("long", @LONG
這裡是殿堂走廊。房頂一側支在南面的高牆上，另一側則與北邊殿
堂的屋頂相連。彩樑畫棟，抬眼望去，連頂棚也用彩漆繪滿了各種
飛天的圖形，每幅畫似乎都在訴說一個娓娓動人的故事。
LONG
        );

        set("exits", ([
                "southeast" : __DIR__"zoulange",
                "southwest" : __DIR__"zoulangw",
                "north" : __DIR__"mishi",
        ]));
        set("objects", ([
                __DIR__"npc/wuaer": 1,
        ]));      
        set("item_desc",([
                "writing" : (: look_writing :),
        ]));
        setup();
}

int valid_leave(object me, string dir)
{
        if (dir == "north" && (me->query_kar()<25) && !wizardp(me))
                return notify_fail("\n突然之間，前面一個陰森森的聲音喝道：
「我在這裡已安安靜靜的住了一千年，誰也不敢來打擾我。那一個大膽過來，立刻就死！」
你只覺得心頭一寒，腳下直哆嗦，再也往前走不了一步。\n ");
        return 1;
}

string look_writing()
{
        return
        "\n"
"              文文文文文文文文文文文文文文文文文\n"
"              文文文文文文文    文文文文文文文文\n"
"              文文文文文文文文    文文文文文文文\n"
"              文文                          文文\n"
"              文文文文文  文文文文文  文文文文文\n"
"              文文文文文文  文文文  文文文文文文\n"
"              文文文文文文文  文  文文文文文文文\n"
"              文文文文文文文    文文文文文文文文\n"
"              文文文文文文  文文  文文文文文文文\n"
"              文文文文文  文文文文  文文文文文文\n"
"              文文文    文文文文文文    文文文文\n"
"              文    文文文文文文文文文    文文文\n"
"              文文文文文文文文文文文文文文文文文\n"
"              文文文文文文文文文文文文文文文文文\n";
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

        if ( (int)me->query_skill("literate", 1) < 100)
        {
             if( query("jing", me)>cost )
              {
                      me->improve_skill("literate",(query("int", me)/4));
                write("你對著牆壁琢磨了一回兒，似乎對讀書識字有點心得。\n");
                set_temp("stone_learned", 1, me);
               }
             else
               {
                cost=query("jing", me);
                write("你現在過于疲倦，無法專心下來研讀讀書識字。\n");
               }
        }

        if( !query_temp("stone_learned", me) )
        {
                write("你對著牆壁琢磨了一回兒，發現上面所說的太過淺顯，對你來說已毫無意義了。\n");
        }
        return 1;
}
