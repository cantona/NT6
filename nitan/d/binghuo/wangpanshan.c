// Room: /binghuo/wangpanshan.c
// Date: Oct.28 1999 by Winder

inherit ROOM;

void create()
{
        set("short", "王盤山海灘");
        set("long", @LONG
只聽得島上號角之聲嗚嗚吹起，岸邊兩人各舉大旗，揮舞示意。
只見兩面大旗上均繡著一頭大鷹，雙翅伸展，甚是威武。兩面大旗之
間站著一個老者。只聽他朗聲說道：“玄武壇白龜壽恭迎貴客。”聲
音漫長，綿綿密密，雖不響亮，卻是氣韻醇厚。往南是一個山谷。北
邊有個港灣，桅檣高聳，停泊著十來艘大船，想是巨鯨幫、海沙派一
幹人的座船。
LONG );
        set("no_sleep_room",1);
        set("outdoors", "wangpan");
        set("exits", ([
                "north":"/d/tulong/tulong/boat2",
                "south" : __DIR__"wangpangu1",
                //"east"  : __DIR__"wangpanlin",
        ]));
        set("objects", ([
                 "/d/tulong/tulong/npc/jiaozhong1": 2,
                 "/d/tulong/tulong/npc/jiaozhong2": 2,
                 "/d/tulong/tulong/npc/bai": 1,
        ]));
        setup();
}

int valid_leave(object me,string dir)
{
        object ob;
        if( !query_temp("dao", me) && dir == "south" )
        return notify_fail("一進了會場就是生死之鬥，還是先砸了他們的船(break boat)以防不測。\n");

        if( query_temp("dao", me) && dir == "south" && ob=present("bai guishou") )
        {
                ob->ccommand("tnnd"+query("id", me));
                ob->ccommand("slap3"+query("id", me));
                message_vision("$N喝道：$n，去死吧！\n",ob,me);
                ob->kill_ob(me);
                ob=present("jiao zhong");
                if (objectp(ob)) ob->kill_ob(me);
                ob=present("jiao zhong 2");
                if (objectp(ob)) ob->kill_ob(me);
                ob=present("jiao zhong 3");
                if (objectp(ob)) ob->kill_ob(me);
                ob=present("jiao zhong 4");
                if (objectp(ob)) ob->kill_ob(me);
                return notify_fail("向南的路被白龜壽攔住了。\n");
        }
        return 1;
}

