//didao2.c                四川唐門─地道

inherit ROOM;

void create()
{
        set("short", "地道");
        set("long",
"這是一條地道。但是它卻並不是一條普通的地道，這裡極寬敞足可以\n"
"有幾十人在這裡舞龍戲獅。這裡亮如白晝，但是你卻無法找到這光亮的來\n"
"源，地道向前延伸不知通向何處。你的心中升起一股莫名的恐懼，還是離\n"
"開的好。\n"
);
        set("exits", ([
                        "northup" : __DIR__"didao1",
                        "southdown" : __DIR__"didao3",
        ]));
        set("area", "tangmen");
        setup();
}

void init()
{
        object me, killer;
        me = this_player();

        if ( wizardp(me) )
                return;

        if( (query("family/family_name", me) == "唐門世家") && query("family/master_id", me) == "tanglyz" )
                return;
        else
        {
                if ( userp(me) )
                {
                        message_vision("突然從石壁中傳來一聲大喝:“擅闖禁地者，死！！！\n", me);
                        message_vision("光滑的石壁上出現了一個石門，一名唐門死士躍了出來，向$N發動進攻！！！\n", me);
                        killer = new("/d/tangmen/npc/killer");
                        killer->move(environment(me));
                        killer->kill_ob(me);
                        me->fight_ob(killer);
                }
        }
        return;
}

int valid_leave(object me, string dir)
{
        me = this_player();

        if ( ((dir == "southdown")||(dir == "northup")) && objectp(present("killer", environment(me))) )
        {
                message_vision("死士一閃身將你攔了下來：想走？沒那麼容易！！！\n", me);
                return notify_fail("\n");
        }
        return ::valid_leave(me, dir);
}