inherit ROOM;

void create()
{
        set("short","王盤山島邊");
        set("long", @LONG
王盤山在錢塘江口的東海之中，是個荒涼小島，山石嶙峋，向無人居。岸邊
兩人各舉大旗，揮舞示意，只見兩面大旗上均繡着一頭大鷹，雙翅伸展，甚是威
武。兩面大旗之間站着一個老者。王盤山是個小島，山石樹木無可觀之處。東南
角有個港灣，桅檣高聳，停泊着十來艘大船，想是巨鯨幫、海沙派一干人的座船。
LONG );
        set("exits",([
                "southdown":"/d/tulong/tulong/boat2",
                "east":"/d/tulong/tulong/gukou",
            ]));

        set("objects",([
                 "/d/tulong/tulong/npc/jiaozhong1": 2,
                 "/d/tulong/tulong/npc/jiaozhong2": 2,
                 "/d/tulong/tulong/npc/bai": 1,
            ]));

setup();
}

int valid_leave(object me,string dir)
{
        object ob;
        if( !query_temp("dao", me) && dir == "east" )
        return notify_fail("一進了會場就是生死之鬥，還是先砸了他們的船(break boat)以防不測。\n");

        if( query_temp("dao", me) && dir == "east" && ob=present("baiguishou") )
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
        return notify_fail("向東的路被白龜壽攔住了。\n"); }
        return 1;
}
